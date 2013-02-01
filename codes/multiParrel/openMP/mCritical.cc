/*
g++ -fopenmp mCritical.cc
*/

#include <omp.h>
#include <stdio.h>
#include <iostream>
using namespace std;

int main (int argc, char *argv[]) {
int id, nthreads;

omp_set_num_threads(4);
//if critial used, print is more beautiful
#pragma omp parallel private(id)
{

    #pragma omp for
    for (int i=0;i<32;i++)
        #pragma omp critical (print_i)
        cout << i << "  " << omp_get_thread_num() << endl;    
}

return 0;
}

