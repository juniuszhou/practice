/*
g++ -S referParam.c
*/

int fun(int & a)
{
int b = a;
return 0;
}

int main()
{
int a;
fun(a);
return 0;
}

