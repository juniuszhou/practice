
#include <stdio.h>

//#include <setjmp.h>
struct array100
{
int data[100];
};

//how to define a int array type in c
typedef int jmp_buf[100];

// a simple implementation of setjmp
/**/
#define _JBFP 1
#define _JBOFF 4
#define _JBMOV 60

static void dummy(int a,int b,int c,int d,
				 int e,int f,int g, int h, int i, int j)
{
}

//return the stack frame pointer
int getfp()
{
int arg;
arg = 23;
int addr = (int)(&arg + _JBFP);
int k = NULL;
k = (int)((int*)addr);

printf("framepointer is %x\n", addr);
printf("framepointer are %x\n", k);

return ((int)(&arg + _JBFP));
}

int setjmp(jmp_buf env)
{
register int a=0,b=0,c=0,d=0,e=0;
register int f=0,g=0,h=0,i=0,j=0;
int t = 9;
printf("setjmp is %x \n",(int)&t);
	
//if (a) dummy(a,b,c,d,e,f,g,h,i,j);
env[1] = getfp();

//destination is global variable env array's second item's address
//origin is framepointer we just get via cally getfp
memcpy((char*)&env[2],(char*)env[1]+_JBOFF,_JBMOV);
return 0;
}


//define a global variable to store the process's snapshot
//actually jmp_buf is an array, so the parameter is pass-by-reference
jmp_buf env; 

int main()
{
   
  int i;
  printf(" length is %d \n",sizeof(int *));
  //getfp();

  //put current process's snapshot, a lot of registers' value into an array.
  //if set successfully, then return 0  
  i = setjmp(env);

  /*
  printf("i = %d\n", i);
  if (i != 0) 
  	{
  		printf("now i is not zero \n");
  		exit(0);  
  	}
  longjmp(env, 2);  
  printf("Does this line get printed \n");*/
  return 1;
}




