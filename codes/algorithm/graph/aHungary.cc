#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
#define MAX 102
 
long n,n1,match;
long adjl[MAX][MAX];//linked table
long mat[MAX];
bool used[MAX];
 
FILE *fi,*fo;
 
void readfile()
{
	fi=fopen("flyer.in","r");
	cout << "read is OK" << endl;
	
	fscanf(fi,"%ld%ld",&n,&n1); //vertex and edge
	long a,b;
	while (fscanf(fi,"%ld%ld",&a,&b)!=EOF)
		{
		adjl[a][ ++adjl[a][0] ]=b;
		adjl[b][ ++adjl[b][0] ]=a;
		cout << a << " link to " << b;
		}
	//[a][0] to store how many edges for a, [a][n] means there is edge a to b.
	match=0;
}
 
bool crosspath(long k)
{
	for (long i=1;i<=adjl[k][0];i++)
	{
		long j=adjl[k][i];//other vertex of this edge
		if (!used[j]) //if false
		{
			used[j]=true;
			// if mat[j] is zero, not call crosspath.
			//store j's previous point into mat, 
			//crosspath(mat[j]) actually is a reserve process. 
			//it is the core of this algorithm
			if (mat[j]==0 || crosspath(mat[j]))
			{
				mat[j]=k;
				cout << "match from " << k << " to " << j << endl; 
				return true;
			}
		}
	}
	return false;
}
 
void hungary()
{
       //n1 is number of vertex
	for (long i=1;i<=n1;i++)
	{
		if (crosspath(i))
			match++;
		memset(used,0,sizeof(used));
	}
	cout << "at last " << match << endl;

	for (int i = 1; i < 11; ++i)
		{
		cout << i << " is " << mat[i] << endl;
		}
}
 
void print()
{
	
	fclose(fi);
	
}
 
int main()
{
	readfile();
	cout << "read is OK" << endl;
	hungary();
	print();
	return 0;
}
