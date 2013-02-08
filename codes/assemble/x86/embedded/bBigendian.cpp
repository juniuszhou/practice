#include <iostream>
using namespace std;

int main()
{
	unsigned int  bff = 0x12345678;
			unsigned int  c;
			cout << hex << bff <<endl;
			int d = 11;
			__asm__ __volatile__ ("bswap %%eax; "
							:"=a"(bff)  /* output */
							:"a"(bff) 	/* input */
							:"bx","memory"); /* clobbered register */
			cout  << hex << bff <<endl;

return 1;

}
