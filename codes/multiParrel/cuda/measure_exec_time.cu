#include "stdafx.h"
#include <time.h>
#include <fstream>
#include "../common/book.h"
#define DIM 32 * 1024

int main( void ) {    
    // capture the start time
    cudaEvent_t     start, stop;
    HANDLE_ERROR( cudaEventCreate( &start ) );
    HANDLE_ERROR( cudaEventCreate( &stop ) );
    HANDLE_ERROR( cudaEventRecord( start, 0 ) );
	// get stop time, and display the timing results
    HANDLE_ERROR( cudaEventRecord( stop, 0 ) );

    //cudaEventSynchronize is important here, then CPU will block until 
    //cuda stream is complete.
    HANDLE_ERROR( cudaEventSynchronize( stop ) );
    float   elapsedTime;
    HANDLE_ERROR( cudaEventElapsedTime( &elapsedTime,
                                        start, stop ) );
    printf( "Time to generate:  %3.1f ms\n", elapsedTime );

    HANDLE_ERROR( cudaEventDestroy( start ) );
    HANDLE_ERROR( cudaEventDestroy( stop ) );
	return 0;
}

