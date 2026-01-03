#include<iostream>
#include <vector>
using namespace std;
//核心 [有序区][无序区]
//          j<--i  插入有序区  
void InsertSort(vector<int>& R, int n)
{
    int temp;
    for(int i=1;i<n;i++)
    {
        temp=R[i];
        int j=i-1;
        if(R[j]<=temp)
        {
            continue;
        }
        else
        {
            while (j >= 0&&R[j]>temp)
            {

                R[j+1]=R[j];
                j--;
            }
            R[j+1]=temp;
        }
    }
}

//折半插入排序就是在有序区进行二分查找
void BinInsertSort(vector<int>& R, int n)
{
    int low,high,mid,temp;
    for(int i=1;i<n;i++)
    {
        temp=R[i];
        low=0;
        high=i-1;
        if(R[high]<=temp)
        {
            continue;
        }
        else
        {
            while(low<=high)
            {
                mid=(low+high)/2;
                if(R[mid]>temp)
                {
                    high=mid-1;
                }
                else
                {
                    low=mid+1;
                }
            }
            for(int j=i-1;j>=low;j--)
            {
                R[j+1]=R[j];
            }
            R[low]=temp;
        }
    }
}

//希尔排序 -> 插入排序的改进版，通过增量分组进行插入排序，逐渐减少增量直到为1
void ShellSort(vector<int>& R, int n) {
    int d = n / 2; // 1. 初始化增量，通常为长度的一半
    
    // 循环直到增量为 0
    while (d > 0) {
        
        // 2. 对距离为 d 的元素组进行直接插入排序
        // 注意：这里 i 从 d 开始，类似于插入排序中 i 从 1 开始
        for (int i = d; i < n; i++) {
            
            // 只有当 R[i] 小于它同组的前一个元素 R[i-d] 时才需要处理
            if (R[i] < R[i - d]) {
                int temp = R[i];
                int j = i - d;
                
                // 3. 组内元素后移 (注意步长是 d)
                // 检查 j>=0 且 R[j] > temp
                while (j >= 0 && R[j] > temp) {
                    R[j + d] = R[j];
                    j -= d; // 向前跳 d 个位置
                }
                
                R[j + d] = temp; // 插入
            }
        }
        
        d = d / 2; // 4. 缩小增量
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
    BinInsertSort(data, n);
    printVector(data);
    return 0;
}