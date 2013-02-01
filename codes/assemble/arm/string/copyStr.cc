/*
g++ -S copyStr.cc
default compiler will add stack protector code, make assembly code
difficult to understand. but it can protect stack if addr process access
is beyong the scope of stack. for instance, some hacker program.

g++ -S -fno-stack-protector copyStr.cc 

*/

int main()
{
char a[20];
char b[20];
for (int i = 0; i < 20;++i)
{
b[i] = a[i];
}
return 0;
}
