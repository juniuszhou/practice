/*
 * public/ann/neuronobj.cpp
 * 2004-03-07 By ShanLanshan
 */
#include <stdio.h>
#include <public/ann/neuronobj.h>

namespace ann {

/////////////////////////////////////////////////////////////////////////
//	class NeuronObj
/////////////////////////////////////////////////////////////////////////
NeuronObj::NeuronObj()
{
	m_type = NeuronObj::TYPE_NEURON;
	m_father = NULL;
}

NeuronObj::~NeuronObj() {}

}
