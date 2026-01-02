#include<iostream>
#include<queue>
using namespace std;

struct HTNode
{
    char data;
    double weight;
    int parent, lchild, rchild; //下标
    bool flag; // 标识：true表示是双亲的左孩子，false表示右孩子（用于编码）
    HTNode() { parent = lchild = rchild = -1; }
    // 重载构造函数：用于初始化叶子结点
    HTNode(char d, double w) {
        data = d;
        weight = w;
        parent = lchild = rchild = -1;
        flag = true;
    }
};

//哈夫曼树构造过程中，需要频繁“选取权值最小的两个结点”。为了高效实现，使用了优先队列
struct HeapNode
{
    double w; // 权值
    int i;   // 结点下标
    HeapNode(double w1, int i1) : w(w1), i(i1) {}
    bool operator<(const HeapNode& s) const {
        return w > s.w;
    }
};

void CreateHT()
{
    priority_queue<HeapNode> qu;
}

int main()
{
    return 0;
}