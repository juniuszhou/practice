/*
 * Math_ml.h(math文件中的函数直接使用没有初始化过程)
 *
 *  Created on: 2012-4-6
 *      Author: bofu
 */

#ifndef MATH_ML_H_
#define MATH_ML_H_
#include "../../MachLearn_ml.h"
#define PI 3.14159265
/*定义接口函数*/
//计算两个计数的熵
double calculateEntropyMath_ML(unsigned int uiPositiveCount,unsigned int uiNegativeCount);
//计算两个向量的内积
double calculateInnerProduct(double *entryA, double *entryB, unsigned int uiLen);
#endif /* MATH_ML_H_ */
