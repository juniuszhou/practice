#include <iostream>
#include <setjmp.h>


using namespace std;

static void f1(int, int, int, int);
static void f2(void);
static void f3(void);

static jmp_buf jmpbuffer;
static int     globval;

int
main(void)
{
     int             autoval;
     register int    regival;
     volatile int    volaval;
     static int      statval;

     globval = 1; autoval = 2; regival = 3; volaval = 4; statval = 5;

     if (setjmp(jmpbuffer) != 0)
	 	{
	 	cout << " i am in setjump  " << endl;
	 	 cout <<globval << autoval<< regival << volaval << statval <<endl;
	 	f3();
		return 0;
     	}
     /*
      * Change variables after setjmp, but before longjmp.
      */
     globval = 95; autoval = 96; regival = 97; volaval = 98;
     statval = 99;

     f1(autoval, regival, volaval, statval); /* never returns */

	 cout <<globval << autoval<< regival << volaval << statval <<endl;
	 
        return 0;
}

static void
f1(int i, int j, int k, int l)
{
    cout << "in f1():\n";
    cout << i << j<< k << l << endl;
    f2();
}
static void
f2(void)
{
    longjmp(jmpbuffer, 1);
}
static void
f3(void)
{
    cout << " i am f3  " << endl;
	
	
}


