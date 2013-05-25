#ifndef _PUBLIC_ANN_ANNFUNC_ANNFUNC_H
#define _PUBLIC_ANN_ANNFUNC_ANNFUNC_H
/*
 * public/ann/annfunc/annfunc.h
 * 2004-02-16 by ShanLanshan
 */
#include "public/ann/anndef.h"
#include "public/ann/interface.h"

namespace ann {

	/* ���庯����
	 * ϵͳ�������ɸ�����õĺ����壬ÿ����Ԫ����ӵ��һ��ָ��ú������ָ��
	 * Ϊʲô��д�ɳ�������麯���أ�
	 * ����д�������麯���ĳ������ǵȼ۵ģ������麯������Ϊ��Ҳ�����ж��Ƿ�Ϊ��
	 * ���ҵ�ÿ����Ԫӵ�еĲ���ָ����õĺ�����ָ��(�൱��_vptr)������һ��
	 * �����Ŀ�������ôЧ�ʾͻ��һЩ
	 * ���ң��Ǻǣ���û���Թ�����̬��Ա�������������麯����
	 */
	typedef struct {
		/*
		bool inited;
		bool suggest_cache;
		*/
		const char *name;						//	����������
		const char *desc;						//	������˵��

		//	��������������֮���Բ����ɹ�������������
		//	��Ҫ����Ϊ������ʱ��ϣ����������
		//	����Ҳ��ϣ��Ϊÿ����ͬ�Ĵ���-����������д��ͬ����
		bool (*init)();							//	��ʼ������
		void (*finalize)();						//	���ٺ���

		ann_float(*main)(ann_float);			//	����������
		ann_float(*derivative)(ann_float);		//	�����������ĵ���
		ann_float(*derivative2)(ann_float);		//	���������ĵ���ֵ������Ĳ�������������ȡֵ
												//	����Ϊ�˼ӿ��ٶȣ���Щ��������˵������S�ͺ���
												//	�����ı���Ǻܸ��ӣ�Ҫ��e���ݣ���������������
												//	֮��Ĺ�ϵȴ����ļ򵥡�
		// ����ĺ���ָ��������ķ��棬�����Ǵ���������
		// ��Ҳ�ǿ��ǵ�Ч�ʵ����أ�����������ʱ����԰ѹؼ��㷨Ƕ�뵽���������ѭ�����ڲ�
		// �Ӷ���ʡ�˴�����ָ����ֵ�ͺ������ÿ���
		// ���ǵĲ�����ʽ����ͬ�������������src, ����Ϊlen, ����ŵ�����dst��,
		// src��dst�����ظ��������ܸ��ǣ���Ҫô��ȫ�����ǣ�Ҫô��ȫ����
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
