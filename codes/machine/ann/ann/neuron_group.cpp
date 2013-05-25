/*
 * public/ann/neuron_group.cpp
 * 2004-03-07 by ShanLanshan
 */
#include <stdio.h>
#include <assert.h>
#include <public/ann/annbase.h>
#include <public/ann/neuron_group.h>

namespace ann {
/////////////////////////////////////////////////////////////////////
//	class NeuronGroup
/////////////////////////////////////////////////////////////////////
NeuronGroup::NeuronGroup()
{
}

NeuronGroup::~NeuronGroup() 
{
	NeuronObjSlot slot;
	//	delete all slot in the group
	for (
		list<NeuronObjSlot>::iterator i = m_objlist.begin();
		i != m_objlist.end();
		++i
	) {
		slot = *i;
		if (slot.m_obj == NULL)
			continue;
		if (slot.m_flag & NeuronObjSlot::FLAG_ATTACH)
			continue;
		delete slot.m_obj;
	}
}

ann_int NeuronGroup::add(NeuronObj *obj, ann_int flag)
{
	assert(obj != NULL);

	NeuronObjSlot slot;
	slot.m_obj = obj;
	slot.m_flag = flag;

	NeuronObj *father;
	father = static_cast<NeuronObj*>(this);
	assert(father != NULL);
	obj->set_father(father);

	m_objlist.push_front(slot);

	return 0;
}

NeuronObj *NeuronGroup::move_first(iterator *i)
{
	if (i == NULL)
		i = &m_currobj;
	(*i) = m_objlist.begin();
	return (*(*i)).m_obj;
}

NeuronObj *NeuronGroup::move_next(iterator *i)
{
	if (i == NULL)
		i = &m_currobj;
	++(*i);
	return (*(*i)).m_obj;
}

bool NeuronGroup::not_end(iterator *i)
{
	if (i == NULL)
		i = &m_currobj;

	if ((*i) == m_objlist.end())
		return false;
	else
		return true;
}

int NeuronGroup::get_count()
{
	return static_cast<int> (m_objlist.size());
}

/////////////////////////////////////////////////////////////////////
//	class NeuronSimpleGroup
/////////////////////////////////////////////////////////////////////
NeuronSimpleGroup::NeuronSimpleGroup() {}

NeuronSimpleGroup::~NeuronSimpleGroup() {}

void NeuronSimpleGroup::random()
{
	NeuronObj *obj;
	Neuron *n;

	for (obj=move_first(); not_end(); obj=move_next()) {
		assert(obj != NULL);
		n = dynamic_cast<Neuron*> (obj);
		assert(n != NULL);
		n->random();
	}
}

void NeuronSimpleGroup::set_output_func(AnnFuncGroup *fg)
{
	NeuronObj *obj;
	Neuron *n;

	for (obj=move_first(); not_end(); obj=move_next()) {
		assert(obj != NULL);
		n = dynamic_cast<Neuron*> (obj);
		assert(n != NULL);
		n->set_output_func(fg);
	}
}

void NeuronSimpleGroup::respond()
{
	NeuronObj *obj;
	Neuron *n;

	for (obj=move_first(); not_end(); obj=move_next()) {
		assert(obj != NULL);
		n = dynamic_cast<Neuron*> (obj);
		assert(n != NULL);
		n->respond();
	}
}

void NeuronSimpleGroup::output()
{
	NeuronObj *obj;
	Neuron *n;

	for (obj=move_first(); not_end(); obj=move_next()) {
		assert(obj != NULL);
		n = dynamic_cast<Neuron*> (obj);
		assert(n != NULL);
		n->output();
	}
}

}	// namespace ann
