//
//  Copyright 2007 Intel Corporation. All Rights Reserved.
//

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

// Time delays
int m1, m2, t1, t2;

class Combine1: public tbb::task {
public:
    tbb::task* execute() {
        TwiddleThumbs("Combine1",m1);
        return NULL;
    }
};

class Combine2: public tbb::task {
public:
    tbb::task* execute() {
        TwiddleThumbs("Combine2",m2);
        return NULL;
    }
};

class Filterb: public tbb::task {
public:
    tbb::empty_task* dummy;
    tbb::task* execute() {
        TwiddleThumbs("Filterb",4);
        // When all the work is done -
        //  start dummy, which does nothing and signals the
        //  second parent to continue.
        dummy->spawn(*dummy);
        return NULL;
    }
};

class Transform2: public tbb::task {
public:
    tbb::task* execute() {
        TwiddleThumbs("Transform2",t1);
        return NULL;
    }
};

class Warp1: public tbb::task {
public:
    tbb::task* execute() {
        TwiddleThumbs("Warp1",t2);
        return NULL;
    }
};

//! Optional command-line argument is number of threads to use.  Default is 3.
int main( int argc, char* argv[] ) {
    tbb::task_scheduler_init init( argc>1 ? strtol(argv[1],0,0) : 3 );
    // Test various time delays
    for( m1=3; m1<=5; ++m1 ) {
        for( m2=3; m2<=5; ++m2 ) {
            for( t1=3; t1<=5; ++t1 ) {
                for( t2=3; t2<=5; ++t2 ) {
                    printf("\nm1=%d m2=%d t1=%d t2=%d\n",m1,m2,t1,t2);
                    tbb::empty_task* root = 
                        new( tbb::task::allocate_root() ) tbb::empty_task;
                    root->set_ref_count(3);
                    Combine1* combine1 = new( root->allocate_child() ) Combine1;
                    combine1->set_ref_count(2);
                    Combine2* combine2 = new( root->allocate_child() ) Combine2;
                    combine2->set_ref_count(2);
                    Filterb* filterb = new( combine1->allocate_child() ) Filterb;
                    filterb->dummy = 
                        new( combine2->allocate_child() ) tbb::empty_task;
                    filterb->spawn( *filterb );
                    Transform2* transform2 = 
                        new( combine1->allocate_child() ) Transform2;
                    combine1->spawn( *transform2 );
                    Warp1* warp1 = 
                        new( combine2->allocate_child() ) Warp1;
                    combine2->spawn( *warp1 );
                    root->wait_for_all();
                    root->destroy(*root);
                }
            }   
        }
    }
}
