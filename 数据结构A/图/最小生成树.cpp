#include<iostream>
#include<vector>
#include<algorithm>
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

// 普里姆算法输出最小生成树
void Prim(MatGraph g, int v)
{ 
    int lowcost[MAXV];    // 建立数组lowcost，记录V-U中各顶点到U的最小边权值 
    int closest[MAXV];    // 建立数组closest，记录该最小边在U中的顶点 
    int min, k;

    // --- 初始化阶段 --- ]
    for (int i = 0; i < g.n; i++) 
    {
        lowcost[i] = g.edges[v][i]; // 给lowcost[]置初值，即起点v到各顶点的边权 
        closest[i] = v;             // 给closest[]置初值，初始所有候选边的端点均为v 
    }
    lowcost[v] = 0;                 // U = {v}，lowcost[i]=0表示顶点i已加入U集合 

    // --- 构造阶段：循环找出剩余的n-1个顶点 --- 
    for (int i = 1; i < g.n; i++) 
    { 
        min = INF; // mindis置最小距离初值 
        k = -1;    // k记录最近顶点的编号 

        // 1. 在 (V-U) 中找出离 U 最近的顶点 k 
        for (int j = 0; j < g.n; j++) 
        {
            if (lowcost[j] != 0 && lowcost[j] < min) 
            { 
                min = lowcost[j];
                k = j;
            }
        }

        // 2. 输出选取的最小边及其权值 
        cout << "边(" << closest[k] << "," << k << "),权为" << min << endl;
        
        // 3. 标记顶点k已经加入U 
        lowcost[k] = 0; 

        // 4. 修改数组lowcost和closest（调整候选边） 
        for (int j = 0; j < g.n; j++) 
        {
            // 若 (k,j) 的权值小于原来顶点 j 到 U 的候选边权值，则进行更新 
            if (lowcost[j] != 0 && g.edges[k][j] < lowcost[j]) 
            {
                lowcost[j] = g.edges[k][j]; // 修改最小边权值 
                closest[j] = k;             // 修改最近顶点编号 
            }
        }
    }
}

// 1. 定义边向量元素类型 
struct Edge {
    int u;      // 边的起始顶点 
    int v;      // 边的终止顶点 
    int w;      // 边的权值 

    Edge(int u, int v, int w) : u(u), v(v), w(w) {} // 构造函数 

    // 重载 < 运算符，用于按权值 w 递增排序 
    bool operator<(const Edge& s) const {
        return w < s.w;
    }
};

// --- 并查集相关全局变量及函数 ---
int parent[MAXV]; // 并查集存储结构 
int rnk[MAXV];    // 存储结点的秩 

// 并查集初始化 
void Init(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i; // 初始时每个顶点自成一个集合 
        rnk[i] = 0;    // 秩初始化为0 
    }
}

// 并查集查找根节点（Find） 
int Find(int i) {
    if (parent[i] == i) return i;
    return parent[i] = Find(parent[i]); // 路径压缩优化
}

// 并查集合并（Union） 
void Union(int i, int j) {
    int root1 = Find(i);
    int root2 = Find(j);
    if (root1 != root2) {
        if (rnk[root1] < rnk[root2]) parent[root1] = root2;
        else if (rnk[root1] > rnk[root2]) parent[root2] = root1;
        else {
            parent[root2] = root1;
            rnk[root1]++;
        }
    }
}

// --- Kruskal 算法主函数 ---
void Kruskal(MatGraph& g) {
    vector<Edge> E; // 建立存放所有边的向量 E 

    // 2. 从邻接矩阵中获取所有边并存入 E 
    for (int i = 0; i < g.n; i++) {
        for (int j = i + 1; j < g.n; j++) { // 仅取上三角，避免无向图重复选边 
            if (g.edges[i][j] != 0 && g.edges[i][j] != INF) {
                E.push_back(Edge(i, j, g.edges[i][j])); 
            }
        }
    }

    // 3. 对边按权值递增排序 
    sort(E.begin(), E.end());

    // 4. 并查集初始化 
    Init(g.n);

    int k = 1; // k表示当前已选中的生成树边数 
    int j = 0; // E中边的下标 
    // 5. 循环直到生成 n-1 条边 
    while (k < g.n) {
        int u1 = E[j].u;
        int v1 = E[j].v;

        // 获取两个顶点所属的集合根节点编号 
        int sn1 = Find(u1);
        int sn2 = Find(v1);

        // 如果两个顶点不在同一个集合，说明不形成回路 
        if (sn1 != sn2) {
            cout << "边(" << u1 << "," << v1 << "),权为" << E[j].w << endl; 
            k++;              
            Union(sn1, sn2);  
        }
        j++; // 扫描下一条边 
    }
}

int main()
{
    return 0;
}