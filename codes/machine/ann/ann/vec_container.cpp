/*
 * public/ann/vec_container.cpp
 * 2004-05-05 by ShanLanshan
 * 
 * 实现向量容器接口
 */
#include "public/ann/vec_container.h"
#include "public/ann/vector.h"
#include "public/prob.h"
#include "public/bit.h"

#include <iostream>

namespace ann {
		
	///////////////////////////////////////////////////////////////////
	//	class AnnVectorContainer
	///////////////////////////////////////////////////////////////////
	AnnVectorContainer::AnnVectorContainer()
	{
		m_curr_sample = 0;
	}

	bool AnnVectorContainer::add(IAnnVector& vec)
	{
		AnnVector *av;
		IAnnVector *iav;

		av = new AnnVector;
		assert(av != NULL);
		*av = vec;
		iav = static_cast<IAnnVector*> (av);
		assert(iav != NULL);

		m_samples.push_back(iav);

		return true;
	}

	IAnnVector* AnnVectorContainer::get_vector(int i /* = -1 */)
	{
		int n = static_cast<int> (m_samples.size());

		assert(i > -3);
		assert(i < n);
		assert(n > 0);

		if (i == -1) {
			m_curr_sample = (m_curr_sample + 1) % n;
		} else if (i== -2) {
			m_curr_sample= prob_get_range(0, n - 1);
		} else {
			m_curr_sample = i;
		}

		return m_samples[m_curr_sample];
	}

	ann_uint AnnVectorContainer::get_count()
	{
		return static_cast<ann_uint> (m_samples.size());
	}

	AnnVectorContainer::~AnnVectorContainer()
	{
		std::vector<IAnnVector*>::iterator i;

		for (i=m_samples.begin(); i != m_samples.end(); ++i) {
			if ((*i) != NULL)
				delete (*i);
		}
	}

	ostream &AnnVectorContainer::operator >> (ostream &os)
	{
		assert(os.good());
		IAnnVector *vec;

		os << "VECCON001" << endl << endl;
		os << "COUNT " << get_count() << endl << endl;

		for (ann_uint i=0; i<get_count(); ++i) {
			vec = get_vector(i);
			assert(vec != NULL);
			os << *(dynamic_cast<ISerialObj*>(vec));
		}

		return os;
	}

	istream &AnnVectorContainer::operator << (istream &is)
	{
		assert(os.good());

		char tmp[128];

		is >> tmp >> tmp >> tmp;
		int size = atoi(tmp);

		AnnVector vec;
		for (int i=0; i<size; ++i) {
			is >> vec;
			add(vec);
		}

		return is;
	}

	///////////////////////////////////////////////////////////////////
	//	class AnnSampleSet
	///////////////////////////////////////////////////////////////////
	bool AnnSampleSet::get_sample(IAnnVector *vec_in, IAnnVector *vec_out, int i /* = -2 */ )
	{
		assert(vec_in != NULL);
		assert(vec_out != NULL);

		IAnnVector *vec_env;
		vec_env = m_vec_container.get_vector(i);
		if (vec_env == NULL)
			return false;
		vec_env->get_sub_vector(0, m_input_division, vec_in);
		vec_env->get_sub_vector(m_input_division, m_output_division, vec_out);
		return true;
	};

	ostream &AnnSampleSet::operator >> (ostream &os)
	{
		assert(os.good());

		os	<< "SAMSET001" << endl << endl
			<< "INPUT_DIVISION  " << m_input_division << endl
			<< "OUTPUT_DIVISION " << m_output_division << endl << endl
			<< m_vec_container;

		return os;
	}

	istream &AnnSampleSet::operator << (istream &is)
	{
		assert(is.good());

		char tmp[128], indiv[32], outdiv[32];

		is >> tmp >> tmp >> indiv >> tmp >> outdiv >> m_vec_container;

		return is;
	}

