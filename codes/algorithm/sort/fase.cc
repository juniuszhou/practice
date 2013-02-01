#include <iostream>
using namespace std;

int i[10];
void rand12()
{
int u = 1234;
for (int j = 0; j < 10; ++j)
{
    i[j] = u % 7777;
    u += u;
    cout << i[j] << " ";
}
cout << endl;
}

void splitAndSort(int s, int t)
{
if (t <= s)
    return;

int focal = i[s];
int tmps = s;
int tmpt = t;

while (tmps < tmpt)
{
    while (tmps < tmpt)
        {
        if (i[tmpt] >= focal)
            --tmpt;
        else{
            i[tmps] = i[tmpt];
            ++tmps;
            break;}
        }

     while (tmps < tmpt)
        {
        if (focal >= i[tmps])
            ++tmps;
        else{
            i[tmpt] = i[tmps];
            --tmpt;
            break;}
        }
}
i[tmps] = focal;

for (int ii = 0; ii < 10; ++ii)
    cout << i[ii] << " ";
cout <<  endl << tmps  << "  "  << tmpt << "  " << focal << endl;

if (s < (tmps-1))
splitAndSort(s, tmps-1);
if (t > (tmps+1))
splitAndSort(tmps+1,t);
}

int main()
{
rand12();

splitAndSort(0,9);

return 0;
}