/*
 * public/ann/neuron.cpp
 * 2004-02-16 by ShanLanshan
 */
#include <assert.h>
#include "public/ann/annbase.h"
#include "public/ann/annfunc/annfunc.h"
#include "public/ann/neuron.h"
#include "public/ann/annprob.h"

namespace ann {

//////////////////////////////////////////////////////////////////////////
//	class Axone 
//////////////////////////////////////////////////////////////////////////
Axone::Axone(Neuron *neuron)
{
	m_funcgroup = annfunc_get("hyperbola_tangent");
	assert(m_funcgroup);
	m_value = 0.0;
	m_neuron = neuron;
}

Axone::~Axone(){}

//	计算轴突输出
inline void Axone::cacu_output() {
	assert(m_neuron != NULL);
	assert(m_funcgroup != NULL);
	assert(m_funcgroup->main != NULL);
	m_value = m_funcgroup->main(m_neuron->get_respond());
};


//////////////////////////////////////////////////////////////////////////
//	class Synapse
//////////////////////////////////////////////////////////////////////////
Synapse::Synapse(Neuron *neuron, SynapsePower *power)
{
	m_neuron = neuron;

	if (power == NULL) {
		power = new SynapsePower;
		assert(power != NULL);
	}

	m_power = power;
	power->addref();
}

Synapse::~Synapse()
{
	if (m_power->release() == 0) {
		delete m_power;
	}
}


ann_float Synapse::get_output()
{
	ann_float ret = m_power->get_value();
	
	for (
		list<Axone*>::const_iterator i = m_input.begin();
		i != m_input.end();
		++i
	) {
		ret *= (*i)->get_output();
	}

	return ret;
}

//////////////////////////////////////////////////////////////////////////
//	class Neuron
//////////////////////////////////////////////////////////////////////////
Neuron::Neuron()
{
	m_stimulation = 0.0;
	m_respond = 0.0;
	//m_respond_func = NULL;

	/* 初始的时候生长一根轴突 */
	Axone axone(this);
	m_axone_list.push_front(axone);
}

Neuron::~Neuron() 
{
	Synapse *s;
	for (
		list<Synapse*>::iterator i = m_synapse_list.begin();
		i != m_synapse_list.end();
		++i
	) {
		s = (*i);
		assert(s != NULL);
		delete s;
	}
}

// 随机化神经元初始状态
void Neuron::random()
{
	ann_float v;
	Synapse *s;
	int n = 0;
	for (
		list<Synapse*>::iterator i = m_synapse_list.begin();
		i != m_synapse_list.end();
		++i
	) {
		++n;
		if (n == 0) {
			do {
				v = (ann_float)(prob_get_range(-999, 999)) / 1000.0;
			} while (v < 0.1 && v > -0.1);
		} else {
			v = (ann_float)(prob_get_range(-999, 999)) / 1000.0;
		}
		s = (*i);
		assert(s != NULL);
		s->set_power(v);
		++n;
	}
}

/* 计算神经元的响应值 */
void Neuron::respond()
{
	Synapse *s;
	/* 计算所有突触的输入之和 */
	m_stimulation = 0.0;
	for (
		list<Synapse*>::iterator i = m_synapse_list.begin();
		i != m_synapse_list.end();
		++i
	) {
		s = (*i);
		assert(s != NULL);
		m_stimulation += s->get_output();
	}

	/* 如果有响应函数则计算响应函数 */
	/*
	if (m_respond_func == NULL) {
		m_respond = m_stimulation;
	} else {
		m_respond = m_respond_func(m_stimulation);
	}
	*/
	m_respond = m_stimulation;
}

/* 将神经元的响应值输出到轴突 */
void Neuron::output()
{
	for (
		list<Axone>::iterator i = m_axone_list.begin();
		i != m_axone_list.end();
		++i
	) {
		(*i).cacu_output();
	}
}

/* 接受轴突的连接 */
int Neuron::accept_conn(Axone &axone)
{
	Synapse *synapse;

	synapse = new Synapse(this);
	assert(synapse != NULL);

	synapse->m_input.push_front(&axone);
	m_synapse_list.push_front(synapse);

	return 0;
}

/* 接受另外一个神经元的连接 */
int Neuron::accept_conn(Neuron *neuron)
{
	assert(neuron != NULL);

	return accept_conn(neuron->get_axone());
}

/* 设置神经元的输出值 */
void Neuron::set_output(ann_float v)
{
	get_axone().set_output(v);
}

} // namespace ann
