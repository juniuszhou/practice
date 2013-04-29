/*
 * NaiveBayes_ml.h
 *
 *  Created on: 2012-4-5
 *      Author: bofu
 * Description: 朴素贝叶斯分类器
 */

#ifndef NAIVEBAYES_ML_H_
#define NAIVEBAYES_ML_H_
#include "../MachLearn_ml.h"
#include "../base/Data_ml/Data_ml.h"
#include "../base/LogFile_ml/LogFile_ml.h"
#include "../base/Math_ml/Math_ml.h"





//样本的统计特征
typedef struct Stat_NB_ML
{
	unsigned int	ui_CountClass;		//类的种类
	unsigned int	ui_Len;				//特征的长度
	unsigned int	ui_num;				//数据的个数
	double *		pd_PrioriProbClass;	//类的先验概率（数组的长度由ui_CountClass决定）
	int *			pi_ClassLabel;		//所有的类标记（数组的长度由ui_CountClass决定）
	FLAG_ML			f_flag;				//该分类的类型，离散或者连续

} Stat_NB_ML;

//初始化相关的统计特征
RETURN_TYPE_ML initNaiveBayesNaiveBayes_ML(FLAG_ML flag);

//显示分类器的信息
RETURN_TYPE_ML showNaiveBayesNaiveBayes_ML();

//用贝叶斯分类器分类输入的数据(离散)
int classifyNaiveBayesDiscreteNaiveBayes_ML(int *entry,unsigned int ui_len,RETURN_TYPE_ML *res);

//用贝叶斯分类器分类输入的数据(连续)
int classifyNaiveBayesContinuousNaiveBayes_ML(double *entry,unsigned int ui_len,RETURN_TYPE_ML *res);

//卸载朴素贝叶斯分类器
RETURN_TYPE_ML destoryNaiveBayesNaiveBayes_ML(void);
#endif /* NAIVEBAYES_ML_H_ */
