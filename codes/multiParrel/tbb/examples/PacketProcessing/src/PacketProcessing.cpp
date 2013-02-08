//
//  Copyright 2007 Intel Corporation. All Rights Reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "tbb/task_scheduler_init.h"
#include "tbb/pipeline.h"
#include "tbb/concurrent_hash_map.h"
#include "tbb/atomic.h"
#include "tbb/pipeline.h"

using namespace std;
// All packet attributes stored as std::strings (for simplicity)
typedef string nic_t, ip_t, port_t, app_t, protocol_t;

// Constants
static const string empty = "";
static const port_t FTPcmdPort  = "21";
static const port_t FTPdataPort = "20";

// Request contains FTP command 
static const protocol_t IPwithFTP = "IPwithFTP";

// Default filenames
#if defined(_WIN32)
    // Added to let the program run out of the box on visual studio
    static const char* in_file_name = "../../data/input.txt";
#elif defined (__APPLE_CC__)
    // Added to let the program run out of the box with XCODE
    static const char* in_file_name = "../../../../data/input.txt";
#else
    // Default
    static const char* in_file_name = "input.txt";
#endif
static const char* out_file_name  = "output.txt";

// Marker for packets stream
static const string end_of_map    = "PacketTrace";

// Hash compare type for tbb::concurrent_hash_map
class string_comparator {
public:
    static size_t hash( const string& x ) {
        size_t h = 0;
        for( const char* s = x.c_str(); *s; s++ )
            h = (h*17)^*s;
        return h;
    }
    static bool equal( const string& x, const string& y ) {
        return x==y;
    }
};

class address;
typedef string_comparator port_comparator, ip_addr_comparator;
// Hash map key is a port_t. This can be either router assigned port number or local device port number
// If key is a router port number, then the value is the local device assigned port;
// If key is an local device port number, then the value is a pair = (IP, router port number).
// The router port numbers are duplicated to avoid linear search at the NAT stage
typedef tbb::concurrent_hash_map<port_t, address*, port_comparator> mapped_ports_table;
// Network configuration table: IP->NIC
typedef tbb::concurrent_hash_map<ip_t, nic_t, ip_addr_comparator> network_table; 

// This is an interface class for value type of mapped_ports_table: PORT->ADDRESS*
// where ADDRESS points to either port_number (local device port number) or
// to ip_address (associated with the local device port number)
class address {
public:
    virtual bool get_ip_address (mapped_ports_table& /*in*/, ip_t& /*out*/) = 0;
    virtual bool get_port_number (port_t& /*out*/) = 0;
};

// If mapped_ports_table is port_number, then router mapped port number is known 
// (stored in the object), IP address can be found in the table via local device port
class port_number : public address {
public:
    port_t port;
    port_number (port_t& _port) : port(_port) {}
    bool get_ip_address (mapped_ports_table& mapped_ports, ip_t& addr) {
        mapped_ports_table::const_accessor a;
        if (mapped_ports.find (a, port)) {
            return a->second->get_ip_address (mapped_ports, addr);
        }
        return false;
    }
    bool get_port_number (port_t& p) { p = port; return true; }
};

// if mapped_ports_table is ip_address, 
// then the router mapped port and associated IP
// address are known (stored in the object)
class ip_address : public address {
public:
    ip_t ip;
    port_t router_port;
    ip_address (ip_t& _ip, port_t& _router_port) : ip(_ip), router_port(_router_port) {}
    bool get_ip_address (mapped_ports_table& mapped_ports /*in*/, ip_t& addr /*out*/) {
        addr = ip;
        return true;
    }
    bool get_port_number (port_t& p) { p = router_port; return true; }
};

// Packet attributes
typedef struct {
    nic_t packetNic;     // the NIC packet into and out of router
    ip_t packetDestIp;   // destination IP into and out of router
    ip_t packetSrcIp;    // source IP into and out of router
    port_t packetDestPort; // destinationPort paired w/destination IP
    port_t packetSrcPort;  // source Port paired w/source IP
    protocol_t packetProtocol;// packet protocol type
    port_t packetPayloadApp;  // any of the packet worth simulating
} packet_trace;

//Input packet
istream& operator>> (istream &s, packet_trace& a)
{
    // No input data verification for simplicity
    s >> a.packetNic >> a.packetDestIp >> a.packetSrcIp >>
    a.packetDestPort >> a.packetSrcPort >> a.packetProtocol; 
    if (a.packetProtocol == IPwithFTP)
        s >> a.packetPayloadApp;
    else
        a.packetPayloadApp = empty;
    return s;
}

// Output packet
ostream& operator<< (ostream &s, packet_trace& a) {
    return s << a.packetNic << " " << a.packetDestIp << " " <<
    a.packetSrcIp << " " << a.packetDestPort << " " <<
    a.packetSrcPort << " " << a.packetProtocol << " " <<
    a.packetPayloadApp << endl;
}

