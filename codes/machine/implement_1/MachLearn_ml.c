/*
 * MachLearn_ml.c
 *
 *  Created on: 2012-3-31
 *      Author: bofu
 */

#include "base/LogFile_ml/LogFile_ml.h"
#include "base/Data_ml/Data_ml.h"
#include "NaiveBayes_ml/NaiveBayes_ml.h"
#include "DecisionTree_ml/DecisionTree_ml.h"
#include "SVM_ml/SVM_ml.h"
#include "MachLearn_ml.h"

static Config_DLL_ML *g_cdmlConfig =0 ;
/*载入动态库
输入：
cdmConfig--------载入动态库时需要的配置信息

返回值：
成功返回SUCCESS_RTML,否则返回FAILED_RTML*/
RETURN_TYPE_ML initMachLearn_ML(Config_DLL_ML cdmConfig)
{
	RETURN_TYPE_ML res=0;
	g_cdmlConfig = (Config_DLL_ML *)malloc(sizeof(Config_DLL_ML));
	g_cdmlConfig->ddmlFun = cdmConfig.ddmlFun;
	g_cdmlConfig->fmlFlag = cdmConfig.fmlFlag;
	g_cdmlConfig->llmlLevel = cdmConfig.llmlLevel;
	g_cdmlConfig->mtmlModule = cdmConfig.mtmlModule;
	g_cdmlConfig->oplmlType = cdmConfig.oplmlType;

	sprintf(g_cdmlConfig->strLogFile,"%s",cdmConfig.strLogFile);
	//Log初始化

	initLogFile_ML(cdmConfig.oplmlType,cdmConfig.llmlLevel,cdmConfig.strLogFile);


	//Data初始化
	initData_ML(cdmConfig.ddmlFun.getNum,cdmConfig.ddmlFun.getLen,
			cdmConfig.ddmlFun.getData,cdmConfig.ddmlFun.getClass);

	switch(cdmConfig.mtmlModule)
	{
		case NAIVEBAYES_MTML:
			//启动朴素贝叶斯分类器
			res = initNaiveBayesNaiveBayes_ML(g_cdmlConfig->fmlFlag);
			if(res >= OK_RTML)
			{//正常初始化贝叶斯分类器
				outputLogLogFile_ML(INFO_LEVEL_TLFML,"MachLearn_ML","initMachLearn_ML","Start NaiveBayes OK!");
			}
			break;
		case DECISIONTREE_MTML:
			//启动决策树分类器
			res = initDecisionTreeDecisionTree_ML();
			if(res >= OK_RTML)
			{//正常初始化决策树分类器
				outputLogLogFile_ML(INFO_LEVEL_TLFML,"MachLearn_ML","initMachLearn_ML","Start DecisionTree OK!");
			}
			break;
		case SVM_MTML:
			//启动SVM分类器
			res = initSVMSVM_ML();
			if(res >= OK_RTML)
			{//正常初始化SVM
				outputLogLogFile_ML(INFO_LEVEL_TLFML,"MachLearn_ML","initMachLearn_ML","Start SVM OK!");
			}
			break;
		default:
			outputLogLogFile_ML(WARNING_LEVEL_TLFML,"MachLearn_ML","initMachLearn_ML","No Classifier was set!");
			break;
	}

	return SUCCESS_RTML;
}

/*显示分类器的信息
输入：
无

返回值：
成功返回OK_RLFML,否则返回NG_RLFML*/
RETURN_TYPE_ML showInfoMachLearn_ML(void)
{
	RETURN_TYPE_ML res = 0;
	char * dsRule=0;
	switch(g_cdmlConfig->mtmlModule)
	{
		case NAIVEBAYES_MTML:
			//显示朴素贝叶斯分类器信息
			res = showNaiveBayesNaiveBayes_ML();
			if(res >= OK_RTML)
			{//正常卸载贝叶斯分类器
				outputLogLogFile_ML(INFO_LEVEL_TLFML,"MachLearn_ML","showInfoMachLearn_ML","Show Information NaiveBayes OK!");
			}
			break;
		case DECISIONTREE_MTML:
			//显示决策树分类器信息

			dsRule = getRulesDecisionTree_ML(&res);
			if(res >= OK_RTML)
			{//正常卸载决策树分类器
				outputLogLogFile_ML(INFO_LEVEL_TLFML,"MachLearn_ML","showInfoMachLearn_ML",dsRule);
				outputLogLogFile_ML(INFO_LEVEL_TLFML,"MachLearn_ML","showInfoMachLearn_ML","Show Information DecisionTree OK!");
				free(dsRule);
			}
			break;
		case SVM_MTML:
			//显示SVM分类器
			res = showSVMSVM_ML();
			if(res >= OK_RTML)
			{//显示SVM分类器正常
				outputLogLogFile_ML(INFO_LEVEL_TLFML,"MachLearn_ML","showInfoMachLearn_ML","Show Information SVM OK!");
			}
			break;
		default:
			outputLogLogFile_ML(WARNING_LEVEL_TLFML,"MachLearn_ML","showInfoMachLearn_ML","No Classifier was set!");
			break;
	}
	return res;
}
/*卸载动态库
输入：
无

返回值：
成功返回SUCCESS_RTML,否则返回NG_RLFML*/
RETURN_TYPE_ML destoryMachLearn_ML(void)
{
	RETURN_TYPE_ML res=0;
	switch(g_cdmlConfig->mtmlModule)
	{
		case NAIVEBAYES_MTML:
			//卸载朴素贝叶斯分类器
			res = destoryNaiveBayesNaiveBayes_ML();
			if(res >= OK_RTML)
			{//正常卸载贝叶斯分类器
				outputLogLogFile_ML(INFO_LEVEL_TLFML,"MachLearn_ML","destoryMachLearn_ML","Unload NaiveBayes OK!");
			}
			break;
		case DECISIONTREE_MTML:
			//卸载决策树分类器
			res = destoryDecisionTreeDecisionTree_ML();
			if(res >= OK_RTML)
			{//正常卸载决策树分类器
				outputLogLogFile_ML(INFO_LEVEL_TLFML,"MachLearn_ML","destoryMachLearn_ML","Unload DecisionTree OK!");
			}
			break;
		case SVM_MTML:
			//卸载SVM分类器
			res = destorySVMSVM_ML();
			if(res >= OK_RTML)
			{//正常卸载SVM
				outputLogLogFile_ML(INFO_LEVEL_TLFML,"MachLearn_ML","destoryMachLearn_ML","Unload SVM OK!");
			}
			break;
		default:
			outputLogLogFile_ML(WARNING_LEVEL_TLFML,"MachLearn_ML","destoryMachLearn_ML","No Classifier was set!");
			break;
	}
	destoryData_ML();
	destoryLogFile_ML();
	free(g_cdmlConfig);
	g_cdmlConfig = 0;
	return SUCCESS_RTML;
}

