/*
/home/junius/toolschain/4.4.3/bin/arm-linux-g++ -S instant.cc

if arm can't represent this instant number, arm will use a memory
to store it. 
*/

int main()
{
int i = 0x100000;
return i;
}
