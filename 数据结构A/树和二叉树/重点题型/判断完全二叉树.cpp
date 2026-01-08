#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    // 判断是否为完全二叉树
    bool isCompleteTree(Node* root) {
        if (root == nullptr) return true;

        queue<Node*> q;
        q.push(root);
        
        // 标记：是否已经遇到了空节点
        bool reachNull = false;

        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();

            // 情况 1: 当前节点为空
            if (curr == nullptr) {
                reachNull = true; // 开启“警戒模式”，后面不能再有活人了
            } 
            // 情况 2: 当前节点非空
            else {
                // 如果之前已经遇到过空节点了，现在又冒出来一个非空节点
                // 说明不连续，断定不是完全二叉树
                if (reachNull) {
                    return false;
                }
                
                // 正常的层序遍历入队操作
                // 注意：这里不管孩子是不是空，都push进去
                q.push(curr->left);
                q.push(curr->right);
            }
        }

        return true;
    }
};

// 辅助代码：构建树进行测试
int main() {
    Solution sol;

    /* 测试用例 1: 完全二叉树
            1
           / \
          2   3
         / \
        4   5
    */
    Node* root1 = new Node(1);
    root1->left = new Node(2);
    root1->right = new Node(3);
    root1->left->left = new Node(4);
    root1->left->right = new Node(5);

    cout << "Test 1 (是): " << (sol.isCompleteTree(root1) ? "Yes" : "No") << endl;

    /* 测试用例 2: 非完全二叉树 (中间有空洞)
            1
           / \
          2   3
           \
            5
       (2没有左孩子，却有右孩子5，断层了)
    */
    Node* root2 = new Node(1);
    root2->left = new Node(2);
    root2->right = new Node(3);
    root2->left->right = new Node(5);

    cout << "Test 2 (否): " << (sol.isCompleteTree(root2) ? "Yes" : "No") << endl;

    return 0;
}