#include <iostream>
#include <vector>
using namespace std;

// 1. 定义邻接表的结构
struct ArcNode
{
    int adjvex;       // 指向的顶点编号
    ArcNode* next;    // 指向下一条边的指针
    ArcNode(int v) : adjvex(v), next(nullptr) {} 
};

struct Hnode
{
    ArcNode* firstarc; // 链表头指针
    Hnode() : firstarc(nullptr) {}
};

class Graph {
public:
    int V; // 顶点数
    vector<Hnode> adjList; // 邻接表数组
    vector<bool> visited;  // 记录是否访问过

    Graph(int n) {
        V = n;
        adjList.resize(n);
        visited.resize(n, false);
    }

    // 2. 建图函数：头插法插入边
    void addEdge(int u, int v) {
        // 因为是无向图，所以要存两次
        // 存 u -> v
        ArcNode* newNode1 = new ArcNode(v);
        newNode1->next = adjList[u].firstarc;
        adjList[u].firstarc = newNode1;

        // 存 v -> u
        ArcNode* newNode2 = new ArcNode(u);
        newNode2->next = adjList[v].firstarc;
        adjList[v].firstarc = newNode2;
    }

    // 3. 深度优先搜索 (DFS)
    void DFS(int u) {
        visited[u] = true; // 标记当前节点已访问
        
        // 遍历该节点的所有邻居
        ArcNode* p = adjList[u].firstarc;
        while (p != nullptr) {
            int neighbor = p->adjvex;
            if (!visited[neighbor]) { // 如果邻居没访问过，这就去访问它
                DFS(neighbor);
            }
            p = p->next;
        }
    }

    // 4. 计算连通分量
    int countComponents() {
        int count = 0;
        for (int i = 0; i < V; i++) {
            // 如果节点 i 还没被访问过，说明找到了一个新的连通分量
            if (!visited[i]) {
                count++;  // 计数器加1
                DFS(i);   // 把和 i 连通的所有人都标记上，防止重复计算
            }
        }
        return count;
    }
};

int main()
{
    // 优化 cin 输出速度，防止超时
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m; // n是顶点数，m是边数
    if (!(cin >> n >> m)) return 0;

    Graph g(n);

    for(int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v); // 真正建立邻接表
    }

    cout << g.countComponents() << endl;

    return 0;
}