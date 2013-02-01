/*
g++ -fopenmp mSection.cc
*/

#include <omp.h>
#include <stdio.h>
int main (int argc, char *argv[]) {
int id, nthreads;

omp_set_num_threads(4);
//for just 2 thread be selected to execute two tasks in sections
//other 2 threads do nothing.
#pragma omp parallel private(id)
{

    #pragma omp sections
    {
        #pragma omp section
            {printf("thread %d do task 1 \n", omp_get_thread_num());}
        #pragma omp section
            {printf("thread %d do task 2 \n", omp_get_thread_num());}
    
    }

    #pragma omp barrier    
}

return 0;
}

