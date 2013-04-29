/*
	日志处理模块(基础模块)
	LogFile.h
*/
#ifndef _LOGFILE_ML_H
#define _LOGFILE_ML_H

/*需要引用的头文件和lib声明*/

#include "../../MachLearn_ml.h"
/************************/

/*宏定义*/

/************************/

/*结构定义*/


/************************/

/*接口函数定义*/

/*初始化LogFile_ml模块
输入：
llmlLevel--------需要输出的日志内容的最低级别
otlfmlType-------日志输出方式
strFile----------日志文件的名称

返回值：
成功返回OK_RLFML,否则返回NG_RLFML*/
RETURN_TYPE_ML initLogFile_ML(OUTPUTTYPE_LOG_ML otlfmlType,LEVEL_LOG_ML llmlLevel,char *strFile);


/*卸载LogFile_ml模块
输入：
无

返回值：
无*/
void destoryLogFile_ML(void);



/*输出日志信息
输入：
llfmlType--------日志的级别
strModName-------发生问题的模块名称
strFunction------发生问题的函数名称
strContent-------发生问题的描述

返回值：
成功返回OK_RLFML,否则返回NG_RLFML*/
RETURN_TYPE_ML outputLogLogFile_ML(LEVEL_LOG_ML llfmlType,char * strModName,char * strFunction,char * strContent);

/************************/

#endif
