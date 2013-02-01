/*
g++ -O2 -DNDEBUG task_group.cc -ltbb -lrt 
*/

#include "tbb/tbb.h"
#include <iostream>
using namespace tbb;
using namespace std;

class say_hello
{ 
   const char* message;
   public: 
    
      say_hello(const char* str) : message(str){}
      void operator()() const {
         cout << message << endl;
        }
      
};

//raw method to add task to task group
int main( )
{ 
    task_group tg;
    tg.run(say_hello("child 1")); // spawn task and return
    tg.run(say_hello("child 2")); // spawn another task and return 
    tg.wait( ); // wait for tasks to complete
}


