#include <iostream>
using namespace std;

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
class coarseList
{
//using lock for add and remove
};


template < typename T >
class window
{
public:
	Node<T> * pred,curr;
	window<T> * find(Node<T> * head, T key)
	{
		
	}
}

template < typename T >
class lockFreeList

{
//using lock for add and remove
};





