/*
 * NaiveBayes_ml.c
 *
 *  Created on: 2012-4-5
 *      Author: bofu
 */
#include "NaiveBayes_ml.h"

/*全局变量定义*/

static Stat_NB_ML * g_snbmlStatistic=0;
/*******************************/

//基于数据集查找满足指定的分类情况下，对应的第index个分量的条件概率
static double _findProbDiscrete(unsigned int index, int value, int class, RETURN_TYPE_ML *res)
{
	unsigned int ui_CountClass = 0;		//类是class的数据的计数
	unsigned int ui_CountFeature = 0;	//在class的情况下，特征的取值是value的数据计数
	double d_Prob = 0;
	unsigned int i = 0;

	for(i = 0; i<g_snbmlStatistic->ui_num; i++)
	{//遍历数据集


		if(fetchclassData_ML(i) == class)
		{
			ui_CountClass++;
			if((int)fetchdataData_ML(i,index) == value)
			{
				ui_CountFeature++;
			}
		}
	}
	d_Prob = (ui_CountFeature*1.0)/(ui_CountClass*1.0);
	*res = SUCCESS_RTML;
	return d_Prob;
}

//基于数据集计算满足指定的分类class情况下，对应的第index个分量的条件概率
static double _findProbContinus(unsigned int index, double value, int class, RETURN_TYPE_ML *res)
{
	double d_Mean = 0.0;		//分类为class的数据的第index个特征值的均值
	double d_Std = 0.0;			//分类为class的数据的第index个特征值的标准差
	double d_Prob = 0.0;		//第index个特征的值为values时的条件概率

	double d_coef = 1.0;//公式的系数 1/(sqrt(2*pi)*第i类的标准差)
	double d_expo = 1.0;//指数的值，(x-u)^2/(2*第i类的标准差^2)

	unsigned int ui_CountClass = 0;	//分类为class的数据项的数量
	unsigned int i = 0;

	for(i = 0; i<g_snbmlStatistic->ui_num; i++)
	{//遍历数据集
		if(fetchclassData_ML(i) == class)
		{
			ui_CountClass++;
			d_Mean = d_Mean + fetchdataData_ML(i,index);
		}
	}
	//计算均值
	d_Mean = d_Mean*1.0/ui_CountClass;

	//计算标准差
	for(i = 0; i<g_snbmlStatistic->ui_num; i++)
	{//遍历数据集
		d_Std = d_Std + (fetchdataData_ML(i,index)-d_Mean)*(fetchdataData_ML(i,index)-d_Mean);
	}
	d_Std = 1.0*sqrt(d_Std/ui_CountClass);

	d_coef = 1.0/(sqrt(2*PI)*d_Std);//计算系数的值
	d_expo= (value-d_Mean)*(value-d_Mean)/(2*d_Std*d_Std);//指数的值

	d_Prob = d_coef*exp(-d_expo);


	return d_Prob;
}

//初始化相关的统计特征
RETURN_TYPE_ML initNaiveBayesNaiveBayes_ML(FLAG_ML flag)
{
	Stat_NB_ML *ps_Stat = 0;
	unsigned int i = 0;
	unsigned int j = 0;

	ps_Stat = (Stat_NB_ML *)malloc(sizeof(Stat_NB_ML));
	if(ps_Stat == 0)
	{
		return FAILED_RTML;
	}
	memset(ps_Stat,0,sizeof(Stat_NB_ML));

	ps_Stat->ui_Len = fetchLenData_ML();
	ps_Stat->ui_num = fetchNumData_ML();
	ps_Stat->f_flag = flag;

	ps_Stat->pi_ClassLabel=fetchClassTypeData_ML(&ps_Stat->ui_CountClass);



	ps_Stat->pd_PrioriProbClass= (double *)malloc(sizeof(double)*ps_Stat->ui_CountClass);
	memset(ps_Stat->pd_PrioriProbClass,0,sizeof(double)*ps_Stat->ui_CountClass);

	for(j = 0; j<ps_Stat->ui_CountClass; j++ )//取每个类的标记
	{
		for(i = 0; i<ps_Stat->ui_num; i++)//遍历样本
		{
			if(ps_Stat->pi_ClassLabel[j] == fetchclassData_ML(i))
			{
				ps_Stat->pd_PrioriProbClass[j] = ps_Stat->pd_PrioriProbClass[j]+1;
			}
		}
		ps_Stat->pd_PrioriProbClass[j] = ps_Stat->pd_PrioriProbClass[j]/ps_Stat->ui_num;
	}
	g_snbmlStatistic = ps_Stat;
	return SUCCESS_RTML;
}

