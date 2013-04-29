/*
 * SVM_ml.c
 *
 *  Created on: 2012-4-10
 *      Author: bofu
 */
#include "SVM_ml.h"
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)>(b)?(b):(a))
#define TINNYGAP 0.000000001
//核函数类型。默认取值为线性核函数
static KERNELFUNCTION_SVM_ML g_kfsmlKernelFunction = LEANER_KFSML;

//核函数向量的矩阵K(xi,yj)
static double ** g_ppdKernelMatrix=0;

//Alpha取值范围的最大值
static double  g_C=0;

//alpha参数
static double * g_pdAlpha = 0;

//阈值参数
static double g_pdThreshold =0.0;
//样本规格
static DataSetSize_SVM_ML g_dasmlSize;



//计算向量的核函数内积
double _calculateKernelInnerProduct(double *entryA,double *entryB)
{
	double tmp =0.0;
	switch(g_kfsmlKernelFunction)
	{
	case LEANER_KFSML:
		return calculateInnerProduct(entryA,entryB,g_dasmlSize.uiCol);
		break;
	default:
		return 0.0;
	}
	return tmp;
}

//计算需要分类数据entry和已知数据的核函数值
double _calculateKernelSum(unsigned int iEntry,double *entry)
{
	unsigned int i;

	double entryA[g_dasmlSize.uiCol];
	for(i=0; i < g_dasmlSize.uiCol; i++)
	{
		entryA[i] = fetchdataData_ML(iEntry,i);
	}

	return _calculateKernelInnerProduct((double *)entryA,entry);
}
//计算核函数的矩阵
void _calculateKernelMatrix(void)
{
	unsigned int i=0;
	unsigned int j=0;
	unsigned int k=0;
	double *entryA = (double *)malloc(sizeof(double)*g_dasmlSize.uiCol);
	double *entryB = (double *)malloc(sizeof(double)*g_dasmlSize.uiCol);
	double ret=0.0;
	for(i=0; i<g_dasmlSize.uiRow; i++)
	{
		for(j=i; j<g_dasmlSize.uiRow; j++)
		{
			for(k =0; k<g_dasmlSize.uiCol; k++)
			{
				entryA[k]=fetchdataData_ML(i,k);
				entryB[k]=fetchdataData_ML(j,k);
			}
			ret = _calculateKernelInnerProduct(entryA,entryB);
			g_ppdKernelMatrix[i][j] = ret;
			g_ppdKernelMatrix[j][i] = ret;
		}
	}
	free(entryA);
	free(entryB);

}
//计算阈值
void _calculateThreshold()
{
	unsigned int i =0;
	unsigned int uiPosIndex = 0;
	unsigned int uiNegIndex = 0;

	double tmpPos =0.0;
	double tmpNeg = 0.0;
	int iClassLabel = 0;
	for(i=0; i<g_dasmlSize.uiRow; i++)
	{
		if((g_pdAlpha[i]>TINNYGAP)&&(abs(g_pdAlpha[i]-g_C)>TINNYGAP))//取值在0,C之间的值对应的向量为支持向量
		{
			iClassLabel = fetchclassData_ML(i);
			if(iClassLabel == 1)
			{
				if(uiPosIndex == 0) uiPosIndex = i;
			}else
			{
				if(uiNegIndex == 0) uiNegIndex = i;
			}
		}
	}
	for(i=0; i<g_dasmlSize.uiRow; i++)
	{
		tmpPos = tmpPos + fetchclassData_ML(i)*g_pdAlpha[i]*g_ppdKernelMatrix[i][uiPosIndex];
		tmpNeg = tmpNeg + fetchclassData_ML(i)*g_pdAlpha[i]*g_ppdKernelMatrix[i][uiNegIndex];
	}

	g_pdThreshold =((tmpPos -1)+(tmpNeg + 1))/2.0;


}
//当前alpha取值时，目标函数的值
double _calculateTargetValue()
{
    double sumQuad = 0.0;		//二次项部份的值
    double sumLinear = 0.0;		//一次项部份的值
    double sumVec =0.0;			//临时变量
	unsigned int i,j;
	for(i=0; i<g_dasmlSize.uiRow; i++)
	{
		sumLinear = sumLinear + g_pdAlpha[i];
		for(j=0; j < g_dasmlSize.uiRow; j++)
		{
			sumVec = g_pdAlpha[i]*g_pdAlpha[j]*fetchclassData_ML(i)*fetchclassData_ML(j);
			sumQuad = sumQuad + sumVec*g_ppdKernelMatrix[i][j];
		}
	}
	return (1.0/2.0)*sumQuad-sumLinear;
}

