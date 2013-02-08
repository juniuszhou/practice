// gcc tThreadID.cc -lstdc++ -lpthread
#include <iostream>
#include "Interface.h"

#include <pthread.h>
#include <semaphore.h>

using namespace std;

void printKey()
{

}

void* minFun(void*)
{
	sleep(1);
	static int shared_value = 0;
	

	int * value = new int;
	shared_value += 10;

	//set a key for thread
	pthread_key_t myWinKey;
	//static pthread_once_t once = PTHREAD_ONCE_INIT;

	//NULL means no destructor method needed
	pthread_key_create(&myWinKey, NULL);

	int*  win = new int;
	*win = getpid();
	//pthread_once ( & once, createMyKey) ;
	pthread_setspecific (myWinKey, win);
	//end of key
	void * result = pthread_getspecific(myWinKey);
	cout << *((int*) result) << endl;
	pthread_t myId;
	myId = pthread_self();
	cout << "my self id is" << myId << endl;
	
	
      cout << "It is a mini function, shared_value is " << shared_value << endl;
	*value = 38;

	
	pthread_exit(value);
}

int main()
{	
	pthread_t id;
	pthread_attr_t attr;
	sched_param param;

	pthread_attr_init(&attr);

	//Set thread binding status, PTHREAD_SCOPE_SYSTEM or PTHREAD_SCOPE_PROCESS
	pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
	//end status
	
	//set thread priority
	int newprio=20;
	pthread_attr_getschedparam(&attr, &param);
	param.sched_priority=newprio;
	pthread_attr_setschedparam(&attr, &param);
	//end priority
	
	//set pthread mutex
	pthread_mutex_t mutex;
	pthread_mutex_init(&mutex,NULL);

	pthread_mutex_lock (&mutex);
	pthread_mutex_unlock(&mutex);

	struct timespec delay;
	//TODO find below method correct parameters
	//pthread_delay_np(&delay);

	//end of mutex.


	//pthread condition variable
	/*
	pthread_cond_ destroy  
	pthread_cond_wait	
	pthread_cond_t 
	pthread_cond_init();
	pthread_cond_wait( &count_nonzero, &count_lock);*/


	pthread_key_t  myKey;
	pthread_key_create(&myKey, NULL);


	
	int ret_val;

	int sleepTime = 1;
	
	//ret_val = pthread_create(&id, NULL, Interface::threadOK, NULL);
	//ret_val = pthread_create(&id, NULL, Interface::threadOK, (void *) &sleepTime);
	ret_val = pthread_create(&id, NULL, minFun,NULL);
	cout << (unsigned int)id << "is created in main process" << endl;
	pthread_t secId;
	ret_val = pthread_create(&secId, NULL, minFun,NULL);
	cout << (unsigned int)secId << "is created in main process" << endl;
	int* ret_value = NULL;	
	pthread_join(id,(void**)&ret_value);
	pthread_join(secId,(void**)&ret_value);


	
      //pthread_detach(id);
      
	//cout << "return value is " << *ret_value << " memory is " << ret_value << endl;

	delete ret_value;

	//ret_val = pthread_create(&id, NULL, minFun,NULL);
	//pthread_join(id,(void**)&ret_value);

	//ret_val = pthread_create(&id, NULL, Interface::threadOK, (void *) &sleepTime);
	//sleep(4);
	//cout << "from main thread" << endl;
	
	return 1;
	
}




