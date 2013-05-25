#ifndef _PUBLIC_ANN_BP_BPNEURON_H
#define _PUBLIC_ANN_BP_BPNEURON_H
/*
 * public/ann/bp/bpneuron.h
 * 2004-2-16 by ShanLanshan
 */

#include "public/ann/annbase.h"
#include "public/ann/neuron.h"
#include "public/ann/neuron_group.h"
#include "public/ann/interface.h"

namespace ann {

class BPNeuron;		// BP网络神经元
class BPLayer;		// BP网络层
class BPNet;		// BP网络

// 定义BP网络神经元类
class BPNeuron: public Neuron {
protected:
	//ann_int		m_layer;			/* 当前层数 */
	ann_float	m_deviation;		/* 当前节点偏差 */
public:
	BPNeuron();
	virtual ~BPNeuron();
	inline void learn_tutor(ann_float t, bool back_pass);
	inline void learn_deviation(bool back_pass);
	inline void prepair_learn() {m_deviation = ANN_FLOAT_ZERO;};
	//virtual void respond();
	//virtual void output();
};

// 定义BP网络神经元层的类
class BPLayer: public NeuronSimpleGroup, public ISerialObj {
protected:
	enum BPLayerType {INPUT_LAYER, HIDDEN_LAYER, OUTPUT_LAYER};
	enum LearnType {DERIVATIVE, GRADIENT};	// 学习算法：导数下降/梯度下降，教科书上是导数下降
	BPLayerType m_type;
	ann_int m_height;
	ann_int m_learn_type;
	ann_int m_size;
	bool m_inited;
	BPNeuron m_fix_neuron;
public:	// method of ISerialObj
	virtual ostream& operator >>(ostream &os);
	virtual istream& operator <<(istream &is);
public:
	BPLayer();
	virtual ~BPLayer();
	bool init(ann_int size);
	inline ann_int get_size() {return m_size;};
	void prepair_learn();
	virtual bool mutual_conn(BPLayer *b);
	virtual bool get_vector(IAnnVector *vec);
	virtual void output();
};

class BPLayerInput: public BPLayer {
public:
	BPLayerInput(){m_type = INPUT_LAYER;};
	virtual bool set_vector(IAnnVector *vec);
};

class BPLayerOutput: public BPLayer {
public:
	BPLayerOutput(){m_type = OUTPUT_LAYER;};
	virtual int learn_tutor(IAnnVector *vec, bool back_pass);
};

class BPLayerHidden: public BPLayer {
public:
	BPLayerHidden() {m_type = HIDDEN_LAYER;};
	virtual int learn_deviation(bool back_pass);
};

// 定义BP神经元网络类
class BPNet: 
	public NeuronGroup,
	public IAnnVectorConverter,
	public ISerialObj {
protected:
	int m_layer_count;
	ann_int m_learn_count;
	ann_int m_convert_count;
	BPLayer **m_layer;
	BPLayerInput *m_layer_input;		// 指向输入层的指针
	BPLayerOutput *m_layer_output;		// 指向输出层的指针
public:	// method of ISerialObj
	virtual ostream& operator >>(ostream &os);
	virtual istream& operator <<(istream &is);
public:
	BPNet();
	virtual ~BPNet();
	bool mutual_conn();
	bool init(const char *s);	// s like this: "1024 * 12 * 4"
	bool init(int a[], int len);
	void random();	// 随机化网络初始值
	void set_output_func(AnnFuncGroup *fg, int layer = -1);
	inline ann_int get_layer_size(ann_int layer) {
		assert(layer >= 0);
		assert(layer < m_layer_count);
		assert(m_layer != NULL);
		assert(m_layer[layer] != NULL);
		return m_layer[layer]->get_size();
	};
	inline ann_int get_layer_count() {return m_layer_count;};
	inline ann_int get_input_division() {return get_layer_size(0);};
	inline ann_int get_output_division() {return get_layer_size(get_layer_count() - 1);};
	inline ann_int get_interface_division() {return get_input_division() + get_output_division();};
public: // interface of IAnnVectorConverse
	virtual bool set_input(IAnnVector *vecin);
	virtual bool get_output(IAnnVector *vecout);
	virtual bool learn(IAnnVector *vecout);
	virtual bool convert();
};

	// global functions
	extern bool set_bp_learn_rate(ann_float rate);
	extern ann_float get_bp_learn_rate();

}

#endif /* !_PUBLIC_ANN_BP_BPNEURON_H */