void get_args (int argc, char* argv[]) {
    // Parse command line
    switch (argc) {
        case 3:  out_file_name = argv[2];
        case 2:  in_file_name  = argv[1]; break;
        case 1:  break;
        default: cerr << "Usage:\trouter input-file output-file" 
                      << endl;
    };
    cerr << "Router: input file - " << in_file_name 
         << ", output file - " << out_file_name << endl;
}

bool init_home_router (ip_t& outgoing_ip, 
                       nic_t& outgoing_nic, 
                       network_table& network_config, 
                       ifstream& in_file)
{
    // Router outgoing IP and NIC: first line of input file
    if (!in_file.eof()) in_file >> outgoing_nic >> outgoing_ip;
    else return false;

    // Initialize network configuration map: IP => NIC
    string nic, ip;
    network_table::accessor a;
    while (!in_file.eof()) {
        in_file >> nic;
        if (nic == end_of_map) break;
        in_file >> ip;
        network_config.insert (a, ip);
        a->second = nic;
    }
    return true;
}

class get_next_packet : public tbb::filter {
    istream& in_file;
public:
    get_next_packet (ifstream& file) : in_file (file), 
                     filter (true) {}
    void* operator() (void*) {
        packet_trace* packet = new packet_trace ();
        in_file >> *packet;
        if (packet->packetNic == empty) {
            delete packet;
            return NULL;
        }
        return packet;
    }
};

class output_packet : public tbb::filter {
    ostream& out_file;
public:
    output_packet (ofstream& file) : out_file (file), filter (true) {}
    void* operator() (void* item) {
        packet_trace* packet = static_cast<packet_trace*> (item);
        out_file << *packet;
        delete packet;
        return NULL;
    }
};

class translator : public tbb::filter {
    const ip_t outgoing_ip;
    const nic_t outgoing_nic; 
    // port => address, where port={router mapped port | home device port}
    // and address = {home device port | pair(IP, router mapped port)}
    mapped_ports_table& mapped_ports; 
    static tbb::atomic<int> spare_port; // Previous spare port number

public:
    translator (ip_t& _outgoing_ip, nic_t& _outgoing_nic, 
                mapped_ports_table& _mapped_ports) : 
                outgoing_ip(_outgoing_ip), outgoing_nic(_outgoing_nic), 
                mapped_ports(_mapped_ports), filter (true /* is_serial*/) { spare_port = 2002; }
    void* operator() (void* item) {
        packet_trace* packet = static_cast<packet_trace*> (item);
        if (packet->packetNic == outgoing_nic) {
            // this is an external incoming packet
            ip_t app_ip;
            port_t app_port;
            if (get_port_mapping (packet->packetDestPort,
                                  app_ip, app_port)) {
                packet->packetDestIp   = app_ip;
                packet->packetDestPort = app_port;
            }
            else
                cerr << "Packet destination unknown" << endl;
        }
        else {
            // this is an internal outgoing packet
            port_t mappedPort;
            if (! get_router_port (mappedPort, packet->packetSrcIp, 
                                   packet->packetSrcPort)) {
                // Changed from the book to avoid taking a reference
                // to a temporary (allows compile on GCC)
                port_t newPort = get_new_port();
                mappedPort = add_new_mapping (packet->packetSrcIp, 
                                              packet->packetSrcPort,
                                              newPort);
            }
            packet->packetSrcPort = mappedPort;
        }
        
        return packet;
    }
    // IP, home device port <= router mapped port
    bool get_port_mapping (port_t& router_port /*in*/, 
                           ip_t& ip  /*out*/, port_t& app_port /*out*/)
    {
        mapped_ports_table::/*const_*/accessor a;
        if (mapped_ports.find (a, router_port))
        {
            address* addr = a->second;
            if (! addr->get_port_number (app_port)) return false;
            a.release();

            return addr->get_ip_address (mapped_ports, ip);
        }
        return false;
    }
    // Router mapped port <= home device assigned port, IP
    bool get_router_port (port_t& router_port /*out*/, 
                          ip_t& ip  /*in*/, port_t& app_port /*in*/)
    {
        mapped_ports_table::/*const_*/accessor a;
        if (mapped_ports.find (a, app_port))
        {
            address* addr = a->second;
            return addr->get_port_number (router_port);
        }
        return false;
    }

    // Allocates next spare port
    port_t get_new_port () {
        int port = ++spare_port; // this is an atomic operation
        stringstream s;
        s << port; 
        return s.str ();
    }

    port_t& add_new_mapping (ip_t& ip, port_t& port, port_t& new_port) {
        mapped_ports_table::accessor a; // acquires writer lock
        if (mapped_ports.insert (a, new_port)) {
            port_number* mapped_port = new port_number (port);
            a->second = mapped_port;
            if (mapped_ports.insert (a, port)) {
                ip_address*  addr = new ip_address (ip, new_port);
                a->second = addr;
            }
        }
        return new_port;
    }
};

tbb::atomic<int> translator::spare_port;

