#include <iostream>
#include <memory.h>
#include <stdio.h>
#include <memory.h>

using namespace std;

#define MAXN 202
#define INT_MAX 10000000
int s, t;
int n, np, nc, m;
char str[50];
int c[MAXN][MAXN];
int f[MAXN][MAXN];
int e[MAXN];
int h[MAXN];
void push(int u, int v)
{
    int d = min(e[u], c[u][v] - f[u][v]);
    f[u][v] += d;
    f[v][u] = -f[u][v];
    e[u] -= d;
    e[v] += d;
}
bool relabel(int u)
{
    int mh = INT_MAX;
    for(int i=0; i<n+2; i++)
    {
        if(c[u][i] > f[u][i])
        	{
            if (h[i] < mh)
				mh = h[i];
        	}
    }
    if(mh == INT_MAX)
        return false; //.......u....
        
    h[u] = mh + 1;
	
    for(int i=0; i<n+2; i++)
    {
        if(e[u] == 0) //.........push
            break;
        if(h[i] == mh && c[u][i] > f[u][i]) //push...
            push(u, i);
    }
    return true;
}
void init_preflow()
{
    memset(h, 0, sizeof(h));
    memset(e, 0, sizeof(e));
    h[s] = n+2;
    for(int i=0; i<n+2; i++)
    {
        if(c[s][i] == 0)
            continue;
        f[s][i] = c[s][i];
        f[i][s] = -f[s][i];
        e[i] = c[s][i];
        e[s] -= c[s][i];
    }
}
void push_relabel()
{
    init_preflow();
    bool flag = true; //......relabel..
    while(flag)
    {
        flag = false;
        for(int i=0; i<n; i++)
            if(e[i] > 0)
                flag = flag || relabel(i);
    }
}
int main()
{
    while(scanf("%d%d%d%d", &n, &np, &nc, &m) != EOF)
    {
        s = n; t = n+1;
        memset(c, 0, sizeof(c));
        memset(f, 0, sizeof(f));
        while(m--)
        {
            scanf("%s", &str);
            int u=0, v=0, z=0;
            sscanf(str, "(%d,%d)%d", &u, &v, &z);
            c[u][v] = z;
        }
        for(int i=0; i<np+nc; i++)
        {
            scanf("%s", &str);
            int u=0, z=0;
            sscanf(str, "(%d)%d", &u, &z);
            if(i < np)
                c[s][u] = z;
            else if(i >= np && i < np + nc)
                c[u][t] = z;
        }
        push_relabel();
        printf("%d\n", e[t]);
    }
}
