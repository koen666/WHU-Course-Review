#include<iostream>
#include<string>
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

// 通过邻接矩阵数组a、顶点数n和边数e来建立邻接表
void AdjGraph::CreateAdjGraph(int a[][MAXV], int n, int e)
{
    ArcNode *p;
    this->n = n; // 置顶点数
    this->e = e; // 置边数

    for (int i = 0; i < n; i++)         // 遍历所有顶点（行）
    {
        for (int j = n - 1; j >= 0; j--) // 遍历所有可能的邻接点（列）
        {
            // 如果存在边（不为0且不为无穷大）
            if (a[i][j] != 0) 
            {
                p = new ArcNode();      // 创建一个边结点
                p->adjvex = j;          // 记录目标顶点下标
                p->weight = a[i][j];    // 记录权值
                
                // 【头插法关键代码】
                p->nextarc = adjlist[i].firstarc; // 新结点的next指向原本的第一个结点
                adjlist[i].firstarc = p;          // 头结点的firstarc指向新结点
            }
        }
    }
}

void AdjGraph::DispAdjGraph()
{
    ArcNode *p;
    for (int i = 0; i < n; i++) // 遍历所有头结点
    {
        cout << "顶点 " << i << ": ";
        p = adjlist[i].firstarc; // p指向该顶点的第一条边
        
        if (p != NULL) cout << "边(目标顶点, 权值):";
        
        while (p != NULL) // 遍历该顶点的单链表
        {
            cout << " (" << p->adjvex << "," << p->weight << ")"; // 打印(目标顶点, 权值)
            p = p->nextarc; // 移向下一条边
        }
        cout << "\n";
    }
}