#include<iostream>
#include <vector>
using namespace std;

//归并排序：每轮都对相邻子序列进行两两归并
//非递归版本
void MergeSort1(vector<int>& R, int n)
{
    for(int len=1;len<n;len*=2)
    {
        MergePass(R,n,len);
    }
}

void MergePass(vector<int>& R, int n, int len)
{
    int i;
    for(i=0;i+2*len-1<n;i+=2*len)
    {
        Merge(R,i,i+len-1,i+2*len-1);
    }
    if(i+len<n)
    {
        Merge(R,i,i+len-1,n-1);
    }
}

//归并：维护一个数组temp存放归并结果
void Merge(vector<int>& R, int low, int mid, int high)
{
    vector<int> temp(high - low + 1);
    int i=low,j=mid+1,k=0;
    while (i <= mid && j <= high) {
        if (R[i] <= R[j]) { temp[k++] = R[i++]; }
        else { temp[k++] = R[j++]; }
    }
    while (i <= mid) { temp[k++] = R[i++]; }
    while (j <= high) { temp[k++] = R[j++]; }

    // 将结果复制回原向量 R
    for (k = 0, i = low; i <= high; k++, i++) 
        R[i] = temp[k];
}

//递归版本
void MergeSort2(vector<int>& R, int n)
{
    _MergeSort2(R, 0, n-1); 
}

void _MergeSort2(vector<int>& R, int low, int high)
{
    if(low<high)
    {
        int mid=(low+high)/2;
        _MergeSort2(R,low,mid);
        _MergeSort2(R,mid+1,high);
        Merge(R,low,mid,high);
    }
}

void printVector(const vector<int>& R) {
    for (int val : R) {
        cout << val << " ";
    }
    cout << endl;
}

int main()
{
    vector<int> data = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int n=data.size();

    printVector(data);
    return 0;
}