/*训练分类器的参数
输入：
无

返回值：
成功返回OK_RLFML,否则返回NG_RLFML*/
RETURN_TYPE_ML trainMachLearn_ML(void)
{
	RETURN_TYPE_ML res =0;
	switch(g_cdmlConfig->mtmlModule)
	{
		case NAIVEBAYES_MTML:
			//训练朴素贝叶斯分类器
			outputLogLogFile_ML(WARNING_LEVEL_TLFML,"MachLearn_ML","trainMachLearn_ML","NaiveBayes should not be trained!");
			res = OK_RTML;
			break;
		case DECISIONTREE_MTML:
			//训练决策树分类器
			res = trainDecisionTreeDecisionTree_ML();
			if(res >= OK_RTML)
			{//训练决策树分类器
				outputLogLogFile_ML(INFO_LEVEL_TLFML,"MachLearn_ML","trainMachLearn_ML","Train DecisionTree OK!");
			}
			break;
		case SVM_MTML:
			//训练SVM分类器
			res = trainSVMSVM_ML();
			if(res >= OK_RTML)
			{//训练SVM
				outputLogLogFile_ML(INFO_LEVEL_TLFML,"MachLearn_ML","trainMachLearn_ML","Train SVM OK!");
			}
			break;
		default:
			outputLogLogFile_ML(WARNING_LEVEL_TLFML,"MachLearn_ML","trainMachLearn_ML","No Classifier was set!");
			break;
	}
	return res;
}

/*训练分类器的参数
输入：
无
注：输入的数据都是double类型，如果分类器是离散型的，分类器会自动将数据分段为int类型，然后再进行离散型分类
返回值：
成功返回OK_RLFML,否则返回NG_RLFML*/
RETURN_TYPE_ML classifyMachLearn_ML(double *entry,unsigned int ui_len,int *iClassLabel)
{
	RETURN_TYPE_ML res;
	int * piEntry = 0;
	int i = 0;
	if(g_cdmlConfig->fmlFlag == DISCRETE)
	{//截断数据
		piEntry = (int *)malloc(sizeof(int)*ui_len);
		memset(piEntry,0,sizeof(int)*ui_len);
		for(i = 0; i < ui_len; i++)
		{
			piEntry[i] = (int)entry[i];
		}
	}
	switch(g_cdmlConfig->mtmlModule)
	{
		case NAIVEBAYES_MTML:
			//用朴素贝叶斯分类器，分类数据
			if(g_cdmlConfig->fmlFlag == DISCRETE)
			{
				*iClassLabel = classifyNaiveBayesDiscreteNaiveBayes_ML(piEntry,ui_len,&res);
			}else
			{
				*iClassLabel = classifyNaiveBayesContinuousNaiveBayes_ML(entry,ui_len,&res);
			}
			if(res >= OK_RTML)
			{
				outputLogLogFile_ML(INFO_LEVEL_TLFML,"MachLearn_ML","classifyMachLearn_ML","Classified by NaiveBayes OK!");
			}
			break;
		case DECISIONTREE_MTML:
			//用决策树分类器，分类数据
			if(g_cdmlConfig->fmlFlag == DISCRETE)
			{
				*iClassLabel = classDecisionTreeDecisionTree_ML(piEntry,ui_len,&res);
			}else
			{//目前不支持连续的决策树分类
				*iClassLabel = 0;
				res = FAILED_RTML;
			}


			if(res >= OK_RTML)
			{//决策树分类器，分类数据正常
				outputLogLogFile_ML(INFO_LEVEL_TLFML,"MachLearn_ML","classifyMachLearn_ML","Classified by DecisionTree OK!");
			}
			else
			{
				outputLogLogFile_ML(ERROR_LEVEL_TLFML,"MachLearn_ML","classifyMachLearn_ML","Classified by DecisionTree Failed!");
			}
			break;
		case SVM_MTML:
			//SVM分类数据
			res = classifySVMSVM_ML(entry,ui_len,iClassLabel);
			if(res >= OK_RTML)
			{//决策树分类器，分类数据正常
				outputLogLogFile_ML(INFO_LEVEL_TLFML,"MachLearn_ML","classifyMachLearn_ML","Classified by SVM OK!");
			}
			else
			{
				outputLogLogFile_ML(ERROR_LEVEL_TLFML,"MachLearn_ML","classifyMachLearn_ML","Classified by SVM Failed!");
			}
			break;
		default:
			outputLogLogFile_ML(WARNING_LEVEL_TLFML,"MachLearn_ML","classifyMachLearn_ML","No Classifier was set!");
			break;
	}
	return res;
}