//优化选择的两个分量
void _optimizeTwoVariable(unsigned int s, unsigned int t)
{
	int Sst = 0;
	double eta = 0.0;	//eta的值，s,t对应分量的二阶导数
	double sLow = 0.0;	//s分量的取值范围，最小值
	double sHigh = 0.0;	//s分量的取值范围，最大值
	double tLow = 0.0;	//s分量的取值范围，最小值
	double tHigh = 0.0;	//s分量的取值范围，最大值
	double sumPart = 0.0; //非s,t项的和
	double leftPart =0.0;
	double alpha_s = 0.0;
	double alpha_t = 0.0;
	unsigned int i = 0;
	double tmp_s,tmp_t;
	double lowValueTarget,highValueTarget;

	Sst = fetchclassData_ML(s)*fetchclassData_ML(t);
	eta = g_ppdKernelMatrix[s][s]+g_ppdKernelMatrix[t][t]-2.0*g_ppdKernelMatrix[s][t];
	sLow = MAX(0,g_pdAlpha[s]+Sst*g_pdAlpha[t]-(1.0/2.0)*(Sst+1.0)*g_C);
	sHigh = MIN(g_C,g_pdAlpha[s]+Sst*g_pdAlpha[t]-(1.0/2.0)*(Sst-1.0)*g_C);
	sumPart = 0;

	for(i=0; i < g_dasmlSize.uiRow; i++)
	{
		if((i!=s)&&(i!=t))
		{
			sumPart = sumPart +
					(g_ppdKernelMatrix[t][t]-g_ppdKernelMatrix[s][t]+
					g_ppdKernelMatrix[s][i]-g_ppdKernelMatrix[t][i])*g_pdAlpha[i]*
					fetchclassData_ML(s)*fetchclassData_ML(i);
		}
	}
	leftPart = 1-Sst-sumPart;

	if(eta> TINNYGAP)
	{//标准的二次规划求值
		alpha_s = leftPart*1.0/eta;
	}else//退化为线性规划
	{
		tLow = g_pdAlpha[t]+Sst*(g_pdAlpha[s]-sLow);
		tHigh = g_pdAlpha[t]+Sst*(g_pdAlpha[s]-sHigh);
		tmp_s = g_pdAlpha[s];
		tmp_t = g_pdAlpha[t];
		g_pdAlpha[s] = sLow;
		g_pdAlpha[t] = tLow;
		lowValueTarget = _calculateTargetValue();
		g_pdAlpha[s] = sHigh;
		g_pdAlpha[t] = tHigh;
		highValueTarget = _calculateTargetValue();

		if(abs(lowValueTarget - highValueTarget)<TINNYGAP)
		{//相等，不更新s,t分量的值
			alpha_s = tmp_s;
			alpha_t = tmp_t;
		}else
		{
			if(lowValueTarget < highValueTarget-TINNYGAP)
			{
				alpha_s = sLow;
			}else
			{
				alpha_s = sHigh;
			}
		}

	}

	if(alpha_s >= sHigh)
	{
		alpha_s = sHigh;
	}else
	{
		if(alpha_s<=sLow)
		{
			alpha_s = sLow;
		}
	}

	alpha_t = g_pdAlpha[t]+Sst*(g_pdAlpha[s]-alpha_s);
	g_pdAlpha[s] = alpha_s;
	g_pdAlpha[t] = alpha_t;
	return ;
}
//初始化SVM向量机
RETURN_TYPE_ML initSVMSVM_ML()
{
	unsigned int i =0;
	g_kfsmlKernelFunction = LEANER_KFSML;
	g_dasmlSize.uiRow = fetchNumData_ML();
	g_dasmlSize.uiCol = fetchLenData_ML();
	g_C = 10.0;
	g_pdAlpha = (double *)malloc(sizeof(double)*g_dasmlSize.uiRow);
	if(g_pdAlpha == 0)
	{
		return FAILED_RTML;
	}
	g_ppdKernelMatrix = (double **)malloc(sizeof(double *)*g_dasmlSize.uiRow);
	if(g_ppdKernelMatrix == 0)
	{
		return FAILED_RTML;
	}
	for(i = 0; i<g_dasmlSize.uiRow; i++)
	{
		g_ppdKernelMatrix[i]=(double *)malloc(sizeof(double)*g_dasmlSize.uiRow);
		g_pdAlpha[i] = 0.001;//初始化alpha参数
	}


	return SUCCESS_RTML;

}
/*设置SVM分类器的分类参数
输入：
type-----------------核函数的类型
uiMaxAlpha-----------最大alpha的取值

返回值：
无
*/
void setSVMParameter(KERNELFUNCTION_SVM_ML type,double uiMaxAlpha)
{
	g_kfsmlKernelFunction = type;
	g_C = uiMaxAlpha;
}
//训练SVM分类器
RETURN_TYPE_ML trainSVMSVM_ML(void)
{
	double err =100;//每次迭代后目标函数的递减率
	double valueTarget = -30000;//前一次alpha取值目标函数的取值
	double valueTargetCurr = 0.0;;//当前alpha取值时目标函数的值
	unsigned int i,j;
	//计算内积核函数矩阵
	_calculateKernelMatrix();
	valueTargetCurr = _calculateTargetValue();

	//迭代计算alpha的值
	while(abs(err)>TINNYGAP)
	{
		//每次迭代时选取第i个和第i+1个分量来尽心最有化
		for(i = 0; i < g_dasmlSize.uiRow-1; i++)
		{
			for(j = i+1; j < g_dasmlSize.uiRow; j++)
			{
				_optimizeTwoVariable(i,j);//选取第i,j分量来优化参数alpha
			}
		}
		valueTarget = valueTargetCurr;
		valueTargetCurr = _calculateTargetValue();
		err = (valueTarget - valueTargetCurr)/valueTarget;//更新目标函数的取值和递减速率
	}

	//计算阈值b
	_calculateThreshold();
	return SUCCESS_RTML;
}

