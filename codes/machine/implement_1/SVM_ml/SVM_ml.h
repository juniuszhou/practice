/*
 * SVM_ml.h
 *
 *  Created on: 2012-4-10
 *      Author: bofu
 */

#ifndef SVM_ML_H_
#define SVM_ML_H_
#include "../MachLearn_ml.h"
#include "../base/Data_ml/Data_ml.h"
#include "../base/LogFile_ml/LogFile_ml.h"
#include "../base/Math_ml/Math_ml.h"

typedef struct DataSetSize_SVM_ML
{
	unsigned int uiRow;	//样本数
	unsigned int uiCol;	//特征长度
} DataSetSize_SVM_ML;

//初始化SVM
RETURN_TYPE_ML initSVMSVM_ML();

//训练SVM分类器
RETURN_TYPE_ML trainSVMSVM_ML(void);

//显示SVM分类器的参数
RETURN_TYPE_ML showSVMSVM_ML(void);

//分类数据
RETURN_TYPE_ML classifySVMSVM_ML(double *entry,unsigned int uiLen,int *iClassLabel);

//分类数据
RETURN_TYPE_ML destorySVMSVM_ML();
#endif /* SVM_ML_H_ */
