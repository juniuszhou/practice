/*
 * DecisionTree_ml.c
 *
 *  Created on: 2012-4-5
 *      Author: bofu
 */
#include "DecisionTree_ml.h"
static DecisionTree_ML * g_pdtdtmlDecisionTree=0;

//统计指定特征的取值范围
//成功返回取值内容数组的地址和数组的个数，同时i_res中写入执行成功的代码SUCCESS_DCDT
//否则返回0，并且在i_res中写入执行失败的代码FAILED_DCDT
static int *_get_ValueRange(unsigned int ui_featureIdx,unsigned int *ui_len,int *i_res)
{
	int *pi_VlaueRange_tmp=(int *)malloc(sizeof(int)*fetchNumData_ML());//初始分配取值范围数组
	int *pi_VlaueRange=0;
	unsigned int i=0;
	unsigned int j =0;
	unsigned int count=0;
	int tmp=0;
	int flag=1;

	if(pi_VlaueRange_tmp == 0)
	{
		*i_res = FAILED_RTML;
		return 0;
	}
	memset(pi_VlaueRange_tmp,0,sizeof(int)*fetchNumData_ML());


	pi_VlaueRange_tmp[0] = fetchdataData_ML(0,ui_featureIdx);


	count++;
	for(i = 1; i < fetchNumData_ML(); i++)
	{
		tmp =fetchdataData_ML(i,ui_featureIdx);

		for(j = 0;j<count; j++)
		{
			if(pi_VlaueRange_tmp[j] == tmp)//已经在数组中
			{
				flag = 0;
				break;
			}
		}
		if( flag ==1 )
		{
			pi_VlaueRange_tmp[count]=tmp;
			count++;

		}else
		{
			flag = 1;
		}

	}



	//重新设置存储区
	pi_VlaueRange=(int *)malloc(sizeof(int)*count);
	memset(pi_VlaueRange,0,sizeof(int)*count);
	for(i=0; i < count ; i++)
	{
		pi_VlaueRange[i]=pi_VlaueRange_tmp[i];
	}
	free(pi_VlaueRange_tmp);
	pi_VlaueRange_tmp = 0;
	*ui_len=count;
	*i_res = SUCCESS_RTML;
	return pi_VlaueRange;
}


//生成特征的取值范围链表
//成功返回对应的地址，同时i_res中写入执行成功的代码SUCCESS_RTML
//否则返回0，并且在i_res中写入执行失败的代码FAILED_RTML
static FeatureRange *_create_FeatureRange(int *i_res)
{
	FeatureRange * pfr_node=0;
	FeatureRange * p;
	FeatureRange * head;
	unsigned int i=0;
	int res=0;
	unsigned int len=0;


	for( i = 0; i< fetchLenData_ML(); i++ )
	{
		if(0 == (pfr_node = (FeatureRange *)malloc(sizeof(FeatureRange))))
		{//分配内存失败
			*i_res = FAILED_RTML;
			return 0;
		}
		memset(pfr_node,0,sizeof(FeatureRange));

		//添加取值范围数据

		pfr_node->pi_value = _get_ValueRange(i,&len,&res);
		pfr_node->ui_lenRange = len;
		if(res==FAILED_RTML)
		{//获取失败
			*i_res = FAILED_RTML;
			return 0;
		}

		//链接每个结点
		if(i !=0 )
		{//非第一次创建特征点取值范围
			p->next=pfr_node;
		}else
		{
			head = pfr_node;
		}

		p=pfr_node;
		len = 0;
	}
	*i_res = SUCCESS_RTML;
	return head;
}


//生成所有结点的链表
//成功返回对应的地址和正例的个数，同时i_res中写入执行成功的代码SUCCESS_RTML
//否则返回0，并且在i_res中写入执行失败的代码FAILED_RTML
static DataEntry * _create_DataEntry(unsigned int *ui_countPos,int *i_res)
{
	unsigned int count=0;
	unsigned int i;
	DataEntry * head;
	DataEntry * p;
	DataEntry * pde_entry=0;



	for(i = 0; i < fetchNumData_ML(); i++)
	{
		if(0 == (pde_entry = (DataEntry *)malloc(sizeof(DataEntry))))
		{//分配内存失败
			*i_res = FAILED_RTML;
			return 0;
		}
		memset(pde_entry,0,sizeof(DataEntry));

		//填充数据
		pde_entry->ui_indexEntry = i ;
		pde_entry->i_class = fetchclassData_ML(i);

		if(pde_entry->i_class > 0 )
		{
			count++;
		}
		//链接每个结点
		if(i !=0 )
		{//非第一次创建特征点取值范围
			p->next=pde_entry;
		}else
		{
			head = pde_entry;
		}

		p=pde_entry;
	}

	*ui_countPos = count;
	*i_res = SUCCESS_RTML;
	return head;
}

