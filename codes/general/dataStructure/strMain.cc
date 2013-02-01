#include <iostream>
#include "string.h"
using namespace std;
int main()
{
char a[]="include_source_destination_tlvs_preatt=true";
if (!strncmp(a, "include_source_destination_tlvs_preatt", 38))
cout << "matched " << endl;
return 1;
}
