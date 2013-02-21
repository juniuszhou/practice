#include <time.h>
#include <stdio.h>

int main()
{
	for(int i =0;i<0x00ffffff;++i)
		;
	//clock
	//in old version lib c, CLOCKS_PER_SEC=1,000, current is 1,000,000
	printf("%d \n",CLOCKS_PER_SEC);
	printf("%d \n",clock());

	//time, how many seconds since 1981
	printf("%d \n",time(NULL));

	//gmtime
	time_t aTime;
	aTime = time(NULL);
	struct tm aTm;
	aTm = *gmtime(&aTime);
	//printf("%s \n",gmtime(time(NULL)));

return 0;
}
