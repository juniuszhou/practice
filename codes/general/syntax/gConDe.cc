#include <iostream>
using namespace std;
//process to show how to use class's constructor
//and destructor method directly

class one
{
public:
one(){cout<<"one created"<<endl;}
~one(){cout<<"one deleted"<<endl;}
};

int main()
{
one aOne = one::one();

one* bone = new one();
aOne.one::~one();
cout<<(void*)&aOne<<endl;
return 1;
}

