 #include <stdlib.h>
#include <iostream>
#include "sys/types.h"
#include "sys/wait.h"
using namespace std;

int main()
{

pid_t pid;
pid = fork();
if (pid > 0)
{
cout<<"it is parent child is"<<pid<< endl;
exit(1);
}
sleep(3);
cout<<"i ma child "<<getppid()<<endl;

return 1;
}
