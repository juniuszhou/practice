#ifndef _PUBLIC_ANN_NEURON_H
#define _PUBLIC_ANN_NEURON_H
/*
 * public/ann/neuron.h
 * 2004-02-16 by ShanLanshan
 */
#include <stdio.h>
#include "public/ann/annbase.h"
#include "public/ann/annfunc/annfunc.h"
#include "public/ann/attrobj.h"
#include "public/ann/neuronobj.h"

namespace ann {

class Neuron;
/* ��ͻ */
class Axone {
public:
	AnnFuncGroup *m_funcgroup;	/* ���������				*/
	ann_float	m_value;		/* ���						*/
	Neuron		*m_neuron;		/* ��ͻ�����ڵ���Ԫ		*/
	list<Synapse*> m_synapse;	/* �����ᵽ��ͻ�����б�		*/
public:
	Axone(Neuron *neuron);
	~Axone();

	//	������ͻ���
	inline void cacu_output();

	//	�õ���ͻͻ��
	inline ann_float get_output() {return m_value;};
	inline void set_output(ann_float v) {m_value= v;};
};

/* ͻ��Ȩֵ */
class SynapsePower: public SharedObj {
private:
	ann_float m_value;
public:
	inline SynapsePower() {m_value = 0;};
	inline ann_float get_value() {return m_value;};
	inline void set_value(ann_float v) {m_value = v;};
	inline void update_value(ann_float v) {m_value += v;};
};

/*	ͻ��	*/
class Synapse: public LifeObj, public GridObj {
public:
	list<Axone*>	m_input;		/* ��һ��Ϊ������ͻ������Ϊ������ͻ */
	SynapsePower	*m_power;		/* ����Ȩֵ							*/
	Neuron			*m_neuron;		/* ���뵽����Ԫ					*/
public:
	Synapse(Neuron *neuron, SynapsePower *power=NULL);
	~Synapse();
	//	ȡ��������ͻ���ϵ���ͻ����
	inline Axone& get_axone() {return *m_input.front();};
	inline ann_float get_input() {return get_axone().get_output();};
	inline Neuron* get_input_neuron() {return get_axone().m_neuron;};
	inline void update_power(ann_float v) {m_power->update_value(v);};
	inline ann_float get_power() {return m_power->get_value();};
	inline void set_power(ann_float v) {m_power->set_value(v);};
	//	����ͻ�������ֵ
	ann_float get_output();
};

/* ������Ԫ��ĸ��� */
class Neuron: public NeuronObj, public LifeObj, public GridObj {
protected:
	ann_float	m_stimulation;		/* �����ܺ�		*/
	//ann_func_p	m_respond_func;	/* ��Ӧ����		*/
	ann_float	m_respond;			/* ��Ӧ			*/
	list<Synapse*>	m_synapse_list;	/* ����ͻ���б� */
	list<Axone>	m_axone_list;		/* �����ͻ�б� */
	friend class Axone;
	friend class Synapse;
	friend class BPLayer;
public:
	Neuron();
	virtual ~Neuron();

	// �������Ԫ��ʼ״̬
	void random();

	ann_float get_respond() {return m_respond;};

	//	ȡ����Ԫ����ͻ����
	inline Axone& get_axone() {return m_axone_list.front();};

	// ȡ��Ԫ�����������
	inline AnnFuncGroup* get_output_func() {return get_axone().m_funcgroup;};

	/* ������Ԫ��������� */
	void set_output_func(AnnFuncGroup *g) {assert(g != NULL); get_axone().m_funcgroup = g;};

	/* ������Ԫ����Ӧֵ */
	virtual void respond();

	/* ����Ԫ����Ӧֵ�������ͻ */
	virtual void output();

	/* ����ͻ�������� */
	int accept_conn(Axone &axone);

	/* ��������һ����Ԫ������ */
	int accept_conn(Neuron *neuron);

	/* ������Ԫ�����ֵ */
	void set_output(ann_float v);

	/* ȡ����Ԫ�����ֵ */
	inline ann_float get_output() {return get_axone().get_output();};

};

}

#endif /* !_PUBLIC_ANN_NEURON_H */
