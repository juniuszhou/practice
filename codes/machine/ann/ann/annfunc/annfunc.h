#ifndef _PUBLIC_ANN_ANNFUNC_ANNFUNC_H
#define _PUBLIC_ANN_ANNFUNC_ANNFUNC_H
/*
 * public/ann/annfunc/annfunc.h
 * 2004-02-16 by ShanLanshan
 */
#include "public/ann/anndef.h"
#include "public/ann/interface.h"

namespace ann {

	/* 定义函数族
	 * 系统中有若干个定义好的函数族，每个神经元可以拥有一个指向该函数族的指针
	 * 为什么不写成抽象类的虚函数呢？
	 * 这样写与做成虚函数的抽象类是等价的，但是虚函数不能为空也不能判断是否为空
	 * 而且当每个神经元拥有的不是指向定义好的函数族指针(相当于_vptr)，而是一个
	 * 完整的拷贝，那么效率就会高一些
	 * 而且，呵呵，我没有试过，静态成员函数可以做成虚函数吗？
	 */
	typedef struct {
		/*
		bool inited;
		bool suggest_cache;
		*/
		const char *name;						//	函数族名称
		const char *desc;						//	函数族说明

		//	下面这两个函数之所以不做成构建和析构函数
		//	主要是因为我们有时候不希望调用他们
		//	而且也不希望为每个不同的创建-析构函数对写不同的类
		bool (*init)();							//	初始化函数
		void (*finalize)();						//	销毁函数

		ann_float(*main)(ann_float);			//	调用主函数
		ann_float(*derivative)(ann_float);		//	调用主函数的导数
		ann_float(*derivative2)(ann_float);		//	求主函数的导数值，输入的参数是主函数的取值
												//	这是为了加快速度，有些函数比如说优美的S型函数
												//	导数的表达是很复杂，要对e求幂，但是它和主函数
												//	之间的关系却出奇的简单。
		// 下面的函数指针是上面的翻版，但都是处理多个量的
		// 这也是考虑到效率的因素，处理多个量的时候可以把关键算法嵌入到多个量计算循环的内部
		// 从而节省了大量的指针求值和函数调用开销
		// 他们的参数形式都相同，计算针对向量src, 长度为len, 结果放到向量dst中,
		// src和dst可以重复，但不能覆盖，即要么完全不覆盖，要么完全覆盖
		void (*multi_main)(ann_float *src, ann_int len, ann_float *dst);
		void (*multi_derivative)(ann_float *src, ann_int len, ann_float *dst);
		void (*multi_derivative2)(ann_float *src, ann_int len, ann_float *dst);
	} AnnFuncGroup;

	class AnnFuncGroupFactory {
	public:
		static const int ANN_MAX_FUNC_GROUP = 16;
		int m_funcgroup_count;
		AnnFuncGroup *m_funcgroup[ANN_MAX_FUNC_GROUP];
		bool m_inited;
	public:
		AnnFuncGroupFactory();
		~AnnFuncGroupFactory();
		bool init();
		void finalize();
	};

	extern AnnFuncGroupFactory g_func_factory;

	typedef ann_float (*ann_func_t)(ann_float);
	typedef ann_float (*ann_multi_func_t)(ann_float *src, ann_int len, ann_float *dst);

	extern AnnFuncGroup *annfunc_get(const char *name);

}	//	namespace ann

#endif /* _PUBLIC_ANN_ANNFUNC_ANNFUNC_H */
