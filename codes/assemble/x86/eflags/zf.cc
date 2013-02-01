/*
g++ -S zf.cc
*/
int main()
{
unsigned int a,b;
a = 0xFFFFFFFF;
b = 2;
//unsigned int c = a+b;
if (a == b)
    return 1;
if (a > b)
    return 1;
int c,d;
if (c > d)
    return 1;

return 0;
}
