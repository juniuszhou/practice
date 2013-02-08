/*
g++ -S objParam.cc
*/

struct abc{
int i[30];
int j;
};

int fun(struct abc a)
{
int k = a.i[10];
return a.i[10];
}

int main()
{
struct abc a;
int i = fun(a);
return 0;
}
