// objdump -d a.out

int func()
{
return 1;
}

int main()
{
int i;

i = func();
if (i>0)
    i = 3;
else
   i = 7;
return 0;
}
