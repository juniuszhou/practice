/*
g++ -O2 -DNDEBUG p_schedule.cc -ltbb -lrt 
*/

#include<tbb/blocked_range.h>   
#include<tbb/parallel_for.h>   
#include<tbb/task_scheduler_init.h>   
#include<iostream>   
  
using namespace std;   
using namespace tbb; 
int main()
{
int nthread = 2;
//defer the initialization of task_inin variable
    task_scheduler_init init(task_scheduler_init::deferred);

//init according to thread number we specify
 if( nthread>=1 )
 init.initialize(nthread);
 // code that uses task scheduler only if nthread>=1
 if( nthread>=1 )
 init.terminate( ); 
   
return 0;
}

