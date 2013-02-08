#include <iostream>
using namespace std;
int main()
{
int a[4];
int b[4];
int c[4];
for(int i=0;i<4;i++)
{
c[i] = a[i] + b[i];
}
cout << c[2] << endl;
return 1;
}
