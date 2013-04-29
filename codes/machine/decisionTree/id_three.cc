//
#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>
#include <string.h> 
#include <math.h>
#include <stdio.h>


#define maxsize 20

struct tree_node   //??????
{
	int attrib_col;          // ????????
	int value;              // ????
	struct tree_node*  left_node;    // ???????
	struct tree_node*  right_node;    //  ???????????
	int isleaf;          // ??????
	int classno;            // ??????
};

typedef struct tree_node s_tree;

double compute_pi(double pi)
{
   if (pi<=0)
	   return 0;
   if (pi>=1)
	   return 0;
   return 0-pi*log(pi)/log(2);
}


int getposition(int *data,int datasize,int value)//??????
{
	int i;
	for (i=0;i<datasize;i++) 
		if (data[i]==value) 
			return i;
		return  -1;
}


double Compute_InforGain(int **data,int record_num,int col_no,int num_attrib)
{
   int *differentvalue;
   int total_differentvalue;
   int s[maxsize][maxsize],classsum,a[maxsize],b[maxsize];
   int sj;
   int i,j,flag;
   int cu[maxsize];
   classsum=0;
   for(i=0;i<maxsize;i++)
	  b[i]=0;

      a[classsum]=data[0][num_attrib-1];//??????
      b[classsum]++;//?????
      classsum++;   //??????
	  
  for(i=1;i<record_num;i++)
  {
	  flag=0;
      for(int k=0;k<classsum;k++)
	  {
         if(data[i][num_attrib-1]==a[k])
		 {
			 flag=1;
			 b[k]++;
		 }
	  }
	  if(flag==0)
	  {
        a[classsum]=data[i][num_attrib-1];
		b[classsum]++;
        classsum++;
	  }
  }
  for(i=0;i<maxsize;i++)
           for(j=0;j<maxsize;j++)
			   s[i][j]=0;


	differentvalue=(int*)malloc(maxsize*sizeof(int));
      total_differentvalue=0;
	  j=0;
      for (i=0;i<record_num;i++)
	  {
        j=getposition(differentvalue,total_differentvalue,data[i][col_no]);
        if(j<0) 
		{
           differentvalue[total_differentvalue]=data[i][col_no];
		   for(int k=0;k<classsum;k++)
		   {
			   if(a[k]==data[i][num_attrib-1])
				   s[k][total_differentvalue]++;
		   }
		    total_differentvalue++;
		
		}
		else
		{
           for(int k=0;k<classsum;k++)
		   {
			   if(a[k]==data[i][num_attrib-1])
				   s[k][j]++;
		   }
		}
	  }
	  for(i=0;i<total_differentvalue;i++)
		  cu[i]=0;
      for(i=0;i<total_differentvalue;i++)
		  for(j=0;j<classsum;j++)
		     cu[i]+=s[j][i];
       double total_I=0;
       for (i=0;i<classsum;i++)
	   {
          total_I+=compute_pi((double)b[i]/record_num);
	   }
        double EA=0;
		for(i=0;i<classsum;i++)
		{  
			sj=0;
			for(j=0;j<total_differentvalue;j++)
		        EA+=(double)cu[i]/record_num*compute_pi((double)s[j][i]/cu[i]);
		}
       return  (total_I-EA);
}



s_tree *Build_ID3(int **data,int record_num,int num_attrib)
{
   int i,p,a[maxsize],b[maxsize],classsum;
   s_tree *p2=(s_tree *)malloc(sizeof(s_tree));
   s_tree *root=NULL;
   int flag,flag2;
   int attrib[maxsize];
   classsum=0;
   for(i=0;i<maxsize;i++)
	  b[i]=0;
      a[classsum]=data[0][num_attrib-1];//??????
      b[classsum]++;//?????
      classsum++;   //??????  1
  for(i=1;i<record_num;i++)
  {
	  flag=0;
      for(int k=0;k<classsum;k++)
	  {
         if(data[i][num_attrib-1]==a[k])
		 {
			 flag=1;
			 b[k]++;
		 }
	  }
	  if(flag==0)
	  {
        a[classsum]=data[i][num_attrib-1];
		b[classsum]++;
        classsum++;
	  }
  }
   if(record_num==0) 
	   return NULL;  
 
   int temp_num_attrib=0;
   for(i=0;i<num_attrib-1;i++) 
   {
     if(data[0][i]>=0)
	 {
		 attrib[temp_num_attrib]=i;
		 temp_num_attrib++;  
	 }
   }
   root=p2;
   p2->attrib_col=-1;          
   p2->value=-1;              
   p2->left_node=NULL;    
   p2->right_node=NULL;    
   p2->isleaf=-1;          
   p2->classno=-1;    
   if(classsum==1)
   {
         p2->classno=a[classsum-1];
         p2->isleaf=1;
         p2->left_node=NULL;
		 p2->right_node=NULL;
         return root;
    }
   if(temp_num_attrib==0)
   {
	   int max=b[0];
	   for(i=0;i<classsum;i++)
	   {
           if(b[i]>max)
		   {
			   max=b[i];
			   p=i;
		   }
	   }
         p2->classno=a[p];
         p2->isleaf=1;
         p2->left_node=NULL;
		 p2->right_node=NULL;
         return root;
   }   
 
    double inforgain=0;
    int currentcol=-1;
    for(i=0;i<temp_num_attrib;i++)
	{
      double tempgain=Compute_InforGain(data,record_num,attrib[i],num_attrib);
      if(inforgain<tempgain)
	  { 
		   inforgain=tempgain; 
	       currentcol=attrib[i];
	  }
	}
      p2->attrib_col=currentcol;
      int j=0;
      int value_no=0;
      int diferentvalue[maxsize];
      while(j<record_num)
	  {
         flag2=0;
         for (int k=0;k<value_no;k++) 
		 {
	        if (diferentvalue[k]==data[j][currentcol]) 
            flag2=1;
		 }
         if(flag2==0)
		 { 
	        diferentvalue[value_no]=data[j][currentcol];
	        value_no++;	  
		 }
        j++;
	  }
int **subdata,k;
	subdata=(int**)malloc(record_num*sizeof(int*));           //?subdata????
	for(i=0;i<record_num;i++)
	{
		subdata[i]=(int*)malloc(num_attrib*sizeof(int));
	}
for(i=0;i<value_no;i++)
{
    k=0;
   for (int x=0;x<record_num;x++)
   {
     if (data[x][currentcol]==diferentvalue[i])
        {		   
           for(int i1=0;i1<num_attrib;i1++)
		   {
			    if(i1!=currentcol)
					subdata[k][i1]=data[x][i1];
                else 
					subdata[k][i1]=-1;
		   }
		    k++;
         }
   }
   p2->attrib_col=currentcol;
   p2->value=diferentvalue[i];
   p2->isleaf=0;
   p2->classno=-1;
   p2->left_node=Build_ID3(subdata,k,num_attrib);
   p2->right_node=(s_tree *)malloc(sizeof(s_tree));
   p2=p2->right_node;
   p2->attrib_col=-1;          
   p2->value=-1;             
   p2->left_node=NULL;    
   p2->right_node=NULL;    
   p2->isleaf=0;          
   p2->classno=-1;    
 }
return root;
}
      

int outputrule(s_tree *p,int *data)
{
	int col_no,class_no=-1;
	int flag1=0,flag2=0;
	int count=0;
	while(flag1==0)
	{
		
		col_no=p->attrib_col;
		while(flag2==0)
		{
			if(data[col_no]!=p->value&&p->right_node!=NULL)
				p=p->right_node;
			else
				flag2=1;

		}		
		if(p->classno!=-1)
		{
			class_no=p->classno;
			flag1=1;
		}
		if(p->left_node!=NULL&&flag1==0)
		{
			p=p->left_node;
			flag2=0;
		}
		
		if(count>9)
			flag1=1;
		count++;
	}
	return class_no;
}

double ID3(int **array,int **data,int n,int r_n,int m)
{
	s_tree *p=NULL;
	int i,j,num=0,temp;
	int rs[maxsize][maxsize];
	int cla=0,class_temp[maxsize];
	//??????
	for(j=0;j<n;j++)
	{
		if(data[j][m-1]>cla)
			cla=data[j][m-1];
	}
	cla++;
	//?rs???????
	for(i=0;i<cla;i++)
	{
		for(j=0;j<cla;j++)
		{
			rs[i][j]=0;
		}
	}
	p=Build_ID3(array,r_n,m);
	for(i=0;i<n;i++)
	{
		temp=outputrule(p,data[i]);
		if(temp==data[i][m-1])
			num++;
		rs[data[i][m-1]][temp]++;
	}
	printf("\n????????");
	//??????
	cla=0;
	for(j=0;j<n;j++)
	{
		if(data[j][m-1]>cla)
			cla=data[j][m-1];
	}
	cla++;
	for(i=0;i<cla;i++)
	{
		printf("\n");
		for(j=0;j<cla;j++)
			printf("%d\t",rs[i][j]);
	}
	printf("\nID3???:%f\n",(double)num/n);
	return (double)num/n;
}



double bayes(int **data,int **record,int n,int m,int r_n)
{
	int i,j,k,t;
	int class_temp[maxsize],temp,count_temp=0,k_temps;
	double **temps,max_temps;
	int rs[maxsize][maxsize];
	int *classs;
	int ***count;  //???????;???????? 
	int sign,num=0;
//????????
	classs=(int*)malloc(r_n*sizeof(int));   //?classs????
	for(i=0;i<m;i++)
	{
		temp=0;
		classs[i]=0;
		for(j=0;j<r_n;j++)
		{
			if(record[j][i]>temp)
				temp=record[j][i];
		}
		classs[i]=temp+1;
		if(classs[i]>count_temp)
			count_temp=classs[i]+1;
	}
//	printf("%d",classs[m-1]);
//???????
	for(k=0;k<classs[m-1];k++)
	{
		class_temp[k]=0;
		for(i=0;i<r_n;i++)
		{
			if(record[i][m-1]==k)
				class_temp[k]++;
		}	
//		printf("\t%d",class_temp[k]);
	}
//????????????
	count=(int***)malloc(m*sizeof(int**));                  //?count????
	for(i=0;i<m;i++)
	{
		count[i]=(int**)malloc(count_temp*sizeof(int*));
		for(j=0;j<count_temp;j++)
		{
			count[i][j]=(int*)malloc(classs[m-1]*sizeof(int));
		}
	}
	temps=(double**)malloc(r_n*sizeof(double*));           //?temps????
	for(i=0;i<r_n;i++)
	{
		temps[i]=(double*)malloc(classs[m-1]*sizeof(double));
	}
	for(k=0;k<classs[m-1];k++)
	{
		for(i=0;i<m-1;i++)
		{
			for(t=0;t<classs[i];t++)
			{
				count[i][t][k]=0;
				for(j=0;j<n;j++)
				{
					if(record[j][i]==t&&record[j][m-1]==k)
						count[i][t][k]++;
				}
			}
		}	
	}
	for(i=0;i<n;i++)
	{
		for(k=0;k<classs[m-1];k++)
		{
			temps[i][k]=1;
			for(j=0;j<m-1;j++)
			{
				temps[i][k]*=(double)count[j][data[i][j]][k]/class_temp[k];
			}
			temps[i][k]*=(double)class_temp[k]/r_n;
		}
	}
	//?rs?????????
	for(i=0;i<classs[m-1];i++)
	{
		for(j=0;j<classs[m-1];j++)
		{
			rs[i][j]=0;
		}
	}
	//?????
	for(i=0;i<n;i++)
	{
		max_temps=-1;
		k_temps=-1;
		for(k=0;k<classs[m-1];k++)
		{
			if(temps[i][k]>max_temps)
			{
				max_temps=temps[i][k];
				k_temps=k;
			}
		}
		sign=k_temps;
		rs[data[i][m-1]][sign]++;
		if(data[i][m-1]==sign)
		{
			num=num+1;
		}	
	}
	//??????
	printf("\n????????");
	for(i=0;i<classs[m-1];i++)
	{
		printf("\n");
		for(j=0;j<classs[m-1];j++)
			printf("%d\t",rs[i][j]);
	}
	printf("\nbayes???%f\n",(double)num/n);
	return (double)num/n;

	//???? 
	free(classs);                 //?classs????

	               
	for(i=0;i<m-1;i++)              //?count????
	{	
		for(j=0;j<count_temp;j++)
		{
			free(count[i][j]);
		}
	}
	for(i=0;i<m-1;i++)
	{	
		free(count[i]);
	}	
	free(count);   

	           
	for(i=0;i<r_n;i++)               //?temps????
	{
		free(temps[i]);
	}
	free(temps);
}


void files(int n,int m,int cross)
{
	FILE *outfile;
	FILE *newfile=NULL;
	FILE *writefile=NULL;
	int file[maxsize];
	int i,j,k;
	char filename[50],s[maxsize],data[500];
	if((outfile=fopen("e:\\a\\table.txt","r"))==NULL) 
	{ 
		printf("???????????????\n");
		exit(0);
	}
	//??1-10??
	for(i=0;i<cross;i++)
	{
		memset(filename, 0, sizeof(filename));
		itoa(i+1,s,10);
		strcat(filename,"e:\\a\\"); 
		strcat(filename,s); 	
		strcat(filename,".txt"); 
		newfile = fopen(filename, "w+");
	}
	//?????????1-10?txt???
	for(i=0;i<n;n++)
	{	fscanf(outfile,"\n");
		while(feof(outfile))
		return;
		for(j=0;j<cross;j++)
		{
			memset(data, 0, sizeof(data));
			for(k=0;k<m;k++)
			{
				file[k]=0;
				fscanf(outfile,"%d",&file[k]);
				strcat(data," "); 
				itoa(file[k],s,10);
				strcat(data,s); 
			}
			memset(filename, 0, sizeof(filename));
			itoa(j+1,s,10);                          //?????
			strcat(filename,"e:\\a\\"); 
			strcat(filename,s); 	
			strcat(filename,".txt"); 
			strcat(data,"\n"); 
			writefile=fopen(filename,"a+");
			fputs(data,writefile);
			fclose(writefile);
		}

	}
}


