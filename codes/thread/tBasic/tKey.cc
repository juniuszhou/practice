// g++ -g tKey.cc -lpthread
#include <iostream>
#include <pthread.h>
#include <semaphore.h>

using namespace std;
void* minFun(void*)
{
	sleep(1);
	static int shared_value = 0;

	//set a key for thread
	pthread_key_t myWinKey;
	
	//NULL means no destructor method needed
	pthread_key_create(&myWinKey, NULL);

    char win[25] = "loving you";
	// set value for key
	pthread_setspecific (myWinKey, win);

	//get value from key
	void * result = pthread_getspecific(myWinKey);
	cout << (char*) result << endl;

	//get my thread id
	pthread_t myId;
	myId = pthread_self();
	cout << "my self id is" << myId << endl;	

	//get process id
	int pid = getpid();
	cout << "main process pid is " << pid << endl;
	
	pthread_exit(NULL);
}

int main()
{	
	pthread_t id;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	int ret_val = pthread_create(&id, NULL, minFun,NULL);

	//join thread until thread exit
	pthread_join(id,NULL);

	//get process id
	int pid = getpid();
	cout << "main process pid is " << pid << endl;
	
	return 1;	
}




