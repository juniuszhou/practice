#include <signal.h>
#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


int a(int i)
{
return i+1;
}

 int	 main(void)
	 {
	a(9);
	 exit(0);
	 	}
     