//计算当前分组中可以产生的最优分组的特征标号(最大熵增益选择最优特征)
//如果查找成功，返回最优特征标号，i_res的值为SUCCESS_RTML。
//如果查找失败，返回0，i_res的值为FAILED_RTML
static unsigned int _findBestFeature(GroupHead *pgh_group,RETURN_TYPE_ML *i_res)
{
	typedef struct statistic{
		unsigned int ui_featureIdx;//特征的标号
		unsigned int * pui_posCount;//该特征在不同取值情况下正例的个数
		unsigned int * pui_negCount;//该特征在不同取值情况下反例的个数
		double d_entropy;//该特征如果分类的话，得到的熵
	}statistic;

	statistic *ps_StatisCount=0;//统计信息汇总
	unsigned int i=0;
	unsigned int j=0;
	unsigned int k=0;
	int value=0;
	double sum=0.0;
	FeatureRange *pfr_Range=0;
	DataEntry *pde_Entry=0;
	unsigned int ui_featureIdx;

	if((pgh_group == 0)||(g_pdtdtmlDecisionTree == 0))
	{
		*i_res=FAILED_RTML;
		return 0;
	}

	ps_StatisCount=(statistic *)malloc(sizeof(statistic)*g_pdtdtmlDecisionTree->ui_lenFeature);
	memset(ps_StatisCount,0,sizeof(statistic)*g_pdtdtmlDecisionTree->ui_lenFeature);
	pfr_Range=g_pdtdtmlDecisionTree->pfr_firstRange;

	for(i=0; i<g_pdtdtmlDecisionTree->ui_lenFeature; i++)
	{
		ps_StatisCount[i].ui_featureIdx = i;
		ps_StatisCount[i].d_entropy=0.0;
		ps_StatisCount[i].pui_posCount=(unsigned int *)malloc(sizeof(unsigned int)*pfr_Range->ui_lenRange);
		ps_StatisCount[i].pui_negCount=(unsigned int *)malloc(sizeof(unsigned int)*pfr_Range->ui_lenRange);
		memset(ps_StatisCount[i].pui_posCount,0,sizeof(unsigned int)*pfr_Range->ui_lenRange);
		memset(ps_StatisCount[i].pui_negCount,0,sizeof(unsigned int)*pfr_Range->ui_lenRange);

		for(j=0; j<pfr_Range->ui_lenRange; j++)
		{
			pde_Entry=pgh_group->pde_firstEntry;
			for(k=0; k<pgh_group->ui_countNeg+pgh_group->ui_countPos; k++)
			{
				value=fetchdataData_ML(pde_Entry->ui_indexEntry,i);
				if(value == pfr_Range->pi_value[j])
				{
					if(pde_Entry->i_class == -1)
					{
						ps_StatisCount[i].pui_negCount[j]++;
					}else
					{
						ps_StatisCount[i].pui_posCount[j]++;
					}
				}
				pde_Entry = pde_Entry->next;
			}


		}
		pfr_Range = pfr_Range->next;
	}

	unsigned int sum_count=0;
	//计算熵
	pfr_Range=g_pdtdtmlDecisionTree->pfr_firstRange;
	for(i=0; i<g_pdtdtmlDecisionTree->ui_lenFeature; i++)
	{
		for(j=0; j<pfr_Range->ui_lenRange; j++)
		{
			sum_count = ps_StatisCount[i].pui_negCount[j] + ps_StatisCount[i].pui_posCount[j];
			sum = sum + (sum_count*1.0/(pgh_group->ui_countNeg+pgh_group->ui_countPos))*
					calculateEntropyMath_ML(
							ps_StatisCount[i].pui_negCount[j],
							ps_StatisCount[i].pui_posCount[j]);

		}

		ps_StatisCount[i].d_entropy = sum;
		sum = 0;
		pfr_Range = pfr_Range->next;
	}

	//查找最大的熵增益,最小的熵
	ui_featureIdx = 0 ;
	sum = ps_StatisCount[0].d_entropy;

	for(i=1; i<g_pdtdtmlDecisionTree->ui_lenFeature; i++)
	{
		if(ps_StatisCount[i].d_entropy < sum)
		{
			ui_featureIdx=i;
			sum = ps_StatisCount[i].d_entropy;
		}
	}

	*i_res = SUCCESS_RTML;
	return ui_featureIdx;

}

