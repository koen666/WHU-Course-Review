#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 全局变量方便访问
vector<vector<int>> adj;
vector<bool> visited;
int n, m;

/**
 * DFS 判环核心函数
 * @param u 当前节点
 * @param p 父节点 (parent)，即你是从哪个节点走过来的
 * @return true 发现环, false 没发现
 */
bool dfs(int u, int p) {
    visited[u] = true;

    for (int v : adj[u]) {
        // 1. 如果邻居是父节点，说明是回头路，忽略
        if (v == p) continue;

        // 2. 如果邻居已经被访问过，且不是父节点 -> 发现环！
        if (visited[v]) {
            return true;
        }

        // 3. 如果没访问过，继续深搜
        // 如果深层递归发现了环，层层返回 true
        if (dfs(v, u)) {
            return true;
        }
    }
    return false;
}

/**
 * BFS 判环核心函数
 * @param start 起始节点
 * @return true 发现环, false 没发现
 */
bool bfs(int start) {
    // 队列存储 {当前节点, 父节点}
    queue<pair<int, int>> q;
    
    q.push({start, -1}); // 起点入队，父节点设为 -1
    visited[start] = true;

    while (!q.empty()) {
        int u = q.front().first;
        int p = q.front().second;
        q.pop();

        for (int v : adj[u]) {
            // 1. 如果邻居是父节点，跳过
            if (v == p) continue;

            // 2. 如果邻居已访问，说明有多条路通向 v -> 发现环
            if (visited[v]) {
                return true;
            }

            // 3. 未访问，标记并入队
            visited[v] = true;
            q.push({v, u}); // 这里的 u 变成了 v 的父节点
        }
    }
    return false; // 跑完连通分量都没发现环
}

int main() {

    if (!(cin >> n >> m)) return 0;

    adj.assign(n, vector<int>());
    visited.assign(n, false);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        // 转换为 0-based 索引
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u); // 无向图双向加边
    }

    bool hasCycle = false;

    // 处理非连通图：需要遍历每一个节点
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            // -1 表示起点没有父节点
            if (dfs(i, -1)) {
                hasCycle = true;
                break;
            }
        }
    }

    if (hasCycle) cout << "Yes" << endl;
    else cout << "No" << endl;

    return 0;
}