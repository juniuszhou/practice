/*
g++ -O2 -DNDEBUG c_queue.cc -ltbb -lrt 
*/

#include "tbb/concurrent_queue.h"
#include <iostream>
using namespace std;
using namespace tbb;

int main( ) {
concurrent_queue<int> queue;

for( int j=0; j<10; ++j ){
    queue.push(j);
    //cout << j << endl;
}

//must use unsafe_begin and unsafe_end if just one thread access to queue.
concurrent_queue<int>::const_iterator i(queue.unsafe_begin());
for(; i != queue.unsafe_end( ); ++i )
{
cout << *i;
//cout << endl;

}
cout << endl;
int k;
//pop_if_present not used anymore
//pop is blocking version, and try_pop is no_blocking
while (queue.try_pop(k))
    cout << k << endl;
return 0;

}


