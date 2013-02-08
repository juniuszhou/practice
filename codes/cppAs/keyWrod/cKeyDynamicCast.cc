#include <iostream>
using namespace std;
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
three aThree;
one * p = &aThree;

cout << p << endl;

three * p3 = dynamic_cast<three *>(p);


cout <<p3 << endl;
return 1;
}


//the case for failed dynamic_cast
int main()
{
    //if cast failed for a pointer, return NULL and continue
	three* aThree = new three;
	two * aTwo =  dynamic_cast<two *>(aThree);
	if (aTwo == NULL)
	cout << "OK" << endl;

	//if cast failed for a reference, throw bad_cast exception
	three& p = *aThree;
	two & bTwo =  dynamic_cast<two &>(*aThree);	
	cout << "OK" << endl;//crash never has chance to exec
	
	return 1;
}
