// g++ -o mutex -g tMutex.cc -lpthread

#include <malloc.h>
#include <pthread.h>
#include <stdio.h>
#include <iostream>

static pthread_mutex_t mutex;
static int i=0;

void* minFun(void*)
{
    pthread_mutex_lock (&mutex);
    ++i;
    std::cout << i << std::endl;
	pthread_mutex_unlock(&mutex);

}

int main()
{
     //set pthread mutex
	//pthread_mutex_t mutex;
	pthread_mutex_init(&mutex,NULL);
    pthread_t id1,id2;

	int ret_val = pthread_create(&id1, NULL, minFun,NULL);
    pthread_create(&id2, NULL, minFun,NULL);

    /* block main exec flow to wait child print or just sleep to wait
    pthread_join(id1,NULL);
    pthread_join(id2,NULL);
    */
    sleep(3);

    return 1;
}

