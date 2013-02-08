class one
{
public:
one();
virtual ~one();
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
two aTwo;
return 1;
}

