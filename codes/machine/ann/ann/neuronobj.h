#ifndef _PUBLIC_ANN_NEURONOBJ_H
#define _PUBLIC_ANN_NEURONOBJ_H
/*
 * public/ann/neuronobj.h
 * 2004-03-07 By ShanLanshan
 */
#include "public/ann/annbase.h"

namespace ann {

class NeuronObj {
private:
	ann_int m_type;
protected:
	NeuronObj *m_father;
public:
	enum {TYPE_NEURON, TYPE_GROUP};
public:
	NeuronObj();
	virtual ~NeuronObj();
	inline ann_int get_type() {return m_type;};
	inline void set_father(NeuronObj *f) {m_father = f;};
};

}

#endif /* !_PUBLIC_ANN_NEURONOBJ_H */
