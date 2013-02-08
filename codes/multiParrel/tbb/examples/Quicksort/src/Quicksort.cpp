//
//  Copyright 2007 Intel Corporation. All Rights Reserved.
//

#include <algorithm>
#include <cstdio>
#include <functional>
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"
#include "tbb/task_scheduler_init.h"
#include "tbb/tick_count.h"

using namespace tbb;

template<typename RandomAccessIterator, typename Compare>
struct quick_sort_range {
   static const size_t grainsize = 500;
   const Compare &comp;
   RandomAccessIterator begin;
   size_t size;

   quick_sort_range( RandomAccessIterator begin_, 
                     size_t size_, 
                     const Compare &comp_ ) :
      comp(comp_), begin(begin_), size(size_) {}

   bool empty() const {return size==0;}
   // Change from the book to make is_divisible() const 
   bool is_divisible() const {return size>=grainsize;}

   quick_sort_range( quick_sort_range& range, split ) : comp(range.comp) {
      RandomAccessIterator array = range.begin;
      RandomAccessIterator key0 = range.begin; 
      size_t m = range.size/2u;
      std::swap ( array[0], array[m] );

      size_t i=0;
      size_t j=range.size;
      // Partition interval [i+1,j-1] with key *key0.
      for(;;) {
       __TBB_ASSERT( i<j, NULL );
       // Loop must terminate since array[l]==*key0.
       do {
           --j;
           __TBB_ASSERT( i<=j, "bad ordering relation?" );
       } while( comp( *key0, array[j] ));
       do {
           __TBB_ASSERT( i<=j, NULL );
           if( i==j ) goto partition;
           ++i;
       } while( comp( array[i],*key0 ));
       if( i==j ) goto partition;
       std::swap( array[i], array[j] );
      }
partition:
      // Put the partition key where it belongs
      std::swap( array[j], *key0 );
      // array[l..j) is less or equal to key.
      // array(j..r) is greater than or equal to key.
      // array[j] is equal to key
      i=j+1;
      begin = array+i;
      size = range.size-i;
      range.size = j;
   }
};


template<typename RandomAccessIterator, typename Compare>
struct quick_sort_body {
   void operator()( const quick_sort_range<RandomAccessIterator,
                    Compare>& range ) const {
      //SerialQuickSort( range.begin, range.size, range.comp );
      std::sort( range.begin, range.begin + range.size, range.comp );
   }
};

template<typename RandomAccessIterator, typename Compare>
void parallel_quick_sort( RandomAccessIterator begin,
                          RandomAccessIterator end,
                          const Compare& comp ) {
   parallel_for( quick_sort_range<RandomAccessIterator,Compare>
                 (begin, end-begin, comp ),
                 quick_sort_body<RandomAccessIterator,Compare>() );
}

template<typename RandomAccessIterator, typename Compare>
void parallel_sort( RandomAccessIterator begin,
                    RandomAccessIterator end, const Compare& comp) { 
   const int min_parallel_size = 500; 
   if( end > begin ) {
      if (end - begin < min_parallel_size) { 
       std::sort(begin, end, comp);
      } else {
       // Removed extraneous "internal::" from book
       parallel_quick_sort(begin, end, comp);
      }
   }
}

template<typename RandomAccessIterator>
inline void parallel_sort( RandomAccessIterator begin,
                           RandomAccessIterator end ) { 
   parallel_sort( begin, end, std::less< typename std::iterator_traits<RandomAccessIterator>::value_type >() );
}

template<typename T>
inline void parallel_sort( T * begin, T * end ) {
   parallel_sort( begin, end, std::less< T >() );
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

    // Static to avoid overflowing the stack
    static float input[N];

    // Initialize the input
    for ( size_t i = 0; i < N; ++i ) {
      input[i] = (float)(rand());
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

        static float output[N];
        // Copy the input to the output (the function sorts in place)
        for ( size_t i = 0; i < N; ++i ) {
          output[i] = input[i];
        }

        tick_count t0 = tick_count::now();
        parallel_sort(output, output + N);
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

