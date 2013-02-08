// g++ -S bHello.c
// g++ -o a.out bHello.s

#include <iostream>
using namespace std;

static char a[] ="hello world!";
int f3(unsigned len)
{
for (int i = 0; i <= len-1;i++)
	{
	cout << "ok" << endl;
}
return 1;
}
int main()
{
f3(1);

/// float f1 = 5.8 + 1e20 - 1e20;
unsigned int f1 = 0x80000000;
cout << (int)f1 << endl;
f1 = f1 >> 4;
cout << f1 << endl;


unsigned int f2 = 0xFF000000;
cout << (int)f2 << endl;
f2 = f2 >> 4;
cout <<(int)f2 << endl;

return 1;
}
