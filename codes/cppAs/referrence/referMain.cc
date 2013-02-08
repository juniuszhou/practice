#include <iostream>
using namespace std;

class a
{
public:
int i;
a();
a(const a& oldObj);
};
a::a()
{
cout << " xx99" << endl;
}
a::a(const a& oldObj)
{
cout << " yy99" << endl;
}

int fun(int i,int &j,a k,a &l)
{
i = 10;
j = 20;
k.i = 44;
return 30;
}
int main()
{
int i;
int j;
int & k = j;
a aObj;
i = 11;
j = 22;
fun(i,k,aObj,aObj);
return 1;
}
