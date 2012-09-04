#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <stack>
#include "sort.h"

using namespace std;

array::array(int num)
{
    how_many=num;
    srand(time(0));
    for(int i=0;i<num;i++)
        set[i]=rand()%10000;
    cout<<"array consist "<<num<<" data has set up\n";
}

int array::partition(int arr[],int low,int high)
{
    int temp=arr[low];
    int i=low;
    int j=high;
    while (i<j)
    {
        while (i<j && arr[j]>temp)
            j--;
        if (i<j)
            arr[i++]=arr[j];
        while (i<j && arr[i]<temp)
            i++;
        if (i<j)
            arr[j--]=arr[i];
    }
    arr[i]=temp;
    return i;
}

void array::AdjustHeap(int arr[],int n,int k)
{
    int max=k;
    int i=k;
    int lchild=2*i+1;
    int rchild=2*i+2;
    while (lchild<n)
    {
        if (lchild<n && arr[lchild]>arr[max])
            max=lchild;

        if (rchild<n && arr[rchild]>arr[max])
            max=rchild;

        if (max==i)
            break;
        else
        {
            swap(arr[i],arr[max]);
            i=max;
            lchild=2*max+1;
            rchild=2*max+2;
        }
    }
}

void array::CreateHeap(int arr[])
{
    for (int i=(how_many-2)/2;i>=0;i--)
        AdjustHeap(arr,how_many,i);
}

void array::TwoMerge(int arr[],int swap[],int low,int mid,int high)
{
    int i=low;
    int j=mid+1;
    int k=low;
    while (i<=mid && j<=high)
    {
        if (arr[i]<=arr[j])
            swap[k++]=arr[i++];
        else
            swap[k++]=arr[j++];
    }
    while (i<=mid)
        swap[k++]=arr[i++];
    while (j<=high)
        swap[k++]=arr[j++];
}

void array::MergePass(int arr[],int swap[],int n,int len)
{
    int p=0;
    while (p+2*len<=n)
    {
        TwoMerge(arr,swap,p,p+len-1,p+2*len-1);
        p+=2*len;
    }
    if (p+len<n)
    TwoMerge(arr,swap,p,p+len-1,n-1);
    else
    for(int i=p;i<n;i++)
        swap[i]=arr[i];
}


void array::InsertSort()
{
    int tempset[how_many];

    for (int i=0;i<how_many;i++)
        tempset[i]=set[i];

    clock_t start=clock();
    for (int i=1;i<how_many;i++)
    {
        int j=i-1;
        int temp=tempset[i];
        while (j>=0 && temp<tempset[j])
        {
            tempset[j+1]=tempset[j];
            j--;
        }
        tempset[j+1]=temp;
    }
    clock_t finish=clock();
    double time=(double)(finish-start)/CLOCKS_PER_SEC;
    //for(int i=0;i<how_many;i++)
        //cout<<tempset[i]<<" ";
    cout<<endl<<"cost "<<time<<" s\n";
}

void array::BinarySort()
{
    int tempset[how_many];

    for (int i=0;i<how_many;i++)
        tempset[i]=set[i];

    clock_t start=clock();
    for (int i=1;i<how_many;i++)
    {
        int temp=tempset[i];
        int low=0;
        int high=i-1;
        while (low<=high)
        {
            int mid=(low+high)/2;
            if (tempset[mid]<temp)
                low=mid+1;
            else high=mid-1;
        }
        for (int j=i-1;j>=low;j--)
            tempset[j+1]=tempset[j];
        tempset[low]=temp;
    }
    clock_t finish=clock();
    double time=(double)(finish-start)/CLOCKS_PER_SEC;
    //for(int i=0;i<how_many;i++)
        //cout<<tempset[i]<<" ";
    cout<<endl<<"cost "<<time<<" s\n";
}

void array::BubbleSort()
{
    int tempset[how_many];

    for (int i=0;i<how_many;i++)
        tempset[i]=set[i];

    clock_t start=clock();
    for (int i=1;i<how_many;i++)
    {
        for (int j=0;j<how_many-i;j++)
            if (tempset[j]>tempset[j+1])
                swap(tempset[j],tempset[j+1]);
    }
    clock_t finish=clock();
    double time=(double)(finish-start)/CLOCKS_PER_SEC;
    //for(int i=0;i<how_many;i++)
        //cout<<tempset[i]<<" ";
    cout<<endl<<"cost "<<time<<" s\n";
}