//根据计算得到的最优特征将pgh_group指向的样本组按照不同的特征取值进行分割????????????
//无返回值，成功就在i_res中记录SUCCESS_RTML，否则记录FAILED_RTML
static void _spliteDecisionTree(GroupHead *pgh_group,unsigned int ui_featureIdx,RETURN_TYPE_ML *i_res)
{
	GroupHead * pgh_HeadFloat = 0;
	GroupHead * pgh_HeadPrev = 0;
	GroupRule * pgr_RuleFloat = 0;
	GroupRule * pgr_RuleFloat_add = 0;
	GroupRule * pgr_RulePrev= 0;
	GroupRule * pgr_RuleFirst= 0;
	FeatureRange * pfr_Range = 0;
	DataEntry * pde_endtry = 0;
	DataEntry * pde_endtryPrev = 0;
	unsigned int i = 0;


	if((pgh_group == 0)||(g_pdtdtmlDecisionTree == 0))
	{//异常数据值检测
		*i_res=FAILED_RTML;
		return ;
	}

	if(ui_featureIdx >= g_pdtdtmlDecisionTree->ui_lenFeature)
	{//特征的标号值异常检测
		*i_res=FAILED_RTML;
		return ;
	}

	pfr_Range = g_pdtdtmlDecisionTree->pfr_firstRange;
	for( i =0; i<ui_featureIdx; i++)
	{//定位到指定的特征取值范围结点
		pfr_Range = pfr_Range->next;
	}

	//定位到需要分裂的组
	pgh_HeadPrev = pgh_HeadFloat = pgh_group;

	//为分组创建头结点
	for(i =0; i<pfr_Range->ui_lenRange; i++)
	{
		//创建分类准则
		pgr_RuleFloat = (GroupRule *)malloc(sizeof(GroupRule));
		memset(pgr_RuleFloat,0,sizeof(GroupRule));
		pgr_RuleFloat->ui_indexFeature = ui_featureIdx;
		pgr_RuleFloat->i_valueFeature = pfr_Range->pi_value[i];
		pgr_RuleFloat->next = 0;

		if(i ==0 )
		{//第一个结点的位置插入新分类准则
			pgr_RuleFloat->next = pgh_group->pgr_firstRule;
			pgh_group->pgr_firstRule = pgr_RuleFloat;


		}

		if(i > 0)
		{//不是第一个分组，需要创建分组头
			pgh_HeadFloat = (GroupHead *)malloc(sizeof(GroupHead));
			memset(pgh_HeadFloat,0,sizeof(GroupHead));
			pgh_HeadFloat->d_entropy = 0.0;
			pgh_HeadFloat->next = 0;
			pgh_HeadFloat->pde_firstEntry = 0;
			pgh_HeadFloat->pgr_firstRule = 0;
			pgh_HeadFloat->ui_countNeg = 0;
			pgh_HeadFloat->ui_countPos = 0;
			pgh_HeadFloat->ui_lenRule = pgh_group->ui_lenRule + 1;

			//插入新建的分组头
			pgh_HeadFloat->next = pgh_HeadPrev->next;
			pgh_HeadPrev->next = pgh_HeadFloat;

			//插入已经创建的分类准则结点(1、插入当前创建的结点；2、copy头结点的准则)
			pgr_RulePrev = pgh_HeadFloat->pgr_firstRule = pgr_RuleFloat;
			while( pgr_RuleFirst !=0 )
			{
				pgr_RuleFloat_add = (GroupRule *)malloc(sizeof(GroupRule));
				memset(pgr_RuleFloat_add,0,sizeof(GroupRule));

				pgr_RuleFloat_add->i_valueFeature = pgr_RuleFirst->i_valueFeature;
				pgr_RuleFloat_add->ui_indexFeature = pgr_RuleFirst->ui_indexFeature;
				pgr_RulePrev->next = pgr_RuleFloat_add;

				pgr_RuleFirst = pgr_RuleFirst->next;
				pgr_RulePrev = pgr_RuleFloat_add;

			}


		}

		//移动到一个分组的第二个准则结点上
		pgr_RuleFirst = pgh_group->pgr_firstRule->next;

		//移动到新建的结点上
		pgh_HeadPrev = pgh_HeadFloat;
	}

	pde_endtry = pgh_group->pde_firstEntry;
	pgh_HeadFloat = pgh_group->next;

	while(pde_endtry!=0)
	{
		if(fetchdataData_ML(pde_endtry->ui_indexEntry,ui_featureIdx) == pgh_group->pgr_firstRule->i_valueFeature)
		{//该结点是输入本头分组要求的特征值。不做处理，pde_endtry移动到下一个entry结点
			pde_endtry=pde_endtry->next;
			continue;
		}

		//否则就在分组头结点中查找合适的准则位置
		while(pgh_HeadFloat!=0)
		{
			if(fetchdataData_ML(pde_endtry->ui_indexEntry,ui_featureIdx) == pgh_HeadFloat->pgr_firstRule->i_valueFeature)
			{//找到合适的分组头结点，将该结点从原来的分组删除，然后将该结点挂在在当前分组头结点后面。？？
				pde_endtryPrev = pgh_group->pde_firstEntry;
				if(pde_endtryPrev == pde_endtry)
				{//第一个结点就是需要删除的结点。
					pgh_group->pde_firstEntry = pde_endtry->next;//删除该结点
					pde_endtry = pde_endtry->next;//指针移动到下一个结点


					pde_endtryPrev->next = pgh_HeadFloat->pde_firstEntry;//添加该结点到指定的分组中
					pgh_HeadFloat->pde_firstEntry = pde_endtryPrev;

				}
				else
				{
					while(pde_endtryPrev->next != pde_endtry)
					{//否则将pde_endtryPrev移动到pde_endtry前面一个结点
						pde_endtryPrev = pde_endtryPrev->next;
					}

					pde_endtryPrev->next = pde_endtry->next;//删除该结点
					pde_endtryPrev = pde_endtryPrev->next;//移动到下一个结点

					pde_endtry->next = pgh_HeadFloat->pde_firstEntry;//添加该结点到指定的分组中
					pgh_HeadFloat->pde_firstEntry = pde_endtry;

					pde_endtry = pde_endtryPrev;





				}

				//重新计算熵
				if(pgh_HeadFloat->pde_firstEntry->i_class == -1)
				{
					pgh_group->ui_countNeg-- ;
					pgh_HeadFloat->ui_countNeg++ ;

				}else
				{
					pgh_HeadFloat->ui_countPos++ ;
					pgh_group->ui_countPos-- ;
				}

				pgh_HeadFloat->d_entropy = calculateEntropyMath_ML(
						pgh_HeadFloat->ui_countNeg,
						pgh_HeadFloat->ui_countPos);

				pgh_group->d_entropy = calculateEntropyMath_ML(
						pgh_group->ui_countNeg,
						pgh_group->ui_countPos);

				break;

			}else
			{
				pgh_HeadFloat = pgh_HeadFloat->next;
			}

		}

		pgh_HeadFloat = pgh_group->next;//移动到第一个需要添加数据的分组头
	}

}

