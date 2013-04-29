#include <iostream>
#include <math.h>
using namespace std;

struct point
{
    int x;
    int y;
};

//insert sorting
void sortx(struct point *pm)
{
    for(int i=2;i<=10;i++)
    {
        int xtemp=pm[i].x;
        int ytemp=pm[i].y;
        int j=i-1;
        while(j>0&&pm[j].x>xtemp)
        {
            pm[j+1].x=pm[j].x;
            pm[j+1].y=pm[j].y;
            j--;
        }
        pm[j+1].x=xtemp;
        pm[j+1].y=ytemp;
    }
    return;
}

void sorty(struct point p[],struct point *y)
{
    for(int i=2;i<=10;i++)
    {
        int xtemp=p[i].x;
        int ytemp=p[i].y;
        int j=i-1;
        while(j>0&&p[j].x>xtemp)
        {
            p[j+1].x=p[j].x;
            p[j+1].y=p[j].y;
            j--;
        }
        p[j+1].x=xtemp;
        p[j+1].y=ytemp;
    }
    for(int k=1;k<=10;k++)
    {
        y[k].x=p[k].x;
        y[k].y=p[k].y;
    }
    return;
}

double distance_find(int low,int high,struct point y[],struct point s[])
{
    double shortest;
    if(high-low+1==3)
    {
        int mid=(high+low)/2;
        double d1=(y[high].x-y[low].x)*(y[high].x-y[low].x)+(y[high].y-y[low].y)*(y[high].y-y[low].y);
        d1=sqrt(d1);
        double d2=(y[mid].x-y[low].x)*(y[mid].x-y[low].x)+(y[mid].y-y[low].y)*(y[mid].y-y[low].y);
        d2=sqrt(d2);
        double d3=(y[high].x-y[mid].x)*(y[high].x-y[mid].x)+(y[high].y-y[mid].y)*(y[high].y-y[mid].y);
        d3=sqrt(d3);
        //cout<<"d1"<<d1<<endl;
        //cout<<"d2"<<d2<<endl;
        //cout<<"d3"<<d3<<endl;
        (d1<d2)?shortest=d1:shortest=d2;
        (shortest<d3)?shortest=shortest:shortest=d3;
    }
    else if(high-low+1==2)
    {
        shortest=(y[high].x-y[low].x)*(y[high].x-y[low].x)+
            (y[high].y-y[low].y)*(y[high].y-y[low].y);
    }
    else if(high-low+1==1)
    {
        shortest=0;
    }
    else
    {
        int mid=(high+low)/2;
        int x0=s[mid].x;
        double sl=distance_find(low,mid,y,s);
        double sr=distance_find(mid+1,high,y,s);
        sl<sr?shortest=sl:shortest=sr;
        int k=0;
        struct point T[8];
        
        for(int i=1;i<=10;i++)
        {
            int ju;
            (y[i].x-x0)>0?(ju=y[i].x-x0):(ju=x0-y[i].x);
            if(ju<=shortest)
            {
                k++;
                T[k]=y[i];
            }
        }
        double shorto=2*shortest;
        for(int i=1;i<=k-1;i++)
        {
            int min;
            (i+7)<k?min=i+7:min=k;
            for(int j=i+1;j<=min;j++)
            {
                double di=(T[i].x-T[j].x)*(T[i].x-T[j].x)+(T[i].y-T[j].y)*(T[i].y-T[j].y);
                di=sqrt(di);
                if(di<shorto)
                    shorto=di;
            }
        }
   shortest<shorto?shortest=shortest:shortest=shorto;
    }
    return shortest;
}
int main()
{
        struct point p[11];
        struct point y[11];
        p[1].x=-7;
        p[1].y=3;
        p[2].x=-1;
        p[2].y=1;
        p[3].x=-5;
        p[3].y=7;
        p[4].x=-5;
        p[4].y=-3;
        p[5].x=4;
        p[5].y=1;
        p[6].x=3;
        p[6].y=0;
        p[7].x=2;
        p[7].y=-6;
        p[8].x=5;
        p[8].y=9;
        p[9].x=1;
        p[9].y=9;
        p[10].x=3;
        p[10].y=4;
        for(int c=1;c<11;c++)
            cout<<"The point "<<c<<" is ("<<p[c].x<<","<<p[c].y<<")"<<endl;
        sortx(p);
        sorty(p,y);
        for (int i = 1;i<11;++i)
            cout << p[i].x << " " << p[i].y << endl;
        for (int i = 1;i<11;++i)
            cout << y[i].x << " " << y[i].y << endl;
        for(int c=1;c<11;c++)
            cout<<"After sort of y ,the point "<<c<<" is ("<<y[c].x<<","<<y[c].y<<")"<<endl;
        double shortest=distance_find(1,10,y,p);
        cout<<"The shortest distance of all the points is:"<<shortest<<endl;





        char o;
        cin >> o;
        return 0;

}


