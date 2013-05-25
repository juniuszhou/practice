// candidate.cpp
#pragma warning (disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <list>
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

// 属性
struct Attribute
{
char name[A_CHAR_MAX];             // 属性名称
int num;                           // 属性值个数
char att[A_VALUE_MAX][A_CHAR_MAX]; // 属性值
};

// 假设
struct Hypothesis
{
int num;                          // 属性个数
Attribute an[A_NUM_MAX];          // 属性集合
};

// 假设值
struct HypoValue
{
int value[A_NUM_MAX];
};

// 样本
struct Sample
{
HypoValue ev;                    // 假设
int result;                      // 正例/反例
};

Hypothesis g_Hypo;                   // 假设集合
Sample g_sa[SAMPLES_MAX];            // 样本空间
int g_sn;                            // 样本数
list<HypoValue*> g_G;                // 一般边界G
list<HypoValue*> g_S;                // 特殊边界S

bool ReadHypothesis(const char* filename)
{

FILE * file;
file = fopen( filename , "r");

int i,j,k;
fscanf(file, "%d\n", &g_Hypo.num);
for (i=0; i<g_Hypo.num ; i++)
{
   fscanf(file, "%s%d\n", g_Hypo.an[i].name, &k);
   g_Hypo.an[i].num = k;
   for (j=0; j<k; j++)
   {
    fscanf(file, "%s", g_Hypo.an[i].att[j]);
   }
   fscanf(file, "\n");
}
fclose(file);
return true;
}


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


void InitGandS()
{
HypoValue* evg = new HypoValue();
HypoValue* evs = new HypoValue();
for (int i=0; i<g_Hypo.num; i++)
{
   evg->value[i] = ALL;
   evs->value[i] = NUL;
}
//at the begin, each list just include one node.
g_G.push_back(evg);//for G, init all value is ALL
g_S.push_back(evs);//for S, init all value is NUL
}

// ps is new sample, h is hypothesis already made
//so if h's are ALL, then return true since it includes
//all positive case.
bool PositiveisConsistent(HypoValue h, HypoValue ps)
{
for (int i=0; i<g_Hypo.num; i++)
{
   if (h.value[i]==ALL)
    continue;
   else if (h.value[i]!=ps.value[i])
    return false;
}
return true;
}

//ns is a negative sample.
//h is an item in special hypothesis
bool NagativeisConsistent(HypoValue h, HypoValue ns)
{
for (int i=0; i<g_Hypo.num; i++)
{
// if at least one attribute is different, or not coverred
// then we think the negative case is consistent, because we
// can recognize it.
   if (h.value[i]!=ALL && h.value[i]!=ns.value[i])
    return true;
}
return false;
}

// G的某个成员是否比h更一般
bool GMemberMoreGeneral(HypoValue h)
{
int i;
list<HypoValue*>::iterator it;
HypoValue mem;
for (it=g_G.begin(); it!=g_G.end(); it++)
{
   mem = **it;
   for (i=0; i<g_Hypo.num; i++)
   {
    if (mem.value[i]==ALL && h.value[i]==ALL)
     continue;
    else if (mem.value[i]==h.value[i])
     continue;
    else if (mem.value[i]!=ALL && h.value[i]==ALL)
     break;
    else if (mem.value[i]==ALL && h.value[i]!=ALL)
     continue;
    else
     break;
   }
   if (i==g_Hypo.num)
    return true;
}
return false;
}

// 把s的所有的极小泛化式h加入到S中，并且满足h与d一致，而且G的某个成员比h更一般
//s is a sample in most special hypo, d is current positive case
void MiniGeneral(HypoValue s, HypoValue d)
{
HypoValue* h = new HypoValue();

//for every attribute, find more general like merge operation
for (int i=0; i<g_Hypo.num; i++)
{
   if (s.value[i]==NUL)
    h->value[i] = d.value[i];
   else if (s.value[i]==ALL)
    h->value[i] = ALL;
   else if (s.value[i]!=d.value[i])
    h->value[i] = ALL;
   else
    h->value[i] = d.value[i];
}

//if in general hypothesis set, there is an item more general than h
//then push it in special hypothesis.
if (GMemberMoreGeneral(*h))
   g_S.push_front(h);
else
   delete h;
}

