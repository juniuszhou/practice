/*
http://yanpol.blog.163.com/blog/static/48170806200982282820314/
*/

#include <iostream>
#include <string>
#include <algorithm>


using namespace std;

#include <stdio.h>

#include "DataStructure.h"

union {
  float a;
  unsigned int b;
} ex;

struct float_32_format {
  unsigned int fraction: 23;    /* 有效数位 */
  unsigned int exp: 8;        /* 指数位 */
  unsigned int sign: 1;        /* 符号位 */
};                /* 倒序表示 */

void analysis(float val)
{
  struct float_32_format *format;

  printf("--- 开始分析浮点数 %f\n",val);

  ex.a=val;
  printf("-- 单精度浮点数存储的4个字节,10进制表示: %u\n",ex.b);
  printf("-- 单精度浮点数存储的4个字节,16进制表示: 0x%X\n",ex.b); /* 妙用union */

  format=(struct float_32_format*)(&ex.a); /* ex.a或ex.b皆可 */
  printf("-- sign: %u\n",format->sign);
  printf("-- exp: %u\n",format->exp);
  printf("-- fraction: %u ( 0x%X )\n",format->fraction,format->fraction);
 
  printf("\n");
}

class grand
{
public:
	virtual void output()=0;
	
};

class parent: public grand
{
	public:
		void output(){cout << "parent" << endl;};

};

class child : public parent
{
	public:
		void output(){cout << "child" << endl;};

};
int main()
{

grand* newGrand = new child;
newGrand->output();
return 0;


string theStr = "hello / replace / ok";
string sedStr = theStr;
string::iterator it = sedStr.begin();
	sedStr.erase(it);
cout << sedStr << endl;

int i;
int & ref = i;
cout << (unsigned int)(&ref) << endl;
return 0;

//cin >> theStr;
//cout << endl << theStr << endl;

//string::size_type pos = theStr.find("//");

//cout << theStr.find("//") << endl;

//string_replace(theStr,"//","/");

/*
string::size_type pos = theStr.find("//");

if (string::npos  !=  pos )
{
	theStr.replace(pos,2,"/");
}
cout << theStr << endl;
*/


/*
myList * theMyList = new myList();
myList * secList = new myList(*theMyList);
theMyList->length = 9;
*secList = *theMyList;
cout << secList->length << endl;
cout << (theMyList == secList) << endl;
*/

  /*print float memory
  float f1 = 0.0f;    
while ( f1 < 1000)
{
 cin >> f1;
  analysis(f1);
}*/

  return 0;
}



