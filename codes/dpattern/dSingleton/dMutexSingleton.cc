#include <iostream>
#include "pthread.h"

class single
{
public:
    static single* instance();
protected:
    single();
private:
    static single* onlyInstance;
};

single* single::onlyInstance=NULL;
single::single()
{
}

single* single::instance()
{
	pthread_mutex_t aMutex;
	//pthread_mutexattr_t mattr;
	//pthread_mutexattr_init(&mattr);
	//pthread_mutexattr_settype(&mattr,PTHREAD_PROCESS_PRIVATE);
	
	//PTHREAD_PROCESS_PRIVATE used in multi-thread in one process
	//PTHREAD_PROCESS_SHARED used in multi-thread in diffrent process
	//pthread_mutexattr_init(&aMutex,&mattr);
	
	pthread_mutex_lock(&aMutex);
	if (onlyInstance == NULL)
		{
			onlyInstance = new single();
		}
	pthread_mutex_unlock(&aMutex);
	
	return onlyInstance;
}

int main()
{
	single * aSingle = single::instance();
  return 1;
}

