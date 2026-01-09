#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

const int MAXSIZE = 100;

// 迷宫：0表示通，1表示墙
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
    Box* pre; // 记录前驱方块地址，用于回溯路径 [cite: 969, 976]
    Box(int x, int y) {
        i = x; j = y;
        pre = nullptr;
    }
};

// 循环队列实现 [cite: 317, 391]
template<typename T>
class Queue {
public:
    int front, rear;
    T* data;
    Queue(int maxsize) {
        data = new T[maxsize];
        front = rear = 0;
    }
    bool push(T x) {
        if ((rear + 1) % MAXSIZE == front) return false; // 队满条件 [cite: 393]
        data[rear] = x;
        rear = (rear + 1) % MAXSIZE;
        return true;
    }
    T pop() {
        if (front == rear) return nullptr;
        T x = data[front];
        front = (front + 1) % MAXSIZE;
        return x;
    }
    bool empty() { return front == rear; } // 队空条件 [cite: 392]
};

// 辅助函数：输出路径 [cite: 1058, 1072]
void printPath(Box* b) {
    vector<pair<int, int>> path;
    while (b != nullptr) {
        path.push_back({ b->i, b->j });
        b = b->pre; // 通过pre指针向入口方向回溯 [cite: 1066]
    }
    reverse(path.begin(), path.end()); // 反向输出 [cite: 1072]
    cout << "找到迷宫路径: ";
    for (auto p : path) cout << "[" << p.first << "," << p.second << "] ";
    cout << endl;
}

bool mgpath(int xi, int yi, int xe, int ye) {
    bool visited[5][5] = { false };
    Queue<Box*> q(MAXSIZE);

    Box* start = new Box(xi, yi);
    q.push(start);
    visited[xi][yi] = true;

    while (!q.empty()) {
        Box* b = q.pop(); // 取出当前方块 [cite: 1020, 1031]

        // 检查是否到达出口 
        if (b->i == xe && b->j == ye) {
            printPath(b);
            return true;
        }

        // 尝试4个方向 [cite: 1038]
        for (int k = 0; k < 4; k++) {
            int next_i = b->i + dir[k][0];
            int next_j = b->j + dir[k][1];

            // 判断边界、是否为墙、是否已访问 [cite: 1042, 1043]
            if (next_i >= 0 && next_i < 5 && next_j >= 0 && next_j < 5 &&
                maze[next_i][next_j] == 0 && !visited[next_i][next_j]) {
                
                Box* next_box = new Box(next_i, next_j);
                next_box->pre = b; // 记录前驱，建立路径链 [cite: 1046, 1057]
                q.push(next_box);
                visited[next_i][next_j] = true; // 标记已访问 [cite: 1049, 1050]
            }
        }
    }
    cout << "无路可通" << endl;
    return false;
}

int main() {
    mgpath(0, 0, 4, 4);
    return 0;
}