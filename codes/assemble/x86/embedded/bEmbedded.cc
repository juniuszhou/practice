#include <iostream>
using namespace std;

int main()
{
	int a=10;
	unsigned long long b;
	unsigned long long c,d;
	b = 0xF000999999;
	c = 1900;
	d = b + c;
	cout << d << endl;
	
      __asm__ __volatile__ ("movl %1, %%eax; \
	  	movl %%esp, %0; \
	  	movl %1, %%ebp"
		:"=r"(b)  /* output */	  
		:"r"(a) 	  /* input */
		:"%eax"); /* clobbered register */

	  cout << hex << b << endl;

return 1;
}
