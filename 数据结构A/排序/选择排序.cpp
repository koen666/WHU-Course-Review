#include<iostream>
#include <vector>
#include<algorithm>
#include<queue>
using namespace std;

//选择排序包含简单选择排序和堆排序

//简单选择排序 -> 每次从无序区选择最小的元素放到有序区的末尾，循环n-1次
void SimpleSelectSort(vector<int>& R, int n)
{
    int minIndex;
    for(int i=0;i<n-1;i++)
    {
        minIndex=i;
        for(int j=i+1;j<n;j++)
        {
            if(R[j]<R[minIndex])
            {
                minIndex=j;
            }
        }
        if(minIndex!=i)
        {
            swap(R[i],R[minIndex]);
        }
    }
}

//堆排序 -> 利用堆这种数据结构进行排序，分为建堆和调整堆两个步骤

// 【核心函数】调整堆 (Sift Down)
// start: 当前需要调整的节点下标
// end: 堆的结束下标（不包含）
void SiftDown(vector<int>& R, int start, int end)
{
    int root=start;
    int child=2*root+1;
    while (child<end)
    {
        if(child+1<end&&R[child+1]>R[child])
        {
            child++;
        }

        if(R[root]<R[child])
        {
            swap(R[root],R[child]);
            root=child;
            child=2*root+1;
        }
        else
        {
            break;
        }
    }
    
}

// 堆排序主函数
void HeapSort(vector<int>& R, int n) {
    // ---------------------------------------------------
    // 第一步：建堆 (Build Heap)
    // 从最后一个非叶子节点开始，自下而上进行调整
    // 最后一个非叶子节点下标 = (n / 2) - 1
    // ---------------------------------------------------
    for (int i = n / 2 - 1; i >= 0; i--) {
        SiftDown(R, i, n);
    }

    // ---------------------------------------------------
    // 第二步：排序 (Sort)
    // 每次将堆顶（最大值）交换到末尾，然后缩小堆范围，再调整
    // ---------------------------------------------------
    for (int i = n - 1; i > 0; i--) {
        // 1. 将堆顶元素 R[0] 与当前末尾元素 R[i] 交换
        // 此时 R[i] 就变成了有序区的元素
        swap(R[0], R[i]);

        // 2. 重新调整堆
        // 范围缩小为 [0, i)，因为 R[i] 已经排好了
        // 只需要调整根节点 R[0]，因为它刚被换上来，可能不满足堆性质
        SiftDown(R, 0, i);
    }
}

// 还有实现大小根堆更简单的方式：STL中的priority_queue
priority_queue<int> maxHeap;
priority_queue<int, vector<int>, greater<int>> minHeap;

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
    SimpleSelectSort(data, n);
    printVector(data);
    return 0;
}