int main ()
{
//????
	int i,j,k,t;
	int **data,**record;    //data??,record????
	int record_num;         //????????????
    int n,m,cross;       //????n???,m???,k???
	double num_cross1=0.00,num_cross2=0.00;
//????????
	int lines=0;
	FILE *outfile;
	char filename[50],s[10];
	printf("??????????");
	scanf("%d",&m);
	printf("???????????????");
	scanf("%d",&cross);
//??????????
	if((outfile=fopen("e:\\a\\table.txt","r"))==NULL) 
	{ 
		printf("???????????????\n");
		exit(0);
	}
	while (!feof(outfile))
    {
		if (fgetc(outfile)=='\n')
			lines++;
	}
	n=lines/cross;                        //???????????????????
	fclose(outfile);
//????
	printf("???????????...");
//	files(n,m,cross);
//?????????
	data=(int**)malloc(n*sizeof(int*)); 
	for(i=0;i<n; i++)
	{
		data[i]=(int*)malloc(m*sizeof(int));
	} 
	record=(int**)malloc(n*cross*sizeof(int*)); 
	for(i=0;i<n*cross;i++)
	{
		record[i]=(int*)malloc(m*sizeof(int));
	}

	for(i=0;i<cross;i++)
	{
		record_num=0;
		memset(filename, 0, sizeof(filename));
		itoa(i+1,s,10);
		strcat(filename,"e:\\a\\"); 
		strcat(filename,s); 	
		strcat(filename,".txt"); 
		outfile=fopen(filename,"r");
		for(j=0;j<n;j++)
		{
			for(k=0;k<m;k++)
			{
				fscanf(outfile,"%d",&data[j][k]);               //???
			}
			fscanf(outfile,"\n");
		}
		fclose(outfile);
		for(t=0;t<i;t++)
		{
			memset(filename, 0, sizeof(filename));
			itoa(t+1,s,10);
			strcat(filename,"e:\\a\\"); 
			strcat(filename,s); 	
			strcat(filename,".txt"); 
			outfile=fopen(filename,"r");
			for(j=0;j<n;j++)
			{
				for(k=0;k<m;k++)
				{
					fscanf(outfile,"%d",&record[record_num][k]); //???
				}
				fscanf(outfile,"\n");
				record_num++;
			}
			fclose(outfile);
		}
		for(t=i+1;t<cross;t++)
		{
			memset(filename, 0, sizeof(filename));
			itoa(t+1,s,10);
			strcat(filename,"e:\\a\\"); 
			strcat(filename,s); 	
			strcat(filename,".txt"); 
			outfile=fopen(filename,"r");
			for(j=0;j<n;j++)
			{
				for(k=0;k<m;k++)
				{
					fscanf(outfile,"%d",&record[record_num][k]);  //???
				}
				fscanf(outfile,"\n");
				record_num++;
			}
			fclose(outfile);
		}
		num_cross1+=(double)bayes(data,record,n,m,n*(cross-1));
		num_cross2+=(double)ID3(record,data,n,record_num,m);
	}
	printf("\nbayes???????%f\n",(double)num_cross1/cross);
	printf("\nID3???????%f\n",(double)num_cross2/cross);
}




























?????
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <conio.h> 
#include <math.h> 

//#define DEBUG 

extern unsigned _stklen = 50000U; 

/***************************************************************************/ 
int id3(int file_code) 
{ 
#define M1 15   // no of rows in learn.dat > no of items clustered 
#define M2 150  // no of atts for ID3 > atts in attrib.dat                               //it was 150 
before 
#define M3 5    // length of string describing attribute                                 //it was 4 
before 
#define M4 141  // no of attributes in attrib.dat + 1 (for EOS)        //it was 101 before 

int data_load(char string[M1][M2][M3], int *, int *, char title[M2][M3]); 
int check_all_positive(char string[M1][M2][M3], int, int); 
int check_all_negative(char string[M1][M2][M3], int, int); 
int get_diff_att_types(char valid[M1], char string[M1][M2][M3], 
                                             char att_names[M1][M3], int, int); 
int create_tree(char rule[M4], char avail_att[M2], FILE *ofp, 
                                             FILE *nfp, FILE *pfp, char string[M1][M2][M3], 
                                             char valid[M1], int, int, char title[M2][M3], int); 
int not_all_same(char valid[M1], char string[M1][M2][M3], int attributes); 

int attributes = 0, rows = 0, tab_cnt = 0; 
char string[M1][M2][M3]; 
char title[M2][M3]; 
char valid[M1]; 
char avail_att[M2]; 
char rule[M4]; 
FILE *ofp, *pfp, *nfp; 

if (data_load(string,&attributes,&rows,title) == 999) 
                    { 
        //printf("load\n"); 
                    return 0; 
                    } 

//printf("%d\n", attributes); 
//printf("%d\n", rows); 

if (file_code == 1) 
          { 
         if ((ofp = fopen("d_tree.dat","w")) == NULL) 
                    { 
                    printf("File error : Cannot create output file TREE.DAT\n"); 
                    return 0; 
                    } 
          if ((pfp = fopen("d_pos.dat","w")) == NULL) 
                    { 
                    printf("File error : Cannot create output file POSITIVE.DAT\n"); 
                    return 0; 
                    } 
          if ((nfp = fopen("d_neg.dat","w")) == NULL) 
                    { 
                    printf("File error : Cannot create output file NEGATIVE.DAT\n"); 
                    return 0; 
                    } 
         } 
else 
          { 
         if ((ofp = fopen("d_tree.dat","a")) == NULL) 
                    { 
                    printf("File error : Cannot create output file TREE.DAT\n"); 
                    return 0; 
                    } 
          if ((pfp = fopen("d_pos.dat","a")) == NULL) 
                    { 
                    printf("File error : Cannot create output file POSITIVE.DAT\n"); 
                    return 0; 
                    } 
          if ((nfp = fopen("d_neg.dat","a")) == NULL) 
                    { 
                    printf("File error : Cannot create output file NEGATIVE.DAT\n"); 
                    return 0; 
                    } 
         } 

fprintf(pfp, "rule\n"); 
fprintf(nfp, "rule\n");
fprintf(ofp, "\n"); 

if (check_all_positive(string,attributes,rows)) 
                    { 
                    fprintf(ofp,"HALT:all_positive\n"); 
                    fprintf(pfp,"HALT:all_positive\n"); 
                    fprintf(nfp,"HALT:all_positive\n"); 
                    fprintf(pfp, "rule_end\n"); 
                    fprintf(nfp, "rule_end\n"); 
                    fclose(ofp); 
                    fclose(nfp); 
                    fclose(pfp); 
                    return 1; 
                    } 

if (check_all_negative(string,attributes,rows)) 
                    { 
                    fprintf(ofp,"HALT:all_negative\n"); 
                    fprintf(pfp,"HALT:all_negative\n"); 
                    fprintf(nfp,"HALT:all_negative\n"); 
                    fprintf(pfp, "rule_end\n"); 
                    fprintf(nfp, "rule_end\n"); 
                    fclose(ofp); 
                    fclose(nfp); 
                    fclose(pfp); 
                    return 1; 
                    } 

memset (valid, 42, rows);    // set to '*' 
memset (avail_att, 42, M2);  // set to '*' 
memset (rule, 45, M4);       // set to '-' 

if (create_tree(rule, avail_att, ofp, nfp, pfp, string, valid, rows, attributes, title, tab_cnt) == 999) 
                    { 
                    return 0; 
                    } 

fprintf(pfp, "rule_end\n"); 
fprintf(nfp, "rule_end\n"); 

fclose(ofp); 
fclose(pfp); 
fclose(nfp); 

return 1; 
} 

