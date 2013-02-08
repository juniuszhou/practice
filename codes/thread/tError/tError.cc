// g++ -o error -g tError.cc -lpthread

#include <malloc.h>
#include <pthread.h>
#include <stdio.h>
#include <iostream>
#include <errno.h>
#include <string.h>

int main()
{
     //set pthread mutex
	//pthread_mutex_t mutex;
	
    pthread_t id1;
    int status;   
    status = pthread_join(id1,NULL);
    if (!status)
        std::cout << status << " " << strerror(status);

    return 1;
}

