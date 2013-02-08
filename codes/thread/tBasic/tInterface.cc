#include "Interface.h"
#include <iostream>

using namespace std;

int Interface::getThreadCount()
{

	return mThreadCount;
}

 void*  Interface::threadOK(void* sleepTime)
{
	//int * strTime = (int *) (sleepTime);
	//sleep(*strTime);
	sleep(1);
	cout <<  "from thread process" << endl;
	cout <<  "from thread process" << endl;
	cout <<  "from thread process" << endl;
	cout <<  "from thread process" << endl;
	cout <<  "from thread process" << endl;
	cout <<  "from thread process" << endl;
	//FILE *fp = open("junius.txt","a");
	//fputs("hello world",fp);
	///close(fp);
	return NULL;
}


Thread::Thread():joinable_(PTHREAD_CREATE_JOINABLE), isThrAttrInit_(0)
	{
	}


	Thread::~Thread()
	{
 // 如果线程属性对象被成功的设置，则对其释放内存
		if( this->isThrAttrInit_ == 1 )
		{
			if( pthread_attr_destroy(& this->thrAttr_) == 0 )
			{
				; // todo
			}
			else
			{
				; // todo
			}
		}
	}


	void* Thread::thr_run(void* args)
	{
		int thr_ret = 0;
		Thread *thr_objp = (Thread*) args;


		thr_ret = thr_objp->run();


		if( thr_ret == 0 ) { // 线程正常退出
			; // todo
		} else { // 返回值为非0，异常退出
			; // todo
		}
		return (void*)thr_ret;
	}


	int Thread::start(int thr_num, int state)
	{
		int err = 0;


		err = pthread_attr_init(& this->thrAttr_);
		if( err != 0 )		  return err;


		if( state == Thread::THR_DETACHED )
		{
			err = pthread_attr_setdetachstate(& this->thrAttr_, PTHREAD_CREATE_DETACHED);
			if( err != 0 )		  return err;
			this->joinable_ = PTHREAD_CREATE_DETACHED;
		}
		else
		{
			err = pthread_attr_setdetachstate(& this->thrAttr_, PTHREAD_CREATE_JOINABLE);
			if( err != 0 )		  return err;
			this->joinable_ = PTHREAD_CREATE_JOINABLE;
		}


		// 线程属性已经被成功设置
		this->isThrAttrInit_ = 1;


		thr_num = (thr_num > 0) ? thr_num : 1;


		pthread_t tid;
		for(int i = 0; i < thr_num; i++ )
		{
			err = pthread_create(& tid, & this->thrAttr_, thr_run, this);
			// save the thread id
			if( err == 0 )
				this->thrIdList_.push_back(tid);
		}
		return err;
	}


	int Thread::wait()
	{
		if( this->joinable())
		{// 如果是可连接的，则等待
			int threadCount = thread_count();
			for(int i = 0; i < threadCount; i++ )
			{
				pthread_join( this->thrIdList_.at(i), NULL);
			}
		}
		return 0;
	}





	int Thread::joinable()
	{
		return this->joinable_ == PTHREAD_CREATE_JOINABLE;
	}


	int Thread::thread_count()
	{
		return this->thrIdList_.size();
	}
	

