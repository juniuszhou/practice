/*
 * DecisionTree_ml.h
 *
 *  Created on: 2012-4-5
 *      Author: bofu
 */

#ifndef DECISIONTREE_ML_H_
#define DECISIONTREE_ML_H_
#include "../MachLearn_ml.h"
#include "../base/Data_ml/Data_ml.h"
#include "../base/Math_ml/Math_ml.h"
#include "../base/LogFile_ml/LogFile_ml.h"

/*    "离散值的决策树分类算法"数据结构设计示意图
 *                   DTDecisionTree_ML--->FeatureRange--->FeatureRange---...--->FeatureRange
 *                        |
 *                        |
 * GroupRule<---...---GroupHead--->DataEntry--->DataEntry---...--->DataEntry
 *                        |
 * GroupRule<---...---GroupHead--->DataEntry--->DataEntry---...--->DataEntry
 *
 * */

//每个特征的取值范围
typedef struct FeatureRange{
	//取值范围的长度
	unsigned int 			ui_lenRange;
	//该特征可使用的取值
	int *					pi_value;
	struct FeatureRange *	next;
} FeatureRange;

//样本结点
typedef struct DataEntry{
	//样本的编号
	unsigned int	ui_indexEntry;
	//样本的分类情况
	int 			i_class;
	struct DataEntry *next;
} DataEntry;

//分类准则结点
typedef struct GroupRule {
	//特征的编号
	unsigned int 	ui_indexFeature;
	//特征的取值
	int 			i_valueFeature;
	struct GroupRule *next;
}GroupRule;

//分组的头结点
typedef struct GroupHead{
	//分组准则的长度
	unsigned int 	ui_lenRule;
	//该分组的正例个数
	unsigned int 	ui_countPos;
	//该分组的反例个数
	unsigned int 	ui_countNeg;
	//该分组的熵
	double			d_entropy;
	//第一个分组结点
	DataEntry		*pde_firstEntry;
	//第一个分类分组准则结点
	GroupRule		*pgr_firstRule;
	//下一个分组头结点
	struct GroupHead * next;
} GroupHead;

//决策树计算结构
typedef struct DecisionTree_ML{
	//特征的个数
	unsigned int 	ui_lenFeature;
	//第一个特征的取值范围结点
	FeatureRange	*pfr_firstRange;
	//第一个分组头结点
	GroupHead		*pgh_firstHead;

} DecisionTree_ML;

//创建基础决策树
//成功返回对应的地址，同时i_res中写入执行成功的代码SUCCESS_DCDT
//否则返回0，并且在i_res中写入执行失败的代码FAILED_DCDT
RETURN_TYPE_ML initDecisionTreeDecisionTree_ML(void);

//训练决策树,在DDecisionTree中记录了分类的准则
//返回值，成功返回SUCCESS_DCDT，否则返回FAILED_DCDT
RETURN_TYPE_ML trainDecisionTreeDecisionTree_ML(void);

//使用决策树对数据entry进行分类
//返回值为分类标签，成功就在res中记录SUCCESS_DCDT，否则记录FAILED_DCDT
int classDecisionTreeDecisionTree_ML(int *entry,unsigned int ui_len,RETURN_TYPE_ML *res);

//读取分类准则
char *getRulesDecisionTree_ML(RETURN_TYPE_ML * res);

//卸载决策树分类器
RETURN_TYPE_ML destoryDecisionTreeDecisionTree_ML(void);

#endif /* DECISIONTREE_ML_H_ */
