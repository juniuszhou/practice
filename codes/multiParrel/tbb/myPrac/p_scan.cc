/*
g++ -O2 -DNDEBUG  -o pscan p_scan.cc -ltbb -lrt 
*/

#include<tbb/blocked_range.h>   
#include<tbb/parallel_scan.h>   
#include<tbb/task_scheduler_init.h>   
#include<iostream>   
  
using namespace std;   
using namespace tbb;   

class computeUnit{
    int reduced_result;
    int * const y;   
    const int * const x;
public:
    int sum;

    //this func is critical to spawn child thread
    computeUnit(computeUnit& c, tbb::split):x(c.x),y(c.y)
    {reduced_result += c.reduced_result;}

    //constructor func
    computeUnit(int y_[], const int x_[]):reduced_result(0),x(x_),y(y_){}

    int get_reduced_result() const {return reduced_result;}
    
    //the most important func, any class want to be second parameter as parallel_for
    template<typename T>
    void operator()(const blocked_range<size_t>& r, T )
    {   

    //copy from global variable to stack, make it faster
    int temp = reduced_result;
    for(size_t i=r.begin();i!=r.end();++i){
        temp += x[i]; 
        if(T::is_final_scan())
            y[i] = temp;
    }
    reduced_result = temp;
    }   

    void reverse_join(const computeUnit& c){reduced_result += c.reduced_result;}

    void assign(computeUnit&c) {reduced_result = c.reduced_result;}
};    

int main()
{
    task_scheduler_init init;   
    int a[100];
    int b[100];
    for(int i=0;i<100;++i)
        a[i] = 1;
    
   computeUnit cu(b,a);
   //parallel_reduce(blocked_range<size_t>(0,100,10),cu); 

   parallel_scan(blocked_range<size_t>(0,100),cu,auto_partitioner()); 

   for (int i = 0; i < 100; ++i)
    cout << b[i] << endl;

   cout << endl << cu.get_reduced_result() << endl;

return 0;
}

