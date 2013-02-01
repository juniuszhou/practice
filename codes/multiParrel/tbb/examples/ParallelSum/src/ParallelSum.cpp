//
//  Copyright 2007 Intel Corporation. All Rights Reserved.
//

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include "tbb/parallel_reduce.h"
#include "tbb/blocked_range.h"
#include "tbb/task_scheduler_init.h"
#include "tbb/tick_count.h"

using namespace tbb;

// Uncomment the line below to enable the auto_partitioner
//#define AUTO_GRAIN

struct Sum {
    float value;
    Sum() : value(0) {}
    Sum( Sum& s, split ) {value = 0;}
    void operator()( const blocked_range<float*>& range ) {
        float temp = value;
        for( float* a=range.begin(); a!=range.end(); ++a ) {
            temp += *a;
        }
        value = temp;
    }
    void join( Sum& rhs ) {value += rhs.value;}
};

float ParallelSum( float array[], size_t n ) {
    Sum total;
#ifndef AUTO_GRAIN
    parallel_reduce( blocked_range<float*>( array, array+n, 1000 ), 
                     total );
#else /* AUTO_GRAIN */
    parallel_reduce( blocked_range<float*>( array, array+n ), 
                     total, auto_partitioner() );
#endif /* AUTO_GRAIN */
    return total.value;
}

//! Problem size
const int N = 1000000;

//! Number of threads to use.
static int MaxThreads = 4;

//! If true, print out bits of the array
static bool VerboseFlag = false;

//! Parse the command line.
static void ParseCommandLine( int argc, char* argv[] ) {
    int i = 1;
    if( i<argc && strcmp( argv[i], "verbose" )==0 ) {
        VerboseFlag = true;
        ++i;
    }
    if( i<argc && !isdigit(argv[i][0]) ) { 
        // Command line is garbled.
        fprintf(stderr,
                "Usage: %s ['verbose'] [max_threads]\n",
                argv[0]);
        fprintf(stderr,
                " where max_threads is positive integer, signifying the \n"
                " maximum number of threads to try [%d]", MaxThreads);
        exit(1);
    }
    if( i<argc )
        MaxThreads = strtol(argv[i++],0,0);
}

int main( int argc, char* argv[] ) {
    srand(2);
    ParseCommandLine( argc, argv );

    static float input[N];

    // Initialize the input
    for ( size_t i = 0; i < N; ++i ) {
      input[i] = (float)(rand() % 10);
    }

    if( VerboseFlag ) {
      printf(" Input: ");
      for ( size_t i = 0; i < 7; ++i ) {
        printf("%7.2f ", input[i]);
      }
      printf("...\n");
    }

    // Try different numbers of threads
    for( int p=1; p<=MaxThreads; ++p ) {

        task_scheduler_init init(p);

        tick_count t0 = tick_count::now();
        float output = ParallelSum(input, N);
        tick_count t1 = tick_count::now();
        
        if( VerboseFlag ) {
          printf("Output: %7.2f\n", output);
        }
        printf("%2d threads: %.3f msec\n", p, (t1-t0).seconds()*1000);
    }
	return 0;

}