//创建基础决策树
//成功返回对应的地址，同时i_res中写入执行成功的代码SUCCESS_RTML
//否则返回0，并且在i_res中写入执行失败的代码FAILED_RTML
RETURN_TYPE_ML initDecisionTreeDecisionTree_ML(void)
{

	unsigned int ui_countPos=0;
	int res=0;

	//output_Status("Begin to Create the Decision Tree");
	if(0 == (g_pdtdtmlDecisionTree=(DecisionTree_ML *)malloc(sizeof(DecisionTree_ML))))
	{//分配内存失败
		return FAILED_RTML;
	}
	memset(g_pdtdtmlDecisionTree,0,sizeof(DecisionTree_ML));

	//添加每个特征的取值范围链表
	g_pdtdtmlDecisionTree->ui_lenFeature = fetchLenData_ML();
	g_pdtdtmlDecisionTree->pfr_firstRange = _create_FeatureRange(&res);
	if(res == FAILED_RTML)
	{
		return FAILED_RTML;
	}

	//添加第一个分组头结点
	if(0 == (g_pdtdtmlDecisionTree->pgh_firstHead =(GroupHead *)malloc(sizeof(GroupHead))))
	{//分配内存失败
		return FAILED_RTML;
	}
	memset(g_pdtdtmlDecisionTree->pgh_firstHead,0,sizeof(GroupHead));

	//为第一个分组头结点填充数据
	g_pdtdtmlDecisionTree->pgh_firstHead->pgr_firstRule=0;//没有分组准则，因为当前所有的数据在同一个组中
	g_pdtdtmlDecisionTree->pgh_firstHead->ui_lenRule=0;

	//为第一个分组添加样本链表
	g_pdtdtmlDecisionTree->pgh_firstHead->pde_firstEntry=_create_DataEntry(&ui_countPos,&res);
	if(res == FAILED_RTML)
	{//创建样本链表失败
		return FAILED_RTML;
	}
	g_pdtdtmlDecisionTree->pgh_firstHead->ui_countPos = ui_countPos;
	g_pdtdtmlDecisionTree->pgh_firstHead->ui_countNeg = fetchNumData_ML() - ui_countPos;
	g_pdtdtmlDecisionTree->pgh_firstHead->d_entropy = calculateEntropyMath_ML(
			g_pdtdtmlDecisionTree->pgh_firstHead->ui_countPos,
			g_pdtdtmlDecisionTree->pgh_firstHead->ui_countNeg);

	g_pdtdtmlDecisionTree->pgh_firstHead->next=0;


	//output_Status("Create Decision Tree Success!");
	return SUCCESS_RTML;
}

