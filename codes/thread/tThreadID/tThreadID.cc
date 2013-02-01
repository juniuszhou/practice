// g++  tThreadID.cc -lstdc++ -lpthread
/* To show child thread share the pid with other child and parent.
actually in linux, LWP has its own process it. but to accomodate POSIX
standard, func getpid return parent thread's pid */

#include "pthread.h"
#include "semaphore.h"
#include <iostream>
#include "sys/types.h"
#include "unistd.h"

using namespace std;

void* minFun(void* p)
{
	int i  = getpid();
	
	cout << "chilld thread pid is " << i << endl;
        pthread_t myId;
        myId = pthread_self();
        cout << "chilld thread tid is " << myId << endl;

	return NULL;
}

int main()
{
	
	int sleepTime = 1;
	pthread_t id;
	
	int ret_val = pthread_create(&id, NULL, minFun,NULL);

    ret_val = pthread_create(&id, NULL, minFun,NULL);
     
	//cout << "created in main process " << ret_val << endl;	
	int i  = getpid();
	
	cout << "pid is for main " << i << endl;
	
	return 1;
	
}




