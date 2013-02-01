/*
g++ -O2 -DNDEBUG mutex.cc -ltbb -lrt
*/

#include "tbb/mutex.h"
#include "tbb/spin_mutex.h"

#include <iostream>
using namespace std;
using namespace tbb;

spin_mutex m1;

void addNode()
{
    spin_mutex::scoped_lock lock(m1);
    //access to critical here
    return;
    //we can see we don't need call unlock here because the lock's
    //destructor will be called and then unlock. it is exception safe
    //also compare with c interface. 

    //so when disign, remember put the critical region just before the
    //expiration of lock.
}

int main( int argc, char* argv[] ) {
	
    m1.lock();
    m1.unlock();

    addNode();
    
    return 1;
	
}

