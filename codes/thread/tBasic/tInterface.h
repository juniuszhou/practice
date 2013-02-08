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
//	  enum {  THR_STATE_READY = 0, // ����״̬���ڵ����̺߳���run()֮ǰ
//			  THR_STATE_RUNNING, // ����״̬������run()��������δ����
//			  THR_STATE_RETURN, // �̳߳ɹ�����
//			  THR_STATE_ERROR // �߳�ʧ�ܷ���
//		   };
protected:
	static void* thr_run(void* args);
protected:
	/**
	 * �̷߳������̳�thread��ʵ�����run��������
	 */
	virtual int run() = 0;
public:
	/**
	 * �߳���������
	 */
	int start(int thr_num = 1, int state = Thread::THR_JOINABLE );
	/**
	 * �ȴ������߳̽���
	 */
	int wait();
	/**
	 * �߳��Ƿ������
	 * @return
	 *		   1: YES
	 *		   0: NO
	 */
	int joinable();
	/**
	 * ���̶߳����ж��ٸ��߳�������
	 */
	int thread_count();
private:
	// �߳�ID����
	vector<pthread_t> thrIdList_;
	// �߳�����
	pthread_attr_t thrAttr_;
	// �߳��Ƿ������
	int joinable_;
	int isThrAttrInit_;
}; 
#endif 

