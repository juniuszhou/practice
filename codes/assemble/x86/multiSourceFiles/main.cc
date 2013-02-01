/*
from this process, we can see g++ follow the same rule for renaming.
fun will become _Z3funv. so they will follow same rule, then we can link
them together.

g++ -c fun.cc
g++ -c main.cc
g++ fun.o main.o -o main
*/
extern int fun();

int main()
{
return fun();
}
