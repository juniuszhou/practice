/*
 * MachLearn_ml.h（接口文件）
 *
 *  Created on: 2012-3-31
 *      Author: bofu
 * Description: 机器学习动态库的接口声明
 */

#ifndef MACHLEARN_ML_H_
#define MACHLEARN_ML_H_

/*需要引用的头文件和lib声明*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
/***********************/

/*Data模块回调函数声明*/
//获取样本的数据数量
typedef unsigned int (* getNumFunc)(void);
//获取样本的特征数量
typedef unsigned int (* getLenFunc)(void);
//获取数据
typedef double (* getDataFunc)(unsigned int entryIndex,unsigned int featureIndex);
//获取数据的分类情况
typedef int (* getClassFunc)(unsigned int entryIndex);
/***********************/

/*结构定义*/

//区别该分类器是离散的还是连续的
typedef enum FLAG_ML
{
	DISCRETE,	//离散
	CONTINUOUS	//连续
} FLAG_ML;

//日志类型级别定义
typedef enum LEVEL_LOG_ML
{
	INFO_LEVEL_TLFML = 0,		//Information级别
	WARNING_LEVEL_TLFML,		//Warning级别
	ERROR_LEVEL_TLFML			//Error级别
} LEVEL_LOG_ML;

//日志的输出方式
typedef enum OUTPUTTYPE_LOG_ML
{
	NONE_OT_LFML =0,		//无日志输出
	STD_OT_LFML,			//输出到标准控制台
	FILE_OT_LFML			//输出到Log文件
} OUTPUTTYPE_LOG_ML;

//返回值信息
typedef enum RETURN_TYPE_ML
{
	FAILED_RTML=0,			//执行出错
	OK_RTML,				//执行中部份有问题，但是不影响使用
	SUCCESS_RTML			//执行正确
} RETURN_TYPE_ML;


//模块的编号信息
typedef enum MODULE_TYPE_ML
{
	NAIVEBAYES_MTML=0,		//朴素贝叶斯分类器
	DECISIONTREE_MTML,		//决策树分类器
	SVM_MTML				//支持向量机分类器
} MODULE_TYPE_ML;

//支持向量机的核函数
typedef enum KERNELFUNCTION_SVM_ML
{
	LEANER_KFSML=0,//线性核函数

} KERNELFUNCTION_SVM_ML;

//回调函数函数指针结构体
typedef struct DataFuncDATA_ML{
	getNumFunc		getNum;
	getLenFunc		getLen;
	getDataFunc		getData;
	getClassFunc	getClass;
} DataFuncDATA_ML;

//加载DLL时的配置信息
typedef struct Config_DLL_ML
{
	//需要启动的模块
	MODULE_TYPE_ML				mtmlModule;
	//数据操作回调函数结构体
	DataFuncDATA_ML				ddmlFun;
	//需要处理的数据类型
	FLAG_ML						fmlFlag;
	char 						strLogFile[128];		//Log文件保存的路径
	LEVEL_LOG_ML				llmlLevel;		//打印log文件的最低等级
	OUTPUTTYPE_LOG_ML			oplmlType;		//Log输出的方式

} Config_DLL_ML;



/***********************/




/*接口函数声明*/

/*载入动态库
输入：
cdmConfig--------载入动态库时需要的配置信息

返回值：
成功返回OK_RLFML,否则返回NG_RLFML*/
RETURN_TYPE_ML initMachLearn_ML(Config_DLL_ML cdmConfig);

/*卸载动态库
输入：
无

返回值：
成功返回OK_RLFML,否则返回NG_RLFML*/
RETURN_TYPE_ML destoryMachLearn_ML(void);

/*显示分类器的信息
输入：
无

返回值：
成功返回OK_RLFML,否则返回NG_RLFML*/
RETURN_TYPE_ML showInfoMachLearn_ML(void);

/*训练分类器的参数
输入：
无

返回值：
成功返回OK_RLFML,否则返回NG_RLFML*/
RETURN_TYPE_ML trainMachLearn_ML(void);

/*训练分类器的参数
输入：
无
注：输入的数据都是double类型，如果分类器是离散型的，分类器会自动将数据分段为int类型，然后再进行离散型分类
返回值：
成功返回OK_RLFML,否则返回NG_RLFML*/
RETURN_TYPE_ML classifyMachLearn_ML(double *entry,unsigned int ui_len,int *iClassLabel);

/*设置Log内容输出的最低级别
输入：
llmlLevel--------需要输出的日志内容的最低级别

返回值：
无*/
void setLogLevel_ML(LEVEL_LOG_ML llmlLevel);

/*设置SVM分类器的分类参数
输入：
type-----------------核函数的类型
uiMaxAlpha-----------最大alpha的取值

返回值：
无
*/
void setSVMParameter(KERNELFUNCTION_SVM_ML type,double uiMaxAlpha);
/***********************/

#endif /* MACHLEARN_ML_H_ */
