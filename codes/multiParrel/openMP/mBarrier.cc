/*
g++ -fopenmp mBarrier.cc
*/

#include <omp.h>
#include <stdio.h>
#include <iostream>
using namespace std;

int main (int argc, char *argv[]) {
int id=0, nthreads;
int a=0;
omp_set_num_threads(4);
//for just usable if number of loop is fixed
#pragma omp parallel shared (a) private(id)
{

    #pragma omp for
    //#pragma omp for nowait
    for (int i=0;i<32;i++)
        {a += i;
        //get the thread number
        //id = omp_get_thread_num();
        printf("I am %d in thread %d\n", id, omp_get_thread_num());
        }

    #pragma omp barrier
    cout << a << endl;
}
//cout << a << endl;

return 0;
}

