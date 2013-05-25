// C4.5_test.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <stdio.h>
#include <math.h>
#include "malloc.h"
#include <stdlib.h>
const int MAX = 10;
int** iInput;
int i = 0;//??
int j = 0;//??
void build_tree(FILE *fp, int* iSamples, int* iAttribute,int ilevel);//????
int choose_attribute(int* iSamples, int* iAttribute);//???????????test_attribute
double info(double dTrue,double dFalse);//??????
double entropy(double dTrue, double dFalse, double dAll);//??
double splitinfo(int* list,double dAll);
int check_samples(int *iSamples);//??samples?????????
int check_ordinary(int *iSamples);//???????
int check_attribute_null(int *iAttribute);//??attribute????
void get_attributes(int *iSamples,int *iAttributeValue,int iAttribute);


int _tmain(int argc, _TCHAR* argv[])
{
 FILE *fp;
 FILE *fp1;
 char iGet;
 int a = 0;
 int b = 0;//a,b?????
 int* iSamples;
 int* iAttribute;
 fp = fopen("c:\\input.txt","r");
 if (NULL == fp)
 {
  printf("error\n");
  return 0;
 }
 iGet = getc(fp);

 //the first line is all attributes.
 while (('\n' != iGet)&&(EOF != iGet))
 {
  if (',' == iGet)
  {
   i++;
  }
  iGet = getc(fp);
 }
 i++;
 
 iAttribute = (int *)malloc(sizeof(int)*i);

 //bug?
 for (int k = 0; k<i; k++)
 {
  iAttribute[k] = (int)malloc(sizeof(int));
  iAttribute[k] = 1;
 }
 while (EOF != iGet)
 {
  if ('\n' == iGet)
  {
   j++;
  }
  iGet = getc(fp);
 }
 j++;
 
 iInput = (int **)malloc(sizeof(int*)*j);
 iSamples = (int *)malloc(sizeof(int)*j);
 for (a = 0;a < j;a++)
 {
  iInput[a] = (int *)malloc(sizeof(int)*i);
  iSamples[a] = (int)malloc(sizeof(int));
  iSamples[a] = a;
 }
 a = 0;
 fclose(fp);
 fp=fopen("c:\\input.txt","r");
 iGet = getc(fp);
 while(EOF != iGet)
 {
  if ((',' != iGet)&&('\n' != iGet))
  {
   iInput[a][b] = iGet - 48;
   b++;
  }
  if (b == i)
  {
   a++;
   b = 0;
  }
  iGet = getc(fp);
 }
 
 fp1 = fopen("d:\\output.txt","w");
 build_tree(fp1,iSamples,iAttribute,0);
 fclose(fp);
 return 0;
}

