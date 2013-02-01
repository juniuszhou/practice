/*
g++ -O2 -DNDEBUG  -o pfor p_for.cc -ltbb -lrt 
*/

#include<tbb/blocked_range.h>   
#include<tbb/parallel_for.h>   
#include<tbb/task_scheduler_init.h>   
#include<iostream>   
  
using namespace std;   
using namespace tbb;   

class computeUnit{   
    float *const array_;   
public:   
    computeUnit(float array[]);
    //the most important func, any class want to be second parameter as parallel_for
    void operator()(const blocked_range<size_t>& r) const;   
};   
  
computeUnit::computeUnit(float array[]):array_(array){
    cout << "constructor called" << endl;}   
  
void  
computeUnit::operator()(const blocked_range<size_t>& r) const{   

    //copy from global variable to stack, make it faster
    float *a=array_;
    for(size_t i=r.begin();i!=r.end();++i)   
        cout << a[i] << endl;
    cout << "hehe  " << r.begin() << " to " << r.end() << endl;
}

class computeUnit2 {
    public:
        computeUnit2(){};
        
        void operator() (const blocked_range<size_t>& r) const;
};  

void  
computeUnit2::operator()(const blocked_range<size_t>& r) const{   

    //copy from global variable to stack, make it faster    
    for(size_t i=r.begin();i!=r.end();++i)   
       cout<<i<<"\t";   
}


int main()
{
    task_scheduler_init init(task_scheduler_init::deferred);   
    init.initialize(4);
    float a[128];
    for(int i=0;i<128;++i)
        a[i] = i + 0.1;
    
   // parallel_for(blocked_range<size_t>(0,1000,100),computeUnit(a));
    
   // fixed grain size
   parallel_for(blocked_range<size_t>(0,128,16),computeUnit(a));

   //if the size of a is 100, and grainsize is 10, then still split into 16 tasks.
   //because when size will be 50->25->12/13 then still bigger than grain size 10
   //so split further, so at last, size become 6 or 7.
   parallel_for(blocked_range<size_t>(0,100,10),computeUnit(a));
   

   // automatic grain size
   //parallel_for(blocked_range<size_t>(0,10),computeUnit2());

   //partitioner
    //parallel_for(blocked_range<size_t>(0,10),computeUnit2(),auto_partitioner());

return 0;
}

