#include <iostream>
using namespace std;
const int i = 99;

class one
{
public:
int i;
	virtual ~one();
};
one::~one(){}
class two: public one
{
};
class three:public one
{
int j;
};

//normal successful case 
int main()
{
int* k = const_cast<int*>(&i);

//it always OK, if there is a value of p, cast happens in compile
int p;
cout << &p << endl;
long* c = reinterpret_cast<long*>(&p);
if (NULL == c)
	cout << "NOK" << endl;
cout << &(*c) << endl;

//static_cast
three * aThree = new three();
one *aOne = static_cast<one*>(aThree);//it is ok

return 1;
}


//the case for failed cast
/*
int main()
{
//an error issued in compile stage
char* k = const_cast<char*>(&i);

//static_cast
three * aThree = new three();
two *aTwo = static_cast<two*>(aThree);//can't pass compile

return 1;
}
*/
