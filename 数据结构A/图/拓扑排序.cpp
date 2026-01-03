#include<iostream>
#include<stack>
using namespace std;

const int MAXV = 100; 

//这是单链表中的节点，表示一条边
struct ArcNode
{
    int adjvex;
    int weight;
    ArcNode* nextarc;
};


//这是数组中的元素，表示图中的一个顶点
struct HNode
{
    string info;      // 顶点信息
    ArcNode* firstarc; // 指向第一条依附该顶点的边
};

class AdjGraph
{
public:
    HNode adjlist[MAXV]; // 头结点数组
    int n, e;

    AdjGraph() {
        for (int i = 0; i < MAXV; i++)
            adjlist[i].firstarc = NULL;
    }
    ~AdjGraph();       
    
    // 核心操作
    void CreateAdjGraph(int a[][MAXV], int n, int e);
    void DispAdjGraph();
};

void TopSort(AdjGraph& g)
{
    int indegree[MAXV]; // 存储各顶点的入度
    stack<int> S;       // 辅助栈

    // 1. 计算每个顶点的入度
    for (int i = 0; i < g.n; i++)
        indegree[i] = 0; // 初始化入度为0

    for (int i = 0; i < g.n; i++)
    {
        ArcNode* p = g.adjlist[i].firstarc;
        while (p != NULL)
        {
            indegree[p->adjvex]++; // 邻接点入度加1
            p = p->nextarc;
        }
    }

    // 2. 将所有入度为0的顶点入栈
    for (int i = 0; i < g.n; i++)
    {
        if (indegree[i] == 0)
            S.push(i);
    }

    // 3. 主循环
    while (!S.empty())
    {
        int v = S.top();
        S.pop();
        cout << g.adjlist[v].info << " "; // 输出拓扑序列中的顶点

        // 遍历v的所有邻接点，更新入度
        ArcNode* p = g.adjlist[v].firstarc;
        while (p != NULL)
        {
            indegree[p->adjvex]--;
            if (indegree[p->adjvex] == 0)
                S.push(p->adjvex);
            p = p->nextarc;
        }
    }
}