//训练决策树,在DDecisionTree中记录了分类的准则
//无返回值，成功就在i_res中记录SUCCESS_RTML，否则记录FAILED_RTML
RETURN_TYPE_ML trainDecisionTreeDecisionTree_ML(void)
{
	GroupHead *pgh_group=0;

	unsigned int ui_featureIdx;
	unsigned int time=0;
	RETURN_TYPE_ML i_res=0;
	if( g_pdtdtmlDecisionTree==0 )
	{
		return FAILED_RTML;
	}

	//output_Status("Begin to Train the Decision Tree");
	pgh_group = g_pdtdtmlDecisionTree->pgh_firstHead;
	while( pgh_group != 0 )
	{
		if(pgh_group->d_entropy > 0.00000001)//熵不为0
		{
			ui_featureIdx = _findBestFeature(pgh_group, &i_res);
			if(i_res == SUCCESS_RTML)
			{
				/*memset(str_log,0,sizeof(char)*1024);
				sprintf(str_log,"[%u] Found the best Feature.(index:%u)",time,ui_featureIdx);*/
				//output_Status(str_log);

				_spliteDecisionTree(pgh_group, ui_featureIdx,&i_res);//////???????
				if(i_res == FAILED_RTML)
				{
					return FAILED_RTML;
				}

				/*memset(str_log,0,sizeof(char)*1024);
				sprintf(str_log,"[%u] Splited the Decision Tree.(index:%u)",time,ui_featureIdx);*/
				//output_Status(str_log);

				pgh_group = g_pdtdtmlDecisionTree->pgh_firstHead;
				//完成分裂后将指针指向第一个分组结点，然后重新开始查找熵不为0的分组
				time ++;
				continue;
			}

		}

		pgh_group = pgh_group->next;
	}
	return SUCCESS_RTML;
}

