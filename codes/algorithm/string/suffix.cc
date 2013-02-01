#include "stdio.h"
#include "string.h"

#include <iostream>
#include <string>
//using namespace std;

#define maxn 2004
#define F(x) ((x)/3+((x)%3==1?0:tb))
#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)

int wa[maxn],wb[maxn],wv[maxn],ws[maxn];

//if top 3 letters are the same
int c0(int *r,int a,int b)
{return r[a]==r[b]&&r[a+1]==r[b+1]&&r[a+2]==r[b+2];}

// if top 3 letters bigger
int c12(int k,int *r,int a,int b)
{if(k==2) return r[a]<r[b]||r[a]==r[b]&&c12(1,r,a+1,b+1);
 else return r[a]<r[b]||r[a]==r[b]&&wv[a+1]<wv[b+1];}
 
void lsort(int *r,int *a,int *b,int n,int m)
{
     int i;
     for(i=0;i<n;i++) wv[i]=r[a[i]];
     for(i=0;i<m;i++) ws[i]=0;
     for(i=0;i<n;i++) ws[wv[i]]++;
     for(i=1;i<m;i++) ws[i]+=ws[i-1];
     for(i=n-1;i>=0;i--) b[--ws[wv[i]]]=a[i];
     return;
}
// dc3(r,sa,n+1,128);
void dc3(int *r,int *sa,int n,int m)
{
     int i,j,*rn=r+n,*san=sa+n,ta=0,tb=(n+1)/3,tbc=0,p;
     r[n]=r[n+1]=0;
	 
     for(i=0;i<n;i++) if(i%3!=0) wa[tbc++]=i;
	 
     lsort(r+2,wa,wb,tbc,m);
     lsort(r+1,wb,wa,tbc,m);
     lsort(r,wa,wb,tbc,m);
	 
     for(p=1,rn[F(wb[0])]=0,i=1;i<tbc;i++)
     rn[F(wb[i])]=c0(r,wb[i-1],wb[i])?p-1:p++;
	 
     if(p<tbc) dc3(rn,san,tbc,p);
     else for(i=0;i<tbc;i++) san[rn[i]]=i;
	 
     for(i=0;i<tbc;i++) if(san[i]<tb) wb[ta++]=san[i]*3;
     if(n%3==1) wb[ta++]=n-1;
	
     lsort(r,wb,wa,ta,m);
	 
     for(i=0;i<tbc;i++) wv[wb[i]=G(san[i])]=i;
     for(i=0,j=0,p=0;i<ta && j<tbc;p++)
	 	
     sa[p]=c12(wb[j]%3,r,wa[i],wb[j])?wa[i++]:wb[j++];
	 
     for(;i<ta;p++) sa[p]=wa[i++];
	 
     for(;j<tbc;p++) sa[p]=wb[j++];
	 
     return;
}
int rank[maxn],height[maxn];
void calheight(int *r,int *sa,int n)
{
     int i,j,k=0;
     for(i=1;i<=n;i++) rank[sa[i]]=i;
     for(i=0;i<n;height[rank[i++]]=k)
     for(k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
     return;
}
int RMQ[maxn];
int mm[maxn];
int best[20][maxn];
void initRMQ(int n)
{
     int i,j,a,b;
     for(mm[0]=-1,i=1;i<=n;i++)
     mm[i]=((i&(i-1))==0)?mm[i-1]+1:mm[i-1];
     for(i=1;i<=n;i++) best[0][i]=i;
     for(i=1;i<=mm[n];i++)
     for(j=1;j<=n+1-(1<<i);j++)
     {
       a=best[i-1][j];
       b=best[i-1][j+(1<<(i-1))];
       if(RMQ[a]<RMQ[b]) best[i][j]=a;
       else best[i][j]=b;
     }
     return;
}
int askRMQ(int a,int b)
{
    int t;
    t=mm[b-a+1];b-=(1<<t)-1;
    a=best[t][a];b=best[t][b];
    return RMQ[a]<RMQ[b]?a:b;
}
int lcp(int a,int b)
{
    int t;
    a=rank[a];b=rank[b];
    if(a>b) {t=a;a=b;b=t;}
    return(height[askRMQ(a+1,b)]);
}

char st[maxn];
int r[maxn*3],sa[maxn*3];
int main()
{
    int i,n,len,k,ans,w;
	ans = 0;
	/*
	std::string str1;
	std::cin >> str1;
	std::cout << str1 << std::endl;
	*/
    scanf("%s",st);
    len=strlen(st);
    
    for(i=0;i<len;i++){ r[i]=st[i]; printf("%d %c ",i, (char)r[i]); }  
	printf("\n");
    r[len]=1;	
	printf("%d %c ",len,r[len]); 
	printf("\n");
    for(i=0;i<len;i++) {r[i+len+1]=st[len-1-i];printf("%d %c ",(i+len+1),(char)r[i+len+1]); } 
	printf("\n");
    n=len+len+1;     	
    r[n]=0;
    printf("%d %c ",n,r[n]); 
	printf("\n");
	
    dc3(r,sa,n+1,128);
    
    calheight(r,sa,n);
    for(i=1;i<=n;i++) 
	std::cout << (char)r[i] << " " << sa[i] << std::endl;	
	
    for(i=1;i<=n;i++) 
    {RMQ[i]=height[i];
    	std::cout << RMQ[i] << " ";
    }
    
    initRMQ(n);
    
    for(i=0;i<len;i++)
    {
      k=lcp(i,n-i);
      if(k*2>ans) ans=k*2,w=i-k;
      k=lcp(i,n-i-1);
      if(k*2-1>ans) ans=k*2-1,w=i-k+1;
    }
    st[w+ans]=0;
    printf("%s\n",st+w);
    return 0;
}
