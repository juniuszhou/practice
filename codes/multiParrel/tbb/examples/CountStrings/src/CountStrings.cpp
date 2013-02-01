//
//  Copyright 2007 Intel Corporation. All Rights Reserved.
//
#include "stdio.h"
#include "stdlib.h"

#include "tbb/concurrent_hash_map.h"
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"
#include "tbb/tick_count.h"
#include "tbb/task_scheduler_init.h"
#include <string>
#include <cctype>

using namespace tbb;
using namespace std;

//! Set to true to counts.
static bool Verbose = false;
//! Working threads count
static int NThread = 1;
//! Problem size
const size_t N = 1000000;

//! Structure that defines hashing and comparison operations for user's type.
struct MyHashCompare {
    static size_t hash( const string& x ) {
        size_t h = 0;
        for( const char* s = x.c_str(); *s; s++ )
            h = (h*17) ^ *s; 
        return h;
    }
    //! True if strings are equal
    static bool equal( const string& x, const string& y ) {
        return x==y;
    }
};

//! A concurrent hash table that maps strings to ints.
typedef concurrent_hash_map<string,int,MyHashCompare> StringTable;

//! Function object for counting occurrences of strings.
struct Tally {
    StringTable& table;
    Tally( StringTable& table_ ) : table(table_) {}
    void operator()( const blocked_range<string*> range ) const {
        for( string* p=range.begin(); p!=range.end(); ++p ) {
            StringTable::accessor a;
            table.insert( a, *p );
            a->second += 1;
        }
    }
};

static string Data[N];

static void CountOccurrences() {
    StringTable table;

    tick_count t0 = tick_count::now(); 
    parallel_for( blocked_range<string*>( Data, Data+N, 1000 ), Tally(table) );
    tick_count t1 = tick_count::now(); 

    int n = 0;
    for( StringTable::iterator i=table.begin(); i!=table.end(); ++i ) {
        if( Verbose )
            printf("%s %d\n",i->first.c_str(),i->second);
        n+=i->second;
    }
    printf("threads = %d  total = %d  time = %g\n", NThread, n, (t1-t0).seconds());
}

static const string Adjective[] =
    { "sour", "sweet", "bitter", "salty", "big", "small" };

// Removed extra brace that is present in the book
static const string Noun[] =
    { "apple", "banana", "cherry", "date", "eggplant",
      "fig", "grape", "honeydew", "icao", "jujube" };

static void CreateData() {
    size_t n_adjective = sizeof(Adjective)/sizeof(Adjective[0]);
    size_t n_noun = sizeof(Noun)/sizeof(Noun[0]);
    for( int i=0; i<N; ++i ) {
        Data[i] = Adjective[12 %n_adjective];
        Data[i] += " ";
        Data[i] += Noun[14 %n_noun];
    }
}

static void ParseCommandLine( int argc, char* argv[] ) {
    int i = 1;
    if( i<argc && strcmp( argv[i], "verbose" )==0 ) {
        Verbose = true;
        ++i;
    }
    if( i<argc && !isdigit(argv[i][0]) ) {
        fprintf(stderr,"Usage: %s [verbose] number-of-threads\n",argv[0]);
        exit(1);
    }
    if( i<argc ) NThread = strtol(argv[i++],0,0);
} 

int main( int argc, char* argv[] ) {
    srand(2);
    ParseCommandLine( argc, argv );
    task_scheduler_init init(NThread);
    CreateData();
    CountOccurrences();
}