// 从S中移去所有这样的假设：它比S中另一个假设更一般
void RemoveMoreGeneralFromS()
{
bool r1,r2;
int i;
HypoValue e1, e2;
list<HypoValue*>::iterator it;
list<HypoValue*>::iterator next;
list<HypoValue*>::iterator temp;
for (it=g_S.begin(); it!=g_S.end();)
{
   e1 = * *it;
   next = it;
   r1 = r2 = false;
   for (next++; next!=g_S.end();)
   {
    e2 = * *next;
    r1 = r2 = false;
    for (i=0; i<g_Hypo.num; i++)
    {
     if (e1.value[i]==ALL && e2.value[i]==ALL)
      continue;
     else if (e1.value[i]==e2.value[i])
      continue;
     else if (e1.value[i]==ALL && e2.value[i]!=ALL)
     {
      r1 = true;
      if (r2) break;
     }
     else if (e1.value[i]!=ALL && e2.value[i]==ALL)
     {
      r2 = true;
      if (r1) break;
     }
     else
     {
      r1 = r2 = true;
      break;
     }
    }
    if (r1==true && r2==false)
     break;
    if (r1==false)
    {
     temp = next;
     next++;
     g_S.remove(*temp);
    }
    else
     next++;
   }
   if (r1==true && r2==false)
   {
    temp = it;
    it++;
    g_S.remove(*temp);
   }
   else
    it++;
}
}

// if in special hypothesis, there is one more special
bool SMemberMoreSpecial(HypoValue h)
{
int i;
list<HypoValue*>::iterator it;
HypoValue mem;
for (it=g_S.begin(); it!=g_S.end(); it++)
{
   mem = **it;
   for (i=0; i<g_Hypo.num; i++)
   {
    if (mem.value[i]==ALL && h.value[i]==ALL)
     continue;
    else if (mem.value[i]==h.value[i])
     continue;
    else if (mem.value[i]!=ALL && h.value[i]==ALL)
     continue;
    else if (mem.value[i]==ALL && h.value[i]!=ALL)
     break;
    else
     break;
   }
   if (i==g_Hypo.num)
    return true;
}
return false;
}

// 把g的所有的极小特殊化式h加入到G中，其中h满足h与d一致，而且S的某个成员比h更特殊
//d is sample ,   g in most general list
void MiniSpecial(HypoValue g, HypoValue d)
{
int i,j;
for (i=0; i<g_Hypo.num; i++)
{
   for (j=1; j<=g_Hypo.an[i].num; j++)
   {
    if (j!=d.value[i])
    {
     //give the same value as g
     HypoValue* h = new HypoValue(g);
     //cout << j <<  " " << h->value[0] << " " << endl;
     //replace the value with j
     h->value[i] = j;
     //in special hypo, there is more special
     // and insert it into general hypo, later more general one will be
     //removed from general hypo
     if (SMemberMoreSpecial(*h))
      g_G.push_front(h);
     else
      delete h;
    }
   }
}
}

// 从G中移去所有这样的假设：它比G中另一个假设更特殊
void RemoveMoreSpecialFromG()
{
bool r1,r2;
int i;
HypoValue e1, e2;
list<HypoValue*>::iterator it;
list<HypoValue*>::iterator next;
list<HypoValue*>::iterator temp;
for (it=g_G.begin(); it!=g_G.end();)
{
   e1 = * *it;
   next = it;
   r1 = r2 = false;
   for (next++; next!=g_G.end();)
   {
    e2 = * *next;
    r1 = r2 = false;
    for (i=0; i<g_Hypo.num; i++)
    {
     if (e1.value[i]==ALL && e2.value[i]==ALL)
      continue;
     else if (e1.value[i]==e2.value[i])
      continue;
     else if (e1.value[i]!=ALL && e2.value[i]==ALL)
     {
      r1 = true;
      if (r2) break;
     }
     else if (e1.value[i]==ALL && e2.value[i]!=ALL)
     {
      r2 = true;
      if (r1) break;
     }
     else
     {
      r1 = r2 = true;
      break;
     }
    }
    if (r1==true && r2==false)
     break;
    if (r1==false)
    {
     temp = next;
     next++;
     g_G.remove(*temp);
    }
    else
     next++;
   }
   if (r1==true && r2==false)
   {
    temp = it;
    it++;
    g_G.remove(*temp);
   }
   else
    it++;
}
}