//用贝叶斯分类器分类输入的数据(离散)
int classifyNaiveBayesDiscreteNaiveBayes_ML(int *entry,unsigned int ui_len,RETURN_TYPE_ML *res)
{
	int i_Class = 0;
	unsigned int i = 0;
	unsigned int j = 0;
	double  pd_ProbCompMulti = 1;//每个特征分量的概率之积
	double * pd_ProbPost = 0;//后验概率
	double  d_MaxProbPost = 0;
	if((g_snbmlStatistic->ui_Len != ui_len)||
		(g_snbmlStatistic->f_flag != DISCRETE))//数据长度不正确或者分类器类型错误
	{
		*res = FAILED_RTML;
		return 0;
	}




	pd_ProbPost = (double *)malloc(sizeof(double)*g_snbmlStatistic->ui_CountClass);
	memset(pd_ProbPost,0,sizeof(double)*g_snbmlStatistic->ui_CountClass);

	for(i = 0; i < g_snbmlStatistic->ui_CountClass; i++)//计算每个分类情况的概率
	{
		for(j = 0; j<ui_len; j++)
		{
			//计算当第i个分类时，所有分量的条件概率之积
			pd_ProbCompMulti = pd_ProbCompMulti * _findProbDiscrete(j,entry[j],g_snbmlStatistic->pi_ClassLabel[i],res);

		}

		pd_ProbPost[i] = pd_ProbCompMulti * g_snbmlStatistic->pd_PrioriProbClass[i];//第i个分类的条件概率与类的先验概率之积 = 后验概率。
		pd_ProbCompMulti = 1;
	}


	for(i = 0; i < g_snbmlStatistic->ui_CountClass; i++)//查找最大的后验概率
	{
		if(d_MaxProbPost < pd_ProbPost[i])
		{
			i_Class = i;
			d_MaxProbPost = pd_ProbPost[i];
		}
	}
	*res = SUCCESS_RTML;
	free(pd_ProbPost);
	pd_ProbPost = 0;
	return g_snbmlStatistic->pi_ClassLabel[i_Class];
}

//用贝叶斯分类器分类输入的数据(连续)
int classifyNaiveBayesContinuousNaiveBayes_ML(double *entry,unsigned int ui_len,RETURN_TYPE_ML *res)
{
	int i_Class = 0;
	unsigned int i = 0;
	unsigned int j = 0;
	double  pd_ProbCompMulti = 1;//每个特征分量的概率之积
	double * pd_ProbPost = 0;//后验概率

	double  d_MaxProbPost = 0;
	if(g_snbmlStatistic == 0)
	{
		*res = FAILED_RTML;
		return 0;
	}
	if((g_snbmlStatistic->ui_Len != ui_len)||
	(g_snbmlStatistic->f_flag != CONTINUOUS))//数据长度不正确或者分类器类型错误
	{
		*res = FAILED_RTML;
		return 0;
	}

	pd_ProbPost = (double *)malloc(sizeof(double)*g_snbmlStatistic->ui_CountClass);
	memset(pd_ProbPost,0,sizeof(double)*g_snbmlStatistic->ui_CountClass);

	for(i = 0; i < g_snbmlStatistic->ui_CountClass; i++)//计算每个分类情况的概率
	{
		for(j = 0; j<ui_len; j++)//计算在第i个分类的情况下，第j个特征的条件概率
		{


			//计算当第i个分类时，所有分量的条件概率之积
			pd_ProbCompMulti = pd_ProbCompMulti * _findProbContinus(j,entry[j],g_snbmlStatistic->pi_ClassLabel[i],res);
		}

		pd_ProbPost[i] = pd_ProbCompMulti * g_snbmlStatistic->pd_PrioriProbClass[i];//第i个分类的条件概率与类的先验概率之积 = 后验概率。
		pd_ProbCompMulti = 1;
	}

	for(i = 0; i < g_snbmlStatistic->ui_CountClass; i++)//查找最大的后验概率
	{
		if(d_MaxProbPost < pd_ProbPost[i])
		{
			i_Class = i;
			d_MaxProbPost = pd_ProbPost[i];
		}
	}
	*res = SUCCESS_RTML;
	free(pd_ProbPost);
	pd_ProbPost = 0;
	return g_snbmlStatistic->pi_ClassLabel[i_Class];
}

//卸载朴素贝叶斯分类器
RETURN_TYPE_ML destoryNaiveBayesNaiveBayes_ML(void)
{
	free(g_snbmlStatistic->pd_PrioriProbClass);
	free(g_snbmlStatistic->pi_ClassLabel);
	free(g_snbmlStatistic);
	return SUCCESS_RTML;
}

//显示分类器的信息
RETURN_TYPE_ML showNaiveBayesNaiveBayes_ML()
{
	RETURN_TYPE_ML res;
	unsigned int i =0;
	char strContent[2048];
	sprintf(strContent,
			"Class_Labels_Count=%u,Feature_Count=%u,Entry_Count=%u,Classify_Type=%d",
			g_snbmlStatistic->ui_CountClass,
			g_snbmlStatistic->ui_Len,
			g_snbmlStatistic->ui_num,
			g_snbmlStatistic->f_flag);
	for(i = 0; i < g_snbmlStatistic->ui_CountClass; i++)
	{
		sprintf(strContent,
				"%s,ClassLabel%u=%d,PriorProb%u=%f",
				strContent,
				i,
				g_snbmlStatistic->pi_ClassLabel[i],
				i,
				g_snbmlStatistic->pd_PrioriProbClass[i]);
	}

	res = outputLogLogFile_ML(INFO_LEVEL_TLFML,"NaiveBayes_ml","showNaiveBayesNaiveBayes_ML",(char *)strContent);
	return res;
}
