/*
g++ -fopenmp mLock.cc
*/

#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
using namespace std;

//from the example, we can see if many threads share a lock.
//efficiency is very low.
void TestOmpLock()
{
      time_t t1;
      time_t t2;
  
     int i;
     int a = 0;
     omp_lock_t    mylock; 
     omp_init_lock(&mylock);
 
    time(&t1); 
     for( i = 0; i < 20000000; i++ )
     {
         omp_set_lock(&mylock);
         a+=1;
         omp_unset_lock(&mylock);
     }
     time(&t2);
    
     cout << "time used " <<  (t2-t1) << endl;
 
     time(&t1); 
#pragma omp parallel for
     for( i = 0; i < 20000000; i++ )
     {
         omp_set_lock(&mylock);
         a+=1;
         omp_unset_lock(&mylock);
     }
     time(&t2);
    
    cout << "time used " <<  (t2-t1) << endl; 
     omp_destroy_lock(&mylock);
}


int main (int argc, char *argv[]) {
    TestOmpLock();
return 0;
}

