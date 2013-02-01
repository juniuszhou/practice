/*
g++ -O2 -DNDEBUG  -o preduce p_reduce.cc -ltbb -lrt 
*/

#include <tbb/blocked_range.h>   
#include <tbb/parallel_reduce.h>   
#include <tbb/task_scheduler_init.h>   
#include <iostream>   
  
using namespace std;   
using namespace tbb;   

class computeUnit{   
    float *const array_;   
public:
    float sum;

    //this func is critical to spawn child thread
    computeUnit(computeUnit& c, tbb::split);

    //constructor func
    computeUnit(float array[]);
    
    //the most important func, any class want to be second parameter as parallel_for
    void operator()(const blocked_range<size_t>& r);   

    void join(const computeUnit& c){sum+=c.sum;}
};   

  //must copy global data from parent thread, so must set array_ as parent's array_
computeUnit::computeUnit(computeUnit& c, tbb::split):array_(c.array_){sum = 0;}   
computeUnit::computeUnit(float array[]):array_(array){sum = 0;}   

  
void  
computeUnit::operator()(const blocked_range<size_t>& r){   

    //copy from global variable to stack, make it faster
    float *aa=array_;
    size_t i;
    for(i=r.begin();i!=r.end();++i)   
        sum += aa[i];
    cout << "begin print " << r.begin() << " " << r.end() << endl;
}

int main()
{
    task_scheduler_init init;   
    float a[1000];
    for(int i=0;i<1000;++i)
        a[i] = i + 0.1;

   computeUnit cu(a);
   //parallel_reduce(blocked_range<size_t>(0,100,10),cu); 


// the difference of auto_partitioner from simple_partitioner is the work stealing
// mechanism included in

//you can see default for auto is grainsize 1
   parallel_reduce(blocked_range<size_t>(0,100),cu,auto_partitioner()); 

   cout << cu.sum << endl;

return 0;
}

