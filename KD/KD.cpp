#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<new>
#define ALL 20000
#define Build 10000
using namespace std;

struct node
{   struct node *lch,*rch;/*�ӽڵ�*/
	bool leaf;/*Ҷ�ڵ��־*/
	int dimen;/*�ָ�ά*/
	int mid;/*�ָ��е���*/
	vector<int> index;/*���ݱ��*/};
typedef struct node* Tree;/*����ָ��*/

struct data
{   double flow[10];/*�������Լ�*/
    bool nor;/*������־*/};

data D[ALL];/*���ݼ�*/

void Input()/*�ļ�����*/
{   FILE *F=fopen("KDDCUP.data_10_percent","r");
    if(!F)
    {   return;}
    string in[42],s;
    char ch;
    for(int i=0;i<ALL;i++)/*D�±�*/
    {   ch=fgetc(F);
        int k=0;
        while(1)/*��ά��*/
        {   s="";
            while(ch!=',')/*�����*/
            {   if(ch=='\n')/*����*/
                {   in[k]=s;
                    goto Next;}
                s+=ch;
                ch=fgetc(F);}
            ch=fgetc(F);
            in[k++]=s;}
Next:   for(int j=21;j<31;j++)/*ѡ���������Լ�*/
        {   D[i].flow[j-21]=atof(in[j].c_str());}
        D[i].nor=(in[41]=="normal.")?1:0;}}

void Trans()/*���*/
{   double Min,Max;
    for(int j=0;j<10;j++)
    {   Min=Max=D[0].flow[j];
        for(int i=1;i<ALL;i++)
        {   if(D[i].flow[j]>Max)
            {   Max=D[i].flow[j];}
            if(D[i].flow[j]<Min)
            {   Min=D[i].flow[j];}}
        if(Max!=Min)
        {   for(int i=0;i<ALL;i++)
            {   D[i].flow[j]=(D[i].flow[j]-Min)/(Max-Min);}}}}

void Create(Tree BT,int number)/*����*/
{   double di[10],Max,Min;
    for(int j=0;j<10;j++)
    {   Max=Min=D[BT->index[0]].flow[j];
        for(int i=1;i<number;i++)
        {   if(D[BT->index[i]].flow[j]>Max)
            {   Max=D[BT->index[i]].flow[j];}
            if(D[BT->index[i]].flow[j]<Min)
            {   Min=D[BT->index[i]].flow[j];}}
        di[j]=Max-Min;}
    int Ch=0;/*�ָ�ά*/
    for(int i=1;i<10;i++)
    {   if(di[i]>di[Ch])
        {   Ch=i;}}
    if(di[Ch]==0)
    {   return;}
    for(int i=0;i<number-1;i++)/*ð������*/
    {   for(int j=i+1;j<number;j++)
        {   if(D[BT->index[i]].flow[Ch]>D[BT->index[j]].flow[Ch])
            {   int tmp=BT->index[i];
                BT->index[i]=BT->index[j];
                BT->index[j]=tmp;}}}
    BT->leaf=0;
    BT->dimen=Ch;
    BT->mid=BT->index[number/2-1];
    BT->lch=new node;
    BT->lch->leaf=1;
    for(int i=0;i<number/2;i++)
    {   BT->lch->index.push_back(BT->index[i]);}
    BT->rch=new node;
    BT->rch->leaf=1;
    for(int i=number/2;i<number;i++)
    {   BT->rch->index.push_back(BT->index[i]);}
    BT->index.clear();
    Create(BT->lch,number/2);
    Create(BT->rch,number-number/2);}

double Judge(Tree BT,int x)/*�ж�����㲢���ط�����*/
{   if(BT->leaf==1)
    {   int tar=BT->index[0];
        double dis=0;
        for(int i=0;i<10;i++)
        {   dis+=pow(D[x].flow[i]-D[tar].flow[i],2);}
        return sqrt(dis);}
    //cout<<BT->dimen<<'\t'<<BT->mid<<endl;
    if(D[x].flow[BT->dimen]<=D[BT->mid].flow[BT->dimen])
    {   return Judge(BT->lch,x);}
    else
    {   return Judge(BT->rch,x);}}

int main()
{   Input();/*�ļ�����*/
    Trans();/*���*/
    Tree KD=new node;/*���ڵ�*/
    KD->lch=KD->rch=NULL;
    KD->leaf=0;
    for(int i=0;i<Build;i++)
    {   (KD->index).push_back(i);}
    Create(KD,Build);/*����*/
    int Right=0,Wrong=0;
    for(int i=Build;i<ALL;i++)
    {   double R=Judge(KD,i);
        if((R>=1&&!D[i].nor)||(R<1&&D[i].nor))
        {   Right++;}
        else
        {   Wrong++;}}
    printf("ALL:%d\tBuild:%d\n",ALL,Build);
    printf("Right:%d\tWrong:%d\t%lf",Right,Wrong,Right*1.0/(Right+Wrong));}
