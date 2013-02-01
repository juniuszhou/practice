//
//  Copyright 2007 Intel Corporation. All Rights Reserved.
//

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctype.h>
#include "tbb/task_scheduler_init.h"
#include "tbb/tick_count.h"

#include "tbb/parallel_for.h"
#include "tbb/blocked_range2d.h"

using namespace tbb;
using namespace std;
//! Working threads count for parallel version
static int NThread = 2;

const size_t L = 150;
const size_t M = 225;
const size_t N = 300;

void SerialMatrixMultiply( float c[M][N], float a[M][L], float b[L][N] ) {
    for( size_t i=0; i<M; ++i ) {
        for( size_t j=0; j<N; ++j ) {
            float sum = 0;
            for( size_t k=0; k<L; ++k )
                sum += a[i][k]*b[k][j];
            c[i][j] = sum;
        }
    }
}

class MatrixMultiplyBody2D {
    float (*my_a)[L];
    float (*my_b)[N];
    float (*my_c)[N];
public:
    void operator()( const blocked_range2d<size_t>& r ) const {
        float (*a)[L] = my_a; // a,b,c used in example to emphasize
        float (*b)[N] = my_b; // commonality with serial code
        float (*c)[N] = my_c;
        for( size_t i=r.rows().begin(); i!=r.rows().end(); ++i ){
            for( size_t j=r.cols().begin(); j!=r.cols().end(); ++j ) {
                float sum = 0;
                for( size_t k=0; k<L; ++k )
                    sum += a[i][k]*b[k][j];
                c[i][j] = sum;
            }
        }
    }
    MatrixMultiplyBody2D( float c[M][N], float a[M][L], float b[L][N] ) :
        my_a(a), my_b(b), my_c(c)
    {}
};

void ParallelMatrixMultiply(float c[M][N], float a[M][L], float b[L][N]){
    parallel_for( blocked_range2d<size_t>(0, M, 16, 0, N, 32),     
                  MatrixMultiplyBody2D(c,a,b) );
}

static void CreateData( float a[M][L], float b[L][N] ) {
    for( size_t i=0; i<M; ++i ) {
        for( size_t j=0; j<L; ++j ) {
            a[i][j] = (rand()%1000)/100.0f;
        }
    }
    for( size_t i=0; i<L; ++i ) {
        for( size_t j=0; j<N; ++j ) {
            b[i][j] = (rand()%1000)/100.0f;
        }
    }
}

static bool VerifyResult( float c1[M][N], float c2[M][N] ) {
    for( size_t i=0; i<M; ++i ) {
        for( size_t j=0; j<N; ++j ) {
            if ( abs(c1[i][j] - c2[i][j]) > 0.0001f ) {
                return false;
            }
        }
    }
    return true;
}


static void ParseCommandLine( int argc, char* argv[] ) {
    int i = 1;
    if( i<argc && !isdigit(argv[i][0]) ) {
        fprintf(stderr,"Usage: %s number-of-threads\n",argv[0]);
        exit(1);
    }
    if( i<argc ) NThread = strtol(argv[i++],0,0);
} 

int main( int argc, char* argv[] ) {
    srand(2);
    ParseCommandLine( argc, argv );
    task_scheduler_init init(NThread);
    float a[M][L];
    float b[L][N];
    CreateData(a, b);

    float c1[M][N];
    tick_count t0 = tick_count::now();
    SerialMatrixMultiply(c1, a, b);
    tick_count t1 = tick_count::now();
    printf("Serial code:               %.4f sec\n", (t1-t0).seconds());

    float c2[M][N];
    t0 = tick_count::now();
    ParallelMatrixMultiply(c2, a, b);
    t1 = tick_count::now();
    printf("Parallel code (%d threads): %.4f sec\n",
		   NThread, (t1-t0).seconds());

    if ( VerifyResult(c1, c2) ) {
        printf("Results match!\n");
        return 0;
    } else {
        printf("Results don't match!\n");
        return 2;
    }
    
}
