/*
 * public/ann/annfunc/func_cache.cpp
 * 2004-05-10 by ShanLanshan
 */
#include "public/ann/annbase.h"
#include "public/ann/annfunc/func_cache.h"

namespace ann {

		FuncCache::FuncCache(cache_func_t func)
		{
			assert(func != NULL);
			m_func = func;
			m_cache = NULL;
			m_low = m_high = 0.0;
			m_step = 0.01;
		}

		FuncCache::~FuncCache()
		{
			if (m_cache != NULL) {
				delete m_cache;
				m_cache = NULL;
			}
		}

		bool FuncCache::build_cache(ann_float low, ann_float high, ann_float step)
		{
			assert(high > low);
			assert(step != 0.0);

			int size;
			size = static_cast<int> ((high - low) / step);

			assert(size * sizeof(float) < MAX_ALLOC_SIZE);

			if (size > m_cache_size) {
				if (m_cache != NULL) {
					delete[] m_cache;
					m_cache = NULL;
				}

				m_cache = new ann_float[size * sizeof(ann_float)];
				assert(m_cache != NULL);
			}

			assert(m_func != NULL);
			for (int i=0; i<size; ++i) {
				m_cache[i] = m_func(low + step * i);
			}

			m_low = low;
			m_high = high;
			m_step = step;
			m_cache_size = size;

			return true;
		}

		ann_float FuncCache::operator () (ann_float v)
		{
			int idx;
			if (m_cache == NULL) {
				//printf("m_cache == NULL\n");
				assert(m_func != NULL);
				return m_func(v);
			}

			assert(m_step != 0.0);
			idx = static_cast<int> ((v - m_low) / m_step);

			if (idx >= m_cache_size || idx < 0) {
				assert(m_func != NULL);
				return m_func(v);
			}

			//printf("find table [%d]\n", idx);
			return m_cache[idx];
		}


} // namespace ann
