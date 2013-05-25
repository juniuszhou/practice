/*
 * public/ann/annfunc/sin.c
 * 2004-05-03 by ShanLanshan
 */
#include "public/ann/annfunc/annfunc.h"
#include "public/ann/annfunc/sin.h"

namespace ann {
namespace annfunc {
namespace sin {

	static bool init();
	static void finalize();
	static ann_float main_func(ann_float f);
	static ann_float derivative_func(ann_float f);
	static ann_float derivative_func2(ann_float f);
	static void multi_main_func(ann_float *src, ann_int len, ann_float *dst);
	static void multi_derivative_func(ann_float *src, ann_int len, ann_float *dst);
	static void multi_derivative_func2(ann_float *src, ann_int len, ann_float *dst);

	extern  AnnFuncGroup g_funcgroup = {
		"sin",
		"ÕýÏÒº¯Êý",
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

	static ann_float main_func(ann_float f)
	{
		return ::sin(f);
	}

	static ann_float derivative_func(ann_float f)
	{
		return ::cos(f);
	}

	static void multi_main_func(ann_float *src, ann_int len, ann_float *dst)
	{
		ann_float f;

		assert(src != NULL);
		if (dst == NULL)
			dst = src;

		for (int i=0; i<len; ++i) {
			f = src[i];
			dst[i] = ::sin(f);
		}
	}
	
	static void multi_derivative_func(ann_float *src, ann_int len, ann_float *dst)
	{
		ann_float f;

		assert(src != NULL);
		if (dst == NULL)
			dst = src;

		for (int i=0; i<len; ++i) {
			f = src[i];
			dst[i] = ::cos(f);
		}
	}

}}} // namespace ann::annfunc::sin

