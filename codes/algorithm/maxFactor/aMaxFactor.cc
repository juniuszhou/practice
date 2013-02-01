#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

int main(int argc, char * argv[])
{
//suppose i always iffer than j
int i = atoi(argv[1]);
int j  = atoi(argv[2]);
int k = 0;
k = i % j;

if (k == 0)
{
cout << j << endl;
return 0;
}

while ( k > 0 )
{
	i = j;
        j = k;
        k = i % j;
}

if (k == 0)
cout << j << endl;

return 0;
}



