/*
 * public/ann/bp/bpneuron.cpp
 * 2004-2-16 by ShanLanshan
 */

#include "public/ann/bp/bpneuron.h"

namespace ann {

	ann_float g_bp_learn_rate = 0.1;
///////////////////////////////////////////////////////////////////////////
//	class BPNeuron
///////////////////////////////////////////////////////////////////////////
BPNeuron::BPNeuron(): m_deviation(ANN_FLOAT_ZERO) {}
BPNeuron::~BPNeuron() { }

inline void BPNeuron::learn_tutor(ann_float v, bool back_pass)
{
	m_deviation = v - get_output();
	//m_deviation = m_deviation * m_deviation * m_deviation;
	learn_deviation(back_pass);
}

inline void BPNeuron::learn_deviation(bool back_pass)
{
	ann_float net_deviation, respond_derivative;
	AnnFuncGroup *fg;

	fg = get_output_func();
	assert(fg != NULL);

	// 计算响应误差
	if (fg->derivative2 == NULL) {
		assert(fg->derivative != NULL);
		respond_derivative = fg->derivative(get_respond());
	} else {
		respond_derivative = fg->derivative2(get_output());
	}
	//net_deviation = m_deviation * respond_derivative;
	net_deviation = m_deviation * respond_derivative;

	// 根据响应误差修改连接到改神经元的突触权值
	// 将误差反向传播到前一层的神经元
	Synapse *synapse;
	Neuron *n;
	BPNeuron *bpn;
	ann_float rate = g_bp_learn_rate;
	ann_float deviation = net_deviation * rate;
	for (
		list<Synapse*>::iterator i = m_synapse_list.begin();
		i != m_synapse_list.end();
		++i
	) {
		synapse = (*i);
		assert(synapse != NULL);

		// 将误差反向传播到前一层的神经元
		if (back_pass) {
			n = synapse->get_input_neuron();
			assert(n != NULL);
			bpn = dynamic_cast<BPNeuron*> (n);
			assert(bpn != NULL);

			bpn->m_deviation += 
				net_deviation * synapse->get_power(); 	// 这句代码表明在学习前一定要调用prepair_learn()
		}

		// 根据响应误差修改连接到改神经元的突触权值
		synapse->update_power(deviation * synapse->get_input());
	}
}


///////////////////////////////////////////////////////////////////////////
//	class BPLayer
///////////////////////////////////////////////////////////////////////////
BPLayer::BPLayer(): m_height(0), m_learn_type(DERIVATIVE), m_inited(false), m_size(0)
{}

bool BPLayer::init(ann_int size)
{
	NeuronObj *obj;
	BPNeuron *bpn;

	for (int i=0; i<size; ++i) {
		bpn = new BPNeuron;
		obj = static_cast<NeuronObj*> (bpn);
		assert(obj != NULL);
		this->add(obj, 0);
	}
	m_fix_neuron.set_output(1.0);
	m_inited = true;
	m_size = size;

	return true;
}

BPLayer::~BPLayer() {}

void BPLayer::prepair_learn()
{
	NeuronObj *obj;
	BPNeuron *bpn;

	for (obj=move_first(); not_end(); obj=move_next()) {
		assert(obj != NULL);
		bpn = dynamic_cast<BPNeuron*> (obj);
		assert(bpn != NULL);
		bpn->prepair_learn();
	}
}

bool BPLayer::mutual_conn(BPLayer *b)
{
	Neuron *n, *n2;
	NeuronObj *obj, *obj2;

	assert(b != NULL);

	for (obj=move_first(); not_end(); obj=move_next()) {
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

/* 将向量导入输入层 */
bool BPLayerInput::set_vector(IAnnVector *vec)
{
	NeuronObj *obj;
	BPNeuron *bpn;
	int i, size;

	assert(vec != NULL);

	size = vec->get_size();
	for (i=0,obj=move_first(); not_end(); obj=move_next(),++i) {
		assert(obj != NULL);
		bpn = dynamic_cast<BPNeuron*> (obj);
		assert(bpn != NULL);
		bpn->set_output(i < size ? vec->get_element(i) : ANN_FLOAT_ZERO);
	}

	return true;
}

/* 从BP网络的某层导出向量 */
bool BPLayer::get_vector(IAnnVector *vec)
{
	NeuronObj *obj;
	BPNeuron *bpn;
	int i, size;

	assert(vec != NULL);

	size = vec->get_size();
	for (i=0,obj=move_first(); not_end(); obj=move_next(),++i) {
		assert(obj != NULL);
		bpn = dynamic_cast<BPNeuron*> (obj);
		assert(bpn != NULL);
		if (i < size)
			vec->set_element(i, bpn->get_output());
	}

	for (; i<size; ++i) {
		vec->set_element(i, ANN_FLOAT_ZERO);
	}

	return true;
}

void BPLayer::output()
{
	NeuronSimpleGroup::output();
	m_fix_neuron.set_output(1.0);
}

ostream& BPLayer::operator >> (ostream &os)
{
	Neuron *n;
	NeuronObj *obj;
	AnnFuncGroup *fg;
	int i;

	for (i=0,obj=move_first(); not_end(); obj=move_next(),++i) {
		assert(obj != NULL);
		n = dynamic_cast<Neuron*> (obj);
		assert(n != NULL);
		fg = n->get_output_func();
		assert(fg != NULL);
		os << "NEURON " << i << " outputfunc " << fg->name << endl;
		for (list<Synapse*>::iterator i = n->m_synapse_list.begin();
			i != n->m_synapse_list.end();
			++i
		){
			os << (*i)->get_power() << " ";
		}
		os << endl;
	}

	return os;
}

istream& BPLayer::operator << (istream &is)
{
	Neuron *n;
	NeuronObj *obj;
	int i, j;
	char buf[128], funcname[128];
	ann_float v;

	for (i=0,obj=move_first(); not_end(); obj=move_next(),++i) {
		assert(obj != NULL);
		n = dynamic_cast<Neuron*> (obj);
		assert(n != NULL);
		is >> buf >> j >> buf >> funcname;
		n->set_output_func(annfunc_get(funcname));
		for (list<Synapse*>::iterator i = n->m_synapse_list.begin();
			i != n->m_synapse_list.end();
			++i
		){
			is >> v;
			(*i)->set_power(v);
		}

	}

	return is;
}

int BPLayerOutput::learn_tutor(IAnnVector *vec, bool back_pass)
{
	assert(vec != NULL);

	NeuronObj *obj;
	BPNeuron *bpn;

	int i, n = vec->get_size();
	for (i=0,obj=move_first(); i<n&&not_end(); ++i,obj=move_next()) {
		assert(obj != NULL);
		bpn = dynamic_cast<BPNeuron*> (obj);
		assert(bpn != NULL);
		bpn->learn_tutor(vec->get_element(i), back_pass);
	}

	return 0;
}

int BPLayerHidden::learn_deviation(bool back_pass)
{
	NeuronObj *obj;
	BPNeuron *bpn;

	for (obj=move_first(); not_end(); obj=move_next()) {
		assert(obj != NULL);
		bpn = dynamic_cast<BPNeuron*> (obj);
		assert(bpn != NULL);
		bpn->learn_deviation(back_pass);
	}

	return 0;
}


///////////////////////////////////////////////////////////////////////////
//	class BPNet
///////////////////////////////////////////////////////////////////////////
BPNet::BPNet():
	m_layer_count(0),
	m_convert_count(0),
	m_learn_count(0),
	m_layer(NULL),
	m_layer_input(NULL),
	m_layer_output(NULL)
{}

bool BPNet::init(const char *s)
{
	char buf[MAX_BPNET_LAYER * 2];
	int a[MAX_BPNET_LAYER];
	int i, n;
	char ns[MAX_BPNET_LAYER * 2];

	if (s == NULL)
		s = "32 * 16 * 8";

	strncpy(buf, s, sizeof(buf));
	buf[sizeof(buf) - 1] = '\0';

	const char *p = buf, *digit = "0123456789";

	for (i=0; i<sizeof(a)/sizeof(a[0]); ++i) {
		p += strcspn(p, digit);
		n = static_cast<int> (strspn(p, digit));
		if (n < 1)
			break;

		memcpy(ns, p, n);
		ns[n] = '\0';
		a[i] = atoi(ns);

		p += n;
	}

	return init(a, i);
}

bool BPNet::init(int a[], int len)
{
	NeuronObj *obj;
	BPLayerHidden *hl;

	assert(a != NULL);
	assert(len > 1);

	m_convert_count = m_learn_count = 0;
	m_layer_count = len;
	m_layer = new BPLayer*[len];
	assert(m_layer != NULL);

	//	generate input layer
	m_layer_input = new BPLayerInput;
	assert(m_layer_input != NULL);
	m_layer_input->init(a[0]);
	obj = static_cast<NeuronObj*> (m_layer_input);
	assert(obj != NULL);
	this->add(obj, 0);
	m_layer[0] = static_cast<BPLayer*> (m_layer_input);
	assert(m_layer[0] != NULL);

	//	generate output layer
	m_layer_output = new BPLayerOutput;
	assert(m_layer_output != NULL);
	m_layer_output->init(a[len - 1]);
	obj = static_cast<NeuronObj*> (m_layer_output);
	assert(obj != NULL);
	this->add(obj, 0);
	m_layer[len - 1] = static_cast<BPLayer*> (m_layer_output);
	assert(m_layer[len - 1] != NULL);

	//	generate hidden layer
	for (int i=1; i<len-1; ++i) {
		hl = new BPLayerHidden;
		assert(hl != NULL);
		hl->init(a[i]);
		obj = static_cast<NeuronObj*> (hl);
		assert(obj != NULL);
		this->add(obj, 0);
		m_layer[i] = static_cast<BPLayer*> (hl);
		assert(m_layer[i] != NULL);
	}

	return true;
}

BPNet::~BPNet()
{
	if (m_layer != NULL) {
		delete[] m_layer;
		m_layer = NULL;
	}
}

ostream& BPNet::operator >> (ostream &os)
{
	assert(os.good());

	os << "BPNET001" << endl << endl 
		<< m_learn_count << " " << m_convert_count << endl << endl
		<< m_layer_count << endl;
	
	assert(m_layer != NULL);
	for (int i=0; i<m_layer_count; ++i) {
		assert(m_layer[i] != NULL);
		os << m_layer[i]->get_size() << " ";
	}

	for (int i=0; i<m_layer_count; ++i) {
		assert(m_layer[i] != NULL);
		os << endl << endl << "LAYER " << i <<endl;
		(*m_layer[i]) >> os;
	}

	return os;
}

istream& BPNet::operator << (istream &is)
{
	assert(is.good());
	char buf[128];
	int n, learn_count, convert_count;

	is >> buf;
	if (memcmp(buf, "BPNET001", 8) != 0)
		return is;

	int layersize[MAX_BPNET_LAYER], layers;

	is >> learn_count >> convert_count >> layers;
	for (int i=0; i<layers; ++i) {
		is >> layersize[i];
	}
	init(layersize, layers);
	m_learn_count = learn_count;
	m_convert_count = convert_count;

	mutual_conn();

	for (int i=0; i<m_layer_count; ++i) {
		assert(m_layer[i] != NULL);
		is >> buf >> n;
		*m_layer[i] << is;
	}

	return is;
}

//	BP网络各个层之间进行前向互连
bool BPNet::mutual_conn()
{
	assert(m_layer != NULL);
	for (int i=1; i<m_layer_count; ++i) {
		assert(m_layer[i] != NULL);
		m_layer[i]->mutual_conn(m_layer[i - 1]);
	}

	return true;
}

// BP网络设置输入向量
bool BPNet::set_input(IAnnVector *vecin)
{
	assert(m_layer_input != NULL);
	assert(vecin != NULL);
	m_layer_input->set_vector(vecin);
	return true;
}

// BP网络取出输出向量
bool BPNet::get_output(IAnnVector *vecout)
{
	assert(m_layer_output != NULL);
	assert(vecout != NULL);
	m_layer_output->get_vector(vecout);
	return true;
}

// BP网络以vecout向量为导师进行一轮学习
bool BPNet::learn(IAnnVector *vecout)
{
	assert(m_layer != NULL);

	BPLayer *layer;
	for (int i=1; i<m_layer_count; ++i) {
		layer = m_layer[i];
		assert(layer != NULL);
		layer->prepair_learn();
	}

	BPLayerHidden *h;
	if (m_layer_output != NULL) // maybe not inited yet!
		m_layer_output->learn_tutor(vecout, m_layer_count > 2);
	for (int i=m_layer_count-2; i > 0; --i) {
		assert(m_layer[i] != NULL);
		h = dynamic_cast<BPLayerHidden*> (m_layer[i]);
		assert(h != NULL);
		h->learn_deviation(i > 1);
	}

	++m_learn_count;
	return true;
}

// BP网络开始计算，转化输入向量
bool BPNet::convert()
{
	// 计算每个层的响应和输出
	assert(m_layer != NULL);
	for (int i=1; i<m_layer_count; ++i) {
		assert(m_layer[i] != NULL);
		m_layer[i]->respond();
		m_layer[i]->output();
	}
	++m_convert_count;
	return true;
}

// 随机化网络初始值
void BPNet::random()
{
	// 计算每个层的响应和输出
	assert(m_layer != NULL);
	for (int i=1; i<m_layer_count; ++i) {
		assert(m_layer[i] != NULL);
		m_layer[i]->random();
	}
}

void BPNet::set_output_func(AnnFuncGroup *fg, int layer)
{
	assert(fg != NULL);
	assert(layer < m_layer_count);

	if (layer < 0) {
		for (int i=0; i<m_layer_count; ++i) {
			set_output_func(fg, i);
		}
		return;
	}

	
	assert(m_layer[layer] != NULL);
	m_layer[layer]->set_output_func(fg);
}

	extern bool set_bp_learn_rate(ann_float rate)
	{
		g_bp_learn_rate = rate;
		return true;
	}

	extern ann_float get_bp_learn_rate()
	{
		return g_bp_learn_rate;
	}

}	// namespace ann
