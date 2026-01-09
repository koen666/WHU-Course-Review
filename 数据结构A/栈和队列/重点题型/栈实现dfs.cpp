#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXSIZE = 100;

// 迷宫地图：0表示通，1表示墙 [cite: 933, 934]
int maze[5][5] = {
    {0, 1, 0, 0, 0},
    {0, 1, 0, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 1, 1, 0, 0},
    {0, 0, 0, 1, 0}
};

// 方向数组：上、下、左、右 [cite: 947, 949]
int dir[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };

struct Box {
    int i, j;
    Box* pre; // 记录前驱方块地址，用于回溯路径 [cite: 954, 969]
    Box(int x, int y) : i(x), j(y), pre(nullptr) {}
};

// 仿照你的代码实现一个栈类
template<typename T>
class Stack {
public:
    int top; // 栈顶指针
    T* data;
    int maxSize;

    Stack(int size) {
        maxSize = size;
        data = new T[maxSize];
        top = -1; // 初始化栈顶指针为-1
    }

    ~Stack() {
        delete[] data;
    }

    // 进栈
    bool push(T x) {
        if (top == maxSize - 1) return false; // 栈满
        data[++top] = x;
        return true;
    }

    // 出栈
    T pop() {
        if (empty()) return nullptr;
        return data[top--];
    }

    // 获取栈顶元素但不弹出
    T getTop() {
        if (empty()) return nullptr;
        return data[top];
    }

    bool empty() {
        return top == -1;
    }
};

// 输出路径函数
void printPath(Box* b) {
    vector<pair<int, int>> path;
    while (b != nullptr) {
        path.push_back({ b->i, b->j });
        b = b->pre; // 通过pre指针向入口方向追溯 [cite: 955, 966]
    }
    reverse(path.begin(), path.end()); // 追溯结果是反的，需要翻转
    cout << "DFS 找到的迷宫路径: ";
    for (auto p : path) cout << "[" << p.first << "," << p.second << "] ";
    cout << endl;
}

// DFS 路径搜索实现
bool mgpath(int xi, int yi, int xe, int ye) {
    bool visited[5][5] = { false };
    Stack<Box*> s(MAXSIZE); // 定义一个辅助栈 

    Box* start = new Box(xi, yi);
    s.push(start);
    visited[xi][yi] = true;

    while (!s.empty()) {
        Box* b = s.getTop(); // 注意：DFS通常先看栈顶而不急着弹出

        // 检查是否到达出口 
        if (b->i == xe && b->j == ye) {
            printPath(b);
            return true;
        }

        bool found = false;
        // 尝试4个方向搜索相邻方块 [cite: 953]
        for (int k = 0; k < 4; k++) {
            int next_i = b->i + dir[k][0];
            int next_j = b->j + dir[k][1];

            if (next_i >= 0 && next_i < 5 && next_j >= 0 && next_j < 5 &&
                maze[next_i][next_j] == 0 && !visited[next_i][next_j]) {
                
                Box* next_box = new Box(next_i, next_j);
                next_box->pre = b; // 记录前驱 [cite: 957]
                s.push(next_box);  // 发现新路，入栈
                visited[next_i][next_j] = true;
                found = true;
                break; // 只要找到一个方向可走，就立即深入，不再看其他方向
            }
        }

        // 如果四个方向都走不通，说明该点是死胡同，回溯（弹出）
        if (!found) {
            s.pop();
        }
    }
    cout << "DFS 未能找到路径" << endl;
    return false;
}

int main() {
    mgpath(0, 0, 4, 4);
    return 0;
}