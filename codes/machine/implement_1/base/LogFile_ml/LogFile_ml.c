/*
	文件:LogFile_ml.cpp
	机器学习库接口函数实现
*/
#include "LogFile_ml.h"

/*宏定义*/
#define ISEMPTYSTRING(p) ((!(p))||(!strcmp((p),"")))
/*******************************/

/*全局变量定义*/

//日志文件的文件句柄
static FILE *g_fp = 0;

//输出日志的方式,默认无日志输出
static OUTPUTTYPE_LOG_ML g_otlfmlType = NONE_OT_LFML;

//输出日志的最低级别,默认Error级别
static LEVEL_LOG_ML g_llfmlType = ERROR_LEVEL_TLFML;
/*******************************/

/*局部函数的实现*/

/*******************************/

/*接口函数实现*/

/*初始化LogFile_ml模块
输入：
tlfmlType--------需要输出的日志内容的最低级别
otlfmlType-------日志输出方式
strFile----------日志文件的名称

返回值：
成功返回OK_RLFML,否则返回NG_RLFML*/
RETURN_TYPE_ML initLogFile_ML(OUTPUTTYPE_LOG_ML otlfmlType,LEVEL_LOG_ML llmlLevel,char *strFile)
{
	if( (otlfmlType == FILE_OT_LFML)&&ISEMPTYSTRING(strFile) )
	{
		printf("Error on loading the LogFile_ML Module\n");
		return FAILED_RTML;
	}
	g_fp = 0;
	g_llfmlType = llmlLevel;
	g_otlfmlType = otlfmlType;
	if(otlfmlType == FILE_OT_LFML)
	{
		if(!ISEMPTYSTRING(strFile))
		{
			g_fp = fopen(strFile,"w");
			if(g_fp == 0)//创建并打开日志文件失败
			{
				return FAILED_RTML;
			}
			fprintf(g_fp,"%s","<LogFile>");
	}

	}

	return SUCCESS_RTML;
}

/*卸载LogFile_ml模块
输入：
无

返回值：
无*/
 void destoryLogFile_ML(void)
{
	
	if(g_otlfmlType == FILE_OT_LFML)
	{
		fprintf(g_fp,"%s","</LogFile>");
		fclose(g_fp);
	}

	
}

/*设置Log内容输出的最低级别
输入：
llmlLevel--------需要输出的日志内容的最低级别

返回值：
成功返回OK_RLFML,否则返回NG_RLFML*/
void setLogLevel_ML(LEVEL_LOG_ML llmlLevel)
{
	g_llfmlType = llmlLevel;

}

/*输出日志信息
输入：
llfmlType--------日志的级别
strModName-------发生问题的模块名称
strFunction------发生问题的函数名称
strContent-------发生问题的描述

返回值：
成功返回OK_RLFML,否则返回NG_RLFML*/
RETURN_TYPE_ML outputLogLogFile_ML(LEVEL_LOG_ML llfmlType,char * strModName,char * strFunction,char * strContent)
{
	char *strLevel[]={"Information","Warning","Error"};
	time_t t;
	//char *strTime=(char *)malloc(128);
	char strTime[128] ="";
	if(llfmlType < g_llfmlType)
	{//没有超过需要打印日志的级别
		return SUCCESS_RTML;
	}
	
	time(&t);
	sprintf(strTime,"%s",ctime(&t));
	strTime[strlen(strTime)-1]='\0';

	switch(g_otlfmlType)
	{
	case FILE_OT_LFML:		//配置需要将内容打印到日志文件中
		if(g_fp == 0)
		{//没有日志文件
			return FAILED_RTML;
		}
		fprintf(g_fp,"<log type=\"%s\" module=\"%s\" function=\"%s\" time=\"%s\">%s</log>\n",
			strLevel[llfmlType],strModName,strFunction,strTime,strContent);
		break;
	case STD_OT_LFML:		//配置需要将内容打印到标准控制台
		printf("[log type=\"%s\" module=\"%s\" function=\"%s\" time=\"%s\"] %s\n",
			strLevel[llfmlType],strModName,strFunction,strTime,strContent);
		break;
	case NONE_OT_LFML:		//配置不需要打印日志内容
		return SUCCESS_RTML;
	}
	//free(strTime);
	return SUCCESS_RTML;
}
/*******************************/
