// g++  tOnce.cc -lstdc++ -lpthread
/* To show make a func just called once by all threads */

#include "pthread.h"
#include "semaphore.h"
#include <iostream>
#include "sys/types.h"
#include "unistd.h"
using namespace std;

/*
pthread_once_t once = PTHREAD_ONCE_INIT;

void once_run(void)
{
        cout<<"once_run in thread "<<(unsigned int )pthread_self()<<endl;
}

void * child1(void * arg)
{
        pthread_t tid =pthread_self();
        cout<<"thread "<<(unsigned int )tid<<" enter"<<endl;
        pthread_once(&once,once_run);
        cout<<"thread "<<tid<<" return"<<endl;
}


void * child2(void * arg)
{
        pthread_t tid =pthread_self();
        cout<<"thread "<<(unsigned int )tid<<" enter"<<endl;
        pthread_once(&once,once_run);
        cout<<"thread "<<tid<<" return"<<endl;
}

int main(void)
{
        pthread_t tid1,tid2;
        cout<<"hello"<<endl;
        pthread_create(&tid1,NULL,child1,NULL);
        pthread_create(&tid2,NULL,child2,NULL);
        sleep(10);
        cout<<"main thread exit"<<endl;
        return 0;

}

*/



pthread_once_t once_var = PTHREAD_ONCE_INIT;

void once_init_routine(void)
{
    cout << "just once printed" << endl;
    sleep(3);
    cout << "exit" << endl;
}

void* minFun(void* p)
{
    cout << "access to minFun" << endl;
    int status;
        status = pthread_once(&once_var,once_init_routine);

    cout << "thread is created successfully" << endl;
	return NULL;
}

int main(){
	
	
	pthread_t id1,id2;
	int* ret_value = NULL;	
    
	int ret_val = pthread_create(&id1, NULL, minFun,NULL);    
    //  pthread_join(id1,(void**)&ret_value);
        ret_val = pthread_create(&id2, NULL, minFun,NULL);    
   // pthread_join(id2,(void**)&ret_value);    

//to make thread running ok after main thread exit call 
//pthread_exit instead of exit/return.

    pthread_exit(NULL);
	//return 1;
	
}


