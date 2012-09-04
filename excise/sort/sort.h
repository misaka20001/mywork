#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED
using namespace std;

class array
{
    private:
    int how_many;
    int set[100000];
    int partition(int arr[],int low,int high);
    void CreateHeap(int arr[]);
    void AdjustHeap(int arr[],int n,int k);
    void TwoMerge(int arr[],int swap[],int low,int mid,int high);
    void MergePass(int arr[],int swap[],int n,int len);

    public:
    array(int num);
    ~array(){}
    void InsertSort();
    void BinarySort();
    void ShellSort(int d[],int num);
    void SelectSort();
    void HeapSort();
    void BubbleSort();
    void QuickSort(int low,int high);
    void RS_QuickSort(int low,int high);
    void MergeSort();
};

#endif // SORT_H_INCLUDED
