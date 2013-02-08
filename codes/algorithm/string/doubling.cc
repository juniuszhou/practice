#include "stdio.h"
#include <string>

#include <vector>
#include <iostream>

using namespace std;

#define maxn 2004

//int wa[maxn],wb[maxn],wv[maxn],ws[maxn];

    int cmp(int *r,int a,int b,int l)
    {return r[a]==r[b]&&r[a+l]==r[b+l];}

void newDa(vector<int> & strOrigin, vector<int> & saVec)
{
	vector<int> wsVec;
	vector<int> xVec;
	
	int i;       
	xVec = strOrigin;
	for (i = 0; i < 128; i++)
		wsVec.push_back(0);
	
      for (vector<int>::iterator ite = strOrigin.begin();ite< strOrigin.end();ite++)
      	{
	  	
	      wsVec[*ite]++;
		cout << *ite << " ";
      	}
      cout << endl;
	for (vector<int>::iterator ite = wsVec.begin();ite< wsVec.end();ite++)
      	{
      	       cout << *ite << " ";
		
      	}
	  cout << endl;
	for (vector<int>::iterator ite = wsVec.begin() + 1;ite< wsVec.end();ite++)
      	{
      	      
		*ite += *(ite-1);
      	}
	cout << endl;
	for (vector<int>::iterator ite = wsVec.begin();ite< wsVec.end();ite++)
      	{
      	       cout << *ite << " ";
		
      	}
	cout << endl << strOrigin.size() << endl  ;

	i = 0;
	for (i = strOrigin.size() - 1; i >=0; i--)
	{
	      cout << (char)strOrigin[i]  << " " << wsVec[strOrigin[i]] << " ";
		saVec[i] = wsVec[strOrigin[i]] ;
		cout << i << " ";
	}
	cout << endl;
	for (i = 0;i < saVec.size();i++)
	{
		cout << saVec[i] << " ";
	}
	cout << endl;
	
	
}
/*    void da(int *r,int *sa,int n,int m)
    {
        int i,j,p,*x=wa,*y=wb,*t; 
        for(i=0;i<m;i++) ws[i]=0; 
        for(i=0;i<n;i++) ws[x[i]=r[i]]++; 
        for(i=1;i<m;i++) ws[i]+=ws[i-1]; 
        for(i=n-1;i>=0;i--) {
			sa[--ws[x[i]]]=i;
			printf ("%d %d %d %d \n",i,x[i],ws[x[i]],sa[ws[x[i]]]);}


for(j=1,p=1;p<n;j*=2,m=p) 
        { 
            for(p=0,i=n-j;i<n;i++) y[p++]=i; 
            for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j; 
            for(i=0;i<n;i++) wv[i]=x[y[i]]; 
            for(i=0;i<m;i++) ws[i]=0; 
            for(i=0;i<n;i++) ws[wv[i]]++; 
            for(i=1;i<m;i++) ws[i]+=ws[i-1]; 
            for(i=n-1;i>=0;i--) sa[--ws[wv[i]]]=y[i]; 
            for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++) 
                x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++; 
        } 
        return; 
    }*/
		
	
int main()
{
  vector<int> saVec;
	vector<int> oriVec;
	
	string str1;
	cin >> str1;
	for (string::iterator ite = str1.begin();ite< str1.end();ite++)
	{
		oriVec.push_back(int(*ite));
	  saVec.push_back(int(*ite));
	}
	
	for (vector<int>::iterator ite = oriVec.begin();ite< oriVec.end();ite++)
		cout << *ite << " ";
	cout << endl;
		
	/*for (i = 0; i < 128; i++)
		saVec.push_back(0);
	
      for (vector<int>::iterator ite = saVec.begin();ite< saVec.end();ite++)
	  	cout << *ite << " ";*/
	  	
	newDa(oriVec,saVec);
	  cout << endl;

return 1;
		}
