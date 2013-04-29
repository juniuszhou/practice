/*
 * Math_ml.c
 *
 *  Created on: 2012-4-6
 *      Author: bofu
 */

#include "Math_ml.h"
//计算两个计数的熵
double calculateEntropyMath_ML(unsigned int uiPositiveCount,unsigned int uiNegativeCount)
{
	if( (uiPositiveCount == 0) || (uiNegativeCount == 0) )
	{
		return 0.00;
	}
	return -(uiPositiveCount*1.0/(uiPositiveCount+uiNegativeCount))*
		(log(uiPositiveCount*1.0/(uiPositiveCount+uiNegativeCount))/log(2.0))
			-(uiNegativeCount*1.0/(uiPositiveCount+uiNegativeCount))*
		(log(uiNegativeCount*1.0/(uiPositiveCount+uiNegativeCount))/log(2.0));
}

//计算两个向量的内积
double calculateInnerProduct(double *entryA, double *entryB, unsigned int uiLen)
{
	unsigned int i=0;
	double sum=0;
	for(i = 0; i<uiLen; i++)
	{
		sum = sum + entryA[i]*entryB[i];
	}
	return sum;
}
