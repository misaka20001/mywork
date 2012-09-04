//A(B(D,E(H,I),F),C(G))
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <queue>
#define MAX_SON_SIZE 10

using namespace std;

typedef char ELEmtype;
typedef struct CTNode
{
    ELEmtype data;
    struct CTNode *child[MAX_SON_SIZE];
}CTNode,*CTree;

void createtree(CTree &T,char *s)
{
    CTree stack[10],p;
    int d[10],top=-1;
    T=NULL;
    while(*s)
    {
        switch(*s)
        {
            case ' ':   break;
            case '(':   stack[++top]=p;
                        d[top]=0;
                        break;
            case ')':   top--;
                        break;
            case ',':   d[top]++;
                        break;
            default:
                if(!(p=new CTNode))
                return;
                p->data=*s;
                for(int i=0;i<MAX_SON_SIZE;i++)
                    p->child[i]=NULL;
                if(!T) T=p;
                else stack[top]->child[d[top]]=p;
                break;
        }
        s++;
    }
}

void visit(void* T)
{
    cout<<((CTree)T)->data<<' ';
}

void preordertree(CTree T,void (*vi)(void* ))
{
    if(T)
    {
    (*vi)((CTree)T);
    for (int i=0;i<MAX_SON_SIZE;i++)
        preordertree(T->child[i],*vi);
    }
}

void postordertree(CTree T,void (*vi)(void *))
{
    if (T)
    {
        for(int i=0;i<MAX_SON_SIZE;i++)
            postordertree(T->child[i],*vi);
        (*vi)(T);
    }
}

void levelordertree(CTree T,void (*vi)(void *))
{
    queue<CTree> Q;
    CTree temp;
    Q.push(T);
    while(!Q.empty())
    {
        temp=Q.front();
        Q.pop();
        (*vi)(temp);
        for(int i=0;i<MAX_SON_SIZE;i++)
        {
            if (temp->child[i])
            Q.push(temp->child[i]);
        }
    }
    cout<<endl;
}


int destroytree(CTree T)
{
    if (T)
    {
        for(int i=0;i<MAX_SON_SIZE;i++)
            destroytree(T->child[i]);
        delete T;
        return 1;
    }
}

bool search(CTree T,ELEmtype mdata)
{
    if (!T)
    return false;
    if (T->data==mdata)
    return true;
    for(int i=0;i<MAX_SON_SIZE;i++)
        if(search(T->child[i],mdata))
        return true;
    return false;
}

int treedepth(CTree T)
{
    if (!T)
    return 0;
    int max=0;
    for(int i=0;i<MAX_SON_SIZE;i++)
    {
        if (treedepth(T->child[i])>max)
        max=treedepth(T->child[i]);
    }
    return max+1;
}

void printtree(CTree T)
{
    if (T)
    {
        visit(T);
        if(T->child[0])
        {
            cout<<"(";
            printtree(T->child[0]);
            for(int i=1;i<MAX_SON_SIZE;i++)
            {
                if(T->child[i])
                {
                cout<<",";
                printtree(T->child[i]);
                }
                else
                break;
            }
            cout<<")";
        }
    }
}



int main()
{
    char *s=new char[20],ch;
    CTree T=new CTNode;
    s="A(B(D,E(H,I),F),C(G))";
    createtree(T,s);
    preordertree(T,visit);
    cout<<endl;
    postordertree(T,visit);
    cout<<endl;
    levelordertree(T,visit);
    cout<<"tree depth is "<<treedepth(T)<<endl;
    printtree(T);
    cout<<endl<<"enter a data to search\n";
    cin>>ch;
    if (search(T,ch))
    cout<<"search succeed\n";
    else
    cout<<"search failed\n";
    if(destroytree(T))
    cout<<"destroyed\n";
    return 0;
}
