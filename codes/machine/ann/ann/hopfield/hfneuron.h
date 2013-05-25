#ifndef _PUBLIC_ANN_HOPFIELD_HFNEURON_H
#define _PUBLIC_ANN_HOPFIELD_HFNEURON_H
/*
 * public/ann/hopfield/hfneuron.h
 * 2004-05-28 by ShanLanshan
 */
#include "public/ann/annbase.h"
#include "public/ann/neuron.h"
#include "public/ann/neuron_group.h"
#include "public/ann/interface.h"

namespace ann {

	class HFNeuron: public Neuron {
	private:
		ann_float m_old_value;
		ann_float m_adjust;
	public:
		HFNeuron();
		~HFNeuron();
	};

	class HFSimpleGroup: public NeuronSimpleGroup {
	public:
		HFSimpleGroup();
		HFSimpleGroup(int size);
		~HFGroup();
		bool init(int size);
		bool mutual_conn();
		void learn();
		void restart();
		void work() {respond(); output(); learn();};
	};

}// namespace ann

#endif /* !_PUBLIC_ANN_HOPFIELD_HFNEURON_H */
