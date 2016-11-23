#include<iostream>
#include<string.h>
#define M 20//State Number
using namespace std;
int Goto[M][28],Fail[M],Top=0;
string Output[M],D[M];

void Reset();/*��ʼ��*/
void AdGoto(string x);/*����Goto&&Output&&D*/
void AdOutput();/*����Fail&&Output*/
void Recognize(string x);/*ƥ��*/
void PrintGoto();/*���Goto*/

int main()
{   Reset();
    string x;
    cin>>x;
    while(x[0]!='#')
    {   AdGoto(x);
        cin>>x;}
    PrintGoto();
    AdOutput();
    cout<<"\n\n";
    cin>>x;
    Recognize(x);}

void Reset()/*��ʼ��*/
{   for(int i=0;i<M;i++)
    {   for(int j=0;j<28;j++)
            Goto[i][j]=0;
        Fail[i]=0;
        Output[i]=D[i]="";}
    D[0]+='0';}

void AdGoto(string x)/*����Goto&&Output&&D*/
{   int len=x.length(),next=0;
    for(int i=0;i<len;i++)
    {   int index=x[i]-97;/*char[26]->int[26]*/
        if(!Goto[next][index])
        {   Goto[next][index]=++Top;
            Goto[Top][26]=next;/*ǰһ״̬*/
            Goto[Top][27]=index;/*�����ַ�*/}
        next=Goto[next][index];
        char num=next+48;/*int->(char)int*/
        if(D[i+1].find(num)==D[i+1].npos)/*��¼���*/
            {D[i+1]+=num;}}
    Output[next]+=x;/*�������*/}

void AdOutput()/*����Fail&&Output*/
{   int k=2,num,prev,in;
    while(D[k]!="")
    {   for(int i=0;i<D[k].length();i++)
        {   num=D[k][i]-48;/*char->int*/
            prev=Goto[num][26];/*ǰ��״̬*/
            in=Goto[num][27];/*�����ַ�*/
            Fail[num]=Goto[Fail[prev]][in];
            if(Output[Fail[num]]!="")
                {Output[num]+=(" "+Output[Fail[num]]);}}
        k++;}
    cout<<'\n';
    for(int i=0;i<=Top;i++)
        if(Output[i]!="")
            cout<<'\n'<<i<<'\t'<<Output[i];}

void Recognize(string x)/*ƥ��*/
{   int state=0,index,i=0;
    while(i<x.length())
    {   index=x[i]-97;/*char[26]->int[26]*/
        if(Goto[state][index]||!state)
        {   state=Goto[state][index];
            if(Output[state]!="")
                cout<<i+1<<'\t'<<Output[state]<<'\n';
            i++;}
        else
            {state=Fail[state];}}}

void PrintGoto()/*���Goto*/
{   cout<<"\n#\ta b c d e f g h i j k l m n o p q r s t u v w x y z P C";
    for(int i=0;i<=Top;i++)
    {   cout<<'\n'<<i<<'\t';
        for(int j=0;j<26;j++)
        {   if(Goto[i][j])
                cout<<Goto[i][j]<<' ';
            else
                cout<<"  ";}
            cout<<Goto[i][26]<<' '<<(char)(Goto[i][27]+97);}}
