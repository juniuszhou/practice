//gcc cLeak.cc -lstdc++

class one
{
public:
one();
~one();
};
one::one()
{
	int i = 234;
}
one::~one()
{
	int i = 567;
}

class two : public one
{
	public:
		two();
		~two();
};
two::two()
{
}
two::~two()
{
}
int main()
{
one aOne;

one* alOne = new two[3];
delete [] alOne;
return 1;
}

