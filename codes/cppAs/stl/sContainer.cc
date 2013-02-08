#include <vector>
#include <utility>
#include <string>
#include <iostream>

using namespace std;

class overOp
{

public:
	overOp(int j){i = j;};
	int i;
	overOp & operator+(overOp right)
		{
		cout << this->i + right.i << endl;
		return *this;
		}
};

struct brTree
{
	brTree * left;
	brTree * right;
	int value;
};

int main()
{
struct brTree root;
root.left = NULL;
root.right = NULL;
root.value = 0;



vector<int> aVec;
aVec.push_back(5);

for (int i = 1; i < 10; ++i)
{
    aVec.push_back(i);
}

for (vector<int>::iterator ite = aVec.begin(); ite < aVec.end(); ++ite)
{
    cout << *ite << endl;
}

pair<string, string> aPair("junius","hello");
cout << aPair.first << endl;

overOp aOver(4);
aOver + overOp(8) + overOp(12); 

return 1;

}
