#include<iostream>
#include <vector>
using namespace std;

// 1. 定义单链表节点结构 [cite: 1452, 1453]
template <typename T>
struct LinkNode {
    T data;
    LinkNode<T>* next;
    LinkNode() : next(nullptr) {}
    LinkNode(T d) : data(d), next(nullptr) {}
};

// 简单的链表封装，方便管理头节点
template <typename T>
struct LinkList {
    LinkNode<T>* head;
    LinkList() { head = new LinkNode<T>(); }
};

// 2. 求基数为 r 的正整数 key 的第 i 位数值 [cite: 1454]
// i=0 表示个位，i=1 表示十位，以此类推
int geti(int key, int r, int i) {
    int k = 0;
    for (int j = 0; j <= i; j++) {
        k = key % r;
        key = key / r;
    }
    return k;
}

// 3. 最低位优先 (LSD) 基数排序算法 [cite: 1456, 1460]
// L: 待排序链表, d: 最大位数, r: 基数 (十进制通常为 10)
void RadixSort1(LinkList<int>& L, int d, int r) {
    const int MAXR = 10; // 假设基数最大为 10
    LinkNode<int>* front[MAXR]; // 存放链队头指针的数组 [cite: 1456]
    LinkNode<int>* rear[MAXR];  // 存放链队尾指针的数组 [cite: 1456]
    LinkNode<int> *p, *t;

    for (int i = 0; i < d; i++) { // 从低位到高位循环 d 趟 [cite: 1457]
        // --- 分配阶段 ---
        for (int j = 0; j < r; j++) // 初始化各链队 [cite: 1457]
            front[j] = rear[j] = nullptr;

        p = L.head->next; // p 指向链表第一个数据节点
        while (p != nullptr) {
            int k = geti(p->data, r, i); // 提取关键字第 i 位的值 k [cite: 1458]
            
            if (front[k] == nullptr) { // 队列为空，建立队头 [cite: 1458]
                front[k] = p;
                rear[k] = p;
            } else { // 队列不为空，采用尾插法 [cite: 1458]
                rear[k]->next = p;
                rear[k] = p;
            }
            p = p->next; // 检查下一个节点 [cite: 1459]
        }

        // --- 收集阶段 ---
        LinkNode<int>* h = nullptr; // 用于收集所有节点的新链表头 [cite: 1460]
        for (int j = 0; j < r; j++) { // 按基数顺序遍历队列 [cite: 1460]
            if (front[j] != nullptr) {
                if (h == nullptr) { // 找到第一个非空队列 [cite: 1460]
                    h = front[j];
                    t = rear[j];
                } else { // 将后续非空队列接在前一个队列尾部 [cite: 1461]
                    t->next = front[j];
                    t = rear[j];
                }
            }
        }
        t->next = nullptr; // 收集完毕，尾节点置空 [cite: 1461]
        L.head->next = h;  // 将排序后的链表挂回原链表头节点
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