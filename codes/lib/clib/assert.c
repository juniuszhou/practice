#include <assert.h>
#include <errno.h>

int main()
{
assert(errno == 0);
int i;
errno = i;
return i;
}




