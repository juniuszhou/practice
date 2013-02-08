#ifndef MAIN_H
#define MAIN_H

#include <assert.h>
#include <iostream>
#include <stdlib.h>

using namespace std;
typedef char UINT8;

template < class T>
T ADDD(T t1,T t2,T t3)
{
return t1 + t2 + t3;
};

int main()
{
cout << __LINE__ << endl << __FILE__ << endl;
//assert(__LINE__ > 10);
//cout << "ok";

int * pI = (int*)malloc(sizeof(int));
int * pTwo = new int;
UINT8 c11;

cout << ADDD(2,3,4) << endl;
return 0;
}

#endif

