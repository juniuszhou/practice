//
//  Copyright 2007 Intel Corporation. All Rights Reserved.
//

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"
#include "tbb/task_scheduler_init.h"
#include "tbb/tick_count.h"

using namespace tbb;

class Average {
public:
    float* input;
    float* output;
    void operator()( const blocked_range<int>& range ) const {
        for( int i=range.begin(); i!=range.end(); ++i )
            output[i] = (input[i-1]+input[i]+input[i+1])*(1/3.0f);
    }
};

// Note: The input must be padded such that input[-1] and input[n] 
// can be used to calculate the first and last output values.
void ParallelAverage( float* output, float* input, size_t n ) {
    Average avg;
    avg.input = input;
    avg.output = output;
    parallel_for( blocked_range<int>( 0, n, 1000 ), avg );
}

//! Problem size
const int N = 100000;

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

    // Save extra space for the padding
    float raw_input[N+2];
    raw_input[0] = 0;
    raw_input[N+1] = 0;
    float* padded_input = raw_input+1;

    // Initialize the input
    for ( size_t i = 0; i < N; ++i ) {
      padded_input[i] = (float)(rand() % 1000);
    }

    if( VerboseFlag ) {
      printf(" Input: ");
      for ( size_t i = 0; i < 7; ++i ) {
        printf("%7.2f ", padded_input[i]);
      }
      printf("...\n");
    }

    // Try different numbers of threads
    for( int p=1; p<=MaxThreads; ++p ) {

        task_scheduler_init init(p);

        float output[N];
        tick_count t0 = tick_count::now();
        ParallelAverage(output, padded_input, N);
        tick_count t1 = tick_count::now();
        
        if( VerboseFlag ) {
          printf("Output: ");
          for ( size_t i = 0; i < 7; ++i ) {
            printf("%7.2f ", output[i]);
          }
          printf("...\n");
        }
        printf("%2d threads: %.3f msec\n", p, (t1-t0).seconds()*1000);
    }
	return 0;

}

