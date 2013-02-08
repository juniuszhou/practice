#ifndef INTERFACE_H
#define INTERFACE_H

#include <vector>
using namespace std;

class Interface
{

private:
	int mThreadCount;

public:
	int getThreadCount();

static void*  threadOK(void* sleepTime);
	//Interface(){}
};

class Thread
{
public:
	Thread();
	virtual ~Thread();
public:
	enum { THR_JOINABLE = 0, THR_DETACHED  };
//	  enum {  THR_STATE_READY = 0, // 就绪状态，在调用线程函数run()之前
//			  THR_STATE_RUNNING, // 工作状态，启动run()函数，但未返回
//			  THR_STATE_RETURN, // 线程成功返回
//			  THR_STATE_ERROR // 线程失败返回
//		   };
protected:
	static void* thr_run(void* args);
protected:
	/**
	 * 线程方法，继承thread，实现这个run方法即可
	 */
	virtual int run() = 0;
public:
	/**
	 * 线程启动方法
	 */
	int start(int thr_num = 1, int state = Thread::THR_JOINABLE );
	/**
	 * 等待所有线程结束
	 */
	int wait();
	/**
	 * 线程是否可连接
	 * @return
	 *		   1: YES
	 *		   0: NO
	 */
	int joinable();
	/**
	 * 本线程对象共有多少个线程在运行
	 */
	int thread_count();
private:
	// 线程ID集合
	vector<pthread_t> thrIdList_;
	// 线程属性
	pthread_attr_t thrAttr_;
	// 线程是否可连接
	int joinable_;
	int isThrAttrInit_;
}; 
#endif 

