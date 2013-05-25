#ifndef _PUBLIC_ANN_ANNFUNC_FUNC_CACHE_H
#define _PUBLIC_ANN_ANNFUNC_FUNC_CACHE_H
/*
 * public/ann/annfunc/func_cache.h
 * 2004-05-10 by ShanLanshan
 */
#include "public/ann/annbase.h"

namespace ann {

	typedef ann_float(*cache_func_t) (ann_float v);

	class FuncCache {
		cache_func_t m_func;
		ann_float *m_cache;
		ann_float m_low, m_high, m_step;
		ann_int m_cache_size;
	public:
		FuncCache(cache_func_t func);
		~FuncCache();
		void set_func(cache_func_t f) {m_func = f;};
		bool build_cache(ann_float low, ann_float high, ann_float step);
		ann_float operator () (ann_float v);
	};


} // namespace ann

#endif /* !_PUBLIC_ANN_ANNFUNC_FUNC_CACHE_H */
