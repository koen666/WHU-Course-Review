#include<iostream>
using namespace std;

//并查集通常使用**数组（森林的双亲表示法）**来实现

const int MAXN = 1005; 
int parent[MAXN]; // 存储每个结点的父结点
int rnk[MAXN];    // 存储结点的秩（近似树的高度），用于优化合并

void Init(int n) {
    for (int i = 1; i <= n; i++) {
        parent[i] = i; // 自己是自己的老板
        rnk[i] = 0;    // 初始高度为0
    }
}

int Find(int x) {
    if (x != parent[x]) {
        // 递归找根，并把沿途所有结点的父指针直接改为根结点
        parent[x] = Find(parent[x]); 
    }
    return parent[x];
}

void Union(int x, int y) {
    int rx = Find(x); // 找 x 的根
    int ry = Find(y); // 找 y 的根
    
    if (rx == ry) return; // 已经是同一家了

    // 谁高谁做父结点
    if (rnk[rx] < rnk[ry]) {
        parent[rx] = ry;  // rx 矮，挂在 ry 下面，总高度不变
    } else {
        if (rnk[rx] == rnk[ry]) {
            rnk[rx]++;    // 高度相同，合并后 rx 高度加 1
        }
        parent[ry] = rx;  // ry 挂在 rx 下面
    }
}

int main() {
    int n, m;
    while (scanf("%d", &n) != EOF && n != 0) {
        scanf("%d", &m);
        Init(n); // 初始化

        for (int i = 1; i <= m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            Union(a, b); // 有路就合并
        }

        int ans = 0;
        for (int i = 1; i <= n; i++) {
            // 统计有多少个根结点（即有多少个连通块）
            if (parent[i] == i) {
                ans++;
            }
        }
        // 需要修的路 = 连通块数量 - 1
        printf("%d\n", ans - 1);
    }
    return 0;
}