class gateway : public tbb::filter {
    const ip_t outgoing_ip;
    const nic_t outgoing_nic; 
    // port => address,
    // where port={router mapped port | home device port}
    // and
    // address = {home device port | pair(IP, router mapped port)}
    mapped_ports_table& mapped_ports; 
public:
    gateway    (ip_t& _outgoing_ip, nic_t& _outgoing_nic, 
            mapped_ports_table& _mapped_ports) : 
            outgoing_ip(_outgoing_ip), outgoing_nic(_outgoing_nic), 
            mapped_ports(_mapped_ports), 
                         filter (true /* is_serial*/) {  }

    void* operator() (void* item) {
        packet_trace* packet = static_cast<packet_trace*> (item);
        if (packet->packetDestPort == FTPcmdPort) {
            // outbound packet sends FTP command
            // packetPayloadApp contains data port - 
            // save it in ports table
            add_new_mapping (packet->packetSrcIp, 
                             packet->packetPayloadApp,
                             packet->packetSrcPort);
            packet->packetSrcIp = outgoing_ip;
            packet->packetPayloadApp = packet->packetSrcPort;
        }
        return packet;
    }
    port_t& add_new_mapping (ip_t& ip, port_t& port, 
                             port_t& new_port) {
        port_number* mapped_port = new port_number (port);
        ip_address*  addr = new ip_address (ip, new_port);
        mapped_ports_table::accessor a; // acquires writer lock
        if (! mapped_ports.find (a, new_port))
            mapped_ports.insert (a, new_port);
        else 
            delete a->second;
        // The port has already been mapped at the NAT stage
        // Re-map the port to the one specified by packet->PayloadApp
        a->second = mapped_port;
        mapped_ports.insert (a, port);
        a->second = addr;
        return new_port;
    }
};

class forwarding : public tbb::filter {
    const ip_t outgoing_ip;
    const nic_t outgoing_nic; 
    network_table& network_config;
public:
    forwarding (ip_t& _outgoing_ip, nic_t& _outgoing_nic, 
                network_table& _network_config) : 
            outgoing_ip(_outgoing_ip), outgoing_nic(_outgoing_nic), 
            network_config(_network_config), 
                           filter (false /* is_serial*/) {  }

    void* operator() (void* item) {
        packet_trace* packet = static_cast<packet_trace*> (item);
        if (packet->packetNic == outgoing_nic) {
            // packet is inbound, so translate it to the target Mac
            nic_t nextNic;
            if (find_next_hop (packet->packetDestIp, nextNic))
                packet->packetNic = nextNic;
            else
                cerr << "No next hop found" << endl;
        }
        else {
            // packet is outbound, only one place it can go
            packet->packetSrcIp = outgoing_ip;
            packet->packetNic = outgoing_nic;
        }
        return packet;
    }

    bool find_next_hop (ip_t& ip, nic_t& nic) {
        network_table::const_accessor a; // acquires reader lock
        if (network_config.find (a, ip)) {
            nic = a->second;
            return true;
        }
        return false;
    }
};

int main (int argc, char** argv)
{
    mapped_ports_table mapped_ports; // Router assigned ports
    network_table network_config; // Network configuration: IP => NIC

    ip_t router_ip;        // Router outgoing IP
    nic_t router_nic;      // Router outgoing NIC
    const size_t number_of_live_items = 10; // Pipeline's throughput

    // Parse command-line arguments
    get_args (argc, argv);

    // Open file streams
    ifstream in_file (in_file_name);
    if (!in_file) {
        cerr << "Cannot open input file " << in_file_name << endl;
        exit (1);
    }
    ofstream out_file (out_file_name);
    if (!out_file) {
        cerr << "Cannot open output file " << out_file_name << endl;
        exit (1);
    }

    // Initialize home router: build network configuration table
    // and read outgoing IP and NIC from input file
    if (! init_home_router (router_ip, router_nic, 
                            network_config, in_file)) exit (1);
    
    // Create home router instance (Line from book unused)
    //home_router router (port_map (port_table), 
    //                    network_map (net_map), 
    //                    router_nic, router_ip);

    // Initialize Threading Building Blocks
    tbb::task_scheduler_init tbb_init;

    // Create Threading Building Blocks pipeline
    tbb::pipeline pipeline;

    // Stage 0: Input Packet
    get_next_packet receive_packet (in_file);
    pipeline.add_filter (receive_packet);

    // Stage 1: Network Address Translator
    translator network_address_translator (router_ip, router_nic, 
                                           mapped_ports);
    pipeline.add_filter (network_address_translator);

    // Stage 2: Application Level Gateway 
    gateway application_level_gateway (router_ip, router_nic,
                                       mapped_ports);
    pipeline.add_filter (application_level_gateway);

    // Stage 3: Packet Forwarding Stage
    forwarding packet_forwarding (router_ip, router_nic, 
                                  network_config);
    pipeline.add_filter (packet_forwarding);

    // Stage 4: Output Packet
    output_packet send_packet (out_file);
    pipeline.add_filter (send_packet);

    cerr << "Starting packets processing..." << endl;
    pipeline.run (number_of_live_items); 
    pipeline.clear ();
    cerr << "All packets are processed. Exiting..." << endl;

    return 0;
}
