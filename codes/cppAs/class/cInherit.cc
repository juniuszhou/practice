class one
{
public:
one();
int i;
};
one::one()
{
i = 99;
}
class two :public one
{
public:
two();
};
two::two()
{
i = 101;
}
int main()
{
one* aOne=new one();
two aTwo;
return 1;
}

