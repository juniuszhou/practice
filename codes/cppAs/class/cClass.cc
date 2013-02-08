//write it to see what's different between call func and virtual func
#include <iostream>
using namespace std;

/*
class one
{
public:
one();
int i;
int norfun(){}
virtual int virOne();
virtual int virTwo(){}
virtual int virfun(){}

};
one::one()
{
	i = 999;
}
int one::virOne()
{
    cout << "i ma one" << endl;
	return 1;
}
class two : public one
{
public:
	int virOne();
};
int two::virOne()
{
one  pOne = (one)(*this);
//cout << (long)pOne << endl;
//pOne.virOne();
one::virOne();

return 1;
}

class three{
public:
bool tlsOrNormal;
one * tobj;
one & oneobj;
three(bool iftls = false):tlsOrNormal(iftls),tobj(),oneobj(*tobj)
	{
	if (iftls)
		tobj = new one; 
	else 
		tobj = new two;
	};
};

/*
three::three()
{
	
}*/

//using namespace std;

class A{
public:
        int a;
        A(int x) {a=x;};
		A(){};
};

class CBA{
};

class B {
	   int j;
	   int k;
	   A ax;
        A* x;
		CBA* y;
		 int j1;
	   int k2;
public:
	void virtual fun4(){int i =90;};
	
        A *operator->();
        B(A a) { cout<<"call B(A)\n";x=&a;j =120;k=20;};
        operator A*();
		//operator CBA*();
};

B::operator A*()
{
    cout<<"call operator A* \n";
    return x;
}

/*B::operator CBA*()
{
    cout<<"call operator CBA* \n";
    return y;
}*/

int main()
{
        A a(5);
        B b(a);
        cout<<"pre call operator A* \n";
        if(b)
        {
            cout << "not null" << endl;
        }

                cout<<"after call operator A* \n";

	CBA c();
	int i = 78;
	if (c)
		{
		 cout<<"herereerereer\n";
		}
        return i;
}




