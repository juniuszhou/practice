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
/* 轴突 */
class Axone {
public:
	AnnFuncGroup *m_funcgroup;	/* 输出函数族				*/
	ann_float	m_value;		/* 输出						*/
	Neuron		*m_neuron;		/* 轴突所属于的神经元		*/
	list<Synapse*> m_synapse;	/* 所连结到的突触的列表		*/
public:
	Axone(Neuron *neuron);
	~Axone();

	//	计算轴突输出
	inline void cacu_output();

	//	得到轴突突出
	inline ann_float get_output() {return m_value;};
	inline void set_output(ann_float v) {m_value= v;};
};

/* 突触权值 */
class SynapsePower: public SharedObj {
private:
	ann_float m_value;
public:
	inline SynapsePower() {m_value = 0;};
	inline ann_float get_value() {return m_value;};
	inline void set_value(ann_float v) {m_value = v;};
	inline void update_value(ann_float v) {m_value += v;};
};

/*	突触	*/
class Synapse: public LifeObj, public GridObj {
public:
	list<Axone*>	m_input;		/* 第一个为输入轴突，其余为辅助轴突 */
	SynapsePower	*m_power;		/* 输入权值							*/
	Neuron			*m_neuron;		/* 输入到的神经元					*/
public:
	Synapse(Neuron *neuron, SynapsePower *power=NULL);
	~Synapse();
	//	取得连接在突出上的轴突引用
	inline Axone& get_axone() {return *m_input.front();};
	inline ann_float get_input() {return get_axone().get_output();};
	inline Neuron* get_input_neuron() {return get_axone().m_neuron;};
	inline void update_power(ann_float v) {m_power->update_value(v);};
	inline ann_float get_power() {return m_power->get_value();};
	inline void set_power(ann_float v) {m_power->set_value(v);};
	//	计算突触的输出值
	ann_float get_output();
};

/* 所有神经元类的父类 */
class Neuron: public NeuronObj, public LifeObj, public GridObj {
protected:
	ann_float	m_stimulation;		/* 输入总和		*/
	//ann_func_p	m_respond_func;	/* 响应函数		*/
	ann_float	m_respond;			/* 响应			*/
	list<Synapse*>	m_synapse_list;	/* 输入突触列表 */
	list<Axone>	m_axone_list;		/* 输出轴突列表 */
	friend class Axone;
	friend class Synapse;
	friend class BPLayer;
public:
	Neuron();
	virtual ~Neuron();

	// 随机化神经元初始状态
	void random();

	ann_float get_respond() {return m_respond;};

	//	取得神经元的轴突引用
	inline Axone& get_axone() {return m_axone_list.front();};

	// 取神经元的输出函数族
	inline AnnFuncGroup* get_output_func() {return get_axone().m_funcgroup;};

	/* 设置神经元的输出函数 */
	void set_output_func(AnnFuncGroup *g) {assert(g != NULL); get_axone().m_funcgroup = g;};

	/* 计算神经元的响应值 */
	virtual void respond();

	/* 将神经元的响应值输出到轴突 */
	virtual void output();

	/* 接受突触的连接 */
	int accept_conn(Axone &axone);

	/* 接受另外一个神经元的连接 */
	int accept_conn(Neuron *neuron);

	/* 设置神经元的输出值 */
	void set_output(ann_float v);

	/* 取得神经元的输出值 */
	inline ann_float get_output() {return get_axone().get_output();};

};

}

#endif /* !_PUBLIC_ANN_NEURON_H */
