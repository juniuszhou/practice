/*
g++ -fopenmp mSingle.cc
*/

#include <omp.h>
#include <stdio.h>
int main (int argc, char *argv[]) {
int id, nthreads;

omp_set_num_threads(4);
//single thread exec 
#pragma omp parallel private(id)
{
    #pragma omp single
    {
        //just need one thread tell you we are into 
        printf("start to parallel, %d\n", omp_get_thread_num());
    }
    //there is barrier here automatically
    
    #pragma omp for
    for (int i=0;i<32;i++)
        //get the thread number
        //id = omp_get_thread_num();
     printf("I am %d in thread %d\n", i, omp_get_thread_num());

    #pragma omp barrier    
}

return 0;
}

