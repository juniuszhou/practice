// g++ -g tConditionVariable.cc -lpthread

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <malloc.h>
#include <iostream>

struct msg {
	struct msg *next;
	int num;
};

struct msg *head;
pthread_cond_t has_product = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *consumer(void *p)
{
	struct msg *mp;

	for (;;) {
        //lock to avoid other thread access to msg queue
		pthread_mutex_lock(&lock);
		while (head == NULL)
            //unlock, let other thread operate msg queue
            //put itself into process queue via condition variable
			pthread_cond_wait(&has_product, &lock);
		mp = head;
		head = mp->next;
		pthread_mutex_unlock(&lock);
		printf("Consume %d\n", mp->num);
		free(mp);
        sleep(1);
    }
}

void *producer(void *p)
{
	struct msg *mp;
	for (;;) {
		mp = (msg*)malloc(sizeof(struct msg));
		mp->num = rand() % 1000 + 1;
		printf("Produce %d\n", mp->num);
		pthread_mutex_lock(&lock);
		mp->next = head;
		head = mp;
		pthread_mutex_unlock(&lock);
        //if one more added into msg queue
        //signal has none business with mutex
		pthread_cond_signal(&has_product);
		sleep(1);
	}
}

int main(int argc, char *argv[]) 
{
	pthread_t pid, cid;  

	srand(time(NULL));
	pthread_create(&pid, NULL, producer, NULL);
	pthread_create(&cid, NULL, consumer, NULL);
	pthread_join(pid, NULL);
	pthread_join(cid, NULL);
	return 0;
}