	AnnSampleSet * generate_builtin_sample(const char *name, AnnSampleSet *ass)
	{
		assert(name != NULL);
		assert(ass != NULL);

		AnnVector vec;
		AnnVectorContainer *avc = &ass->m_vec_container;

		if (strcmp(name, "xor") == 0) {
			ann_float a [][3] = {
				{-1, -1, 1},
				{-1, 1, -1},
				{1, -1, -1},
				{1, 1, 1}
			};

			ass->set_division(2, 1);
			vec.set_size(3);

			for (int i=0; i<4; ++i) {
				ann_float n[3];
				for (int j=0; j<3; ++j) {
					if (a[i][j] > 0) {
						n[j] = 1.0;
					} else {
						n[j] = -1.0;
					}
				}
				vec.set_element(0, n, 3);
				avc->add(vec);
			}
		} else if (strcmp(name, "or") == 0) {
			ann_float a [][3] = {
				{-1, -1, -1},
				{-1, 1, 1},
				{1, -1, 1},
				{1, 1, 1}
			};

			ass->set_division(2, 1);
			vec.set_size(3);

			for (int i=0; i<4; ++i) {
				ann_float n[3];
				for (int j=0; j<3; ++j) {
					if (a[i][j] > 0) {
						n[j] = 1.0;
					} else {
						n[j] = -1.0;
					}
				}
				vec.set_element(0, n, 3);
				avc->add(vec);
			}
		} else if (strcmp(name, "and") == 0) {
			ann_float a [][3] = {
				{-1, -1, -1},
				{-1, 1, -1},
				{1, -1, -1},
				{1, 1, 1}
			};

			ass->set_division(2, 1);
			vec.set_size(3);

			for (int i=0; i<4; ++i) {
				ann_float n[3];
				for (int j=0; j<3; ++j) {
					if (a[i][j] > 0) {
						n[j] = 1.0;
					} else {
						n[j] = -1.0;
					}
				}
				vec.set_element(0, n, 3);
				avc->add(vec);
			}
		} else if (memcmp(name, "宇称", 4) == 0) {
			int n = name[4] - '0';
			if (n < 2 || n > 9)
				return NULL;
			int size = 1 << n;
			int a[10];
			ann_float f[10];
			int result;

			ass->set_division(n, 1);
			vec.set_size(n + 1);

			for (int i=0; i<size; ++i) {
				result = 0;
				for (int j=0; j<n; ++j) {
					a[j] = bit_get(i, j);
					result ^= a[j];
				}
				a[j] = result;

				for (int j=0; j<=n; ++j) {
					if (a[j])
						f[j] = 1.0;
					else
						f[j] = -1.0;
				}
				vec.set_element(0, f, n + 1);
				avc->add(vec);
			}
		} else {
			return NULL;
		}

		strncpy(ass->name, name, sizeof(ass->name));
		ass->name[sizeof(ass->name) - 1] = '\0';

		return ass;
	}


/*
	static void build_sample2(AnnVectorContainer *sample)
{
	AnnVector vec;
	ann_float a [][10] = {
		{1, 1, 1, -1, -1,
		 1, 1, 1,  1, -1},
		{1, 1, -1, -1, -1,
		 1, 1, 1,  -1, 1},
		{1, -1, -1, -1, 1,
		 1, 1, -1,  1, 1},
		{-1, -1, -1, 1, 1,
		 1, -1, 1,  1, 1},
		{-1, -1, 1, 1, 1,
		 -1, 1, 1,  1, 1},
	};
	assert(sample != NULL);

	vec.set_size(10);
	for (int i=0; i<5; ++i) {
		ann_float n[10];
		for (int j=0; j<10; ++j) {
			if (a[i][j] > 0) {
				n[j] = 1.0;
			} else {
				n[j] = -1.0;
			}
		}
		vec.set_element(0, n, 10);
		sample->add(vec);
	}
}
static void build_sample3(AnnVectorContainer *sample)
{
	AnnVector vec;
	ann_float a [][10] = {
		{1, 1, 1,  1, -1,
		 1, -1, -1,  -1, -1},
		{1, 1, 1, -1, 1,
		 -1, 1, -1,  -1, -1},
		{1, 1, -1, 1, 1,
		 -1, -1, 1,  -1, -1},
		{1, -1, 1, 1, 1,
		 -1, -1, -1,  1, -1},
		{-1, 1, 1, 1, 1,
		 -1, -1, -1,  -1, 1},
	};
	assert(sample != NULL);

	vec.set_size(10);
	for (int i=0; i<5; ++i) {
		ann_float n[10];
		for (int j=0; j<10; ++j) {
			if (a[i][j] > 0) {
				n[j] = 1.0;
			} else {
				n[j] = -1.0;
			}
		}
		vec.set_element(0, n, 10);
		sample->add(vec);
	}
}
*/

} // namespace ann
