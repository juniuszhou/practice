#include <stdio.h>
int main()
{
struct myArray
{
int i;
char k[8];
}myArray;

struct myArray aArray;
int j = 0;

while (j < 8115)
{
printf("%c %d\n",aArray.k[j],j);
j=j+1;
}
return 1;
}