void array::SelectSort()
{
    int tempset[how_many];

    for (int i=0;i<how_many;i++)
        tempset[i]=set[i];

    clock_t start=clock();
    for (int i=0;i<how_many-1;i++)
    {
        int minindex=i;
        int min=tempset[i];

        for (int j=i+1;j<how_many;j++)
            if (tempset[j]<min)
            {
                min=tempset[j];
                minindex=j;
            }

        if (minindex!=i)
            swap(tempset[i],tempset[minindex]);
    }

    clock_t finish=clock();
    double time=(double)(finish-start)/CLOCKS_PER_SEC;
    //for(int i=0;i<how_many;i++)
        //cout<<tempset[i]<<" ";
    cout<<endl<<"cost "<<time<<" s\n";
}

void array::ShellSort(int d[],int num)
{
    int tempset[how_many];

    for (int i=0;i<how_many;i++)
        tempset[i]=set[i];

    clock_t start=clock();
    for (int i=0;i<num;i++)
    {
        int inc=d[i];
        for (int j=0;j<inc;j++)
        {
            for (int k=j+inc;k<how_many;k+=inc)
            {
                int m=k-inc;
                int temp=tempset[k];
                while (m>=0 && temp<tempset[m])
                {
                    tempset[m+inc]=tempset[m];
                    m-=inc;
                }
                tempset[m+inc]=temp;
            }
        }
    }

    clock_t finish=clock();
    double time=(double)(finish-start)/CLOCKS_PER_SEC;
    //for(int i=0;i<how_many;i++)
        //cout<<tempset[i]<<" ";
    cout<<endl<<"cost "<<time<<" s\n";
}

void array::QuickSort(int low,int high)
{
    if (low<high)
    {
        int mid=partition(set,low,high);
        QuickSort(low,mid-1);
        QuickSort(mid+1,high);
    }
}

void array::RS_QuickSort(int low,int high)
{
    typedef pair<int,int> PAIR;
    int tempset[how_many],mid;

    for (int i=0;i<how_many;i++)
        tempset[i]=set[i];

    stack<PAIR> st;
    clock_t start=clock();

    if(low<high)
    {
        mid=partition(tempset,low,high);
        if(low<mid-1)
            st.push(PAIR(low,mid-1));
        if(mid+1<high)
            st.push(PAIR(mid+1,high));
    }

    while (!st.empty())
    {
        PAIR q=st.top();
        st.pop();
        mid=partition(tempset,q.first,q.second);
        if(q.first<mid-1)
            st.push(PAIR(q.first,mid-1));
        if(mid+1<q.second)
            st.push(PAIR(mid+1,q.second));
    }

    clock_t finish=clock();
    double time=(double)(finish-start)/CLOCKS_PER_SEC;
    //for(int i=0;i<how_many;i++)
        //cout<<tempset[i]<<" ";
    cout<<endl<<"cost "<<time<<" s\n";
}

void array::MergeSort()
{
    int len=1;
    int tempset[how_many];
    int *swap=new int [how_many];

    for (int i=0;i<how_many;i++)
        tempset[i]=set[i];

    clock_t start=clock();
    while (len<how_many)
    {
        MergePass(tempset,swap,how_many,len);
        len*=2;
        MergePass(swap,tempset,how_many,len);
        len*=2;
    }
    delete []swap;

    clock_t finish=clock();
    double time=(double)(finish-start)/CLOCKS_PER_SEC;
    //for(int i=0;i<how_many;i++)
        //cout<<tempset[i]<<" ";
    cout<<endl<<"cost "<<time<<" s\n";
}

void array::HeapSort()
{
    int tempset[how_many];

    for (int i=0;i<how_many;i++)
        tempset[i]=set[i];

    clock_t start=clock();
    CreateHeap(tempset);
    for(int i=how_many-1;i>0;i--)
    {
        swap(tempset[0],tempset[i]);
        AdjustHeap(tempset,i,0);
    }
    clock_t finish=clock();
    double time=(double)(finish-start)/CLOCKS_PER_SEC;
    //for(int i=0;i<how_many;i++)
        //cout<<tempset[i]<<" ";
    cout<<endl<<"cost "<<time<<" s\n";
}

int main()
{
    int d[3]={6,3,1};
    array h(10000);
    h.InsertSort();
    h.BinarySort();
    h.RS_QuickSort(0,9999);
    h.QuickSort(0,9999);
    h.BubbleSort();
    h.SelectSort();
    h.ShellSort(d,3);
    h.HeapSort();
    h.MergeSort();
}

