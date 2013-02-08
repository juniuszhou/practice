/*
g++ -O2 -DNDEBUG p_while.cc -ltbb -lrt 
*/
    
#include<tbb/blocked_range.h>   
#include<tbb/parallel_while.h>   
#include<tbb/task_scheduler_init.h> 

#include "tbb/tbb.h"
#include <iostream>
    using namespace tbb;
    using namespace std;

struct Item{
int data;
Item* next;
};

class ItemStream {
Item* my_ptr;
public:

//important func in stram, list iterator in container.
//this method don't need to be thread safe, since tbb framework
//never call it concurrently.
bool pop_if_present( Item*& item ) {
    if( my_ptr ) {
        item = my_ptr;
        my_ptr = my_ptr->next; 
        return true;
        } else {
         return false;
    }
}

ItemStream( Item* root ) : my_ptr(root) {}
};

class ApplyFoo {
public:
    //this one can be calle concurrently, since its defined as const
    // so it doesn't change anything stream.
void operator( )( Item* item ) const {
    cout << item->data << endl;
    }
typedef Item* argument_type;
};

int main()
{
    //need compute unit as init parameter
    parallel_while<ApplyFoo> w;
    
    Item firstOne;
    firstOne.data = -1;
    firstOne.next = NULL;
    Item* lastOne = &firstOne;
    for (int i = 0; i < 10; ++i)
        {
        Item* tmp = new Item();
        tmp->data = i;
        tmp->next = NULL;
        lastOne->next = tmp;
        lastOne = tmp;
        }

    //init the stream, the structure can be iterative such as list,vector
    ItemStream stream(&firstOne);

    //instantiate a computing unit
    ApplyFoo body;

    //start to run
    w.run( stream, body );

    return 0;
}

