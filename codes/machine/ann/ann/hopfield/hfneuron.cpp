/*
 * public/ann/hopfield/hfneuron.cpp
 * 2004-05-28 by ShanLanshan
 */
#include <stdio.h>
#include <assert.h>
#include "public/ann/hopfield/hfneuron.h"

namespace ann {

	//////////////////////////////////////////////////////////////
	//	class HFNeuron
	//////////////////////////////////////////////////////////////
	HFNeuron::HFNeuron():
		m_old_value(ANN_FLOAT_ZERO),
		m_adjust(ANN_FLOAT_ZERO) { }
	HFNeuron::~HFNeuron(){}

	//////////////////////////////////////////////////////////////
	//	class HFGroup
	//////////////////////////////////////////////////////////////
	HFGroup::HFGroup(){}
	HFGroup::HFGroup(int size) { init(size); }
	HFGroup::~HFGroup(){}
	bool HFGroup::init(int size)
	{
		NeuronObj *obj;
		HFNeuron *hfn;

		for (int i=0; i<size; ++i) {
			hfn = new HFNeuron;
			obj = static_cast<NeuronObj*> (hfn);
			assert(obj != NULL);
			this->add(obj, 0);
		}

		return true;
	}

	bool HFGroup::mutual_conn()
	{
		Neuron *n, *n2;
		NeuronObj *obj, *obj2;

		assert(b != NULL);

		NeuronGroup::iterator i, j;
		for (obj=move_first(&i); not_end(&i); obj=move_next(&i)) {
			assert(obj != NULL);
			n = dynamic_cast<Neuron*> (obj);
			assert(n != NULL);
			n->accept_conn(&b->m_fix_neuron);
			for (obj2=b->move_first(); b->not_end(); obj2=b->move_next()) {
				n2 = dynamic_cast<Neuron*> (obj2);
				assert(n2 != NULL);
				n->accept_conn(n2);
			}
		}
		return true;
	}

	void HFGroup::learn()
	{
	}


	void HFGroup::restart()
	{
	}

} // namespace ann
