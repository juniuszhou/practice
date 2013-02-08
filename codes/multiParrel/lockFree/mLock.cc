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

inline int CAS(unsigned long *mem,unsigned long newval,unsigned long oldval)
{
  unsigned long ret;
  __asm __volatile ("lock; cmpxchgl %2, %1"
  : "=a" (ret), "=m" (*mem)
  : "r" (newval), "m" (*mem), "0" (oldval));
  //put oldval into eax, then compare eax and *mem
  //if equal, then exchange eax and *mem
  //if not equal, do nothing
  return (int) ret;
}

int main()
{
unsigned long * a = new unsigned long;
*a = 10;
unsigned long b,c;
b = 12;
c = 10;

cout << tCAS(a,b,c) << endl;
cout << *a << endl;

return 1;
}
