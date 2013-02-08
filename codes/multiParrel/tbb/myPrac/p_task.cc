/*
g++ -O2 -DNDEBUG p_task.cc -ltbb -lrt 
*/

#include "tbb/tbb.h"
#include <iostream>
using namespace tbb;
using namespace std;
bool noMore = false;

class parent_block : public task { 
    public: 
    task* execute( ) { 
       cout << "Hello World! \n";
       if (!noMore){
        noMore = true;

       set_ref_count(3); // 2 (1 per child task) + 1 (for the wait)
       cout << "if parent blocked" << endl;
       task & t2 = new( allocate_child() ) parent_block();
       t2.spawn();
       task & t1 = new( allocate_child() ) parent_block();
       t1.spawn_and_wait(t1);       
       }
       return NULL;
    }
};

class parent_no_block : public task { 
    public: 
    task* execute( ) { 
       cout << "Hello World! \n";
       if (!noMore){
        noMore = true;
       task_list list1; 
       list1.push_back( *new( allocate_child() ) multi_task( ) );
       list1.push_back( *new( allocate_child() ) multi_task( ) );
       set_ref_count(3); // 2 (1 per child task) + 1 (for the wait) 
       spawn_and_wait_for_all(list1);
       
       }
       return NULL;
    }
};

class first_task : public task { 
    public: 
        first_task(int i):m_i(i){};
        int m_i;
    task* execute( ) { 
       cout << "Hello World! " << m_i << endl;
      // set_ref_count(1);
       return NULL;
    }
};

class multi_task : public task { 
    public: 
    task* execute( ) { 
       cout << "Hello World! \n";
       if (!noMore){
        noMore = true;
       task_list list1; 
       list1.push_back( *new( allocate_child() ) multi_task( ) );
       list1.push_back( *new( allocate_child() ) multi_task( ) );
       set_ref_count(3); // 2 (1 per child task) + 1 (for the wait) 
       spawn_and_wait_for_all(list1);
       
       }
       return NULL;
    }
};

int main( )
{ 

    task_scheduler_init init(task_scheduler_init::automatic);
    multi_task * f1 = new( tbb::task::allocate_root()) multi_task( );
    tbb::task::spawn_root_and_wait(*f1);

    cout << "@@@@@@@@@@@@@@@@@@@@" << endl;

    parent_block * f2 = new( tbb::task::allocate_root()) parent_block();
    tbb::task::spawn_root_and_wait(*f2);

    return 1;
}

