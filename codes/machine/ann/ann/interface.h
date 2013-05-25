#ifndef _PUBLIC_ANN_INTERFACE_H
#define _PUBLIC_ANN_INTERFACE_H

/*
 * public/ann/interface.h
 * 2004-04-24 by ShanLanshan
 *
 * Define ann lib interface
 */

#include "public/ann/annbase.h"

namespace ann {

	class ISerialObj {
	public:
		virtual ostream& operator >>(ostream &os) = 0;
		virtual istream& operator <<(istream &is) = 0;
	};
	inline ostream& operator << (ostream &os, ISerialObj &so) {return so >> os;}
	inline istream& operator >> (istream &is, ISerialObj &so) {return so << is;}

	class IAnnVector {
	public:
		virtual ~IAnnVector();
		virtual IAnnVector* get_sub_vector(int off, int len, IAnnVector *vec) = 0;
		virtual void set_size(ann_int size) = 0;
		virtual ann_int get_size() = 0;
		virtual ann_float get_element(int n) = 0;
		virtual void set_element(int n, ann_float v) = 0;
		virtual void get_element(int i, ann_float a[], int n) = 0;
		virtual void set_element(int i, ann_float a[], int n) = 0;
		virtual ann_float *get_buffer() = 0;
		virtual void release_buffer() = 0;
		virtual IAnnVector& operator=(IAnnVector &av) = 0;
		virtual bool operator ==(IAnnVector &av) = 0;
		//virtual ostream& operator >>(ostream &os) = 0;
	};
	
	//inline ostream& operator << (ostream &os, IAnnVector &av) {return av >> os;}

	class IAnnVectorContainer {
	public:
		virtual ~IAnnVectorContainer();
		virtual bool add(IAnnVector &vec) = 0;
		virtual IAnnVector *get_vector(int i) = 0;
		virtual ann_uint get_count() = 0;
	};

	class IAnnVectorConverter {
	public:
		virtual ~IAnnVectorConverter();
		virtual bool set_input(IAnnVector *vecin) = 0;
		virtual bool get_output(IAnnVector *vecout) = 0;
		virtual bool learn(IAnnVector *vecout) = 0;
		virtual bool convert() = 0;
	};

}	// namespace ann

#endif /* !_PUBLIC_ANN_INTERFACE_H */