/***************************************************************************/ 
int create_tree(char rule[M4], char avail_att[M2], FILE *ofp, 
                                             FILE *nfp, FILE *pfp, char string[M1][M2][M3], 
                                              char valid[M1], int rows, int attributes, char 
title[M2][M3], 
                                              int tab_cnt) 
{ 
int get_diff_att_types(char valid[M1], char string[M1][M2][M3], 
                                              char att_names[M1][M3], int, int); 
int not_all_same(char valid[M1], char string[M1][M2][M3], int attributes); 
int find_att(char avail_att[M2], char string[M1][M2][M3], char valid[M1], 
                                               int attributes, int rows); 

char att_names[M1][M3] = {" "}; 
char valid_2[M1]; 
char avail_att_2[M2]; 
char rule_2[M4]; 
int  j, l, i, ret, tot_diff_atts, att_no; 

for (i=0;i<tab_cnt+tab_cnt;++i) 
                    { 
                    fprintf(ofp,"\t"); 
                    } 

tab_cnt++; 

if ((att_no = find_att(avail_att, string, valid, attributes, rows)) == 999) 
                    { 
        //printf("attno\n"); 
                    return 999; 
                    } 

rule[M4-1] = '\0';                 //make string 
avail_att[M2-1] = '\0';            //make string 
strcpy(avail_att_2, avail_att); 
avail_att_2[att_no] = ' '; 

fprintf(ofp, "[%s]\n", title[att_no]); 

tot_diff_atts = get_diff_att_types(valid, string, att_names, att_no, rows); 

for (j=0;j<tot_diff_atts;++j) 
                    { valid[M1-1] = '\0'; 
                    strcpy(valid_2,valid); 

                    for (l=0;l<rows;++l) 
                                             { 
                                             if (strcmp(att_names[j],string[l][att_no]) != 0) 
                                                                      { 
                                                                      valid_2[l] = ' '; 
                                                                      } 
                                             } 

                    if ((ret = not_all_same(valid_2,string,attributes)) == 1) 
                                             { 
                                             for (i=0;i<tab_cnt+tab_cnt-1;++i) 
                                                                      { 
                                                                      fprintf(ofp,"\t"); 
                                                                      } 

                                             fprintf(ofp,"%s\n",att_names[j]); 
                                             rule[att_no-1] = att_names[j][0]; 
                                             strcpy(rule_2, rule); 

                                             if (create_tree(rule_2, avail_att_2, ofp, nfp, pfp, 
                                                                      string, valid_2, rows, 
attributes,title,tab_cnt) == 999) 
                                                                      { 
                                                                      return 999; 
                                                                      } 
                                             } 
                    else 
                                             { 
                                             for (i=0;i<tab_cnt+tab_cnt-1;++i) 
                                                                      { 
                                                                      fprintf(ofp,"\t"); 
                                                                      } 
                                             if (ret == 2) 
                                                                      { 
                                                                      fprintf(ofp,"%s\t - 
YES\n",att_names[j]); 
                                                                      rule[att_no-1] = att_names[j][0]; 
                                                                      fprintf(pfp,"%s\n",rule); 
                                                                      } 
                                             else 
                                                                      { 
                                                                      fprintf(ofp,"%s\t - 
NO\n",att_names[j]); 
                                                                      rule[att_no-1] = att_names[j][0]; 
                                                                      fprintf(nfp,"%s\n",rule); 
                                                                      } 
                                             } 
                   } 
return 1; 
} 

/***************************************************************************/ 
int find_att(char avail_att[M2], char string[M1][M2][M3], char valid[M1], 
                                             int attributes, int rows) 
{ 

int get_diff_att_types(char valid[M1], char string[M1][M2][M3], 
                                             char att_names[M1][M3], int, int); 
void disaster(int); 

int i, j, l, y_tot = 0, n_tot = 0, y_tot_2, n_tot_2; 
int tot_diff_atts; 
int att_no = 0; 
double max_inf_gain = -1.0; 
double entropy, entropy_2, r_entropy_tot; 
double att_entropy[M2]; 
char att_names[M1][M3] = {" "}; 
char valid_2[M1]; 

// CHOSE ONE OF THE FOLLOWING 

// THIS IS THE MAX INFO GAIN 

for (i=0;i<M2;++i) 
                   { 
                    att_entropy[i] = -2.0; 
                   } 

// THIS IS THE MIN INFO GAIN 

//for (i=0;i<M2;++i) 
//                 { 
//                 att_entropy[i] = 2.0; 
//                 } 

// CHOSE ONE OF THE ABOVE 

for (i=1;i<=M1;i++)    { 
                    if (valid[i] == '*') 
                                             { 
                                             if (strcmp(string[i][attributes],"yes") == 0) 
                                                                      ++y_tot; 
                                             if (strcmp(string[i][attributes],"no") == 0) 
                                                                      ++n_tot; 
                                             } 
                    } 

if (y_tot == 0 || n_tot == 0) 
                    entropy = 0.0; 
else 
                    { 
                    entropy =  0.0 - ((y_tot/(double)(y_tot+n_tot)) 

         *log((y_tot/(double)(y_tot+n_tot)))) 
                                                                      - ((n_tot/(double)(y_tot+n_tot))* 

         log((n_tot/(double)(y_tot+n_tot)))); 
                    } 

for (i=1;i<attributes;++i) 
                    { 
                    if (avail_att[i] == '*') 
                                             { 
                                             r_entropy_tot = 0.0; 
                                             tot_diff_atts = get_diff_att_types(valid, string, 

                                                                att_names, i, rows); 

                                             for (j=0;j<tot_diff_atts;++j) 
                                                                       { 

                                                                      memset (valid_2, 32, M1); 

                                                                      for (l=1;l<=rows;++l) 
                                                                                          { 
                                                                                          if 
((strcmp(att_names[j],string[l][i]) == 0) 

                   && (valid[l] == '*')) 

                   valid_2[l] = '*'; 
                                                                                          } 

                                                                      y_tot_2 = 0; 
                                                                      n_tot_2 = 0; 

                                                                      for (l=1;l<=M1;l++) 
                                                                                          { 
                                                                                          if (valid_2[l] 
== '*') 

                   { 

                   if (strcmp(string[l][attributes],"yes") == 0) 

                                            ++y_tot_2; 

                   if (strcmp(string[l][attributes],"no") == 0) 

                                            ++n_tot_2; 

                   } 
                                                                                          } 

                                                                      if (n_tot_2 == 0 || y_tot_2 == 0) 
                                                                                          entropy_2 = 
0.0; 
                                                                      else 
                                                                                          { 
                                                                                          entropy_2 = 
0.0 - ((y_tot_2/(double)(y_tot_2+n_tot_2)) 

                                             *log((y_tot_2/(double)(y_tot_2+n_tot_2)))) 

                                             - ((n_tot_2/(double)(y_tot_2+n_tot_2)) 

                                             *log((n_tot_2/(double)(y_tot_2+n_tot_2)))); 
                                                                                          } 

                                                                      r_entropy_tot = r_entropy_tot + 
(entropy_2 

                   * ((n_tot_2+y_tot_2)/(double)(n_tot+y_tot))); 
                                                                       } 

                                             att_entropy[i] = entropy - r_entropy_tot; 

                                             }// CHOSE ONE OF THE FOLLOWING 

// THIS IS THE MAX INFO GAIN 

for (l=0;l<M2;++l) 
                   { 
                    if (att_entropy[l] >= max_inf_gain) 
                                             { 
                                             max_inf_gain = att_entropy[l]; 
                                             att_no = l; 
                                             } 
                   } 

if (max_inf_gain == 0.0) 
                   { 
                    disaster(1); 
                    return 999; 
                   } 

// THIS IS THE MIN INFO GAIN 

//max_inf_gain = 1.99; 

//for (l=0;l<M2;++l) 
//                 { 
//                 if (att_entropy[l] <= max_inf_gain) 
//                                           { 
//                                           max_inf_gain = att_entropy[l]; 
//                                           att_no = l; 
//                                           } 
//                 } 

//if (max_inf_gain == 1.99) 
//                 { 
//                 disaster(1); 
//                 return 999; 
//                 } 

// CHOOSE ONE OF THE ABOVE 

return att_no; 

} 

/***************************************************************************/ 
int not_all_same(char valid[M1], char string[M1][M2][M3], int attributes) 
{ 
int i, y_tot = 0, n_tot = 0; 

for (i=0;i<M1;i++) 
                   { 
                    if (valid[i] == '*') 
                                             { 
                                             if (strcmp(string[i][attributes],"yes") == 0) 
                                                                      ++y_tot; 
                                             if (strcmp(string[i][attributes],"no") == 0) 
                                                                      ++n_tot; 
                                             } 
                   } 

if (n_tot == 0) 
                    return 2;    /* all yes */ 
else if (y_tot == 0) 
                    return 3;    /* all no  */ 
else 
                    return 1; 
} 

/***************************************************************************/ 
int get_diff_att_types(char valid[M1], char string[M1][M2][M3], 
                                                                                          char 
att_names[M1][M3], int att, int max_row) 
{ 
int j,l,k; 
char att_temp[M1][M3]; 

for(j=0;j<max_row;j++) 
                   { 
                    strcpy(att_names[j],string[j][att]); 
                   } 

for(l=0;l<j;++l) 
                   { 
                    if (valid[l] != '*') 
                                              memset(att_names[l], 42, M3-1); 
                   } 

for(j=0;j<max_row;j++) 
                   {
                    l=1; 
                    for(l=l+j;l<max_row;l++) 
                                             { 
                                             if (strcmp(att_names[j],att_names[l]) == 0) 
                                                                      { 
                                                                      memset(att_names[l], 42, M3-1); 
                                                                      } 
                                             } 
                   } 

for(l=0,k=0;l<j;l++) 
                   { 
                    if (att_names[l][0] != '*') 
                                             { 
                                             strcpy(att_temp[k],att_names[l]); 
                                             k++; 
                                             } 
                   } 

for(l=0;l<j;++l) 
                   { 
                   memset(att_names[l], 42, M3-1); 
                   } 

for(l=0;l<k;++l) 
                   { 
                    strcpy(att_names[l],att_temp[l]); 
                   } 

for(l=0,k=0;l<j;l++) 
                   { 
                    if (att_names[l][0] != '*') 
                                             ++k; 
                   } 

return k; 

} 

/***************************************************************************/ 
int check_all_positive(char string[M1][M2][M3], int attributes, int rows) 
{ 
int i; 

for(i=0;i<rows;++i) 
                   { 
                    if (strcmp(string[i][attributes],"no") == 0) 
                                             { 
                                             return 0; 
                                             } 
                   } 
return 1; 
} 

/***************************************************************************/ 
int check_all_negative(char string[M1][M2][M3], int attributes, int rows) 
{ 
int i; 

for(i=0;i<rows;++i) 
                   { 
                    if (strcmp(string[i][attributes],"yes") == 0) 
                                             { 
                                             return 0; 
                                             } 
                   } 
return 1; 
} 

/***************************************************************************/ 
int data_load(char string[M1][M2][M3], int* a, int* b, char title[M2][M3]) 
{ 
char linebuff[20]; 
int k=0; 

FILE *ifp; 

if ((ifp = fopen("d_learn.dat","r")) == NULL) 
                   { 
                   printf("File error : Cannot open input file LEARN.DAT\n"); 
                    return 999; 
                   } 

do { 
                    fscanf(ifp,"%s",title[k]); 
         }while(title[k++][0] != '*'); 

do { 
                   (*a)=0; 

                    do     {
                                     fscanf(ifp,"%s",linebuff); 
                                     strcpy(string[(*b)][(*a)],linebuff); 
                                     (*a)++; 
                                     }while(linebuff[0] != '*'); 

                     (*b)++; 

          }while(linebuff[1] !='*'); 

*a = *a - 2; 

fclose(ifp); 

return 1; 
} 

/***************************************************************************/ 
void disaster(int i) 
{ 

switch(i) 
                     { 
                     case 1: printf("** ID3 failure **\n"); 
                                                                 //system("cls"); 
                                               //printf("\nA serious error has occured.\n\n"); 
                                               //printf("All output files may be corrupt.\n\n"); 
                                               //printf("Possible inconistancies or contradictory\n"); 
                                               //printf("input cases may be the cause.\n\n"); 
                                               //printf("\n\nPress any key"); 
                                               //getche(); 
                                               break; 
                     } 
} 

/***************************************************************************/#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <conio.h> 
#include <math.h> 

//#define DEBUG 

extern unsigned _stklen = 50000U; 

/***************************************************************************/ 
int id3(int file_code) 
{ 
#define M1 15   // no of rows in learn.dat > no of items clustered 
#define M2 150  // no of atts for ID3 > atts in attrib.dat                              //it was 150 
before 
#define M3 5    // length of string describing attribute                                //it was 4 
before 
#define M4 141  // no of attributes in attrib.dat + 1 (for EOS)         //it was 101 before 

int data_load(char string[M1][M2][M3], int *, int *, char title[M2][M3]); 
int check_all_positive(char string[M1][M2][M3], int, int); 
int check_all_negative(char string[M1][M2][M3], int, int); 
int get_diff_att_types(char valid[M1], char string[M1][M2][M3], 
                                         char att_names[M1][M3], int, int); 
int create_tree(char rule[M4], char avail_att[M2], FILE *ofp, 
                                         FILE *nfp, FILE *pfp, char string[M1][M2][M3], 
                                         char valid[M1], int, int, char title[M2][M3], int); 
int not_all_same(char valid[M1], char string[M1][M2][M3], int attributes); 

int attributes = 0, rows = 0, tab_cnt = -1; 
char string[M1][M2][M3]; 
char title[M2][M3]; 
char valid[M1]; 
char avail_att[M2]; 
char rule[M4]; 
FILE *ofp, *pfp, *nfp; 

if (data_load(string,&attributes,&rows,title) == 999) 
                  { 
                  //printf("load\n"); 
                  return 0; 
                  } 

//printf("%d\n", attributes); 
//printf("%d\n", rows); 

if (file_code == 1) 
         { 
        if ((ofp = fopen("d_tree.dat","w")) == NULL) 
                  { 
                  printf("File error : Cannot create output file TREE.DAT\n"); 
                  return 0; 
                  } 
         if ((pfp = fopen("d_pos.dat","w")) == NULL) 
                  { 
                  printf("File error : Cannot create output file POSITIVE.DAT\n"); 
                  return 0; 
                  } 
         if ((nfp = fopen("d_neg.dat","w")) == NULL) 
                  { 
                  printf("File error : Cannot create output file NEGATIVE.DAT\n"); 
                  return 0; 
                  } 
         } 
else 
         { 
         if ((ofp = fopen("d_tree.dat","a")) == NULL) 
                  { 
                  printf("File error : Cannot create output file TREE.DAT\n"); 
                  return 0; 
                  } 
         if ((pfp = fopen("d_pos.dat","a")) == NULL) 
                  { 
                  printf("File error : Cannot create output file POSITIVE.DAT\n"); 
                  return 0; 
                  } 
         if ((nfp = fopen("d_neg.dat","a")) == NULL) 
                  { 
                  printf("File error : Cannot create output file NEGATIVE.DAT\n"); 
                  return 0; 
                  } 
        }fprintf(pfp, "rule\n"); 
fprintf(nfp, "rule\n"); 
fprintf(ofp, "\n"); 

if (check_all_positive(string,attributes,rows)) 
                  { 
                  fprintf(ofp,"HALT:all_positive\n"); 
                  fprintf(pfp,"HALT:all_positive\n"); 
                  fprintf(nfp,"HALT:all_positive\n"); 
                  fprintf(pfp, "rule_end\n"); 
                  fprintf(nfp, "rule_end\n"); 
                  fclose(ofp); 
                  fclose(nfp); 
                  fclose(pfp); 
                  return 1; 
                  } 

if (check_all_negative(string,attributes,rows)) 
                  { 
                  fprintf(ofp,"HALT:all_negative\n"); 
                  fprintf(pfp,"HALT:all_negative\n"); 
                  fprintf(nfp,"HALT:all_negative\n"); 
                  fprintf(pfp, "rule_end\n"); 
                  fprintf(nfp, "rule_end\n"); 
                  fclose(ofp); 
                  fclose(nfp); 
                  fclose(pfp); 
                  return 1; 
                  } 

memset (valid, 42, rows);    // set to '*' 
memset (avail_att, 42, M2);  // set to '*' 
memset (rule, 45, M4);       // set to '-' 

if (create_tree(rule, avail_att, ofp, nfp, pfp, string, valid, rows, attributes, title, tab_cnt) == 999) 
                  { 
                  return 0; 
                  } 

fprintf(pfp, "rule_end\n"); 
fprintf(nfp, "rule_end\n"); 

fclose(ofp); 
fclose(pfp); 
fclose(nfp); 

return 1; 
} 

/***************************************************************************/ 
int create_tree(char rule[M4], 
                                         char avail_att[M2], 
                                         FILE *ofp, 
                                         FILE *nfp, 
                                         FILE *pfp, 
                                         char string[M1][M2][M3], 
                                         char valid[M1], 
                                         int rows, int attributes, 
                                         char title[M2][M3], 
                                         int tab_cnt) 
        { 
        int get_diff_att_types(char valid[M1], 
                                                                   char string[M1][M2][M3], 
                                                                   char att_names[M1][M3], 
                                                                   int, 
                                                                   int); 

        int not_all_same(char valid[M1], 
                                                  char string[M1][M2][M3], 
                                                   int attributes); 

        int find_att(char avail_att[M2], 
                                         char string[M1][M2][M3], 
                                         char valid[M1], 
                                         int attributes, 
                                         int rows, 
                                         int function_code, 
                                         int which_best); 

        char att_names[M1][M3] = {" "}; 
        char valid_2[M1]; 
        char avail_att_2[M2]; 
        char rule_2[M4]; 
        char rule_work[M4]; 
        int j; 
        int l; 
        int i; 
        int ret; 
        int tot_diff_atts; 
        int att_no; int function_code; 
        int equal_best; 
        int which_best; 
        int for_each_rule; 

//      for (i=0;i<tab_cnt+tab_cnt;++i) 
//              { 
//              fprintf(ofp,"\t"); 
//              } 

        tab_cnt++; 

        which_best = 999; 
        function_code = 1; 

        if ((equal_best = find_att(avail_att, string, valid, attributes, rows, function_code, 
which_best)) == 999) 
                { 
                return 999; 
                } 

//      printf("Equal best : %d \n", equal_best); getche(); 

        for (for_each_rule = 1; for_each_rule <= equal_best; for_each_rule++) 
                { 
//              printf("for each rule : %d \n", for_each_rule); getche(); 

                function_code = 3; 
                which_best = for_each_rule; 

                if ((att_no = find_att(avail_att, string, valid, attributes, rows, function_code, 
which_best)) == 999) 
                        { 
                        return 999; 
                        } 

                rule[M4-1] = '\0';                 //make string 
                avail_att[M2-1] = '\0';            //make string 
                strcpy(rule_work, rule); 
                strcpy(avail_att_2, avail_att); 

                avail_att_2[att_no] = ' '; 

                for (i=0;i<tab_cnt+tab_cnt;++i) 
                        { 
                        fprintf(ofp,"\t"); 
                        } 

//              tab_cnt++; 

                fprintf(ofp, "[%s]\n", title[att_no]); 

                tot_diff_atts = get_diff_att_types(valid, string, att_names, att_no, rows); 

                for (j=0;j<tot_diff_atts;++j) 
                        { 
                        valid[M1-1] = '\0'; 
                        strcpy(valid_2,valid); 
                        for (l=0;l<rows;++l) 
                                { 
                                if (strcmp(att_names[j],string[l][att_no]) != 0) 
                                        { 
                                        valid_2[l] = ' '; 
                                        } 
                                } 
                        if ((ret = not_all_same(valid_2,string,attributes)) == 1) 
                                { 
                                for (i=0;i<tab_cnt+tab_cnt+1;++i) 
                                        { 
                                        fprintf(ofp,"\t"); 
                                        } 
                                fprintf(ofp,"%s\n",att_names[j]); 
                                rule_work[att_no-1] = att_names[j][0]; 
                                strcpy(rule_2, rule_work); 
                                if (create_tree(rule_2, avail_att_2, ofp, nfp, pfp, 
                                                string, valid_2, rows, attributes,title,tab_cnt) == 999) 
                                        { 
                                        return 999; 
                                        } 
                                } 
                        else 
                                { 
                                for (i=0;i<tab_cnt+tab_cnt+1;++i) 
                                        { 
                                        fprintf(ofp,"\t"); 
                                        } 
                                if (ret == 2) 
                                        { 
                                        fprintf(ofp,"%s\t - YES\n",att_names[j]); 
                                        rule_work[att_no-1] = att_names[j][0]; 
                                        fprintf(pfp,"%s\n",rule_work); 
                                        } 
                                else 
                                        { 
                                        fprintf(ofp,"%s\t - NO\n",att_names[j]); 
                                        rule_work[att_no-1] = att_names[j][0]; 
                                        fprintf(nfp,"%s\n",rule_work); 
                                        } 
                                } 
                        } 
                } // end for each of the best 

        return 1; 
        } 

/***************************************************************************/ 
int find_att(char avail_att[M2], 
                                 char string[M1][M2][M3], 
                                 char valid[M1], 
                                 int attributes, 
                                 int rows, 
                                 int function_code, 
                                 int which_best) 
        { 

        int get_diff_att_types(char valid[M1], 
                                                                  char string[M1][M2][M3], 
                                                                  char att_names[M1][M3], 
                                                                  int, 
                                                                  int); 
        void disaster(int); 

        int i, j, l, y_tot = 0, n_tot = 0, y_tot_2, n_tot_2; 
        int tot_diff_atts; 
        int att_no = 0; 
        double max_inf_gain = -1.0; 
        double entropy, entropy_2, r_entropy_tot; 
        double att_entropy[M2]; 
        char att_names[M1][M3] = {" "}; 
        char valid_2[M1]; 
        int equal_best; 

// CHOSE ONE OF THE FOLLOWING 

// THIS IS THE MAX INFO GAIN 

        for (i=0;i<M2;++i) 
                { 
                att_entropy[i] = -2.0; 
                } 

// THIS IS THE MIN INFO GAIN 

// for (i=0;i<M2;++i) 
//              { 
//              att_entropy[i] = 2.0; 
//              } 

// CHOSE ONE OF THE ABOVE 

        for (i=1;i<=M1;i++) 
                { 
                if (valid[i] == '*') 
                        { 
                        if (strcmp(string[i][attributes],"yes") == 0) 
                                { 
                                ++y_tot; 
                                } 
                        if (strcmp(string[i][attributes],"no") == 0) 
                                { 
                                ++n_tot; 
                                } 
                        } 
                } 

        if (y_tot == 0 || n_tot == 0) 
                { 
                entropy = 0.0; 
                } 
        else 
                { 
                entropy =  0.0 - ((y_tot/(double)(y_tot+n_tot)) 
                                                                * log((y_tot/(double)(y_tot+n_tot)))) 
                                                                - ((n_tot/(double)(y_tot+n_tot)) 
                                                                * log((n_tot/(double)(y_tot+n_tot)))); 
                } 

        for (i=1;i<attributes;++i) 
                { 
                if (avail_att[i] == '*') 
                        { 
                        r_entropy_tot = 0.0; 
                        tot_diff_atts = get_diff_att_types(valid, string, att_names, i, rows); 
                        for (j=0;j<tot_diff_atts;++j) 
                                { 
                                memset (valid_2, 32, M1); 
                                for (l=1;l<=rows;++l) 
                                        { 
                                        if ((strcmp(att_names[j],string[l][i]) == 0) && (valid[l] == 
'*')) 
                                                { 
                                                valid_2[l] = '*'; 
                                                } 
                                        } 
                                y_tot_2 = 0; 
                                n_tot_2 = 0; 
                                for (l=1;l<=M1;l++) 
                                        { 
                                        if (valid_2[l] == '*') 
                                                { 
                                                if (strcmp(string[l][attributes],"yes") == 0) 
                                                        { 
                                                        ++y_tot_2; 
                                                        } 
                                                if (strcmp(string[l][attributes],"no") == 0) 
                                                        { 
                                                        ++n_tot_2; 
                                                        } 
                                                } 
                                        } 
                                if (n_tot_2 == 0 || y_tot_2 == 0) 
                                        { 
                                        entropy_2 = 0.0; 
                                        } 
                                else 
                                        { 
                                        entropy_2 =  0.0 - ((y_tot_2/(double)(y_tot_2+n_tot_2)) 
                                                                                          * 
log((y_tot_2/(double)(y_tot_2+n_tot_2)))) 
                                                                                          - 
((n_tot_2/(double)(y_tot_2+n_tot_2)) 
                                                                                          * 
log((n_tot_2/(double)(y_tot_2+n_tot_2)))); 
                                        } 
                                r_entropy_tot = r_entropy_tot + (entropy_2 
                                                                  * 
((n_tot_2+y_tot_2)/(double)(n_tot+y_tot))); 
                                } 
                                att_entropy[i] = entropy - r_entropy_tot; 
                        } 
                } 

// CHOSE ONE OF THE FOLLOWING 

// THIS IS THE MAX INFO GAIN 

        equal_best = 0; 

        for (l=0;l<M2;++l) 
                { 
                if (att_entropy[l] >= max_inf_gain) 
                        { 
//                      printf("Att entropy : %f \n", att_entropy[l]); getche(); 
//                      if ((att_entropy[l] == max_inf_gain) && (max_inf_gain >= 0.0)) 
//                              { 
//                              equal_best++; 
//                              } 
                        max_inf_gain = att_entropy[l]; 
                        att_no = l; 
                        } 
                } 

        if (function_code == 1) 
                { 
                for (l=0;l<M2;++l) 
                        { 
                        if (att_entropy[l] >= max_inf_gain) 
                                { 
//                              printf("Att entropy : %f \n", att_entropy[l]); getche(); 
                                equal_best++; 
                                } 
                        } 
                } 

//      printf("Max info gain : %f \n", max_inf_gain); getche(); 

        if (function_code == 3) 
                { 
                equal_best = 0; 
                for (l=0;l<M2;++l) 
                        { 
//                      printf("Att entropy : %f \n", att_entropy[l]); getche(); 
                        if (att_entropy[l] >= max_inf_gain)   { 
                                att_no = l; 
                                equal_best++; 
                                } 
                        if (which_best == equal_best) 
                                { 
                                break; 
                                } 
                        } 
                } 

//      if (equal_best > 0) 
//              { 
//              printf("Equal best : %d %f %d \n", equal_best, max_inf_gain, att_no); getche(); 
//              } 

        if (max_inf_gain == 0.0) 
                { 
                disaster(1); return 999; 
                } 

// THIS IS THE MIN INFO GAIN 

// max_inf_gain = 1.99; 

// for (l=0;l<M2;++l) 
//         { 
//         if (att_entropy[l] <= max_inf_gain) 
//            { 
//                 max_inf_gain = att_entropy[l]; 
//                 att_no = l; 
//                 } 
//         } 

// if (max_inf_gain == 1.99) 
//         { 
//         disaster(1); 
//         return 999; 
//         } 

// CHOOSE ONE OF THE ABOVE 

        if (function_code == 0) 
                { 
                return att_no; 
                } 

        if (function_code == 1) 
                { 
                return equal_best; 
                } 

        if (function_code == 3) 
                { 
                return att_no; 
                } 

        } 

/***************************************************************************/ 
int not_all_same(char valid[M1], char string[M1][M2][M3], int attributes) 
{ 
int i, y_tot = 0, n_tot = 0; 

for (i=0;i<M1;i++) 
                  { 
                  if (valid[i] == '*') 
                                         { 
                                         if (strcmp(string[i][attributes],"yes") == 0) 
                                                                ++y_tot; 
                                         if (strcmp(string[i][attributes],"no") == 0) 
                                                                ++n_tot; 
                                         } 
                  } 

if (n_tot == 0) 
                  return 2;    /* all yes */ 
else if (y_tot == 0) 
                  return 3;    /* all no  */ 
else 
                  return 1; 
} 

/***************************************************************************/ 
int get_diff_att_types(char valid[M1], char string[M1][M2][M3], 
                                                                                  char 
att_names[M1][M3], int att, int max_row) 
{ 
int j,l,k; 
char att_temp[M1][M3]; for(j=0;j<max_row;j++) 
                  { 
                  strcpy(att_names[j],string[j][att]); 
                  } 

for(l=0;l<j;++l) 
                  { 
                  if (valid[l] != '*') 
                                          memset(att_names[l], 42, M3-1); 
                  } 

for(j=0;j<max_row;j++) 
                  { 
                  l=1; 
                  for(l=l+j;l<max_row;l++) 
                                         { 
                                         if (strcmp(att_names[j],att_names[l]) == 0) 
                                                                { 
                                                                memset(att_names[l], 42, M3-1); 
                                                                } 
                                         } 
                  } 

for(l=0,k=0;l<j;l++) 
                  { 
                  if (att_names[l][0] != '*') 
                                         { 
                                         strcpy(att_temp[k],att_names[l]); 
                                         k++; 
                                         } 
                  } 

for(l=0;l<j;++l) 
                  { 
                  memset(att_names[l], 42, M3-1); 
                  } 

for(l=0;l<k;++l) 
                  { 
                  strcpy(att_names[l],att_temp[l]); 
                  } 

for(l=0,k=0;l<j;l++) 
                  { 
                  if (att_names[l][0] != '*') 
                                         ++k; 
                  } 

return k; 

} 

/***************************************************************************/ 
int check_all_positive(char string[M1][M2][M3], int attributes, int rows) 
{ 
int i; 

for(i=0;i<rows;++i) 
    { 
    if (strcmp(string[i][attributes],"no") == 0) 
    { 
    return 0; 
    } 
    } 
return 1; 
} 

/***************************************************************************/ 
int check_all_negative(char string[M1][M2][M3], int attributes, int rows) 
{ 
int i; 

for(i=0;i<rows;++i) 
                  { 
                  if (strcmp(string[i][attributes],"yes") == 0) 
                                         { 
                                         return 0; 
                                         } 
                  } 
return 1; 
} 

/***************************************************************************/ 
int data_load(char string[M1][M2][M3], int* a, int* b, char title[M2][M3]) 
{ 
char linebuff[20]; 
int k=0; 

FILE *ifp; 

if ((ifp = fopen("d_learn.dat","r")) == NULL)   { 
                  printf("File error : Cannot open input file LEARN.DAT\n"); 
                  return 999; 
                  } 

do { 
                  fscanf(ifp,"%s",title[k]); 
        }while(title[k++][0] != '*'); 

do { 
                  (*a)=0; 

                  do    { 
                                fscanf(ifp,"%s",linebuff); 
                                strcpy(string[(*b)][(*a)],linebuff); 
                                (*a)++; 
                                }while(linebuff[0] != '*'); 

                  (*b)++; 

        }while(linebuff[1] !='*'); 

*a = *a - 2; 

fclose(ifp); 

return 1; 
} 

/***************************************************************************/ 
void disaster(int i) 
{ 

switch(i) 
                  { 
                  case 1: printf("** ID3 failure **\n"); 
                                                        //system("cls"); 
                                         //printf("\nA serious error has occured.\n\n"); 
                                         //printf("All output files may be corrupt.\n\n"); 
                                         //printf("Possible inconistancies or contradictory\n"); 
                                         //printf("input cases may be the cause.\n\n"); 
                                         //printf("\n\nPress any key"); 
                                         //getche(); 
                                         break; 
                  } 
} 

/***************************************************************************/#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <conio.h> 

#include "MLTClust.h" 

//#define DEBUG 

#define LIMIT1 10                                   // how many records input ie pages in input1.dat 
#define LIMIT2 (((LIMIT1 * LIMIT1) - LIMIT1) / 2)   // required array size 

int clust() 
{ 

// Function prototype definitions 

int find_cluster_diameter(char *, cluster_record *, attribute_record_out *); 
int nearly_central(int, char *, cluster_record *, attribute_record_out *); 
int find_distance_1(attribute_data, attribute_data); 
int sort_function_1(cluster_record *, cluster_record *); 
int sort_function_2(attribute_record_out *, attribute_record_out *); 
attribute_data find_subj_attribute_vector(char *, FILE *); 
void new_name(char *, int *); 

// Local variables 

FILE *ifp, *ofp, *afp; 
int i, j, k, max, biggest, new_clust = 1, lines; 
int last_page_num, latest, actual; 
int cur_weight, max_weight, heaviest; 
char buffer[8], temp_a[8], temp_b[8], last_page[8]; 
attribute_record_out attribute_rec_out[LIMIT1]; 
cluster_record sort_array[LIMIT2]; 

// Open the input and output attribute record files. 

if ((ifp = fopen("d_input1.dat","r")) == NULL) 
        { 
        printf("File error : Cannot open input file INPUT1.DAT\n"); 
        return 0; 
        } 

if ((ofp = fopen("d_output.dat","w")) == NULL) 
        { 
        printf("File error : Cannot create output file OUTPUT.DAT\n"); 
        return 0; 
        } 

if ((afp = fopen("d_attrib.dat","r")) == NULL) 
        { 
        printf("File error : Cannot open attribute file ATTRIB.DAT\n"); 
        return 0; 
        } 

// Read the subj identifiers into memory and access the attribute 
// descriptions from the subj attribute database. 

fseek(ifp, -(LIMIT1 * 9), 2); 

for (i=0; i<LIMIT1; ++i) 
        { 
        fscanf(ifp, "%s", attribute_rec_out[i].attribute_record_in.subj_id); 
        attribute_rec_out[i].attribute_record_in.subj_attributes = 
        find_subj_attribute_vector(attribute_rec_out[i].attribute_record_in.subj_id, afp); 
        strcpy(attribute_rec_out[i].assigned_cluster_name, "DUMMY"); 
        attribute_rec_out[i].weight = i+1; 
        if (i==LIMIT1-1) 
                { 
                strcpy(last_page,attribute_rec_out[i].attribute_record_in.subj_id); 
                //printf("Last page id is : %s ", last_page); 
                last_page_num = atoi(last_page+5); 
                //printf("Last page id is : %d ", last_page_num); 
                } 
        } 

// Load the sort array with pairs of unordered input points. Add the 
// distance between the pairs to the array. 

k = 0; 
for (i=0; i<LIMIT1; ++i) 
        { 
        for (j=i+1; j<LIMIT1; ++j) 
                {
                sort_array[k].input_case_a = i; 
                sort_array[k].input_case_b = j; 
                sort_array[k].distance_a_to_b = 
                find_distance_1(attribute_rec_out[i].attribute_record_in.subj_attributes, 
                        attribute_rec_out[j].attribute_record_in.subj_attributes); 
                ++k; 
                } 
        } 

// Sort the sort array 

qsort(sort_array, LIMIT2, sizeof(cluster_record), (int(*)(const void *,const void *))sort_function_1); 

// Perform the clustering 

for (k=0; k<LIMIT2; k++) 
        { 
        if ((strcmp(attribute_rec_out[sort_array[k].input_case_a].assigned_cluster_name, "DUMMY") == 0) 
        && (strcmp(attribute_rec_out[sort_array[k].input_case_b].assigned_cluster_name, "DUMMY") == 0)) 
                { 
                // put both into a new cluster 
                new_name(buffer, &new_clust); 
                strcpy(attribute_rec_out[sort_array[k].input_case_a].assigned_cluster_name, buffer); 
                strcpy(attribute_rec_out[sort_array[k].input_case_b].assigned_cluster_name, buffer); 
                } 
        if ((strcmp(attribute_rec_out[sort_array[k].input_case_a].assigned_cluster_name, "DUMMY") == 0) 
        && (strcmp(attribute_rec_out[sort_array[k].input_case_b].assigned_cluster_name, "DUMMY") != 0)) 
                   { 
                   // one in cluster one not so put the other in the same cluster 
                   strcpy(attribute_rec_out[sort_array[k].input_case_a].assigned_cluster_name, 
                   attribute_rec_out[sort_array[k].input_case_b].assigned_cluster_name); 
                   } 
        if ((strcmp(attribute_rec_out[sort_array[k].input_case_a].assigned_cluster_name, "DUMMY") != 0) 
        && (strcmp(attribute_rec_out[sort_array[k].input_case_b].assigned_cluster_name, "DUMMY") == 0)) 
                   { 
                   // one in cluster one not so put the other in the same cluster 
                   strcpy(attribute_rec_out[sort_array[k].input_case_b].assigned_cluster_name, 
                   attribute_rec_out[sort_array[k].input_case_a].assigned_cluster_name); 
                   } 
        if ((strcmp(attribute_rec_out[sort_array[k].input_case_a].assigned_cluster_name, "DUMMY") != 0) 
        && (strcmp(attribute_rec_out[sort_array[k].input_case_b].assigned_cluster_name, "DUMMY") != 0) 
        && (strcmp(attribute_rec_out[sort_array[k].input_case_a].assigned_cluster_name, 
           attribute_rec_out[sort_array[k].input_case_b].assigned_cluster_name) != 0) 
        && (nearly_central(sort_array[k].input_case_a, 
                        attribute_rec_out[sort_array[k].input_case_a].assigned_cluster_name, 
                        sort_array, 
                        attribute_rec_out)) 
        && (nearly_central(sort_array[k].input_case_b, 
                        attribute_rec_out[sort_array[k].input_case_b].assigned_cluster_name, 
                        sort_array, 
                        attribute_rec_out)) 
        && ((float)sort_array[k].distance_a_to_b < 
(((float)(find_cluster_diameter(attribute_rec_out[sort_array[k].input_case_a].assigned_cluster_name, 
sort_array, attribute_rec_out) + 

find_cluster_diameter(attribute_rec_out[sort_array[k].input_case_b].assigned_cluster_name, sort_array, 
attribute_rec_out)) / 2)))) 
                   { 
                   // both in clusters but different ones 
                   new_name(buffer, &new_clust); 
                   strcpy(temp_a,attribute_rec_out[sort_array[k].input_case_a].assigned_cluster_name); 
                   strcpy(temp_b,attribute_rec_out[sort_array[k].input_case_b].assigned_cluster_name); 
                   for (i=0; i<LIMIT1; ++i) 
                        { 
                        if ((strcmp(attribute_rec_out[i].assigned_cluster_name,temp_a) == 0) 
                        || (strcmp(attribute_rec_out[i].assigned_cluster_name,temp_b) == 0)) 
                                strcpy(attribute_rec_out[i].assigned_cluster_name,buffer); 
                        } 
                   } 
        } 

// Sort the output records 

qsort(attribute_rec_out, LIMIT1, sizeof(attribute_record_out), (int(*)(const void *,const void 
*))sort_function_2); 

// Write the clustered records to the output file 

fprintf(ofp, "clust00subj000 a001 a002 a003 a004 a005 a006 a007 a008 a009 a010 "); 
fprintf(ofp, "a011 a012 a013 a014 a015 a016 a017 a018 a019 a020 a021 a022 a023 a024 "); 
fprintf(ofp, "a025 a026 a027 a028 a029 a030 a031 a032 a033 a034 a035 a036 a037 a038 "); 
fprintf(ofp, "a039 a040 a041 a042 a043 a044 a045 a046 a047 a048 a049 a050 a051 a052 "); 
fprintf(ofp, "a053 a054 a055 a056 a057 a058 a059 a060 a061 a062 a063 a064 a065 a066 "); 
fprintf(ofp, "a067 a068 a069 a070 a071 a072 a073 a074 a075 a076 a077 a078 a079 a080 "); 
fprintf(ofp, "a081 a082 a083 a084 a085 a086 a087 a088 a089 a090 a091 a092 a093 a094 "); 
fprintf(ofp, "a095 a096 a097 a098 a099 a100 a101 a102 a103 a104 a105 a106 a107 a108 "); 
fprintf(ofp, "a109 a110 a111 a112 a113 a114 a115 a116 a117 a118 a119 a120 a121 a122 "); 
fprintf(ofp, "a123 a124 a125 a126 a127 a128 a129 a130 a131 a132 a133 a134 a135 a136 "); 
fprintf(ofp, "a137 a138 a139 a140     *\n"); 

strcpy(temp_a,"1234567");k = 0;           // the current cluster number (reuse k) 
j = 0;           // the number of lines in cluster (reuse j) 
lines = 0;       // the number of lines written for cluster 
max = 0;         // the number of lines in the largest cluster so far 
biggest = 0;     // the number of the biggest cluster so far 
actual = 0;      // the number of the current cluster 
latest = 0;      // the cluster containing the most recent page 
cur_weight = 0;  // the current cluster weight 
max_weight = 0;  // the largest cluster weight 
heaviest = 0;    // the cluster with greatest weight 

for (i=0; i<LIMIT1; ++i) 
        { 
        if (strcmp(attribute_rec_out[i].assigned_cluster_name,temp_a) != 0) 
                { 
                strcpy(temp_a, attribute_rec_out[i].assigned_cluster_name); 

                actual++;             // increment for each cluster processed 

                cur_weight = 0;       // reset for a new cluster 

                lines = 0;            // reset for new cluster 
                } 

        lines++;                      // increment for each line written 

        if (lines > max) 
                { 
                max = lines;                // update max 
                biggest = actual;           // store for return 
                } 

        cur_weight = cur_weight + attribute_rec_out[i].weight; 

        if (cur_weight > max_weight) 
                { 
                max_weight = cur_weight;    // update max 
                heaviest = actual;          // save heaviest so far 
                } 

        //printf("Cluster weight %d \n", cur_weight); 
        //getche(); 

        if (strcmp(attribute_rec_out[i].attribute_record_in.subj_id,last_page) == 0) 
                { 
                latest = actual;      // latest is the cluster position NOT no 
                } 

        fprintf(ofp, "%s%s    %d    %d    %d    %d    %d    %d    ", 
                    attribute_rec_out[i].assigned_cluster_name, 
                    attribute_rec_out[i].attribute_record_in.subj_id, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute01, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute02, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute03, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute04, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute05, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute06); 

        fprintf(ofp, "%d    %d    %d    %d    %d    %d    %d    %d    ", 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute07, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute08, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute09, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute10, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute11, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute12, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute13, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute14); 

        fprintf(ofp, "%d    %d    %d    %d    %d    %d    %d    ", 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute15, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute16, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute17, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute18, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute19, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute20, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute21); 

        fprintf(ofp, "%d    %d    %d    %d    %d    %d    %d    ", 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute22, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute23, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute24, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute25, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute26, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute27, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute28); 

        fprintf(ofp, "%d    %d    %d    %d    %d    %d    %d    ", 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute29, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute30, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute31, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute32, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute33, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute34, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute35); 

       fprintf(ofp, "%d    %d    %d    %d    %d    %d    %d    ", 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute36, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute37, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute38, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute39, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute40, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute41, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute42); 

       fprintf(ofp, "%d    %d    %d    %d    %d    %d    %d    ", 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute43, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute44, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute45, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute46, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute47, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute48, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute49); 

       fprintf(ofp, "%d    %d    %d    %d    %d    %d    %d    ", 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute50, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute51, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute52, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute53, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute54, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute55, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute56); 

       fprintf(ofp, "%d    %d    %d    %d    %d    %d    %d    ", 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute57, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute58, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute59, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute60, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute61, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute62, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute63); 

       fprintf(ofp, "%d    %d    %d    %d    %d    %d    %d    ", 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute64, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute65, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute66, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute67, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute68, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute69, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute70); 

       fprintf(ofp, "%d    %d    %d    %d    %d    %d    %d    ", 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute71, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute72, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute73, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute74, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute75, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute76, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute77); 

       fprintf(ofp, "%d    %d    %d    %d    %d    %d    %d    ", 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute78, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute79, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute80, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute81, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute82, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute83, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute84); 

       fprintf(ofp, "%d    %d    %d    %d    %d    %d    %d    ", 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute85, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute86, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute87, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute88, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute89, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute90, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute91); 

       fprintf(ofp, "%d    %d    %d    %d    %d    %d    %d    ", 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute92, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute93, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute94, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute95, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute96, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute97, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute98); 

       fprintf(ofp, "%d    %d    %d    %d    %d    %d    %d    ", 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute99, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute100, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute101, 
                  attribute_rec_out[i].attribute_record_in.subj_attributes.attribute102,   attribute_rec_out[i].attribute_record_in.subj_attributes.attribute103, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute104, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute105); 

        fprintf(ofp, "%d    %d    %d    %d    %d     %d    %d    ", 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute106, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute107, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute108, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute109, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute110, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute111, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute112); 

        fprintf(ofp, "%d    %d    %d    %d    %d     %d    %d    ", 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute113, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute114, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute115, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute116, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute117, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute118, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute119); 

        fprintf(ofp, "%d    %d    %d    %d    %d     %d    %d    ", 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute120, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute121, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute122, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute123, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute124, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute125, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute126); 

        fprintf(ofp, "%d    %d    %d    %d    %d     %d    %d    ", 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute127, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute128, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute129, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute130, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute131, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute132, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute133); 

        fprintf(ofp, "%d    %d    %d    %d    %d     %d    %d xxx ", 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute134, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute135, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute136, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute137, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute138, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute139, 
                    attribute_rec_out[i].attribute_record_in.subj_attributes.attribute140); 

        if (i == LIMIT1 - 1) 
                { 
                fprintf(ofp, "**\n"); 
                } 
        else 
                { 
                fprintf(ofp, "*\n"); 
                } 

        } 

fclose(ifp); 
fclose(ofp); 
fclose(afp); 

//printf("Weights : %d %d \n", heaviest, max_weight); 
//printf("Largest : %d %d \n", biggest, max); 
//printf("Latest  : %d \n", latest); 

//getche(); 

//return actual;     // this is the number of clusters 
//return biggest;    // this is the position of the biggest cluster 
//return latest;     // this is the position of the cluster with the last page in it 
return heaviest;     // this is the position of the heaviest cluster 
} 

// Fuction to determine if a record is nearly central in a cluster. 

int nearly_central(int record_no, char * cluster_name, cluster_record dist_array[], attribute_record_out 
output_records[]) 
{ 
int find_cluster_diameter(char *, cluster_record *, attribute_record_out *); 

int diameter, k; 
float delta; 

diameter = find_cluster_diameter(cluster_name, dist_array, output_records); 
delta = (float)diameter * 0.666; 

for (k=0; k<LIMIT2; ++k)    { 
                    if ((((dist_array[k].input_case_a == record_no) 
                    && (strcmp(output_records[dist_array[k].input_case_a].assigned_cluster_name, 
                              output_records[dist_array[k].input_case_b].assigned_cluster_name) == 0)) 

                    || ((dist_array[k].input_case_b == record_no) 
                    && (strcmp(output_records[dist_array[k].input_case_b].assigned_cluster_name, 
                              output_records[dist_array[k].input_case_a].assigned_cluster_name) == 0))) 

                    && ((float)dist_array[k].distance_a_to_b > delta)) 
                                               return(0); 
                    } 
return(1); 
} 

// Find diameter of the requested cluster. 

int find_cluster_diameter(char * cluster_name, cluster_record dist_array[], attribute_record_out 
output_records[]) 
{ 
int k, max_dist = -1; 

for (k=0; k<LIMIT2; k++) 
                    { 
                    if ((strcmp(output_records[dist_array[k].input_case_a].assigned_cluster_name, 
cluster_name) == 0) 
                    && (strcmp(output_records[dist_array[k].input_case_b].assigned_cluster_name, 
cluster_name) == 0) 
                    && (dist_array[k].distance_a_to_b > max_dist)) 
                                               max_dist = dist_array[k].distance_a_to_b; 
                    } 
return(max_dist); 
} 

// Generate a new name for a cluster. 

void new_name(char *buffer, int *value) 
{ 
strcpy(buffer, "clust"); 
sprintf(buffer+5, "%02d", *value); 
(*value)++; 
} 

// This function searches the attribute database and returns the 
// attribute description for the supplied subj id. 

attribute_data find_subj_attribute_vector(char * search_key, FILE *fp) 
{ 
attribute_file_record afr; 
char att_rec[198];               // change to length of the attribute record 
int pos; 

pos = atoi(search_key+4); 
fseek(fp, (pos * 199), 0);       // change to match length of attribute record + 1 

fscanf(fp, "%s", att_rec); 

att_rec[147] = '\0'; 
afr.subj_attributes.attribute140 = atoi(att_rec+146); 
att_rec[146] = '\0'; 
afr.subj_attributes.attribute139 = atoi(att_rec+145); 
att_rec[145] = '\0'; 
afr.subj_attributes.attribute138 = atoi(att_rec+144); 
att_rec[144] = '\0'; 
afr.subj_attributes.attribute137 = atoi(att_rec+143); 
att_rec[143] = '\0'; 
afr.subj_attributes.attribute136 = atoi(att_rec+142); 
att_rec[142] = '\0'; 
afr.subj_attributes.attribute135 = atoi(att_rec+141); 
att_rec[141] = '\0'; 
afr.subj_attributes.attribute134 = atoi(att_rec+140); 
att_rec[140] = '\0'; 
afr.subj_attributes.attribute133 = atoi(att_rec+139); 
att_rec[139] = '\0'; 
afr.subj_attributes.attribute132 = atoi(att_rec+138); 
att_rec[138] = '\0'; 
afr.subj_attributes.attribute131 = atoi(att_rec+137); 
att_rec[137] = '\0'; 
afr.subj_attributes.attribute130 = atoi(att_rec+136); 
att_rec[136] = '\0'; 
afr.subj_attributes.attribute129 = atoi(att_rec+135); 
att_rec[135] = '\0'; 
afr.subj_attributes.attribute128 = atoi(att_rec+134); 
att_rec[134] = '\0'; 
afr.subj_attributes.attribute127 = atoi(att_rec+133); 
att_rec[133] = '\0'; 
afr.subj_attributes.attribute126 = atoi(att_rec+132); 
att_rec[132] = '\0'; 
afr.subj_attributes.attribute125 = atoi(att_rec+131); 
att_rec[131] = '\0'; 
afr.subj_attributes.attribute124 = atoi(att_rec+130); att_rec[130] = '\0'; 
afr.subj_attributes.attribute123 = atoi(att_rec+129); 
att_rec[129] = '\0'; 
afr.subj_attributes.attribute122 = atoi(att_rec+128); 
att_rec[128] = '\0'; 
afr.subj_attributes.attribute121 = atoi(att_rec+127); 
att_rec[127] = '\0'; 
afr.subj_attributes.attribute120 = atoi(att_rec+126); 
att_rec[126] = '\0'; 
afr.subj_attributes.attribute119 = atoi(att_rec+125); 
att_rec[125] = '\0'; 
afr.subj_attributes.attribute118 = atoi(att_rec+124); 
att_rec[124] = '\0'; 
afr.subj_attributes.attribute117 = atoi(att_rec+123); 
att_rec[123] = '\0'; 
afr.subj_attributes.attribute116 = atoi(att_rec+122); 
att_rec[122] = '\0'; 
afr.subj_attributes.attribute115 = atoi(att_rec+121); 
att_rec[121] = '\0'; 
afr.subj_attributes.attribute114 = atoi(att_rec+120); 
att_rec[120] = '\0'; 
afr.subj_attributes.attribute113 = atoi(att_rec+119); 
att_rec[119] = '\0'; 
afr.subj_attributes.attribute112 = atoi(att_rec+118); 
att_rec[118] = '\0'; 
afr.subj_attributes.attribute111 = atoi(att_rec+117); 
att_rec[117] = '\0'; 
afr.subj_attributes.attribute110 = atoi(att_rec+116); 
att_rec[116] = '\0'; 
afr.subj_attributes.attribute109 = atoi(att_rec+115); 
att_rec[115] = '\0'; 
afr.subj_attributes.attribute108 = atoi(att_rec+114); 
att_rec[114] = '\0'; 
afr.subj_attributes.attribute107 = atoi(att_rec+113); 
att_rec[113] = '\0'; 
afr.subj_attributes.attribute106 = atoi(att_rec+112); 
att_rec[112] = '\0'; 
afr.subj_attributes.attribute105 = atoi(att_rec+111); 
att_rec[111] = '\0'; 
afr.subj_attributes.attribute104 = atoi(att_rec+110); 
att_rec[110] = '\0'; 
afr.subj_attributes.attribute103 = atoi(att_rec+109); 
att_rec[109] = '\0'; 
afr.subj_attributes.attribute102 = atoi(att_rec+108); 
att_rec[108] = '\0'; 
afr.subj_attributes.attribute101 = atoi(att_rec+107); 
att_rec[107] = '\0'; 
afr.subj_attributes.attribute100 = atoi(att_rec+106); 
att_rec[106] = '\0'; 
afr.subj_attributes.attribute99 = atoi(att_rec+105); 
att_rec[105] = '\0'; 
afr.subj_attributes.attribute98 = atoi(att_rec+104); 
att_rec[104] = '\0'; 
afr.subj_attributes.attribute97 = atoi(att_rec+103); 
att_rec[103] = '\0'; 
afr.subj_attributes.attribute96 = atoi(att_rec+102); 
att_rec[102] = '\0'; 
afr.subj_attributes.attribute95 = atoi(att_rec+101); 
att_rec[101] = '\0'; 
afr.subj_attributes.attribute94 = atoi(att_rec+100); 
att_rec[100] = '\0'; 
afr.subj_attributes.attribute93 = atoi(att_rec+99); 
att_rec[99] = '\0'; 
afr.subj_attributes.attribute92 = atoi(att_rec+98); 
att_rec[98] = '\0'; 
afr.subj_attributes.attribute91 = atoi(att_rec+97); 
att_rec[97] = '\0'; 
afr.subj_attributes.attribute90 = atoi(att_rec+96); 
att_rec[96] = '\0'; 
afr.subj_attributes.attribute89 = atoi(att_rec+95); 
att_rec[95] = '\0'; 
afr.subj_attributes.attribute88 = atoi(att_rec+94); 
att_rec[94] = '\0'; 
afr.subj_attributes.attribute87 = atoi(att_rec+93); 
att_rec[93] = '\0'; 
afr.subj_attributes.attribute86 = atoi(att_rec+92); 
att_rec[92] = '\0'; 
afr.subj_attributes.attribute85 = atoi(att_rec+91); 
att_rec[91] = '\0'; 
afr.subj_attributes.attribute84 = atoi(att_rec+90); 
att_rec[90] = '\0'; 
afr.subj_attributes.attribute83 = atoi(att_rec+89); 
att_rec[89] = '\0'; 
afr.subj_attributes.attribute82 = atoi(att_rec+88); 
att_rec[88] = '\0'; 
afr.subj_attributes.attribute81 = atoi(att_rec+87); 
att_rec[87] = '\0'; 
afr.subj_attributes.attribute80 = atoi(att_rec+86); 
att_rec[86] = '\0'; 
afr.subj_attributes.attribute79 = atoi(att_rec+85); 
att_rec[85] = '\0'; afr.subj_attributes.attribute78 = atoi(att_rec+84); 
att_rec[84] = '\0'; 
afr.subj_attributes.attribute77 = atoi(att_rec+83); 
att_rec[83] = '\0'; 
afr.subj_attributes.attribute76 = atoi(att_rec+82); 
att_rec[82] = '\0'; 
afr.subj_attributes.attribute75 = atoi(att_rec+81); 
att_rec[81] = '\0'; 
afr.subj_attributes.attribute74 = atoi(att_rec+80); 
att_rec[80] = '\0'; 
afr.subj_attributes.attribute73 = atoi(att_rec+79); 
att_rec[79] = '\0'; 
afr.subj_attributes.attribute72 = atoi(att_rec+78); 
att_rec[78] = '\0'; 
afr.subj_attributes.attribute71 = atoi(att_rec+77); 
att_rec[77] = '\0'; 
afr.subj_attributes.attribute70 = atoi(att_rec+76); 
att_rec[76] = '\0'; 
afr.subj_attributes.attribute69 = atoi(att_rec+75); 
att_rec[75] = '\0'; 
afr.subj_attributes.attribute68 = atoi(att_rec+74); 
att_rec[74] = '\0'; 
afr.subj_attributes.attribute67 = atoi(att_rec+73); 
att_rec[73] = '\0'; 
afr.subj_attributes.attribute66 = atoi(att_rec+72); 
att_rec[72] = '\0'; 
afr.subj_attributes.attribute65 = atoi(att_rec+71); 
att_rec[71] = '\0'; 
afr.subj_attributes.attribute64 = atoi(att_rec+70); 
att_rec[70] = '\0'; 
afr.subj_attributes.attribute63 = atoi(att_rec+69); 
att_rec[69] = '\0'; 
afr.subj_attributes.attribute62 = atoi(att_rec+68); 
att_rec[68] = '\0'; 
afr.subj_attributes.attribute61 = atoi(att_rec+67); 
att_rec[67] = '\0'; 
afr.subj_attributes.attribute60 = atoi(att_rec+66); 
att_rec[66] = '\0'; 
afr.subj_attributes.attribute59 = atoi(att_rec+65); 
att_rec[65] = '\0'; 
afr.subj_attributes.attribute58 = atoi(att_rec+64); 
att_rec[64] = '\0'; 
afr.subj_attributes.attribute57 = atoi(att_rec+63); 
att_rec[63] = '\0'; 
afr.subj_attributes.attribute56 = atoi(att_rec+62); 
att_rec[62] = '\0'; 
afr.subj_attributes.attribute55 = atoi(att_rec+61); 
att_rec[61] = '\0'; 
afr.subj_attributes.attribute54 = atoi(att_rec+60); 
att_rec[60] = '\0'; 
afr.subj_attributes.attribute53 = atoi(att_rec+59); 
att_rec[59] = '\0'; 
afr.subj_attributes.attribute52 = atoi(att_rec+58); 
att_rec[58] = '\0'; 
afr.subj_attributes.attribute51 = atoi(att_rec+57); 
att_rec[57] = '\0'; 
afr.subj_attributes.attribute50 = atoi(att_rec+56); 
att_rec[56] = '\0'; 
afr.subj_attributes.attribute49 = atoi(att_rec+55); 
att_rec[55] = '\0'; 
afr.subj_attributes.attribute48 = atoi(att_rec+54); 
att_rec[54] = '\0'; 
afr.subj_attributes.attribute47 = atoi(att_rec+53); 
att_rec[53] = '\0'; 
afr.subj_attributes.attribute46 = atoi(att_rec+52); 
att_rec[52] = '\0'; 
afr.subj_attributes.attribute45 = atoi(att_rec+51); 
att_rec[51] = '\0'; 
afr.subj_attributes.attribute44 = atoi(att_rec+50); 
att_rec[50] = '\0'; 
afr.subj_attributes.attribute43 = atoi(att_rec+49); 
att_rec[49] = '\0'; 
afr.subj_attributes.attribute42 = atoi(att_rec+48); 
att_rec[48] = '\0'; 
afr.subj_attributes.attribute41 = atoi(att_rec+47); 
att_rec[47] = '\0'; 
afr.subj_attributes.attribute40 = atoi(att_rec+46); 
att_rec[46] = '\0'; 
afr.subj_attributes.attribute39 = atoi(att_rec+45); 
att_rec[45] = '\0'; 
afr.subj_attributes.attribute38 = atoi(att_rec+44); 
att_rec[44] = '\0'; 
afr.subj_attributes.attribute37 = atoi(att_rec+43); 
att_rec[43] = '\0'; 
afr.subj_attributes.attribute36 = atoi(att_rec+42); 
att_rec[42] = '\0'; 
afr.subj_attributes.attribute35 = atoi(att_rec+41); 
att_rec[41] = '\0'; 
afr.subj_attributes.attribute34 = atoi(att_rec+40); 
att_rec[40] = '\0'; 
afr.subj_attributes.attribute33 = atoi(att_rec+39); att_rec[39] = '\0'; 
afr.subj_attributes.attribute32 = atoi(att_rec+38); 
att_rec[38] = '\0'; 
afr.subj_attributes.attribute31 = atoi(att_rec+37); 
att_rec[37] = '\0'; 
afr.subj_attributes.attribute30 = atoi(att_rec+36); 
att_rec[36] = '\0'; 
afr.subj_attributes.attribute29 = atoi(att_rec+35); 
att_rec[35] = '\0'; 
afr.subj_attributes.attribute28 = atoi(att_rec+34); 
att_rec[34] = '\0'; 
afr.subj_attributes.attribute27 = atoi(att_rec+33); 
att_rec[33] = '\0'; 
afr.subj_attributes.attribute26 = atoi(att_rec+32); 
att_rec[32] = '\0'; 
afr.subj_attributes.attribute25 = atoi(att_rec+31); 
att_rec[31] = '\0'; 
afr.subj_attributes.attribute24 = atoi(att_rec+30); 
att_rec[30] = '\0'; 
afr.subj_attributes.attribute23 = atoi(att_rec+29); 
att_rec[29] = '\0'; 
afr.subj_attributes.attribute22 = atoi(att_rec+28); 
att_rec[28] = '\0'; 
afr.subj_attributes.attribute21 = atoi(att_rec+27); 
att_rec[27] = '\0'; 
afr.subj_attributes.attribute20 = atoi(att_rec+26); 
att_rec[26] = '\0'; 
afr.subj_attributes.attribute19 = atoi(att_rec+25); 
att_rec[25] = '\0'; 
afr.subj_attributes.attribute18 = atoi(att_rec+24); 
att_rec[24] = '\0'; 
afr.subj_attributes.attribute17 = atoi(att_rec+23); 
att_rec[23] = '\0'; 
afr.subj_attributes.attribute16 = atoi(att_rec+22); 
att_rec[22] = '\0'; 
afr.subj_attributes.attribute15 = atoi(att_rec+21); 
att_rec[21] = '\0'; 
afr.subj_attributes.attribute14 = atoi(att_rec+20); 
att_rec[20] = '\0'; 
afr.subj_attributes.attribute13 = atoi(att_rec+19); 
att_rec[19] = '\0'; 
afr.subj_attributes.attribute12 = atoi(att_rec+18); 
att_rec[18] = '\0'; 
afr.subj_attributes.attribute11 = atoi(att_rec+17); 
att_rec[17] = '\0'; 
afr.subj_attributes.attribute10 = atoi(att_rec+16); 
att_rec[16] = '\0'; 
afr.subj_attributes.attribute09 = atoi(att_rec+15); 
att_rec[15] = '\0'; 
afr.subj_attributes.attribute08 = atoi(att_rec+14); 
att_rec[14] = '\0'; 
afr.subj_attributes.attribute07 = atoi(att_rec+13); 
att_rec[13] = '\0'; 
afr.subj_attributes.attribute06 = atoi(att_rec+12); 
att_rec[12] = '\0'; 
afr.subj_attributes.attribute05 = atoi(att_rec+11); 
att_rec[11] = '\0'; 
afr.subj_attributes.attribute04 = atoi(att_rec+10); 
att_rec[10] = '\0'; 
afr.subj_attributes.attribute03 = atoi(att_rec+9); 
att_rec[9] = '\0'; 
afr.subj_attributes.attribute02 = atoi(att_rec+8); 
att_rec[8] = '\0'; 
afr.subj_attributes.attribute01 = atoi(att_rec+7); 
att_rec[7] = '\0'; 
strcpy(afr.subj_id, att_rec); 

if (strcmp(afr.subj_id, search_key) == 0) 
                    return (afr.subj_attributes); 

printf ("Attribute not found for key!!! %s %d \n", search_key, pos); 

return (afr.subj_attributes); // to prevent compiler warning only 
} 

// This is the cluster QSORT sort function. 

int sort_function_1(cluster_record *first, cluster_record *second) 
{ 
         if (first->distance_a_to_b < second->distance_a_to_b) 
                    return (-1); 
         else if (first->distance_a_to_b > second->distance_a_to_b) 
                    return (+1); 
         else 
                    return (0); 
} 

// This is the output QSORT sort function. 

int sort_function_2(attribute_record_out *first, attribute_record_out *second) 
{  return(strcmp(first->assigned_cluster_name, second->assigned_cluster_name)); 
} 

// This function finds the distance between two attribute records. The 
// pseudo metric employed is the number of differing attribute values. 

int find_distance_1(attribute_data rec01, attribute_data rec02) 
{ 
int distance = 0; 

if (rec01.attribute01 != rec02.attribute01) 
                   ++distance; 

if (rec01.attribute02 != rec02.attribute02) 
                   ++distance; 

if (rec01.attribute03 != rec02.attribute03) 
                   ++distance; 

if (rec01.attribute04 != rec02.attribute04) 
                   ++distance; 

if (rec01.attribute05 != rec02.attribute05) 
                   ++distance; 

if (rec01.attribute06 != rec02.attribute06) 
                   ++distance; 

if (rec01.attribute07 != rec02.attribute07) 
                   ++distance; 

if (rec01.attribute08 != rec02.attribute08) 
                   ++distance; 

if (rec01.attribute09 != rec02.attribute09) 
                   ++distance; 

if (rec01.attribute10 != rec02.attribute10) 
                   ++distance; 

if (rec01.attribute11 != rec02.attribute11) 
                   ++distance; 

if (rec01.attribute12 != rec02.attribute12) 
                   ++distance; 

if (rec01.attribute13 != rec02.attribute13) 
                   ++distance; 

if (rec01.attribute14 != rec02.attribute14) 
                   ++distance; 

if (rec01.attribute15 != rec02.attribute15) 
                   ++distance; 

if (rec01.attribute16 != rec02.attribute16) 
                   ++distance; 

if (rec01.attribute17 != rec02.attribute17) 
                   ++distance; 

if (rec01.attribute18 != rec02.attribute18) 
                   ++distance; 

if (rec01.attribute19 != rec02.attribute19) 
                   ++distance; 

if (rec01.attribute20 != rec02.attribute20) 
                   ++distance; 

if (rec01.attribute21 != rec02.attribute21) 
                   ++distance; 

if (rec01.attribute22 != rec02.attribute22) 
                   ++distance; 

if (rec01.attribute23 != rec02.attribute23) 
                   ++distance; 

if (rec01.attribute24 != rec02.attribute24) 
                   ++distance; 

if (rec01.attribute25 != rec02.attribute25) 
                   ++distance; 

if (rec01.attribute26 != rec02.attribute26) 
                   ++distance; 

if (rec01.attribute27 != rec02.attribute27) 
                   ++distance; if (rec01.attribute28 != rec02.attribute28) 
                            ++distance; 

if (rec01.attribute29 != rec02.attribute29) 
                            ++distance; 

if (rec01.attribute30 != rec02.attribute30) 
                            ++distance; 

if (rec01.attribute31 != rec02.attribute31) 
                            ++distance; 

if (rec01.attribute32 != rec02.attribute32) 
                            ++distance; 

if (rec01.attribute33 != rec02.attribute33) 
                            ++distance; 

if (rec01.attribute34 != rec02.attribute34) 
                            ++distance; 

if (rec01.attribute35 != rec02.attribute35) 
                            ++distance; 

if (rec01.attribute36 != rec02.attribute36) 
                            ++distance; 

if (rec01.attribute37 != rec02.attribute37) 
                            ++distance; 

if (rec01.attribute38 != rec02.attribute38) 
                            ++distance; 

if (rec01.attribute39 != rec02.attribute39) 
                            ++distance; 

if (rec01.attribute40 != rec02.attribute40) 
                            ++distance; 

if (rec01.attribute41 != rec02.attribute41) 
                            ++distance; 

if (rec01.attribute42 != rec02.attribute42) 
                            ++distance; 

if (rec01.attribute43 != rec02.attribute43) 
                            ++distance; 

if (rec01.attribute44 != rec02.attribute44) 
                            ++distance; 

if (rec01.attribute45 != rec02.attribute45) 
                            ++distance; 

if (rec01.attribute46 != rec02.attribute46) 
                            ++distance; 

if (rec01.attribute47 != rec02.attribute47) 
                            ++distance; 

if (rec01.attribute48 != rec02.attribute48) 
                            ++distance; 

if (rec01.attribute49 != rec02.attribute49) 
                            ++distance; 

if (rec01.attribute50 != rec02.attribute50) 
                            ++distance; 

if (rec01.attribute51 != rec02.attribute51) 
                            ++distance; 

if (rec01.attribute52 != rec02.attribute52) 
                            ++distance; 

if (rec01.attribute53 != rec02.attribute53) 
                            ++distance; 

if (rec01.attribute54 != rec02.attribute54) 
                            ++distance; 

if (rec01.attribute55 != rec02.attribute55) 
                            ++distance; 

if (rec01.attribute56 != rec02.attribute56) 
                            ++distance; 

if (rec01.attribute57 != rec02.attribute57) 
                            ++distance; 

if (rec01.attribute58 != rec02.attribute58)                
                            ++distance; 

if (rec01.attribute59 != rec02.attribute59) 
                            ++distance; 

if (rec01.attribute60 != rec02.attribute60) 
                            ++distance; 

if (rec01.attribute61 != rec02.attribute61) 
                            ++distance; 

if (rec01.attribute62 != rec02.attribute62) 
                            ++distance; 

if (rec01.attribute63 != rec02.attribute63) 
                            ++distance; 

if (rec01.attribute64 != rec02.attribute64) 
                            ++distance; 

if (rec01.attribute65 != rec02.attribute65) 
                            ++distance; 

if (rec01.attribute66 != rec02.attribute66) 
                            ++distance; 

if (rec01.attribute67 != rec02.attribute67) 
                            ++distance; 

if (rec01.attribute68 != rec02.attribute68) 
                            ++distance; 

if (rec01.attribute69 != rec02.attribute69) 
                            ++distance; 

if (rec01.attribute70 != rec02.attribute70) 
                            ++distance; 

if (rec01.attribute71 != rec02.attribute71) 
                            ++distance; 

if (rec01.attribute72 != rec02.attribute72) 
                            ++distance; 

if (rec01.attribute73 != rec02.attribute73) 
                            ++distance; 

if (rec01.attribute74 != rec02.attribute74) 
                            ++distance; 

if (rec01.attribute75 != rec02.attribute75) 
                            ++distance; 

if (rec01.attribute76 != rec02.attribute76) 
                            ++distance; 

if (rec01.attribute77 != rec02.attribute77) 
                            ++distance; 

if (rec01.attribute78 != rec02.attribute78) 
                            ++distance; 

if (rec01.attribute79 != rec02.attribute79) 
                            ++distance; 

if (rec01.attribute80 != rec02.attribute80) 
                            ++distance; 

if (rec01.attribute81 != rec02.attribute81) 
                            ++distance; 

if (rec01.attribute82 != rec02.attribute82) 
                            ++distance; 

if (rec01.attribute83 != rec02.attribute83) 
                            ++distance; 

if (rec01.attribute84 != rec02.attribute84) 
                            ++distance; 

if (rec01.attribute85 != rec02.attribute85) 
                            ++distance; 

if (rec01.attribute86 != rec02.attribute86) 
                            ++distance; 

if (rec01.attribute87 != rec02.attribute87) 
                            ++distance; 

if (rec01.attribute88 != rec02.attribute88) 
                            ++distance; 
if (rec01.attribute89 != rec02.attribute89) 
                            ++distance; 

if (rec01.attribute90 != rec02.attribute90) 
                            ++distance; 

if (rec01.attribute91 != rec02.attribute91) 
                            ++distance; 

if (rec01.attribute92 != rec02.attribute92) 
                            ++distance; 

if (rec01.attribute93 != rec02.attribute93) 
                            ++distance; 

if (rec01.attribute94 != rec02.attribute94) 
                            ++distance; 

if (rec01.attribute95 != rec02.attribute95) 
                            ++distance; 

if (rec01.attribute96 != rec02.attribute96) 
                            ++distance; 

if (rec01.attribute97 != rec02.attribute97) 
                            ++distance; 

if (rec01.attribute98 != rec02.attribute98) 
                            ++distance; 

if (rec01.attribute99 != rec02.attribute99) 
                            ++distance; 

if (rec01.attribute100 != rec02.attribute100) 
                            ++distance; 

if (rec01.attribute101 != rec02.attribute101) 
                            ++distance; 

if (rec01.attribute102 != rec02.attribute102) 
                            ++distance; 

if (rec01.attribute103 != rec02.attribute103) 
                            ++distance; 

if (rec01.attribute104 != rec02.attribute104) 
                            ++distance; 

if (rec01.attribute105 != rec02.attribute105) 
                            ++distance; 

if (rec01.attribute106 != rec02.attribute106) 
                            ++distance; 

if (rec01.attribute107 != rec02.attribute107) 
                            ++distance; 

if (rec01.attribute108 != rec02.attribute108) 
                            ++distance; 

if (rec01.attribute109 != rec02.attribute109) 
                            ++distance; 

if (rec01.attribute110 != rec02.attribute110) 
                            ++distance; 

if (rec01.attribute111 != rec02.attribute111) 
                            ++distance; 

if (rec01.attribute112 != rec02.attribute112) 
                            ++distance; 

if (rec01.attribute113 != rec02.attribute113) 
                            ++distance; 

if (rec01.attribute114 != rec02.attribute114) 
                            ++distance; 

if (rec01.attribute115 != rec02.attribute115) 
                            ++distance; 

if (rec01.attribute116 != rec02.attribute116) 
                            ++distance; 

if (rec01.attribute117 != rec02.attribute117) 
                            ++distance; 

if (rec01.attribute118 != rec02.attribute118) 
                            ++distance; 
if (rec01.attribute119 != rec02.attribute119) 
                            ++distance; 

if (rec01.attribute120 != rec02.attribute120) 
                            ++distance; 

if (rec01.attribute121 != rec02.attribute121) 
                            ++distance; 

if (rec01.attribute122 != rec02.attribute122) 
                            ++distance; 

if (rec01.attribute123 != rec02.attribute123) 
                            ++distance; 

if (rec01.attribute124 != rec02.attribute124) 
                            ++distance; 

if (rec01.attribute125 != rec02.attribute125) 
                            ++distance; 

if (rec01.attribute126 != rec02.attribute126) 
                            ++distance; 

if (rec01.attribute127 != rec02.attribute127) 
                            ++distance; 

if (rec01.attribute128 != rec02.attribute128) 
                            ++distance; 

if (rec01.attribute129 != rec02.attribute129) 
                            ++distance; 

if (rec01.attribute130 != rec02.attribute130) 
                            ++distance; 

if (rec01.attribute131 != rec02.attribute131) 
                            ++distance; 

if (rec01.attribute132 != rec02.attribute132) 
                            ++distance; 

if (rec01.attribute133 != rec02.attribute133) 
                            ++distance; 

if (rec01.attribute134 != rec02.attribute134) 
                            ++distance; 

if (rec01.attribute135 != rec02.attribute135) 
                            ++distance; 

if (rec01.attribute136 != rec02.attribute136) 
                            ++distance; 

if (rec01.attribute137 != rec02.attribute137) 
                            ++distance; 

if (rec01.attribute138 != rec02.attribute138) 
                            ++distance; 

if (rec01.attribute139 != rec02.attribute139) 
                            ++distance; 

if (rec01.attribute140 != rec02.attribute140) 
                            ++distance; 

return distance; 
}
























////Id??3
#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <string.h>

using namespace  std;


typedef struct tnode
{
 char tdata[100];

}tnode;

typedef struct Tree_Node
{
 char name[100];
 bool isLeaf; //????????

 vector<tnode> att_list;//??????

 vector<Tree_Node * > child_list;


}Tree_Node,* pTreeNpde;

typedef struct dnode
{
 vector<tnode>row;
}dnode;

typedef struct D_Node
{
 vector<dnode>DB;
 vector<tnode> attr_name;
 tnode class_name;
 
}D_Node;

D_Node G_DB;
pTreeNpde Root = NULL;

 


typedef struct FreeQNode
{
 char name[100];
 int count;
 vector<int> Set_ID;
}FreeQNode;

typedef struct FreeQNodeDouble
{
 char name[100];
 int count;
 vector<int> row_id;

 vector<FreeQNode> classes;//????????????????
}FreeQNodeDouble;

typedef struct attr_node
{
 int attr_id;
 vector<tnode> attr_name;
 vector<int> count_list;
 
}attr_node;

vector<attr_node> G_Attr_List;


typedef struct binNode
{
 char name[100];
 int count;
 vector<int> Set_ID;

 struct binNode * lchild;
 struct binNode * rchild;
}binNode;

typedef struct binNodeDouble
{
 char name[100];
 int count;
 vector<int> row_id;
 struct binNodeDouble * lchild;
 struct binNodeDouble * rchild;

 vector<FreeQNode>  classes;

}binNodeDouble;

 

 

void insert_tree(binNode  * & r, char str[100])
{

 if (NULL == r)
 {
 
  binNode * node = new binNode;
  strcpy(node->name,str);
  node->count = 1;
  //printf("[%s,%d]/n",node->name,node->count);
  node->lchild = node->rchild = NULL;
  r = node;
 }
 else
 {
  if (strcmp(r->name,str) == 0)
  {
   r->count ++;
  }
  else if (strcmp(r->name,str) < 0)
  {
   insert_tree(r->lchild,str);
  }
  else
  {
   insert_tree(r->rchild,str);
  }
 }

}

void delete_bin_tree(binNode *& r)
{
 if (r != NULL)
 {
  delete_bin_tree(r->lchild);
  delete_bin_tree(r->rchild);
  delete(r);
  r = NULL;
 }
}


void Bin_tree_inorder(binNode * r,vector<FreeQNode> & Fq)
{
 if (r != NULL)
 {
  Bin_tree_inorder(r->lchild,Fq);

  FreeQNode ft;
  //printf("%s,%d/n",r->name,r->count);
  strcpy(ft.name,r->name);
  ft.count = r->count;
  for (int i= 0;i < r->Set_ID.size();i++)
  {
   ft.Set_ID.push_back(r->Set_ID[i]); //???????ID?
  }

  Fq.push_back(ft); //?????????????????

  Bin_tree_inorder(r->rchild,Fq);

 }
}


void Get_attr(binNode * r,attr_node & attr)
{
 if (r != NULL)
 {
  Get_attr(r->lchild,attr);

  tnode t;
  strcpy(t.tdata,r->name);

   
  //printf("%s,%d/n",r->name,r->count);
  attr.attr_name.push_back(t);
  attr.count_list.push_back(r->count);//??????
  
  Get_attr(r->rchild,attr);
  
 }
}


void insert_tree_double(binNodeDouble *& r, int DB_ID,char attr_name[100],char class_name[100])
{
 
 if (NULL == r)
 {
  binNodeDouble * node = new binNodeDouble;
  strcpy(node->name,attr_name);
  node->count = 1; 
  node->row_id.push_back(DB_ID);

  node->lchild = node->rchild = NULL;  


  FreeQNode fq;
  strcpy(fq.name,class_name);
  fq.count = 1;
  fq.Set_ID.push_back(DB_ID); //????????ID?
  node->classes.push_back(fq);
  r= node;
 }
 else
 {
  if (strcmp(r->name,attr_name) == 0)
  {
   r->count ++;
   r->row_id.push_back(DB_ID);//??????????ID?

   bool found = false;

   for (int i = 0; i< r->classes.size();i++)
   {
    if (strcmp(r->classes[i].name,class_name) == 0)
    {
     r->classes[i].count ++;
     r->classes[i].Set_ID.push_back(DB_ID);//???????ID?

     found = true; //?????????????1,
     break;        //?????
    }    

   }
   if (!found)
   {
    FreeQNode fq;
    strcpy(fq.name,class_name);
    fq.count = 1;
    fq.Set_ID.push_back(DB_ID);//????????ID?
    r->classes.push_back(fq);
   }
  }
  else if (strcmp(r->name,attr_name) < 0)
  {
   insert_tree_double(r->lchild,DB_ID,attr_name,class_name);
  }
  else
  {
   insert_tree_double(r->rchild,DB_ID,attr_name,class_name);
  }
 }
 
}

void delete_bin_tree_double(binNodeDouble *& r)
{
 if (r != NULL)
 {
  delete_bin_tree_double(r->lchild);
  delete_bin_tree_double(r->rchild);
  delete(r);
  r = NULL;
 }
}

void Bin_tree_inorder_double(binNodeDouble *& r,vector<FreeQNodeDouble> &Fq)
{
 if (r != NULL)
 {
  Bin_tree_inorder_double(r->lchild,Fq);
  
  FreeQNodeDouble ft;
  strcpy(ft.name,r->name); //????????
  ft.count = r->count;

  for (int k = 0;k< r->row_id.size();k++)
  {
   ft.row_id.push_back(r->row_id[k]);
  }

  //printf("doubleTree. %s,%d/n",r->name,r->count);

  for (int i = 0;i< r->classes.size();i++)
  {
   FreeQNode fq;   
   strcpy(fq.name,r->classes[i].name);
   fq.count = r->classes[i].count;
   for (int j = 0;j < r->classes[i].Set_ID.size();j++)
   {
    fq.Set_ID.push_back( r->classes[i].Set_ID[j]); //???????ID?
   }
   ft.classes.push_back(fq);
   
  

  }

  Fq.push_back(ft);
  ft.classes.erase(ft.classes.begin(),ft.classes.end());//????????

  Bin_tree_inorder_double(r->rchild,Fq);
  
 }
}

 

void getFqI(vector<int> S,int class_id,vector<FreeQNode> & Fq)
{
 binNode * root = NULL;

 for (int i = 0;i< S.size();i++)
 {
  insert_tree(root,G_DB.DB[S[i]].row[class_id].tdata);
 }

 Bin_tree_inorder(root,Fq);

 delete_bin_tree(root);

}

void getFqIA(vector<int> S,int attr_id,int class_id,vector<FreeQNodeDouble> & Fq)
{
 binNodeDouble * root = NULL;
 
 for (int i = 0;i< S.size();i++)
 {
  insert_tree_double(root,S[i],G_DB.DB[S[i]].row[attr_id].tdata,G_DB.DB[S[i]].row[class_id].tdata);
 }
 
 Bin_tree_inorder_double(root,Fq);
 
 delete_bin_tree_double(root);
 
}
void readdata(char *filename)
{
 char str[1000];
 FILE * fp;
 fp = fopen(filename,"r");
 fgets(str,1000,fp);
 int len = strlen(str);
 int attr_no = 0; //????
 int row_num = 0;
 if (str != NULL)
 {
  row_num = 1;
 }

 for (int i = 0;i< len;i++)
 {
  if (str[i] == '/t')
  {
   attr_no ++;
  }
 }
 attr_no ++;//?????????????+1

 printf("%d/n",attr_no);
 while(fgets(str,1000,fp) != NULL)
 {
  row_num ++; //????
 }
 fclose(fp);
 fopen(filename,"r");
 tnode t;
 for (i = 0;i<attr_no;i++)
 {
  fscanf(fp,"%s",t.tdata);
  G_DB.attr_name.push_back(t);
  printf("%s/n",t.tdata);
 }
 strcpy(G_DB.class_name.tdata,G_DB.attr_name[attr_no-1].tdata);
 for (int j = 1;j< row_num;j++)
 {
  dnode dt;
  tnode temp;

  for (int i = 0;i<attr_no;i++)
  {
   fscanf(fp,"%s",temp.tdata);
   dt.row.push_back(temp);
  }
  G_DB.DB.push_back(dt);
  dt.row.erase(dt.row.begin(),dt.row.end());
 }

 printf("%d/n",G_DB.DB.size());
 for (i = 0;i< G_DB.DB.size();i++)
 {
  for (int j = 0;j< G_DB.DB[i].row.size();j++)
  {
   printf("%s/t",G_DB.DB[i].row[j].tdata);
  }
  printf("/n");
 }
}

double Fnc_I(vector<int> S,int class_id)
{
 //????????????class_id????????????????I
// printf("called Fnc_I(%d)/n ",class_id);

 vector<FreeQNode> Fq;

 getFqI(S,class_id,Fq); //??getFqI????Class_id??????????,?Fq???????????S???????
                         //?????????????????????


  //  printf("begin to compute I /n");
 double total = 0;
 for (int i = 0;i< Fq.size();i++)
 {
  total += Fq[i].count;
 // printf("%s,%d/n",Fq[i].name,Fq[i].count);
 }

 double result = 0;


 if (0 == total)
 {
  return 0;
 }

 for (i = 0;i< Fq.size();i++)
 {
  double p = Fq[i].count/total;
  result += -1*(p * log(p)/log(2));
 }

   // printf("FNC_I return/n/n");

 return result;


}

double Fnc_IA(vector<int> S,int attr_id,int class_id,vector<FreeQNodeDouble> & Fq)
{
 //????????????class_id????????????????I
 
 
 
 getFqIA(S,attr_id,class_id,Fq);
 
 double total = 0;
 for (int i = 0;i< Fq.size();i++)
 {
  total += Fq[i].count;
 }
 
 double result = 0;
 
 
 if (0 == total)
 {
  return 0;
 }
 bool pr= false;
 for (i = 0;i< Fq.size();i++)
 {
  double stotal = Fq[i].count;
  double sresult = 0;
 if (pr) printf("[%s,%d]/n",Fq[i].name,Fq[i].count);
  for (int j = 0;j < Fq[i].classes.size();j++)
  {
  if (pr) printf("%s,%d/n",Fq[i].classes[j].name,Fq[i].classes[j].count);
   for (int k = 0;k < Fq[i].classes[j].count;k++)
   {
   // printf("%d/t",Fq[i].classes[j].Set_ID[k]+1);
   }
      //printf("/n");
   double sp = Fq[i].classes[j].count/stotal; //???????
   sresult += -1*(sp*log(sp)/log(2));
  }
  
  result += (stotal/total) * sresult;
 }
  if (pr) printf("/n");
 
 return result;
 
 
}

int  SelectBestAttribute(vector<int> Samples,vector<int> attribute_list,int class_id)
{
 //???????Samples???????attribute_list
 //??????class_id
 //??best_attribute

 double fi = Fnc_I(Samples,5);
// printf("%lf/n",fi); 

 double IA = 999999999;
 int best_attrib = -1;

 


 for (int i = 0;i < attribute_list.size();i++)
 {
  vector<FreeQNodeDouble> fqd;
     double tfa = Fnc_IA(Samples,attribute_list[i],class_id,fqd);
 // printf("%d, FIA = %lf/n",i,tfa);

      if (IA > tfa)
      {
    IA = tfa;
    best_attrib = i;
      }
 }
 //printf("%lf/n",IA);

 printf("gain(%d) = %lf - %lf = %lf/n",best_attrib,fi,IA,fi - IA);

 return attribute_list[best_attrib];  
}

void fnc_getattr(vector<int> Samples,int att_id,attr_node &at)
{
 binNode * root = NULL;
 
 for (int i = 0;i< Samples.size();i++)
 {
  insert_tree(root,G_DB.DB[Samples[i]].row[att_id].tdata);
 }
 
 Get_attr(root,at);
 
 delete_bin_tree(root);

 

}

void get_class_num_and_name(vector<int> Samples,int class_id,int & class_num,tnode & class_name)
{

 attr_node at;

 binNode * root = NULL;
 
 for (int i = 0;i< Samples.size();i++)
 {
  insert_tree(root,G_DB.DB[Samples[i]].row[class_id].tdata);
 }
 
 Get_attr(root,at); 
 delete_bin_tree(root);

 //printf("att_size = %d/n",at.attr_name.size());

 class_num = at.attr_name.size();

 int num = 0;
 int id = 0;
 if (1 == class_num)
 {
  strcpy(class_name.tdata,at.attr_name[0].tdata);
 }
 else
 {
  
  for (int j = 0;j < at.attr_name.size();j++ )
  {
   if (at.count_list[j] > num)
   {
    num = at.count_list[j];
    id = j;
   }
  }
 }

 strcpy(class_name.tdata,at.attr_name[id].tdata);//????????

 

 

 

}

void getAllTheAttribute(vector<int> Samples,vector<int> attribute_list,int class_id)
{
 printf("all the attribute are:/n");
 
 for (int i = 0;i < attribute_list.size();i++)
 {
 
  attr_node at;
  at.attr_id = attribute_list[i];
  fnc_getattr(Samples,attribute_list[i],at); 

  G_Attr_List.push_back(at);
  
 }
 for (i = 0;i <G_Attr_List.size();i++)
 {
  printf("%d/n",G_Attr_List[i].attr_id);
  for (int j = 0;j< G_Attr_List[i].attr_name.size();j++)
  {
   printf("%s/t",G_Attr_List[i].attr_name[j].tdata);
  }
  printf("/n");
 }

}


void Generate_decision_tree(Tree_Node * & root,vector<int> Samples, vector<int> attribute_list,int class_id)
{
 /*???Generate_decision_tree(samples, attribute)?????????????????
  ???????samples?????????????????attribute_list?
  ?????????
???

  (1) ???? N?
  (2) if samples ??????C then   //?????????C??????????
  (3) return N ????????C ???
  (4) if attribut_list ?? then       
  (5) return N ????????? samples ??????? //?????????????
  (6) ??attribute_list ????????????best_attribute?//?????????
  (7) ???? N ?best_attribute?
  (8) for each best_attribute ?????a i //???samples??best_attribute????
  (9) ??? N ??????? best_attribute = a i ????
  (10) ?si ?samples ?best_attribute = a i ???????//a partition
  (11) if si ?? then
  (12) ?????????? samples ???????//???????????????????????
  (13) else ????? Generate_decision_tree(si,attribute_list - best_attribute)??????//?????si,??????????????best_attribute

*/
 printf("begin to call Generate_decision_tree./n");
 printf("the samples are:/n");
 for (int ts = 0;ts < Samples.size();ts++)
 {
  printf("%d/t",Samples[ts]);
 }
 printf("/nend/n");

 int class_num = 0;
 tnode class_name;
 get_class_num_and_name(Samples,class_id,class_num,class_name); //?????????
 //????????class_num =1?class_name????
 //???class_num >1 ,class_name?? ??????

 //printf("class_num = %d/n",class_num);


  root = new Tree_Node;//(1) ???? N?

  root->isLeaf = false; //????????False??????? 2011.01.13 17:08
 
 if (1 == class_num)
 {
  printf("samples ???????%s? ,??/n",class_name.tdata);
  //(2) if samples ??????C then   //?????????C??????????
  //(3) return N ????????C ???
  strcpy(root->name,class_name.tdata);
  root->isLeaf = true;
  
  return;
 }
 
 if (attribute_list.size() == 0)
 {
  printf("attribute_list.size() == 0/n");
  //(4) if attribut_list ?? then       
  //(5) return N ????????? samples ??????? //?????????????
  //???????????????
  strcpy(root->name,class_name.tdata);
  root->isLeaf = true;
 
  return;
  
 }


 //???????

 int best_arrtib = SelectBestAttribute(Samples,attribute_list,class_id);
 
 printf("the best attrib_id is %d,attribute_name is [%s]/n",best_arrtib,G_DB.attr_name[best_arrtib].tdata);
    
 vector<FreeQNodeDouble> Fq;
 double tfa = Fnc_IA(Samples,best_arrtib,class_id,Fq);

 

 vector<int> att_list;
 for (int tt = 0;tt<attribute_list.size();tt++ )
 {
  if (attribute_list[tt] != best_arrtib)
  {
   att_list.push_back(attribute_list[tt]);
  }
 }

 


///////////////////////////???????????///////////////////////////////////////////////
 int id = 0;
 int num = Fq[id].count;
 
 for (int i = 1;i < Fq.size();i++)
 {
  if (num < Fq[i].count)
  {
   id = i;
   num = Fq[i].count;
  }
 } 
 printf("??????:%s/n",Fq[id].name);
///////////////////////////???????????///////////////////////////////////////////////
 
 

 printf("??????Sample??%d,%s????/n",best_arrtib,G_DB.attr_name[best_arrtib].tdata);


 strcpy(root->name,G_DB.attr_name[best_arrtib].tdata); //???????????
 //(6) ??attribute_list ????????????best_attribute?//?????????
 //(7) ???? N ?best_attribute?
 printf("????%d???/n",Fq.size());

 

 for (int k = 0;k < G_Attr_List[best_arrtib].attr_name.size();k++)
 {

  root->att_list.push_back(G_Attr_List[best_arrtib].attr_name[k]);//????????

  // (8) for each best_attribute ?????a i //???samples??best_attribute????
  printf("/n?????[%d]???/n",k);
  //printf("[%d],name = %s/n",k,G_Attr_List[best_arrtib-1].attr_name[k].tdata); ?????????????best_arrtib
  printf("[%d],??? = %s/n",k,G_Attr_List[best_arrtib].attr_name[k].tdata);
  bool found = false;

  for (int n = 0;n < Fq.size();n++)
  {
   if (strcmp(G_Attr_List[best_arrtib].attr_name[k].tdata,Fq[n].name) == 0)
   {
    //(13) else ????? Generate_decision_tree(si,attribute_list - best_attribute)
    //??????//?????si,??????????????best_attribute
    pTreeNpde trnode = new Tree_Node;//(1) ???? N?
    Generate_decision_tree(trnode,Fq[k].row_id,att_list,class_id);

    root->child_list.push_back(trnode);
    found = true;
    break;

   }
  }

  if (!found)
  {
   // (9) ??? N ??????? best_attribute = a i ????
   //(10) ?si ?samples ?best_attribute = a i ???????//a partition
   //(11) if si ?? then
   //  (12) ?????????? samples ???????//???????????????????????

    pTreeNpde trnode = new Tree_Node;//(1) ???? N?
    strcpy(trnode->name,Fq[id].name);
          trnode->isLeaf = true;
    root->child_list.push_back(trnode);
  }
 }

 

 

}

void generage_decision_rules(Tree_Node * r,char rules[1000],int level)
{
 //printf("%d,%s/n",level,r->name);
 if (1 == level)
 {
  for (int i = 0;i < r->child_list.size();i++)
  {
   char str[1000];
   strcpy(str,rules);
   strcat(str,"IF ");
   strcat(str,r->name);
   strcat(str," = /"");
   strcat(str,r->att_list[i].tdata);
   strcat(str,"/"");
   
   generage_decision_rules(r->child_list[i],str,level +1 );
  }
 }
 else 
 {
  if(! r->isLeaf)
  {
   for (int i = 0;i < r->child_list.size();i++)
   {
    char str[1000];
    strcpy(str,rules);
    strcat(str," AND ");
    strcat(str,r->name);
    strcat(str," = /"");
    strcat(str,r->att_list[i].tdata);
    strcat(str," /"");
    
    //printf(" AND %s = /"%s/" ",r->name,r->att_list[i].tdata);
    generage_decision_rules(r->child_list[i],str,level +1 );
   } 
  }
  else
  {  
   printf("%s",rules);
   printf(" THEN %s = /"%s/"/n",G_DB.class_name.tdata,r->name);
   
  }  
  
  
 }

 

}


void test()
{
  
 vector<int> s;


 for (int i = 0;i< G_DB.DB.size();i++)
 {
  s.push_back(i);
 }
 vector<int> arrt_list;
 int class_id = G_DB.attr_name.size()-1;

 for ( i =0;i< G_DB.attr_name.size()-1;i++)
 {
  arrt_list.push_back(i);
 }

 


 getAllTheAttribute(s,arrt_list,class_id);

 Generate_decision_tree(Root,s,arrt_list,class_id);

 char rules[1000] ="";

 generage_decision_rules(Root,rules,1);

 

 

}


void main()
{
 readdata("data.txt");
 test();

}



