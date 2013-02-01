// g++ -S bHello.c
// g++ -o a.out bHello.s

#include <iostream>
using namespace std;

static char a[] ="hello world!";

int main()
{

cout << a << endl;

return 1;
}
