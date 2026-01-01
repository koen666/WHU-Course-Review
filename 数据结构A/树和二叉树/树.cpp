#include<iostream>
#include<vector>
using namespace std;

//双亲存储结构
struct PNode
{
    char data;
    int parent;

    PNode(char d,int p)
    {
        data = d;
        parent = p;
    }
};

//孩子链存储结构
struct SonNode {
    char data;
    vector<SonNode*> sons;
    
    SonNode(char d) : data(d) {}
};  

//长子兄弟链存储结构

struct EBNode {
    char data;
    EBNode* brother; // 指向下一个兄弟节点
    EBNode* eson;    // 指向长子节点（第一个孩子）
    
    EBNode(char d) {
        data = d;
        brother = eson = NULL;
    }
};

//求解结点层次
int level(vector<PNode> &T,int i)
{
    int level = 1;
    while(T[i].parent != -1)
    {
        i = T[i].parent;
        level++;
    }
    return level;
}

int Height(SonNode* t) {
    // 1. 递归出口：空树高度为0
    if (t == NULL) return 0;
    
    int maxsh = 0; // 用于记录子树中的最大高度
    
    // 2. 遍历当前节点的所有孩子（sons向量）
    for (int i = 0; i < t->sons.size(); i++) {
        int sh = Height(t->sons[i]); // 递归求第i个子树的高度
        maxsh = max(maxsh, sh);      // 更新最大高度
    }
    
    // 3. 返回结果：最大子树高度 + 根节点自己(1)
    return maxsh + 1; 
}

int Height2(EBNode* t) {
    // 1. 递归出口
    if (t == NULL) return 0;
    
    int maxsh = 0; 
    
    // 2. 获取第一个孩子
    EBNode* p = t->eson; 
    
    // 3. 遍历由 eson 开始的“兄弟链表”
    // 这个循环实际上是在遍历普通树中 t 的所有孩子节点
    while (p != NULL) {
        int sh = Height2(p);       // 递归求这个孩子子树的高度
        maxsh = max(maxsh, sh);   // 找出最高的子树
        p = p->brother;           // 移动到下一个兄弟（即普通树中的下一个孩子）
    }
    
    // 4. 最终高度 = 最高子树高度 + 1
    return maxsh + 1;
}

int main()
{
    vector<PNode> t;
    return 0;
}