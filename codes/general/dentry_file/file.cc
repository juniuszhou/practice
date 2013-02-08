#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <iostream>
#include "dirent.h"
using namespace std;

int main()
{
int fd,size;
fd = open("zj.txt",O_RDWR);
char s[100];
size = 2;
read(fd,s,size);
lseek(fd,2,SEEK_CUR);
cout << s << endl;
read(fd,s,20);
close(fd);
cout << s << endl;
return 1;




}
