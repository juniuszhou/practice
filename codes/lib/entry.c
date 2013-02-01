#include "minicrt.h"

extern int main(int argc, char * argv[]);
void exit(int);
static void crt_fatal_error(const char * msg)
{
exit(1);
}

void mini_crt_entry(void)
{
int ret;
int argc;
char ** argv;
char* ebp_reg = 0;
asm();
}


