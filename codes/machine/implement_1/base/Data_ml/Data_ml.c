/*
 * Data_ml.c
 *
 *  Created on: 2012-4-5
 *      Author: bofu
 */
#include "Data_ml.h"

/*全局变量定义*/

static DataFuncDATA_ML *g_dfdmDataSet=0;
/*初始化Data_ml模块
输入：
无


返回值：
成功返回SUCCESS_RTML,否则返回FAILED_RTML*/
RETURN_TYPE_ML initData_ML(getNumFunc getNum,getLenFunc getLen,getDataFunc getData,getClassFunc getClass)
{

	g_dfdmDataSet  = (DataFuncDATA_ML *)malloc(sizeof(DataFuncDATA_ML));
	if(g_dfdmDataSet == 0)
	{
		return FAILED_RTML;
	}
	memset(g_dfdmDataSet,0,sizeof(DataFuncDATA_ML));
	g_dfdmDataSet->getNum = getNum;
	g_dfdmDataSet->getLen = getLen;
	g_dfdmDataSet->getData = getData;
	g_dfdmDataSet->getClass = getClass;


	return SUCCESS_RTML;
}

/*获取样本大小
输入：
无

返回值：
返回数据*/
unsigned int fetchNumData_ML(void)
{
	return g_dfdmDataSet->getNum();
}

/*获取样本特征个数
输入：
无

返回值：
返回数据*/
unsigned int fetchLenData_ML(void)
{
	return g_dfdmDataSet->getLen();
}

/*获取数据
输入：
uiEntryIdx--------------数据的index,从0开始
uiFeatureIdx------------数据特征的index，从0开始

返回值：
返回数据*/
double fetchdataData_ML(unsigned int uiEntryIdx,unsigned int uiFeatureIdx)
{
	return (double)g_dfdmDataSet->getData(uiEntryIdx+1,uiFeatureIdx+1);
}

/*获取分类情况
输入：
uiEntryIdx--------------数据的index

返回值：
分类标签*/
int fetchclassData_ML(unsigned int uiEntryIdx)
{
	return (int)g_dfdmDataSet->getClass(uiEntryIdx+1);
}

/*获取样本分类标签数量和标签
输入：
无

返回值：
返回数据*/
int *fetchClassTypeData_ML(unsigned int *count)
{
	unsigned int uiRowCount = fetchNumData_ML();
	int *iClassLabels=(int *)malloc(sizeof(int)*uiRowCount);
	int *iClassLabelsReturn = 0;
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int len = 0;
	int flag = 0;
	int iTemp = 0;
	iClassLabels[0] = fetchclassData_ML(0);

	len=1;
	for(i = 1; i < uiRowCount; i++)
	{
		iTemp = fetchclassData_ML(i);
		for(j = 0; j < len; j++)
		{
			if(iTemp == iClassLabels[j])
			{
				flag =1;
				break;
			}
		}
		if(flag == 0)
		{//查找已经存在的Label失败
			iClassLabels[len] = iTemp;
			len++;
		}
		flag = 0;
	}

	*count = len;
	iClassLabelsReturn = (int *)malloc(sizeof(int)*len);
	memset(iClassLabelsReturn,0,sizeof(int)*len);
	for(i = 0; i<len; i++)
	{
		iClassLabelsReturn[i] = iClassLabels[i];
	}
	free(iClassLabels);
	iClassLabels = 0;
	return iClassLabelsReturn;
}
/*卸载Data_ml模块
输入：
无

返回值：
成功返回SUCCESS_RTML,否则返回FAILED_RTML*/
RETURN_TYPE_ML destoryData_ML(void)
{
	free(g_dfdmDataSet);
	return SUCCESS_RTML;
}
