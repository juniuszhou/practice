struct abc
{
int k;
int l;
int f[18];
};

int fun(int i, int &j)
{
i = 99;
j = 88;
return 1;
}
int funs(struct abc *a)
{
return 1;
}

int main()
{
int i,j;
int k;
k = fun(i,j);
struct abc a;
k = funs(&a);
return 1;
}
