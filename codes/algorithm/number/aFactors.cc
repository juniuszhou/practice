#include <iostream>
#include "stdlib.h"
using namespace std;

struct Node{
	Node * next;
	int value;
};

static int a[][2]={{1,2},{2,3}};

void merge()
{
}
void mergeSort(int * a, int l, int r)
{
	if (l >= r)
		return;
	int m = (l + r)/2;
	mergeSort(a,l,m);
	mergeSort(a,m+1,r);
	merge();
	
}

int main(int argc, char *argv[])
{
struct Node n1;
struct Node * p1 = (struct Node * )malloc(sizeof(struct Node));
n1.next = p1;

delete p1;
//delete &n1;
int MAXLEN=100;
int a[MAXLEN];
int b[MAXLEN];

a[0] = 1;
a[1] = 3;
a[2] = 1;
a[3] = 1;
a[4] = 1;
a[5] = 4;
a[6] = 3;
a[7] = 2;

for (int i = 0; i < 100; ++i)
{
	b[i] = 0;
}

int j = 0;
while (b[j] != 3)
{
	b[j]+=1;
	j = a[j];
}

int count = 0;
for (int i = 0; i < 100; ++i)
{
	if (b[i] > 1){
		++count;
		cout << i <<endl;}
}

cout << count << endl;

/*
int num;
cin >> num;
int i = 2;
int count = 1;
while (i * i < num)
{
	if (!(num % i))
	{
		cout << i << endl;
		count ++;
	}
	++i;
}
cout << count * 2 << endl;
*/
return 1;
}
