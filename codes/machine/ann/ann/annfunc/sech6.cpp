/*
 * public/ann/annfunc/sech6.c
 * 2004-05-03 by ShanLanshan
 */
#include "public/ann/annfunc/annfunc.h"
#include "public/ann/annfunc/sech6.h"
#include "public/ann/annfunc/func_cache.h"

namespace ann {
namespace annfunc {
namespace sech6 {

	static bool init();
	static void finalize();
	static ann_float main_func(ann_float f);
	static ann_float derivative_func(ann_float f);
	static ann_float derivative_func2(ann_float f);
	static void multi_main_func(ann_float *src, ann_int len, ann_float *dst);
	static void multi_derivative_func(ann_float *src, ann_int len, ann_float *dst);
	static void multi_derivative_func2(ann_float *src, ann_int len, ann_float *dst);

	extern  AnnFuncGroup g_funcgroup = {
		"sech6",
		"一阶导为正切六次方的函数",
		init,
		finalize,
		main_func,
		derivative_func,
		NULL,
		multi_main_func,
		multi_derivative_func,
		NULL
	};

	#define _CACHE_FUNC_NAME	"sech6_cache"
	#define _CACHE_FUNC_DESC	"一阶导为正切六次方的函数(带缓冲)"

	#include "public/ann/annfunc/cache_template"

	#undef _CACHE_FUNC_NAME
	#undef _CACHE_FUNC_DESC

	static bool init()
	{
		return true;
	}

	static void finalize() {}

	static ann_float main_func(ann_float f)
	{
		ann_float u, tanh, tanh2, tanh3, tanh5;
		u = pow(E, -f);
		tanh = (1 - u) / (1 + u);
		tanh2 = tanh * tanh;
		tanh3 = tanh2 * tanh;
		tanh5 = tanh3 * tanh2;
		return (15.0 / 8.0) * (tanh - (2.0 / 3.0) * tanh3 + tanh5 / 5.0);
	}

	static ann_float derivative_func(ann_float f)
	{
		ann_float sech;
		f /= 2.0;
		sech = 2 / (pow(E, f) + pow(E, -f));

		sech *= sech * sech;
		sech *= sech;

		return sech;
	}

	static void multi_main_func(ann_float *src, ann_int len, ann_float *dst)
	{
		ann_float f, u, tanh, tanh2, tanh3, tanh5;

		assert(src != NULL);
		if (dst == NULL)
			dst = src;

		for (int i=0; i<len; ++i) {
			f = src[i];
			u = pow(E, -f);
			tanh = (1 - u) / (1 + u);
			tanh2 = tanh * tanh;
			tanh3 = tanh2 * tanh;
			tanh5 = tanh3 * tanh2;
			dst[i] = (15.0 / 8.0) * (tanh - (2.0 / 3.0) * tanh3 + tanh5 / 5.0);
		}
	}
	
	static void multi_derivative_func(ann_float *src, ann_int len, ann_float *dst)
	{
		ann_float f;
		ann_float sech;

		assert(src != NULL);
		if (dst == NULL)
			dst = src;

		for (int i=0; i<len; ++i) {
			f = src[i];
			f /= 2.0;
			sech = 2 / (pow(E, f) + pow(E, -f));

			sech *= sech * sech;
			sech *= sech;
			dst[i] = sech;
		}
	}

}}} // namespace ann::annfunc::sech6

