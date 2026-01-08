#include <iostream>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int x) : val(x), left(nullptr), right(nullptr) {}
};

class BST {
public:
    Node* root;

    BST() : root(nullptr) {}

    // --- 1. 插入 (Public) ---
    void insert(int val) {
        root = insertRec(root, val);
    }

    // --- 2. 查找 (Public) ---
    bool search(int val) {
        return searchRec(root, val) != nullptr;
    }

    // --- 3. 删除 (Public) ---
    void remove(int val) {
        root = removeRec(root, val);
    }

    // --- 4. 中序遍历 (Public) ---
    void printSorted() {
        inOrderRec(root);
        cout << endl;
    }

private:
    // --- 插入的递归实现 ---
    Node* insertRec(Node* node, int val) {
        // 1. 如果走到空地了，就在这里种树（创建新节点）
        if (node == nullptr) {
            return new Node(val);
        }

        // 2. 比当前节点小，往左走
        if (val < node->val) {
            node->left = insertRec(node->left, val);
        }
        // 3. 比当前节点大，往右走
        else if (val > node->val) {
            node->right = insertRec(node->right, val);
        }
        // 4. 如果相等，通常不处理（不允许重复），直接返回当前节点
        return node;
    }

    // --- 查找的递归实现 ---
    Node* searchRec(Node* node, int val) {
        // 没找到 或 找到了
        if (node == nullptr || node->val == val) {
            return node;
        }
        // 小往左，大往右
        if (val < node->val) return searchRec(node->left, val);
        else return searchRec(node->right, val);
    }

    // --- 遍历的递归实现 (左-根-右) ---
    void inOrderRec(Node* node) {
        if (node != nullptr) {
            inOrderRec(node->left);
            cout << node->val << " ";
            inOrderRec(node->right);
        }
    }

    // --- 辅助函数：找最小节点 (用于删除) ---
    Node* findMin(Node* node) {
        while (node->left != nullptr) node = node->left;
        return node;
    }

    // --- 删除的递归实现 (核心难点) ---
    Node* removeRec(Node* node, int val) {
        if (node == nullptr) return nullptr;

        // 1. 先找到要删除的节点
        if (val < node->val) {
            node->left = removeRec(node->left, val);
        } else if (val > node->val) {
            node->right = removeRec(node->right, val);
        } 
        else {
            // 找到了！准备删除 node
            
            // 情况 A: 没有孩子 (叶子节点) 或 只有右孩子
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp; // 返回右孩子给父节点接上
            }
            // 情况 B: 只有左孩子
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp; // 返回左孩子给父节点接上
            }

            // 情况 C: 有两个孩子 (最麻烦)
            // 策略：找右子树里最小的那个节点(后继)，把它提拔上来替换我
            Node* temp = findMin(node->right);

            // 把它的值复制给我
            node->val = temp->val;

            // 去右子树里，把那个被提拔的替身删掉
            node->right = removeRec(node->right, temp->val);
        }
        return node;
    }
};

int main() {
    BST tree;
    
    // 插入测试
    tree.insert(50);
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(70);
    tree.insert(60);
    tree.insert(80);

    cout << "原始树(中序遍历): ";
    tree.printSorted(); // 应该输出 20 30 40 50 60 70 80

    // 查找测试
    cout << "查找 40: " << (tree.search(40) ? "存在" : "不存在") << endl;
    cout << "查找 90: " << (tree.search(90) ? "存在" : "不存在") << endl;

    // 删除测试
    cout << "\n删除 20 (叶子节点)..." << endl;
    tree.remove(20);
    tree.printSorted();

    cout << "删除 30 (只有一个孩子 40)..." << endl;
    tree.remove(30);
    tree.printSorted();

    cout << "删除 50 (有两个孩子，根节点)..." << endl;
    tree.remove(50);
    tree.printSorted(); // 根节点应该变成 60 (右子树最小)

    return 0;
}