void outputCur()
{
    list<HypoValue*>::iterator it;
    list<HypoValue*>::iterator temp;
    int i;

       for (it=g_S.begin(); it!=g_S.end(); it++)
    {
       HypoValue s = **it;
       printf("<");
       for (i=0; i<g_Hypo.num-1; i++)
       {
        if (s.value[i]==ALL)
         printf("?, ");
        else if (s.value[i]==NUL)
         printf("O, ");
        else
         printf("%s, ", g_Hypo.an[i].att[s.value[i]-1]);
       }
       if (s.value[i]==ALL)
        printf("?>\n");
       else if (s.value[i]==NUL)
        printf("O>\n");
       else
        printf("%s>\n", g_Hypo.an[i].att[s.value[i]-1]);
    }
    cout << "************************" << endl;
    
    for (it=g_G.begin(); it!=g_G.end(); it++)
    {
       HypoValue s = **it;
       printf("<");
       for (i=0; i<g_Hypo.num-1; i++)
       {
        if (s.value[i]==ALL)
         printf("?, ");
        else if (s.value[i]==NUL)
         printf("O, ");
        else
         printf("%s, ", g_Hypo.an[i].att[s.value[i]-1]);
       }
       if (s.value[i]==ALL)
        printf("?>\n");
       else if (s.value[i]==NUL)
        printf("O>\n");
       else
        printf("%s>\n", g_Hypo.an[i].att[s.value[i]-1]);
    }

}
int main(int arc, char** argv)
{
// 读取假设和样本
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

// 初始化G和S
InitGandS();
list<HypoValue*>::iterator it;
list<HypoValue*>::iterator temp;
int i;
for (i=0; i<g_sn; i++)
{
   if (g_sa[i].result==YES)   //positive case
   {
    
    for (it=g_G.begin(); it!=g_G.end(); it++)
    {
    //compare positive case with general hypothsis, which init 
    // as most general, all attributes given ALL value.
    //
     if (!PositiveisConsistent(**it, g_sa[i].ev))
     {
      temp = it;
      it++;
      //remove this item from list
      g_G.remove(*temp);
     }
    }
    // compare positive case with special hypothesis.
    //which init as all NULL values.
    for (it=g_S.begin(); it!=g_S.end();)
    {
    // if consistent, means the hypothesis already include it.
    // else means this case conflict with item in special hypothesis
    // find the mini general
     if (!PositiveisConsistent(**it, g_sa[i].ev))
     {
     //combine both conflicted case, and to check if in general hypothesis,
     //there is item more general than combined case. if yes, all combines
     //item into special hypothesis
      MiniGeneral(**it, g_sa[i].ev);
      temp = it;
      it++;
      //since this item conflict with a positive case, so remove it
      g_S.remove(*temp);        // 从S中移去s

      //because combined item may added into special hypothesis, which may
      //more general than already existed item, so we need remove it.
      RemoveMoreGeneralFromS();
     }
     else
      it++;
    }
   }
   else              // 反例时
   {  
    // 从S中移去所有与d不一致的假设
    for (it=g_S.begin(); it!=g_S.end(); it++)
    {
     if (!NagativeisConsistent(**it, g_sa[i].ev))
     {
      temp = it;
      it++;
      //remove it from special hypothesis.
      g_S.remove(*temp);
     }
    }
    // 对G中每个与d不一致的假设g
    for (it=g_G.begin(); it!=g_G.end();)
    {
    //for each item in general.
     if (!NagativeisConsistent(**it, g_sa[i].ev))
     {
     //not consistent means an item in general hypo take it as positive case.
      MiniSpecial(**it, g_sa[i].ev);
      temp = it;
      it++;
      //remove it, of course. since it is wrong.
      g_G.remove(*temp);    // 从G中移去g
      //since several may added in, so need remove more special ones, just
      //keep most general cases is enough.
      RemoveMoreSpecialFromG();
     }
     else
      it++;
    }
   }


outputCur();

printf("-------------------------------- \n");
cout << i << endl;
//getchar();

}
// 输出S
printf("over \n");


// 释放空间
g_S.erase(g_S.begin(), g_S.end());
g_G.erase(g_G.begin(), g_G.end());

getchar();
return 0;
}

