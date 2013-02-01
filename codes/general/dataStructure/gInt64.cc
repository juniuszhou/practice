#include <iostream>
#include <stdio.h>
using namespace std;

void f1(int &i)
{
i = 1;
}

void f2(int &i)
{
f1(i);
}
int main()
{
int i = 0;
f2(i);

cout << i << endl;
return 0;

}
