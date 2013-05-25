/*
 * public/prob.c
 * 2004-04-25 by ShanLanshan
 *
 * probability library
 */
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include "public/prob.h"

/*
 * prob_set_seed
 * set random seed
 * -1 for random seed
 */
void prob_set_seed(unsigned int seed)
{
	if (seed == 0)
		seed = (unsigned int)time(NULL);

	printf("Set random seed [%d]\n", seed);
	srand(seed);
}

/*
 * prob_get_number
 * get random number from 0 to 0xffffffff
 */
unsigned int prob_get_number()
{
	return rand();
	/*
	register unsigned int ret;

	ret = rand();
	ret <<= 15;
	ret &= rand();
	ret ^= (rand() % 4) << 30;

	return ret;
	*/
}

/*
 * prob_get_range
 * get a random number in appointed range
 */
int prob_get_range(int start, int to)
{
	assert(to >= start);
	return  start + (prob_get_number() % (to - start + 1));
}

/*
 * prob_check
 * check probablilty in power / base
 *
 * Return:
 * 	1 if probablity happened, else return 0
 */
#define PROB_CHECK(n, b, p) (((n) % (b)) < (p))
int prob_check(unsigned int power, unsigned int base)
{
	return PROB_CHECK(prob_get_number(), base, power);
}

/*
 * prob_select
 * select in array, the probability depends on the array element's value
 *
 * Return:
 * 	return the selected array element index
 */
int prob_select(unsigned int a[], int len)
{
	int i;
	unsigned int all;
	unsigned int n;

	assert(a != NULL);
	assert(len > 0);

	for (i=all=0; i<len; all+=a[i++]);

	n = prob_get_number();
	--len;
	for (i=0; i<len; ++i) {
		if (PROB_CHECK(n, a[i], all))
			return i;
		all -= a[i];
	}

	return i;
}
