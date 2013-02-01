#include <iostream>
#include "string.h"
using namespace std;
enum colour
{
red,blue,yellow
};

int main()
{
char a[100];
memset(a,8,100);
//placement new
int * p = new (a) int;
cout << hex << *p << endl;

bool abool[190];
cout << dec << sizeof(abool) << endl;
//result is 190, every bool occupy one byte
return 1;
}
