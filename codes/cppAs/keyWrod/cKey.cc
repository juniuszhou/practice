#include <iostream>
using namespace std;
class one
{
public:
	virtual ~one();
};
class two: public one
{
};
class three:public one
{
};

int main()
{
two aTwo;
one * p = &aTwo;
int i = 99;
three* pThree = dynamic_cast<three*>(p);

return 1;
}
