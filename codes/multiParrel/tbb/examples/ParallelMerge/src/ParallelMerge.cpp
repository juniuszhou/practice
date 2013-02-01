//
//  Copyright 2007 Intel Corporation. All Rights Reserved.
//

#ifdef _WIN32
// Necessary to keep std::min from being redefined
#define NOMINMAX
#endif

#include "tbb/parallel_for.h"
#include "tbb/task_scheduler_init.h"
#include "tbb/tick_count.h"
#include <algorithm>
#include <cstdio>

using namespace tbb;

template<typename Iterator>
struct ParallelMergeRange {
    static size_t grainsize;
    Iterator begin1, end1; // [begin1,end1) is 1st sequence to be merged
    Iterator begin2, end2; // [begin2,end2) is 2nd sequence to be merge
    Iterator out;               // where to put merged sequence    
    bool empty()   const {return (end1-begin1)+(end2-begin2)==0;}
    bool is_divisible() const {
        return std::min( end1-begin1, end2-begin2 ) > grainsize;
    }
    ParallelMergeRange( ParallelMergeRange& r, split ) {
        if( r.end1-r.begin1 < r.end2-r.begin2 ) {
            std::swap(r.begin1,r.begin2);
            std::swap(r.end1,r.end2);
        }
        Iterator m1 = r.begin1 + (r.end1-r.begin1)/2;
        Iterator m2 = std::lower_bound( r.begin2, r.end2, *m1 );
        begin1 = m1;
        begin2 = m2;
        end1 = r.end1;
        end2 = r.end2;
        out = r.out + (m1-r.begin1) + (m2-r.begin2);
        r.end1 = m1;
        r.end2 = m2;
    }
    ParallelMergeRange( Iterator begin1_, Iterator end1_, 
                        Iterator begin2_, Iterator end2_, 
                        Iterator out_ ) :
        begin1(begin1_), end1(end1_), 
        begin2(begin2_), end2(end2_), out(out_)
    {}
};

template<typename Iterator>
size_t ParallelMergeRange<Iterator>::grainsize = 1000;

template<typename Iterator>
struct ParallelMergeBody {
    void operator()( ParallelMergeRange<Iterator>& r ) const {
        std::merge( r.begin1, r.end1, r.begin2, r.end2, r.out );
    }
};

template<typename Iterator>
void ParallelMerge( Iterator begin1, Iterator end1, Iterator begin2, Iterator end2, Iterator out ) {
    parallel_for(     
        ParallelMergeRange<Iterator>(begin1,end1,begin2,end2,out),
        ParallelMergeBody<Iterator>() 
    );
}

//! Problem size
const int N = 500000;

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

    // Declared static to prevent overflowing the stack
    static float input1[N];
    static float input2[N];

    input1[0] = 0;
    input2[0] = 0;
    // Initialize the inputs
    for ( size_t i = 1; i < N; ++i ) {
      input1[i] = input1[i-1] + (rand() % 10);
      input2[i] = input2[i-1] + (rand() % 10);
    }

    if( VerboseFlag ) {
      printf("Input1: ");
      for ( size_t i = 0; i < 7; ++i ) {
        printf("%7.2f ", input1[i]);
      }
      printf("...\n");

      printf("Input2: ");
      for ( size_t i = 0; i < 7; ++i ) {
        printf("%7.2f ", input2[i]);
      }
      printf("...\n");
    }

    // Try different numbers of threads
    for( int p=1; p<=MaxThreads; ++p ) {

        task_scheduler_init init(p);

        // Declared static to prevent overflowing the stack
        static float output[2*N];
        tick_count t0 = tick_count::now();
        ParallelMerge(input1, input1+N,
                      input2, input2+N,
                      output);
        tick_count t1 = tick_count::now();
        
        if( VerboseFlag ) {
          printf("output: ");
          for ( size_t i = 0; i < 7; ++i ) {
            printf("%7.2f ", output[i]);
          }
          printf("...\n");
        }
        printf("%2d threads: %.3f msec\n", p, (t1-t0).seconds()*1000);
    }
	return 0;

}

