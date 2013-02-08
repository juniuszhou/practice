#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
	FILE * fp;
	fp = fopen("a.out","r");
	cout << ftell(fp) << endl;
	
	long i = 1L;
	cout << i << endl;
	return 1;
}