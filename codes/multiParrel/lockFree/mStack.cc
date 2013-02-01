#include <iostream>
using namespace std;

template < typename T >
T tCAS(T * mem,T newval,T oldval)
{
	T ret;
	  __asm __volatile ("lock; cmpxchgl %2, %1"
	  : "=a" (ret), "=m" (*mem)
	  : "r" (newval), "m" (*mem), "0" (oldval));
	  //put oldval into eax, then compare eax and *mem
	  //if equal, then exchange eax and *mem
	  //if not equal, do nothing
	  return (int) ret;
}

//Compare and Swap pointer, for linked table
template < typename T >
bool ifCAS(T ** mem,T * newval,T * oldval)
{
	T * ret;	
	  __asm __volatile ("lock; cmpxchgl %2, %1"
	  : "=a" (ret), "=m" (*mem)
	  : "r" (newval), "m" (*mem), "0" (oldval));
	  //put oldval into eax, then compare eax and *mem
	  //if equal, then exchange eax and *mem
	  //if not equal, do nothing
	 
	  return ret == oldval;
	  //swap successful then return true
	  //swap failed then return false
}

template < typename T >
struct Node
{
T value;
Node * next;
};

template < typename T >
class lockFreeStack
{
public:
	Node<T> * top;
	static int minDelay;
	static int maxDelay;
	//Backoff backoff;
	lockFreeStack(){top = NULL;}
public:
	bool tryPush(Node<T> node)
	{
		Node<T> * oldtop = top;
		node.next = oldtop;		
		return ifCAS(&top,&node,oldtop);
	}
	void push(Node<T> node)
	{
		Node<T> * newNode = new Node<T>;
		while (true)
		{
			if (tryPush(*newNode))
				return;
			//else
		}		
	}

	Node<T> * tryPop()
	{
		Node<T> * oldtop = top;
		if (NULL == oldtop)
			throw "stack is empty";
		Node<T> * newtop = oldtop->next;
		if (ifCAS(&top,newtop,oldtop))
			return oldtop;
		else
			return NULL;		
	}

	Node<T> * Pop()
	{
		try
		{
			while (true)
			{
				Node<T> * ret = tryPop();
				if (NULL != ret)
					return ret;
				//else backoff			
				
			}
		}
		catch(...)
		{
		}
		return NULL;
	}	
};

template < typename T >
class lockFreeExchange
{
public:
	enum status 
	{
		EMPTY,WAITING,BUSY
	};
	int slot;
	T exchange(T myItem,long timeout, long timeStart)
	{
		
	}
};

int main()
{
Node<int> *a = new Node<int>;
a->value = 10;
a->next = NULL;

lockFreeStack<int> stack;
stack.tryPush(*a);

cout << (stack.top)->value << endl;

Node<int>* b = new Node<int>;
b->value = 100;
b->next = NULL;
stack.tryPush(*b);

cout << (stack.top)->value << endl;


}

