//
//  Copyright 2007 Intel Corporation. All Rights Reserved.
//

// The technique is similar to one used in tbb/parallel_while.h 

#include "tbb/task.h"
#include "tbb/task_scheduler_init.h"
#include <stdio.h>
#include <stdlib.h>

//! Some busywork
void TwiddleThumbs( const char * message, int n ) {
    for( int i=0; i<n; ++i ) {
         printf(" %s: i=%d\n",message,i);
         static volatile int x;
         for( int j=0; j<20000000; ++j ) 
            ++x;
    }
}

//! SideShow task
class SideShow: public tbb::task {
    tbb::task* execute() {
        TwiddleThumbs("Sideshow task",4);
        return NULL;
    }
};

//! Start up a SideShow task.
//! Return pointer to dummy task that acts as parent of the SideShow.
tbb::empty_task* StartSideShow() {
    tbb::empty_task* parent = new( tbb::task::allocate_root() ) tbb::empty_task;
    // 2 = 1 for SideShow and C
    parent->set_ref_count(2);
    SideShow* s = new( parent->allocate_child() ) SideShow;
    parent->spawn(*s);
    return parent;
}

//! Wait for SideShow task.  Argument is dummy parent of the SideShow.
void WaitForSideShow( tbb::empty_task* parent ) {
    parent->wait_for_all();
    // parent not actually run, so we need to destroy it explicitly.
    // (If you forget this line, the debug version of tbb reports a task leak.)
    parent->destroy(*parent);
}

//! Optional command-line argument is number of threads to use.  Default is 2.
int main( int argc, char* argv[] ) {
    tbb::task_scheduler_init init( argc>1 ? strtol(argv[1],0,0) : 2 );
    // Loop over n tests various cases where SideShow/Main finish twiddling first.
    for( int n=3; n<=5; ++n ) {
        printf("\ntest with n=%d\n",n);

        // Start up a Sideshow task
        tbb::empty_task* e = StartSideShow();
    
        // Do some useful work
        TwiddleThumbs("master",n);
        
        // Wait for Sideshow task to complete
        WaitForSideShow(e);
    }
    return 0;
}
