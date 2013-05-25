/*
 * public/ann/annfunc/hyperbola_tangent.c
 * 2004-05-03 by ShanLanshan
 */
#include "public/ann/annfunc/annfunc.h"
#include "public/ann/annfunc/hyperbola_tangent.h"

namespace ann {
namespace annfunc {
namespace hyperbola_tangent {

	static bool init();
	static void finalize();
	static ann_float main_func(ann_float f);
	static ann_float derivative_func(ann_float f);
	static ann_float derivative_func2(ann_float f);
	static void multi_main_func(ann_float *src, ann_int len, ann_float *dst);
	static void multi_derivative_func(ann_float *src, ann_int len, ann_float *dst);
	static void multi_derivative_func2(ann_float *src, ann_int len, ann_float *dst);

	extern  AnnFuncGroup g_funcgroup = {
		"hyperbola_tangent",
		"双曲正切函数",
		init,
		finalize,
		main_func,
		derivative_func,
		derivative_func2,
		multi_main_func,
		multi_derivative_func,
		multi_derivative_func2
	};

	static bool init()
	{
		return true;
	}

	static void finalize() {}

	/* 
	 * 双曲正切函数 
	 * w = (1- e ^ (-f)) / ( 1 + e ^ (-f))
	 */
	static ann_float main_func(ann_float f)
	{
		ann_float u;
		u = pow(E, -f);
		return (1 - u) / (1 + u);
	}

	/* 
	 * 双曲正切函数的导数
	 *
	 * 	w = (1- e ^ (-f)) / ( 1 + e ^ (-f));
	 * 	Let u(f) = e ^ (-f), => @u/@f = - e ^ (-f) = -u
	 * 	@w/@f = (@w/@u) * (@u/@f)
	 * 	w = (1 - u) / (1 + u)
	 * 	@w/@u = (-1 * (1 + u) - (1 - u) * 1) / (( 1 + u ) ^ 2)
	 * 	      = -2 / ((1 + u) ^ 2);
	 *	@w/@f = 2u / ((1 + u) ^ 2)
	 */
	static ann_float derivative_func(ann_float f)
	{
		ann_float u;
		u = pow(E, -f);
		return 2 * u / ((1 + u) * (1 + u));
	}

	/* 
	 * 求双曲正切函数的导数值，输入的参数是主函数的值
	 * 	Let u(f) = e ^ (-f)
	 * 	w = (1 - u) / (1 + u)
	 *	@w/@f = 2u / ((1 + u) ^ 2)
	 *	      = 0.5 * ((1 + u) ^ 2 - (1 - u) ^ 2) / ((1 + u) ^ 2)
	 *	      = 0.5 * (1 - (((1 - u) ^ 2)/((1 + u) ^ 2)))
	 *	      = 0.5 * (1 - w ^ 2)
	 */
	static ann_float derivative_func2(ann_float f)
	{
		return (1 - f * f) / 2;
	}

	static void multi_main_func(ann_float *src, ann_int len, ann_float *dst)
	{
		ann_float u, f;

		assert(src != NULL);

		if (dst == NULL)
			dst = src;

		for (int i=0; i<len; ++i) {
			f = src[i];
			u = pow(E, -f);
			dst[i] = (1 - u) / (1 + u);
		}
	}
	
	static void multi_derivative_func(ann_float *src, ann_int len, ann_float *dst)
	{
		ann_float u, f;

		assert(src != NULL);
		if (dst == NULL)
			dst = src;

		for (int i=0; i<len; ++i) {
			f = src[i];
			u = pow(E, -f);
			dst[i] = 2 * u / ((1 + u) * (1 + u));
		}
	}

	static void multi_derivative_func2(ann_float *src, ann_int len, ann_float *dst)
	{
		ann_float f;

		assert(src != NULL);
		if (dst == NULL)
			dst = src;

		for (int i=0; i<len; ++i) {
			f = src[i];
			dst[i] = (1 - f * f) / 2;
		}
	}

}}} // namespace ann::annfunc::hyperbola_tangent

