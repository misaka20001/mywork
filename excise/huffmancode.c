#include <iostream>

#define MAXVALUE 10000
#define MAXBIT 10

using namespace std;

typedef struct{
    int weight;
    int parent,lchild,rchild;
}HTNode,*HuffmanTree;

void select(HuffmanTree HT,int n,int &i1, int &i2)
{
    int m1,m2;
    m1=m2=MAXVALUE;
    i1=i2=0;
    for(int i=0;i<n;i++)
    {
        if (HT[i].weight<m1 && HT[i].parent==-1)
        {
            m2=m1;
            m1=HT[i].weight;
            i2=i1;
            i1=i;
        }
        else if (HT[i].weight<m2 && HT[i].parent==-1)
        {
            m2=HT[i].weight;
            i2=i;
        }
    }
}

void HuffmanTreeing(HuffmanTree &HT,int *w,int n)
{
    int s1,s2;
    HT=new HTNode[2*n-1];
    for(int i=0;i<2*n-1;i++)
    {
        if (i<n)  HT[i].weight=w[i];
        else  HT[i].weight=0;
        HT[i].parent=-1;
        HT[i].lchild=-1;
        HT[i].rchild=-1;
    }
    for(int i=n;i<2*n-1;i++)
    {
        select(HT,i,s1,s2);
        HT[i].weight=HT[s1].weight+HT[s2].weight;
        HT[i].lchild=s1;
        HT[i].rchild=s2;
        HT[s1].parent=HT[s2].parent=i;
    }
}

typedef struct{
    int weight;
    char code[MAXBIT];
}HTCode,*HuffmanCode;

void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,int n)
{
    int child,parent,start;
    HC=new HTCode[n];
    HTCode cd;
    for(int i=0;i<n;i++)
    {
        start=MAXBIT-1;
        HC[i].weight=HT[i].weight;
        child=i;
        parent=HT[child].parent;
        while (parent!=-1)
        {
            if (HT[parent].lchild==child)
            cd.code[start]='0';
            else
            cd.code[start]='1';
            start--;
            child=parent;
            parent=HT[child].parent;
        }
        for(int j=start+1;j<MAXBIT;j++)
        HC[i].code[j-start-1]=cd.code[j];
        HC[i].code[MAXBIT-start-1]='\0';
    }
}

int main()
{
    int i,j,*w,n;
    HuffmanTree HT;
    HuffmanCode HC;
    cout<<"please enter num of weight : ";
    cin>>n;
    w=new int [n];
    cout<<"please enter each "<<n<<" weight : ";
    for(i=0;i<n;i++)
    cin>>w[i];
    HuffmanTreeing(HT,w,n);
    HuffmanCoding(HT,HC,n);
    for(i=0;i<n;i++)
    {
        cout<<"Weight = "<<HT[i].weight<<" Code = "
            <<HC[i].code<<endl;
    }
}
