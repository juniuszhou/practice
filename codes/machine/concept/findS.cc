
#pragma warning (disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
using namespace std;


#define A_CHAR_MAX 16
#define A_VALUE_MAX 16
#define A_NUM_MAX   32


#define SAMPLES_MAX 256
#define ALL -1
#define NUL -2


#define YES     1
#define NO      0
#define NUKOWN -1

struct Attribute
{
char name[A_CHAR_MAX];
int num;                           
char att[A_VALUE_MAX][A_CHAR_MAX];
};


struct Hypothesis
{
int num;                         
Attribute an[A_NUM_MAX];
};


struct HypoValue
{
int value[A_NUM_MAX];
};


struct Sample
{
HypoValue ev;
int result;                      
};


Hypothesis g_Hypo;                   
Sample g_sa[SAMPLES_MAX];           
int g_sn;                           
HypoValue g_hm;                     


//read how many attributes and its name. 
//and how many possible value for each attribute.
bool ReadHypothesis(const char* filename)
{
FILE * file;
file = fopen( filename , "r");
int i,j,k;
fscanf(file, "%d\n", &g_Hypo.num);
cout << g_Hypo.num << endl;
for (i=0; i<g_Hypo.num ; i++)
{
   fscanf(file, "%s%d\n", g_Hypo.an[i].name, &k);
   g_Hypo.an[i].num = k;
   cout << g_Hypo.an[i].name << " " << k << endl;
   for (j=0; j<k; j++)
   {
    fscanf(file, "%s", g_Hypo.an[i].att[j]);
    cout << g_Hypo.an[i].att[j] << endl;
   }
   fscanf(file, "\n");
}
fclose(file);
return true;
}

//read each attribute's value and result.
bool ReadSamples(const char* filename)
{
FILE * file;
file = fopen( filename , "r");
int i,j;
fscanf(file, "%d\n", &g_sn);
for (i=0; i<g_sn ; i++)
{
   for (j=0; j<g_Hypo.num; j++)
   {
    fscanf(file, "%d", &g_sa[i].ev.value[j]);
   }
   fscanf(file, "%d\n",&g_sa[i].result);
}
fclose(file);
return true;
}


int main(int arc, char** argv)
{
if (!ReadHypothesis(argv[1]))
{
   printf("read Hypothesis file error");
   return 0;
}

if (!ReadSamples(argv[2]))
{
   printf("read samples file error");
   return 0;
}


int i,j;
//init
for (i=0; i<g_Hypo.num; i++)
{
   g_hm.value[i] = NUL;
}

//sample number
for (i=0; i<g_sn; i++)
{
 
   if (g_sa[i].result==YES)
   {
    for (j=0; j<g_Hypo.num; j++)
    {
     if (g_hm.value[j]==NUL)
      g_hm.value[j] = g_sa[i].ev.value[j];
     else if (g_hm.value[j]==ALL)// strcmp(h[j], "?")==0)
      ;
     else if (g_hm.value[j]!=g_sa[i].ev.value[j]) // strcmp(h[j], H[i][j])!=0)
      g_hm.value[j] = ALL; //combine and set a general value
    }
   }
}
printf("start \n");
for (i=0; i<g_Hypo.num-1; i++)
{
   if (g_hm.value[i]==ALL)
    printf("?, ");
   else if (g_hm.value[i]==NUL)
    printf("O, ");
   else
    printf("%s, }}}}}", g_Hypo.an[i].att[g_hm.value[i]-1]);
}

if (g_hm.value[i]==ALL)
   printf("?>\n");
else if (g_hm.value[i]==NUL)
   printf("O>\n");
else
   printf("%s>>>>\n", g_Hypo.an[i].att[g_hm.value[i]-1]);


getchar();
return 0;
}


