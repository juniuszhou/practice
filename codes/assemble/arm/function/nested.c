/*
/home/junius/toolschain/4.4.3/bin/arm-linux-g++ -S nested.c
*/
void fun2()
{
return ;
}

int fun()
{
int i =0;
fun2();
return 0;
}

int main()
{
short a = 12;
int b = fun();
return 0;
}

