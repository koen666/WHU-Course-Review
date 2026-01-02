#include<iostream>
#include<iomanip>
using namespace std;

const int MAXV = 100;         // 图中允许的最大顶点数 
const int INF = 0x3f3f3f3f;   // 定义无穷大 (用于带权图中表示无连接) 

class MatGraph
{
public:
    int edges[MAXV][MAXV];    // 邻接矩阵数组，存放权值或0/1 
    int n, e;                 // n为顶点数，e为边数 
    string vexs[MAXV];        // 存放顶点信息（如顶点的名称"v0", "v1"等） 
    
    // 成员函数声明
    void CreateMatGraph(int a[][MAXV], int n, int e);
    void DispMatGraph();
};

// 通过数组a、顶点数n和边数e来建立图的邻接矩阵 
void MatGraph::CreateMatGraph(int a[][MAXV], int n, int e)
{
    this->n = n; // 置顶点数 
    this->e = e; // 置边数
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            this->edges[i][j] = a[i][j]; // 将数据复制到内部矩阵中 
        }
    }
}

void MatGraph::DispMatGraph() // 
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (edges[i][j] == INF) // 如果是无穷大，打印特殊符号 
                cout << "  ∞";
            else                    // 否则打印权值 
                cout << setw(4) << edges[i][j];
        }
        cout << endl; // 每打印完一行后换行 
    }
}