//显示SVM分类器的参数
RETURN_TYPE_ML showSVMSVM_ML(void)
{
	RETURN_TYPE_ML res;
	unsigned int i =0;
	char strContent[2048];
	sprintf(strContent,"The Alpha vector=[\t");
	for(i = 0; i < g_dasmlSize.uiRow; i++)
	{
		sprintf(strContent,"%s%f\t",strContent,g_pdAlpha[i]);
	}
	sprintf(strContent,"%s],The Threadhold=%f",strContent,g_pdThreshold);
	res = outputLogLogFile_ML(INFO_LEVEL_TLFML,"SVM_ml","showSVMSVM_ML",(char *)strContent);
	return res;
}
//分类数据
RETURN_TYPE_ML classifySVMSVM_ML(double *entry,unsigned int uiLen,int *iClassLabel)
{
	unsigned int i;
	double sumPart = 0.0;
	for(i = 0; i < g_dasmlSize.uiRow; i++)
	{
		sumPart = sumPart +fetchclassData_ML(i)*g_pdAlpha[i]*_calculateKernelSum(i,entry);
	}
	if(sumPart - g_pdThreshold > TINNYGAP)
	{
		*iClassLabel = 1;
	}else
	{
		*iClassLabel = -1;
	}
	return SUCCESS_RTML;
}

//分类数据
RETURN_TYPE_ML destorySVMSVM_ML()
{
	unsigned int i ;
	free(g_pdAlpha);
	for(i = 0; i<g_dasmlSize.uiRow; i++)
	{
		free(g_ppdKernelMatrix[i]);
	}
	free(g_ppdKernelMatrix);
	return SUCCESS_RTML;
}
