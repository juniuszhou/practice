/*
g++ -O2 -DNDEBUG m_aligned.cc -ltbb -lrt -ltbbmalloc 
*/

#include "tbb/concurrent_queue.h"
#include <iostream>
using namespace std;
using namespace tbb;


#include <cstdio>
#include "tbb/cache_aligned_allocator.h"


int main( int argc, char* argv[] ) {
	cache_aligned_allocator<int> alloc;
    int* a = alloc.allocate(10);
	cout << (int)a << endl;

	alloc.deallocate(a,10);
	
}

