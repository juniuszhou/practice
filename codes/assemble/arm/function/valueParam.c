/*
/home/junius/toolschain/4.4.3/bin/arm-linux-g++  -S valueParam.c
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
