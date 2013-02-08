/*
g++ -O2 -DNDEBUG p_sort.cc -ltbb -lrt 
*/

#include "tbb/parallel_sort.h"
#include <math.h>
#include <iostream>

using namespace tbb;
using namespace std;

const int N = 1000;
float a[N];
float b[N];

void SortExample( ) {
for( int i = 0; i < N; i++ ) {
a[i] = sin((double)i);
b[i] = cos((double)i);
}
}

int main()
{
    SortExample();

parallel_sort(a, a + N);
parallel_sort(b, b + N, std::greater<float>( ));

for( int i = 0; i < N; i++ ) {
cout << a[i] << "   " << b[i] << endl;
}
return 1;
}

