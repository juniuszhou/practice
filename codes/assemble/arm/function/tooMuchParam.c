// /home/junius/toolschain/4.4.3/bin/arm-linux-g++ -S tooMuchParam.c

#include <iostream>

using namespace std;
int kkk()
{
return 0;
}

int tooMuch(int i,int j, int k, int l)
{
kkk();
return i+j+k+l;
}
int main()
{
int c = 123;
tooMuch(c,c,c,c);

return 1;
}

