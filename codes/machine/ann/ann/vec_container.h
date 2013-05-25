#ifndef _PUBLIC_ANN_VEC_CONTAINER_H
#define _PUBLIC_ANN_VEC_CONTAINER_H
/*
 * public/ann/vec_container.h
 * 2004-05-05 by ShanLanshan
 * 
 * 实现向量容器接口
 */
#include <vector>
#include <assert.h>
#include "public/ann/interface.h"

namespace ann {

	class AnnVectorContainer:
		public IAnnVectorContainer, public ISerialObj {
	private:
		std::vector<IAnnVector*> m_samples;
		ann_int m_curr_sample;
	public:
		AnnVectorContainer();
		virtual ~AnnVectorContainer();
		virtual bool add(IAnnVector &vec);
		virtual IAnnVector* get_vector(int i = -2);
		virtual ann_uint get_count();
		virtual ostream &operator >> (ostream &os);
		virtual istream &operator << (istream &is);
	};

	class AnnSampleSet;
	extern AnnSampleSet * generate_builtin_sample(const char *name, AnnSampleSet *ass);

	class AnnSampleSet: public ISerialObj {
	public:
		char name[64];
		AnnVectorContainer m_vec_container;
		int m_input_division;
		int m_output_division;
	public:
		AnnSampleSet(int in, int out) {set_division(in, out);};
		AnnSampleSet(const char *name) {
			set_division(1, 1);
			generate_builtin_sample(name, this);
		};
		inline void set_division(int in, int out) {
			m_input_division = in;
			m_output_division = out;
		};
		bool get_sample(IAnnVector *vec_in, IAnnVector *vec_out, int i = -2);
		virtual ostream &operator >> (ostream &os);
		virtual istream &operator << (istream &is);
	};


} // namespace ann

#endif // !_PUBLIC_ANN_VEC_CONTAINER_H
