/*
 * Data_ml.h(数据接口)
 *
 *  Created on: 2012-3-31
 *      Author: bofu
 * Description: 用回调函数的方式为用户提供数据输入的接口
 */

#ifndef DATA_ML_H_
#define DATA_ML_H_

/*需要引用的头文件和lib声明*/

#include "../../MachLearn_ml.h"

/************************/
/*结构体声明*/



/************************/

/*初始化Data_ml模块
输入：
无

返回值：
成功返回SUCCESS_RTML,否则返回FAILED_RTML*/
RETURN_TYPE_ML initData_ML(getNumFunc getNum,getLenFunc getLen,getDataFunc getData,getClassFunc getClass);

/*卸载Data_ml模块
输入：
无

返回值：
成功返回SUCCESS_RTML,否则返回FAILED_RTML*/
RETURN_TYPE_ML destoryData_ML(void);

/*获取样本大小
输入：
无

返回值：
返回数据*/
unsigned int fetchNumData_ML(void);

/*获取样本分类标签数量和标签
输入：
无

返回值：
返回数据*/
int *fetchClassTypeData_ML(unsigned int *count);

/*获取样本特征个数
输入：
无

返回值：
返回数据*/
unsigned int fetchLenData_ML(void);

/*获取数据
输入：
uiEntryIdx--------------数据的index
uiFeatureIdx------------数据特征的index

返回值：
返回数据*/
double fetchdataData_ML(unsigned int uiEntryIdx,unsigned int uiFeatureIdx);

/*获取分类情况
输入：
uiEntryIdx--------------数据的index

返回值：
分类标签*/
int fetchclassData_ML(unsigned int uiEntryIdx);
#endif /* DATA_ML_H_ */
