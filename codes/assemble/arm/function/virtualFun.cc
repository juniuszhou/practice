/*
g++ -S virtualFun.cc
*/
#include <iostream>
using namespace std;

class a
{
public:
    virtual void ok(){int i = k;cout<<i;}
    virtual void ok2(){int i = k;cout<<i;}
    virtual void fun(){int i = 0;cout<<i;}
    int k;
};

class b : public a
{
};

int main()
{
a * pa = new b;
pa->fun();
return 0;
}

