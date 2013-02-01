#include <iostream>
using namespace std;

int main()
{
	int a=10;
	unsigned long long b = 3;
      __asm__ __volatile__ ("movl %1, %%eax; \
	  	movl $0x10, %%ecx; \
	  	sum: addl %1, %%eax; \
	  	loop sum; \
	  	movl %%eax, %0;" 	  	
		:"=r"(b)  /* output */	  
		:"r"(a) 	  /* input */
		:"%eax"); /* clobbered register */

	  cout << b << endl;

return 1;
}
