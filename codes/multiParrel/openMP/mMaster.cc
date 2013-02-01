/*
g++ -fopenmp mMaster.cc
*/

#include <omp.h>
#include <stdio.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
int id, nthreads;

omp_set_num_threads(4);
//for just usable if number of loop is fixed
#pragma omp parallel private(id)
{
    //thread 0 is master thread, just master thread exec this section
    #pragma omp master
    {
        sleep(1);
        printf("I am master in thread %d\n", omp_get_thread_num());
    }

    #pragma omp for
    for (int i=0;i<32;i++)
        //get the thread number
        //id = omp_get_thread_num();
     printf("I am %d in thread %d\n", i, omp_get_thread_num());

    #pragma omp barrier    
}

return 0;
}

