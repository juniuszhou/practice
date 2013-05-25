#ifndef _PUBLIC_PROB_H
#define _PUBLIC_PROB_H
/*
 * public/prob.h
 * 2004-04-25 by ShanLanshan
 *
 * probability library
 */

#ifdef __cplusplus
	extern "C" {
#endif

/*
 * prob_set_seed
 * set random seed
 * 0 for random seed
 */
void prob_set_seed(unsigned seed);


/*
 * prob_get_number
 * get random number from 0 to 0xffffffff
 */
unsigned int prob_get_number();

/*
 * prob_get_range
 * get a random number in appointed range
 */
int prob_get_range(int start, int to);

/*
 * prob_check
 * check probablilty in power / base
 *
 * Return:
 * 	1 if probablity happened, else return 0
 */
int prob_check(unsigned int power, unsigned int base);

/*
 * prob_select
 * select in array, the probability depends on the array element's value
 *
 * Return:
 * 	return the selected array element index
 */
int prob_select(unsigned int a[], int len);


#ifdef __cplusplus
	}
#endif

#endif /* !_PUBLIC_PROB_H */
