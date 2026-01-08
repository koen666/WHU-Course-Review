#include <iostream>
#include <algorithm> // for max

using namespace std;

struct Node {
    int key;
    Node *left;
    Node *right;
    int height;
    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
public:
    Node* root;

    AVLTree() : root(nullptr) {}

    // 获取高度
    int getHeight(Node *N) {
        if (N == nullptr) return 0;
        return N->height;
    }

    // 获取平衡因子
    int getBalance(Node *N) {
        if (N == nullptr) return 0;
        return getHeight(N->left) - getHeight(N->right);
    }

    // 右旋
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    // 左旋
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    // 插入函数
    Node* insert(Node* node, int key) {
        // 1. BST 插入
        if (node == nullptr) return new Node(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else 
            return node;

        // 2. 更新高度
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        // 3. 获取平衡因子
        int balance = getBalance(node);

        // 4. 四种旋转情况
        // LL -> 右旋
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        // RR -> 左旋
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        // LR -> 先左旋子节点，再右旋自己
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RL -> 先右旋子节点，再左旋自己
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // 对外接口
    void add(int key) {
        root = insert(root, key);
    }

    // 前序遍历（根左右）用于验证
    void preOrder(Node *root) {
        if (root != nullptr) {
            cout << root->key << " ";
            preOrder(root->left);
            preOrder(root->right);
        }
    }
};

int main() {
    AVLTree tree;
    
    /* 构造一个极端的输入，如果是普通BST会变成链表
       10 -> 20 -> 30 -> 40 -> 50 -> 25
    */
    tree.add(10);
    tree.add(20);
    tree.add(30);
    tree.add(40);
    tree.add(50);
    tree.add(25);

    /* 构造后的 AVL 树应该是平衡的：
            30
           /  \
         20    40
        /  \     \
      10   25    50
    */

    cout << "前序遍历构建好的AVL树: " << endl;
    tree.preOrder(tree.root);
    cout << endl;
    
    // 验证：输出应该是 30 20 10 25 40 50
    // 说明 30 被自动提到了根节点，树保持了平衡

    return 0;
}