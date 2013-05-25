/*
 * public/ann/annfunc/sign.c
 * 2004-05-03 by ShanLanshan
 */
#include "public/ann/annfunc/annfunc.h"
#include "public/ann/annfunc/sign.h"

namespace ann {
namespace annfunc {
namespace sign {

	static bool init();
	static void finalize();
	static ann_float main_func(ann_float f);
	static ann_float derivative_func(ann_float f);
	static ann_float derivative_func2(ann_float f);
	static void multi_main_func(ann_float *src, ann_int len, ann_float *dst);
	static void multi_derivative_func(ann_float *src, ann_int len, ann_float *dst);
	static void multi_derivative_func2(ann_float *src, ann_int len, ann_float *dst);

	extern  AnnFuncGroup g_funcgroup = {
		"sign",
		"符号函数",
		init,
		finalize,
		main_func,
		derivative_func,
		NULL,
		multi_main_func,
		multi_derivative_func,
		NULL
	};

	static bool init()
	{
		return true;
	}

	static void finalize() {}

	/* 
	 * 符号函数 
	 * w = 1 / ( 1 + e ^ (-f))
	 */
	static ann_float main_func(ann_float f)
	{
		if (f >= 0.0)
			return 1;
		else
			return -1;
	}

	/*
	 * 符号函数的导数
	 * 符号函数是不可导的，我们把它当作双曲正切函数看
	 */
	static ann_float derivative_func(ann_float f)
	{
		ann_float u;
		u = pow(E, -f);
		return 2 * u / ((1 + u) * (1 + u));
	}

	static void multi_main_func(ann_float *src, ann_int len, ann_float *dst)
	{
		ann_float f;

		assert(src != NULL);
		if (dst == NULL)
			dst = src;

		for (int i=0; i<len; ++i) {
			f = src[i];
			dst[i] = f >= 0.0 ? 1 : -1;
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

}}} // namespace ann::annfunc::sign

