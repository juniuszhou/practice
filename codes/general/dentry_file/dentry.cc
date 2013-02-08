#include <iostream>
#include "dirent.h"
using namespace std;

int main()
{
char ai[]="/home/juzhou/practice/codes/py";
DIR *dp = opendir(ai);
struct dirent * dirp = readdir(dp);
while (dirp != NULL)
{
cout<< dirp->d_name << endl;
dirp = readdir(dp);
}
return 1;




}
