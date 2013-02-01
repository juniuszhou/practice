#include <iostream>
using namespace std;

class a
{
public:
	a(){}
	a(a& tmp)
	{
		cout << "constuct " << endl;
	}
	//a(a tmp)
	//we can't define constructor 
};
int main()
{
a a1;
a a2(a1);
return 1;
}
