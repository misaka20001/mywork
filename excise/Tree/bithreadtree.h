#include <iostream>
#include <stack>
#include <queue>
#include <cstdlib>
#include <cstdio>
#include <string>
#define tree_root test_tree.getroot()

using namespace std;

template <class type>
void visit(void *);

template <class type>
class BiThreadTree
{
    private:
    typedef struct BiThreadNode
    {
        type data;
        struct BiThreadNode *lchild;
        struct BiThreadNode *rchild;
        bool lflag;
        bool rflag;
    }BiThreadNode,*BiThreadtree;

    BiThreadtree head;
    BiThreadtree root;

    typedef void (*VISITDATA)(void *);
    friend void visit<type>(void *);

    public:
    BiThreadTree() {head=NULL; root=NULL;}
    ~BiThreadTree() {DestroyBiThreadTree(); cout<<"delete successfully\n";}
    BiThreadtree& getroot(){ return root;}

    void CreateBiThreadTree(BiThreadtree &node,type *&s)
    {
        if (!s || !(*s)) return;
        if (*s=='#') node=NULL;
        else
        {
            node=new BiThreadNode;
            node->data=*s;
            CreateBiThreadTree(node->lchild,++s);
            if (node->lchild)
            node->lflag=0;
            else node->lflag=1;
            CreateBiThreadTree(node->rchild,++s);
            if (node->rchild)
            node->rflag=0;
            else node->rflag=1;
        }
    }

    void InThreading(BiThreadtree node,BiThreadtree &pre)
    {
        if (node)
        {
            InThreading(node->lchild,pre);
            if (!node->lchild)
                node->lchild=pre;
            if (!pre->rchild)
                pre->rchild=node;
            pre=node;
            InThreading(node->rchild,pre);
        }
    }

    void InThreading_head()
    {
        head=new BiThreadNode;
        head->lflag=0;
        head->rflag=1;
        head->rchild=head;
        if (!root) head->lchild=head;
        else
        {
            head->lchild=root;
            BiThreadtree pre=head;
            InThreading(root,pre);
            pre->rchild=head;
            head->rchild=pre;
        }
    }

    BiThreadtree FirstNode()
    {
        BiThreadtree p=root;
        while(!p->lflag)
        p=p->lchild;
        return p;
    }

    BiThreadtree LastNode()
    {
        return head->rchild;
    }

    BiThreadtree PreNode(BiThreadtree node)
    {
        BiThreadtree pre=node->lchild;
        if (node->lflag==0)
            while (pre->rflag==0)
                pre=pre->rchild;
        return pre;
    }

    BiThreadtree PostNode(BiThreadtree node)
    {
        BiThreadtree post=node->rchild;
        if (node->rflag==0)
            while (post->lflag==0)
                post=post->lchild;
        return post;
    }

    void InorderTravel_Thr(VISITDATA vi)
    {
        BiThreadtree firstnode;
        firstnode=(*this).FirstNode();
        while(firstnode!=head)
        {
            vi(firstnode);
            firstnode=(*this).PostNode(firstnode);
        }
    }

    void InorderTravel_Thr_Reverse(VISITDATA vi)
    {
        BiThreadtree firstnode;
        firstnode=(*this).LastNode();
        while(firstnode!=head)
        {
            vi(firstnode);
            firstnode=(*this).PreNode(firstnode);
        }
    }

    void PrintBiThreadTree(BiThreadtree node)
    {
        cout<<node->data;
        if (node->lflag==0 || node->rflag==0)
        {
            cout<<"(";
            if (node->lflag==0)
                PrintBiThreadTree(node->lchild);
            if (node->rflag==0)
            {
                cout<<",";
                PrintBiThreadTree(node->rchild);
            }
            cout<<")";
        }
    }

    void DestroyBiTree(BiThreadtree &node)
    {
        if (node)
        {
            if (node->lflag==0)
            DestroyBiTree(node->lchild);
            if (node->rflag==0)
            DestroyBiTree(node->rchild);
            delete node;
        }
    }

    void DestroyBiThreadTree()
    {
        if (head)
        {
            if (head->lchild)
            DestroyBiTree(head->lchild);
            delete head;
        }
    }
};

template <class type>
void visit(void *node)
{
    cout<<((typename BiThreadTree<type>::BiThreadtree)node)->data<<" ";
}

int main()
{
    BiThreadTree<char> test_tree;
    char *pData=new char[20];
    cout<<"enter a tree like \"AB##C##\""<<endl;
    cin>>pData;
    test_tree.CreateBiThreadTree(tree_root,pData);
    test_tree.InThreading_head();
    cout<<"BiThreadTree is : ";
    test_tree.PrintBiThreadTree(tree_root);
    cout<<endl;
    cout<<"BiThreadTree's InorderTravel is : ";
    test_tree.InorderTravel_Thr(visit<char>);
    cout<<endl;
    cout<<"BiThreadTree's InorderTravel_Reverse is : ";
    test_tree.InorderTravel_Thr_Reverse(visit<char>);
    cout<<endl;
}











