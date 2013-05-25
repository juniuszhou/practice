/*
 * public/ann/vector.cpp
 * 2004-05-01 by ShanLanshan
 */
#include <stdio.h>
#include <stdlib.h>
#include "public/ann/annbase.h"
#include "public/ann/vector.h"

namespace ann {
	AnnVector::AnnVector(): m_element(NULL), m_size(-1), m_space_size(-1), m_flag(0UL)
	{}

	AnnVector::~AnnVector()
	{
		if (m_flag & FLAG_SUB_VECTOR)
			return;

		if (m_element == NULL)
			return;

		free(m_element);
		//m_element = NULL;
	}

	void AnnVector::set_size(ann_int size)
	{
		assert(size > -1);

		if (size > m_space_size) {
			ann_int space_size;
			if (m_flag & FLAG_SUB_VECTOR)
				return;
			space_size = size == 0 ? 1 : size;
			m_element = reinterpret_cast<double*>
				(realloc(m_element, sizeof(ann_float) * space_size));
			assert(m_element != NULL);
			m_space_size = space_size;
		}

		m_size = size;
	}

	IAnnVector* AnnVector::get_sub_vector(int off, int len, IAnnVector *vec)
	{
		assert(off > -1);
		assert(off + len <= m_size);
		assert(vec != NULL);
		assert(m_element != NULL);
		
		AnnVector *av;	// HA! AV
		av = dynamic_cast<AnnVector*> (vec);
		assert(av != NULL);

		av->m_element = m_element + off;
		av->m_flag |= FLAG_SUB_VECTOR;
		av->m_size = len;
		av->m_space_size = m_space_size - off;

		return av;
	}

	ann_int AnnVector::get_size()
	{
		return m_size;
	}

	ann_float AnnVector::get_element(int n)
	{
		assert(n > -1);
		assert(n < m_size);
		assert(m_element != NULL);

		return m_element[n];
	}

	void AnnVector::set_element(int n, ann_float v)
	{
		assert(n > -1);
		assert(n < m_size);
		assert(m_element != NULL);

		m_element[n] = v;
	}

	void AnnVector::get_element(int i, ann_float a[], int n)
	{
		assert(i > -1);
		assert(n > -1);
		assert(i + n <= m_size);
		assert(a != NULL);
		assert(m_element != NULL);
		
		memcpy(a, m_element + i, sizeof(m_element[0]) * n);
	}

	void AnnVector::set_element(int i, ann_float a[], int n)
	{
		assert(i > -1);
		assert(n > -1);
		assert(i + n <= m_size);
		assert(a != NULL);
		assert(m_element != NULL);

		memcpy(m_element + i, a, sizeof(m_element[0]) * n);
	}

	ann_float *AnnVector::get_buffer()
	{
		assert(m_element != NULL);
		return m_element;
	}

	void AnnVector::release_buffer()
	{
	}

	IAnnVector& AnnVector::operator=(IAnnVector &av)
	{
		int n;

		n = av.get_size();
		set_size(n);

		for (int i=0; i<n; ++i) {
			set_element(i, av.get_element(i));
		}

		return *(static_cast<IAnnVector*> (this));
	}

	bool AnnVector::operator == (IAnnVector &av)
	{
		int n;

		n = av.get_size();
		set_size(n);

		for (int i=0; i<n; ++i) {
			if (get_element(i) != av.get_element(i))
				return false;
		}

		return true;
	}

	ostream &AnnVector::operator >> (ostream &os)
	{
		assert(os.good());
		
		int n = get_size();

		os << "SIZE " << n << " VALUE ";
		for (int i=0; i<n; ++i)
			os << get_element(i) << " ";
		os << endl;

		return os;
	}

	istream &AnnVector::operator << (istream &is)
	{
		assert(is.good());

		char tmp[128], sizes[32];

		is >> tmp >> sizes >> tmp;
		
		int n = atoi(sizes);
		set_size(n);

		ann_float v;
		for (int i=0; i<n; ++i) {
			is >> v;
			set_element(i, v);
		}

		return is;
	}

};	//	namespace ann
