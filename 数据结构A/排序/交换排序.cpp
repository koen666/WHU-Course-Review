#include<iostream>
#include <vector>
using namespace std;

//交换排序主要有冒泡排序和快速排序
//冒泡排序 -> 相邻元素两两比较，大的往后冒泡，每次遍历将最大的元素放到最后，循环n-1次
void BubbleSort(vector<int>& R, int n)
{
    bool flag=false;
    for(int i=0;i<n-1;i++)
    {
        flag=false;
        for(int j=0;j<n-i-1;j++)
        {
            if(R[j]>R[j+1])
            {
                swap(R[j],R[j+1]);
                flag=true;
            }
        }
        if(!flag)
        {
            break;
        }
    }
}

//快速排序 -> 分治思想，选定一个基准元素，将数组划分为两部分，一部分小于基准，一部分大于基准，然后递归排序两部分
int Partition(vector<int>& R, int low, int high)
{
    int pivot=R[low];
    while (low<high)
    {
        while(low<high&&R[high]>=pivot)
        {
            high--;
        }
        R[low]=R[high];
        while(low<high&&R[low]<=pivot)
        {
            low++;
        }
        R[high]=R[low];
    }
    R[low] = pivot;
    return low;
}

void QuickSort(vector<int>& R, int low, int high)
{
    if(low<high)
    {
        int pivotpos=Partition(R,low,high);
        QuickSort(R,low,pivotpos-1);
        QuickSort(R,pivotpos+1,high);
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
    QuickSort(data, 0, n-1);
    printVector(data);
    return 0;
}