void build_tree(FILE * fp, int* iSamples, int* iAttribute,int level)//
{
 int iTest_Attribute = 0;
 int iAttributeValue[MAX];
 int k = 0;
 int l = 0;
 int m = 0;
 int *iSamples1;
 for (k = 0; k<MAX; k++)
 {
  iAttributeValue[k] = -1;
 }
 if (0 == check_samples(iSamples))
 {
  fprintf(fp,"result: %d\n",iInput[iSamples[0]][i-1]);
  return;
 }
 if (1 == check_attribute_null(iAttribute))
 {
  fprintf(fp,"result: %d\n",check_ordinary(iSamples));
  return;
 }
 iTest_Attribute = choose_attribute(iSamples,iAttribute);
 iAttribute[iTest_Attribute] = -1;
 get_attributes(iSamples,iAttributeValue,iTest_Attribute);
 k = 0;
 while ((-1 != iAttributeValue[k])&&(k < MAX))
 {
  l = 0;
  m = 0;
  while ((-1 != iSamples[l])&&(l < j))
  {
   if (iInput[iSamples[l]][iTest_Attribute] == iAttributeValue[k])
   {
    m++;
   }
   l++;
  }
  iSamples1 = (int *)malloc(sizeof(int)*(m+1));
  l = 0;
  m = 0;
  while ((-1 != iSamples[l])&&(l < j))
  {
   if (iInput[iSamples[l]][iTest_Attribute] == iAttributeValue[k])
   {
    iSamples1[m] = iSamples[l];
    m++;
   }
   l++;
  }
  iSamples1[m] = -1;
  if (-1 == iSamples1[0])
  {
   fprintf(fp,"result: %d\n",check_ordinary(iSamples));
   return;
  }
  fprintf(fp,"level%d: %d = %d\n",level,iTest_Attribute,iAttributeValue[k]);
  build_tree(fp,iSamples1,iAttribute,level+1);
  k++;
 }
}
int choose_attribute(int* iSamples, int* iAttribute)
{
 int iTestAttribute = -1;
 int k = 0;
 int l = 0;
 int m = 0;
 int n = 0;
 int iTrue = 0;
 int iFalse = 0;
 int iTrue1 = 0;
 int iFalse1 = 0;
 int iDepart[MAX];
 int iRecord[MAX];
 double dEntropy = 0.0;
 double dGainratio = 0.0;
 double test = 0.0;
 
 for (k = 0;k<MAX;k++)
 {
  iDepart[k] = -1;
  iRecord[k] = 0;
 }
 k = 0;
 while ((l!=2)&&(k<(i - 1)))
 {
  if (iAttribute[k] == -1)
  {
   l++;
  }
  k++;
 }
 if (l == 1)
 {
  for (k = 0;k<(k-1);k++)
  {
   if (iAttribute[k] == -1)
   {
    return iAttribute[k];
   }
  }
 }
 for (k = 0;k < (i-1);k++)
 {
  l = 0;
  iTrue = 0;
  iFalse = 0;

  //for each attribute
  if (iAttribute[k] != -1)
  {
   while ((-1 != iSamples[l])&&(l < j))
   {
    if (0 == iInput[iSamples[l]][i-1])
    {
     iFalse++;
    }
    if (1 == iInput[iSamples[l]][i-1])
    {
     iTrue++;
    }
    l++;    
   }
   for (n = 0;n<l;n++)//???????????????
   {
    m = 0;
    while((iDepart[m]!=-1)&&(m!=MAX))
    {
     if (iInput[iSamples[n]][iAttribute[k]] == iDepart[m])
     {
      break;
     }
     m++;
    }
    if (-1 == iDepart[m])
    {
     iDepart[m] = iInput[iSamples[n]][iAttribute[k]];
    }
   }
   while ((iDepart[m] != -1)&&(m!=MAX))
   {
   //statistic true and false samples.
    for (n = 0;n<l;n++)
    {
     if (iInput[iSamples[n]][iAttribute[k]] == iDepart[m])
     {
      if (1 == iInput[iSamples[n]][i-1])
      {
       iTrue1++;
      }
      if (0 == iInput[iSamples[n]][i-1])
      {
       iFalse1++;
      }
      iRecord[m]++;
     }
    }
    
    dEntropy += entropy((double)iTrue1,(double)iFalse1,(double)l);
    iTrue1 = 0;
    iFalse1 = 0;
    m++;
   }
   double dSplitinfo = splitinfo(iRecord,(double)l);
   if (-1 == iTestAttribute)
   {
    iTestAttribute = k;
    dGainratio = (info((double)iTrue,(double)iFalse)-dEntropy)/dSplitinfo;
   }
   else
   {
    test = (info((double)iTrue,(double)iFalse)-dEntropy)/dSplitinfo;
    if (dGainratio < test)
    {
     iTestAttribute = k;
     dGainratio = test;
    }
   }
  }
 }
 return iTestAttribute;
}
double info(double dTrue,double dFalse)
{
 double dInfo = 0.0;
 dInfo = ((dTrue/(dTrue+dFalse))*(log(dTrue/(dTrue+dFalse))/log(2.0))
    +(dFalse/(dTrue+dFalse))*(log(dFalse/(dTrue+dFalse))/log(2.0)))*(-1);
 return dInfo;
}
double entropy(double dTrue, double dFalse, double dAll)
{
 double dEntropy = 0.0;
 dEntropy = (dTrue + dFalse)*info(dTrue,dFalse)/dAll;
 return dEntropy;
}
double splitinfo(int* list,double dAll)
{
 int k = 0;
 double dSplitinfo = 0.0;
 while (0!=list[k])
 {
  dSplitinfo -= ((double)list[k]/(double)dAll)*(log((double)list[k]/(double)dAll));
  k++;
 }
 return dSplitinfo;
}
int check_samples(int *iSamples)
{
 int k = 0;
 int b = 0;
 while ((-1 != iSamples[k])&&(k < j-1))
 {
  if (iInput[k][i-1] != iInput[k+1][i-1])
  {
   b = 1;
   break;
  }
  k++;
 }
 return b;
}
int check_ordinary(int *iSamples)
{
 int k = 0;
 int iTrue = 0;
 int iFalse = 0;
 while ((-1 != iSamples[k])&&(k < i))
 {
  if (0 == iInput[iSamples[k]][i-1])
  {
   iFalse++;
  }
  else
  {
   iTrue++;
  }
  k++;
 }
 if (iTrue >= iFalse)
 {
  return 1;
 }
 else
 {
  return 0;
 }
}
int check_attribute_null(int *iAttribute)
{
 int k = 0;
 while (k < (i-1))
 {
  if (-1 != iAttribute[k])
  {
   return 0;
  }
  k++;
 }
 return 1;
}
void get_attributes(int *iSamples,int *iAttributeValue,int iAttribute)
{
 int k = 0;
 int l = 0;
 while ((-1 != iSamples[k])&&(k < j))
 {
  l = 0;
  while (-1 != iAttributeValue[l])
  {
   if (iInput[iSamples[k]][iAttribute] == iAttributeValue[l])
   {
    break;
   }
   l++;
  }
  if (-1 == iAttributeValue[l])
  {
   iAttributeValue[l] = iInput[iSamples[k]][iAttribute];
  }
  k++;
 }
}

