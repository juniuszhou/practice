#ifndef _PUBLIC_ANN_ANNDEF_H
#define _PUBLIC_ANN_ANNDEF_H
/*
 * public/ann/anndef.h
 * 2004-02-16 by ShanLanshan
 */

#define ann_int			long
#define ann_uint		unsigned long
#define ann_sint		signed long

#define ann_int8		char
#define ann_uint8		unsigned char
#define ann_sint8		signed char

#define ann_int16		short
#define ann_uint16		unsigned short
#define ann_sint16		signed short

#define ann_int32		long
#define ann_uint32		unsigned long
#define ann_sint32		signed long

//	surpport by gcc3 and vc7
#define ann_int64		long long
#define ann_uint64		unsigned long long
#define ann_sint64		signed long long

#define ann_float		double
#define ann_float32		float	
#define ann_float64		double
#define ann_float80		long double		// maybe, it's still 64 bit

#define ann_char		char
#define ann_char8		char
#define ann_char16		wchar_t


#define ANN_INT_ZERO	0
#define ANN_FLOAT_ZERO	0.0
#define ANN_CHAR_ZERO	'\0'

#define E					((ann_float)(2.7))
#define PI					((ann_float)(3.1415926))
#define MAX_ALLOC_SIZE		(16 * 1024 * 1024)

#endif /* !_PUBLIC_ANN_ANNDEF_H */
