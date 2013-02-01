/*
g++ -S valueParam.c
*/
int fun(int a, int b, int c)
{
return a+b+c;
}

int main()
{
int d;
d = fun(d,d,d);
return d;
}
