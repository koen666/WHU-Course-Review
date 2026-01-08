#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 哈夫曼树节点结构
struct HTNode {
    int weight;
    int parent;
    int lchild;
    int rchild;
};

class HuffmanTree {
public:
    vector<HTNode> HT;
    int leafNum; // 叶子节点数量

    // --- 辅助函数：Select ---
    // 在 1 到 n 范围内，找到两个 parent 为 0 且权值最小的节点下标
    // 通过引用 s1, s2 返回
    void Select(int n, int& s1, int& s2) {
        int min1 = 1e9; // 最小值
        int min2 = 1e9; // 次小值
        s1 = -1;
        s2 = -1;

        // 第一次遍历：找最小的 s1
        for (int i = 1; i <= n; i++) {
            if (HT[i].parent == 0 && HT[i].weight < min1) {
                min1 = HT[i].weight;
                s1 = i;
            }
        }

        // 第二次遍历：找次小的 s2 (不能是 s1)
        for (int i = 1; i <= n; i++) {
            if (HT[i].parent == 0 && i != s1 && HT[i].weight < min2) {
                min2 = HT[i].weight;
                s2 = i;
            }
        }
    }

    // --- 1. 构建哈夫曼树 ---
    void CreateHuffman(vector<int>& weights) {
        leafNum = weights.size();
        int totalNodes = 2 * leafNum - 1;
        
        // 初始化数组，下标从1开始，所以大小设为 totalNodes + 1
        HT.resize(totalNodes + 1);

        // 1. 初始化叶子节点
        for (int i = 0; i < leafNum; i++) {
            HT[i + 1].weight = weights[i];
            HT[i + 1].parent = 0;
            HT[i + 1].lchild = 0;
            HT[i + 1].rchild = 0;
        }
        // 初始化非叶子节点部分
        for (int i = leafNum + 1; i <= totalNodes; i++) {
            HT[i].weight = 0;
            HT[i].parent = 0;
            HT[i].lchild = 0;
            HT[i].rchild = 0;
        }

        // 2. 循环 n-1 次进行合并
        for (int i = leafNum + 1; i <= totalNodes; i++) {
            int s1, s2;
            // 在范围 1 到 i-1 中找两个最小的孤儿
            Select(i - 1, s1, s2);

            // 建立新关系
            HT[s1].parent = i;
            HT[s2].parent = i;
            
            HT[i].lchild = s1;
            HT[i].rchild = s2;
            HT[i].weight = HT[s1].weight + HT[s2].weight;
            
            // 调试输出（可选）
            // cout << "合并: " << HT[s1].weight << " 和 " << HT[s2].weight 
            //      << " -> 新节点: " << HT[i].weight << endl;
        }
    }

    // --- 2. 生成编码 ---
    void PrintCodes() {
        // 遍历所有叶子节点 (1 到 leafNum)
        for (int i = 1; i <= leafNum; i++) {
            string code = "";
            int curr = i;
            int f = HT[curr].parent;

            // 从叶子一直往上找，直到根节点 (parent == 0)
            while (f != 0) {
                // 如果我是父节点的左孩子 -> '0'
                if (HT[f].lchild == curr) {
                    code += '0';
                }
                // 如果我是父节点的右孩子 -> '1'
                else {
                    code += '1';
                }
                // 继续往上爬
                curr = f;
                f = HT[curr].parent;
            }

            // 因为是从下往上生成的，所以要反转
            reverse(code.begin(), code.end());
            
            cout << "权值 " << HT[i].weight << " 的编码: " << code << endl;
        }
    }
};

int main() {
    int n;
    cout << "请输入叶子节点数量: ";
    cin >> n;

    vector<int> weights(n);
    cout << "请输入 " << n << " 个权值: ";
    for (int i = 0; i < n; i++) {
        cin >> weights[i];
    }

    HuffmanTree huff;
    huff.CreateHuffman(weights);
    huff.PrintCodes();

    return 0;
}