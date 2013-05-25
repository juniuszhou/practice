#ifndef _PUBLIC_BIT_H
#define _PUBLIC_BIT_H
/*
 * public/bit.h
 * 2004-05-10 by ShanLanshan
 */

#define bit_place(n, i) do {n |= (1 << i);} while(0)

#define bit_clear(n, i) do {n &= ~(1 << i);} while(0)

#define bit_set(n, i, v) do {	\
	n = v ? 				\
		n | (1 << i) 		\
		:					\
		n & ~(1 << i);		\
} while(0)

#define bit_get(n, i) (1&&(n & (1 << i)))

#define bit_placed(n, i) (1&&(n & (1 << i)))

#define bit_cleared(n, i) (!(n & (1 << i)))

#endif /* !_PUBLIC_BIT_H */
