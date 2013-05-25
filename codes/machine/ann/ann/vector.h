#ifndef _PUBLIC_ANN_VECTOR_H
#define _PUBLIC_ANN_VECTOR_H
/*
 * public/ann/vector.h
 * 2004-05-01 by ShanLanshan
 * Implement the interface IAnnVector
 */
#include "public/ann/interface.h"

namespace ann {

	class AnnVector: public IAnnVector, public ISerialObj {
	private:
		ann_float *m_element;
		ann_int m_size;
		ann_int m_space_size;
		ann_uint32	m_flag;
	public:
		static const int FLAG_SUB_VECTOR = 0x00000001UL;
	public:
		AnnVector();
		virtual ~AnnVector();
		virtual void set_size(ann_int size);
		virtual IAnnVector* get_sub_vector(int off, int len, IAnnVector* vec);
		virtual ann_int get_size();
		virtual ann_float get_element(int n);
		virtual void set_element(int n, ann_float v);
		virtual void get_element(int i, ann_float a[], int n);
		virtual void set_element(int i, ann_float a[], int n);
		virtual ann_float *get_buffer();
		virtual void release_buffer();
		virtual IAnnVector& operator=(IAnnVector &av);
		virtual bool operator== (IAnnVector &av);
		virtual ostream &operator >> (ostream &os);
		virtual istream &operator << (istream &is);
	};

}	//	namespace ann

#endif /* !_PUBLIC_ANN_VECTOR_H */
