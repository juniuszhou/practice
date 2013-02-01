#include <iostream>
#include <climits>
#include <stdio.h>

using namespace std;

#define BUF 100
int f[BUF][BUF];  //preflow value
int c[BUF][BUF]; //flow can be pass

struct Edge{
	int v;
	Edge *next; //next edge
};

struct Node{
	int h;  //high
	int ef; //flow
	Edge *firste; //first edge
};

Node graph[BUF]; //define all static Nodes
Edge *current[BUF];

struct List{
	int n;
	List *next;
};//linked table

List *L;
int N;  //vertex number
int S,T;
/*
sample input:
6 1 6 10
1 2 16
1 4 13
2 4 10
4 2 4
2 3 12
3 4 9
4 5 14
5 3 7
3 6 20
5 6 4
the first line represent |V|=6,S=1,T=6,|E|=10.
then the next ten lines represent 10 edges of the graph.
*/
void init_graph()
{
	int eN; 	   
	//vertex number, source,dest,edge number
	scanf("%d%d%d%d",&N,&S,&T,&eN);
	
	for(int i=1;i<N;i++)
	  graph[i].firste = NULL;
		
	for(int i=1;i<=eN;i++){ 		   
		int s,e;	
		//source,dest id
		scanf("%d%d",&s,&e);

		//if not init yet
		if(c[e][s]==0){
			Edge *e1 = new Edge();
			Edge *e2 = new Edge();			  
			e1->v = s;
			e2->v = e;			
			e1->next = graph[e].firste;
			e2->next = graph[s].firste;
			graph[e].firste = e1;
			graph[s].firste = e2;
		}			 
		scanf("%d",&c[s][e]);//flow can be passed		
	}
}
//to print the debug information 

void print()
{
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++)
			printf("%d ",c[i][j]);		
		printf("\n");
	}
	printf("\n");
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++)
			printf("%d ",f[i][j]);		
		printf("\n");
	}
	printf("\n");
	List *p = L->next;
	while(p!=NULL){
		printf("%d ",p->n);
		p = p->next;
	}
	printf("\n");
	for(int i=1;i<=N;i++)
		printf("%d ",graph[i].ef);
	printf("\n\n");
}

void init_preflow()
{
	for(int i=0;i<N;i++){
		graph[i].h = 0;
		graph[i].ef = 0;
	}
	
	fill_n(&f[0][0],BUF*BUF,0); 	   
	graph[S].h = N;

	//generate preflow
	for(Edge *p=graph[S].firste;p!=NULL;p=p->next){ 
		f[S][p->v] = c[S][p->v];
		f[p->v][S] = -1*c[S][p->v];
		graph[p->v].ef = c[S][p->v];
		graph[S].ef -= c[S][p->v];
	}
}

void init_list()
{
	L = new List();
	List *p = L;		
	for(int i=1;i<=N;i++)
		if(i != S && i != T){//don't for source and dest points
			p->next = new List();
			p->next->n = i;
			p = p->next;
		}
	p->next = NULL;
}
			
// the next four functions are the core of the relabel to front algorithm.
	
void push(int u,int v)
{
	if(graph[u].ef>0&&graph[u].h==(graph[v].h+1)){
		int df = c[u][v]-f[u][v];
		df = min(df,graph[u].ef);
		f[u][v] += df;
		f[v][u] = -1*f[u][v];
		graph[u].ef -= df;
		graph[v].ef += df;
	}
}

void relabel(int u)
{
	if(graph[u].ef>0){
		
		int low = INT_MAX;
		bool have = false;
		
		for(Edge *p=graph[u].firste;p!=NULL;p=p->next)
			if(c[u][p->v]-f[u][p->v]>0&&graph[u].h<=graph[p->v].h){ 				
				low = min(low,graph[p->v].h);
				have = true;
			}
		if(have)
			graph[u].h = low+1;
	}
}
			
void discharge(int u)
{
	while(graph[u].ef>0){			 
		Edge *pv = current[u];
		//why we relabel just for pv is NULL
		if(pv == NULL){
			relabel(u);
			current[u] = graph[u].firste;
		}else if(c[u][pv->v]-f[u][pv->v]>0 && graph[u].h==(graph[pv->v].h+1)){
		//if can allow more flow and height is OK, let's push
			push(u,pv->v);
		}else {
			current[u] = pv->next;
		}
	}
}
		
void relabel_front()
{
	init_preflow(); 	   
	init_list();

	//init current vector
	for(int i=1;i<=N;i++)
		if(i != S && i != T)
			current[i] = graph[i].firste;
	
	List *q = L;
	List *p = L->next;
	
	while(p!=NULL){
		
		int oh = graph[p->n].h;
		discharge(p->n);
		
		if(graph[p->n].h>oh){//means it is relabeled
			
			q->next = p->next;
			q = L;
			p->next = q->next;
			q->next = p;
			//move q as head, and p as first node.
		}

		//move forward
		p = p->next;
		q = q->next;
//		print();
	}
}
			
int main()
{
	freopen("rf1.in","r",stdin);
	freopen("rf.out","w",stdout);		 
	init_graph();		 
	relabel_front();		
	printf("%d\n",-1*graph[S].ef);		  
	return 0;
}