//读取分类准则
char *getRulesDecisionTree_ML(RETURN_TYPE_ML * res)
{
	//将数据训练的规则读取出来，生成一个if-then的字符串
		char * str_rule=0;
		GroupHead * pgh_group=0;
		GroupRule * pgr_rule= 0;
		int flag_a =0;
		int flag_o = 0;
		if(g_pdtdtmlDecisionTree==0)
		{
			*res = FAILED_RTML;
			return (char*)0;
		}
		str_rule=(char *)malloc(sizeof(char)*1024);
		memset(str_rule,0,sizeof(char)*1024);
		sprintf(str_rule,"if(");

		pgh_group = g_pdtdtmlDecisionTree->pgh_firstHead;
		while(pgh_group!=0)
		{
			if(pgh_group->ui_countPos > 0)
			{//正例的分组
				pgr_rule = pgh_group->pgr_firstRule;

				if(flag_o == 0)
				{
					sprintf(str_rule,"%s (",str_rule);
					flag_o=1;
				}else
				{
					sprintf(str_rule,"%sOR(",str_rule);
				}


				while(pgr_rule != 0)
				{
					if(flag_a == 0)
					{
						sprintf(str_rule,"%s(the \"%u\" == %d)",str_rule,
							pgr_rule->ui_indexFeature,pgr_rule->i_valueFeature);
						flag_a = 1;
					}else
					{
						sprintf(str_rule,"%sAND(the \"%u\" == %d)",str_rule,
							pgr_rule->ui_indexFeature,pgr_rule->i_valueFeature);
					}


					pgr_rule = pgr_rule->next;
				}
				flag_a = 0;
				sprintf(str_rule,"%s)",str_rule);


			}
			pgh_group = pgh_group->next;
		}
		sprintf(str_rule,"%s )",str_rule);
		*res = SUCCESS_RTML;
		return str_rule;
}

//使用决策树对数据entry进行分类
//返回值为分类标签，成功就在res中记录SUCCESS_DCDT，否则记录FAILED_DCDT
int classDecisionTreeDecisionTree_ML(int *entry,unsigned int ui_len,RETURN_TYPE_ML *res)
{
	GroupHead * pHead = g_pdtdtmlDecisionTree->pgh_firstHead;
	GroupRule * pRule = pHead->pgr_firstRule;
	int flag = 0;
	int iClass = 0;
	if(pHead == 0)
	{
		*res = FAILED_RTML;
		return 0;
	}
	while(pHead!=0)
	{
		pRule  = pHead->pgr_firstRule;
		while(pRule!=0)
		{
			if(entry[pRule->ui_indexFeature] == pRule->i_valueFeature)
			{//该条件匹配，转到下一个条件
				flag = 1;
			}else
			{
				flag = 0;
				break;
			}
			pRule = pRule->next;
		}
		if(flag == 0)
		{//当前rule不满足，跳转下一个Group对应的rule
			pHead = pHead->next;
		}else
		{//当前的rule满足,跳出循环，并且标记分类标签
			if(pHead->ui_countPos == 0)
			{
				iClass = -1;
				break;
			}
			else
			{
				iClass = 1;
				break;
			}
		}
	}

	*res = SUCCESS_RTML;
	return iClass;
}
//卸载决策树分类器
RETURN_TYPE_ML destoryDecisionTreeDecisionTree_ML(void)
{
	FeatureRange * f1=g_pdtdtmlDecisionTree->pfr_firstRange;
	FeatureRange * f2=f1;
	GroupHead * g1 = g_pdtdtmlDecisionTree->pgh_firstHead;
	GroupHead * g2 = g1;
	GroupRule * r1 = 0;
	GroupRule * r2 = r1;
	DataEntry * d1 = 0;
	DataEntry * d2 = d1;
	g_pdtdtmlDecisionTree->pfr_firstRange = 0;
	g_pdtdtmlDecisionTree->pgh_firstHead = 0;
	while(f1!=0)
	{
		f1=f1->next;
		free(f2->pi_value);
		free(f2);
		f2 = f1;
	}
	while(g1!=0)
	{
		g1= g1->next;
		r1 = g2->pgr_firstRule;
		d1 = g2->pde_firstEntry;
		g2->pgr_firstRule = 0;
		g2->pde_firstEntry = 0;
		r2 = r1;
		d2 = d1;
		while(r1!=0)
		{
			r1=r1->next;
			free(r2);
			r2 = r1;
		}
		while(d1!=0)
		{
			d1=d1->next;
			free(d2);
			d2 = d1;
		}
		free(g2);
		g2 = g1;
	}
	return SUCCESS_RTML;
}
