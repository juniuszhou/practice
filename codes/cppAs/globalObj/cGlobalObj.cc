#include <iostream>
using namespace std;

class a
{
int i;
public:
a();
virtual ~a();
};

a::a()
{
i = 10;
}

a::~a()
{
cout << "out of provess" << endl;
}

class aa
{
int i;
public:
aa();
virtual ~aa();
};

aa::aa()
{
i = 10;
}

aa::~aa()
{
cout << "out of provess" << endl;
}
aa gaa1234;
a ga1234;
int abcd=23456;
int main()
{
return 1;
}
