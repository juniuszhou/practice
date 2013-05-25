#ifndef _PUBLIC_ANN_NEURON_GROUP_H
#define _PUBLIC_ANN_NEURON_GROUP_H
/*
 * public/ann/neuron_group.h
 * 2004-03-07 by ShanLanshan
 */
#include "public/ann/annbase.h"
#include "public/ann/neuron.h"
#include "public/ann/neuronobj.h"

namespace ann {

/* 神经元物体槽	*/
class NeuronObjSlot {
public:
	static const int FLAG_ATTACH = 1;
	NeuronObj *m_obj;	/* 神经元物体		*/
	ann_int m_flag;		/* 入槽标志			*/
};

class NeuronGroup: public NeuronObj {
public:
	typedef list<NeuronObjSlot>::iterator iterator;
private:
	list<NeuronObjSlot>	m_objlist;
	iterator m_currobj;
public:
	NeuronGroup();
	virtual ~NeuronGroup();
	NeuronObj *move_first(iterator *i = NULL);
	NeuronObj *move_next(iterator *i = NULL);
	bool not_end(iterator *i = NULL);
	int get_count();
	ann_int add(NeuronObj *obj, ann_int flag);
};

class NeuronSimpleGroup: public NeuronGroup {
public:
	NeuronSimpleGroup();
	~NeuronSimpleGroup();
	virtual void random();
	virtual void set_output_func(AnnFuncGroup *fg);
	virtual void respond();
	virtual void output();
};

}
#endif /* !_PUBLIC_ANN_NEURON_GROUP_H */
