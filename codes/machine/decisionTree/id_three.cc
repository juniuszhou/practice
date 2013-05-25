
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



