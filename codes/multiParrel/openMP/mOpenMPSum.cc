/*
g++ -fopenmp mOpenMPSum.cc
*/

#include <omp.h>
#include <stdio.h>
int main (int argc, char *argv[]) 
{
    int sum = 0;
    int *x;
    int n;
    //omp_set_num_threads(2);
    #pragma omp parallel for reduction(+:sum)
        for (int i = 0; i < n; ++i)
            sum += x[i];
    return 0;
}

