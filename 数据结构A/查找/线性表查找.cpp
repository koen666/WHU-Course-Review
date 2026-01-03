#include<iostream>
#include<vector>
using namespace std;

//基本思路： 从线性表的一端（通常是头部）开始，依次将每个元素的关键字与给定值k进行比较。若相等则查找成功；若遍历完仍未找到，则查找失败

//顺序查找
//纯循环
int searchLinear(const vector<int>& arr, int k,int n)
{
    for(int i=0;i<n;i++)
    {
        if(arr[i]==k)
        {
            return i; 
        }
    }
    return -1;
}

//哨兵法
int SeqSearch2(vector<int>& R, int k,int n) 
{
    R.push_back(k);
    int i = 0;
    while (R[i] != k)
        i++;
    if (i == n) return -1;
    else return i;
}

//二分查找
//非递归实现
int BinarySearch(const vector<int>&arr,int k,int n)
{
    int low=0,high=n-1;
    while (low<=high)
    {
        int mid=(low+high)/2;
        if(arr[mid]==k)
        {
            return mid;
        }
        else if(arr[mid]<k)
        {
            low=mid+1;
        }
        else
        {
            high=mid-1;
        }
    }
    return -1;
}

//递归实现
int BinarySearchRecursive(const vector<int>&arr,int k,int low,int high)
{
    if(low>high)
    {
        return -1;
    }
    int mid=(low+high)/2;
    if(arr[mid]==k)
    {
        return mid;
    }
    else if(arr[mid]<k)
    {
        return BinarySearchRecursive(arr,k,mid+1,high);
    }
    else
    {
        return BinarySearchRecursive(arr,k,low,mid-1);
    }
}

//分块查找
struct IdxType { // 索引项结构
    int key;     // 块中最大关键字
    int link;    // 块起始下标
};

int BlkSearch(vector<int>& R, IdxType I[], int b, int k) {
    int n = R.size();
    int low = 0, high = b - 1;
    
    // 1. 在索引表中折半查找确定块
    while (low <= high) {
        int mid = (low + high) / 2;
        if (k <= I[mid].key) high = mid - 1; 
        else low = mid + 1;
    }
    // 此时 low 是块号（或者 high+1）
    if (high + 1 >= b) return -1; // 越界，不存在
    
    // 2. 在具体块中顺序查找
    int i = I[high + 1].link; // 块起始位置
    // 计算块长度 s (假设均匀分布，除最后一块外)
    int s = (n + b - 1) / b; 
    int end = I[high + 1].link + s - 1; // 块结束位置大致范围(需处理边界)
    // 实际代码需处理最后一块长度不同的情况，这里简化展示逻辑
    
    while (i <= end && i < n && R[i] != k) {
        i++;
    }
    
    if (i <= end && i < n && R[i] == k) return i; // 找到
    else return -1;
}

int main()
{
    vector<int> nums={3,1,4,1,5,9,2,6,5,3,5};
    int n=nums.size();
    return 0;
}