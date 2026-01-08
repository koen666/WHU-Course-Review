#include <iostream>
using namespace std;

struct ThreadNode {
    char val;
    ThreadNode *left, *right;
    int ltag, rtag; // 0:child, 1:thread

    ThreadNode(char x) : val(x), left(nullptr), right(nullptr), ltag(0), rtag(0) {}
};

class ThreadedTree {
public:
    ThreadNode* root;
    ThreadNode* pre; // 辅助线索化的指针

    ThreadedTree() : root(nullptr), pre(nullptr) {}

    // 简单构建一个树用于测试: 
    //      A
    //     / \
    //    B   C
    //     \
    //      D
    // 中序应该为: B D A C
    void createSampleTree() {
        root = new ThreadNode('A');
        root->left = new ThreadNode('B');
        root->right = new ThreadNode('C');
        root->left->right = new ThreadNode('D');
    }

    // 核心：中序线索化函数
    void _InThreading(ThreadNode* p) {
        if (p == nullptr) return;

        // 1. 左
        _InThreading(p->left);

        // 2. 根（处理线索）->更新当前p的前驱和pre的后继
        if (p->left == nullptr) {
            p->ltag = 1;
            p->left = pre;
        }
        if (pre != nullptr && pre->right == nullptr) {
            pre->rtag = 1;
            pre->right = p;
        }
        pre = p; // 更新 pre

        // 3. 右
        _InThreading(p->right);
    }

    void PreThreading(ThreadNode* p) 
    {
        if (p == nullptr) return;

        // ============ 1. 处理根节点 (建立线索) ============
        // A. 处理 p 的左指针 (前驱)
        if (p->left == nullptr) {
            p->ltag = 1;
            p->left = pre; 
        }
        
        // B. 处理 pre 的右指针 (后继)
        if (pre != nullptr && pre->right == nullptr) {
            pre->rtag = 1;
            pre->right = p;
        }
        
        pre = p; // 更新 pre

        // ============ 2. 递归左子树 (注意陷阱) ============
        // 【关键】必须判断 ltag == 0，否则会顺着刚才建立的左线索跑回 pre 去
        if (p->ltag == 0) {
            PreThreading(p->left);
        }

        // ============ 3. 递归右子树 ============
        PreThreading(p->right);
    }


    void PostThreading(ThreadNode* p) 
    {
        if (p == nullptr) return;

        // ============ 1. 递归左子树 ============
        // 后序是左右根，所以先递归，不需要像前序那样判 ltag
        PostThreading(p->left);

        // ============ 2. 递归右子树 ============
        PostThreading(p->right);

        // ============ 3. 处理根节点 (建立线索) ============
        // 逻辑与中序、前序完全一样
        
        // A. 处理 p 的左指针
        if (p->left == nullptr) {
            p->ltag = 1;
            p->left = pre;
        }

        // B. 处理 pre 的右指针
        if (pre != nullptr && pre->right == nullptr) {
            pre->rtag = 1;
            pre->right = p;
        }

        pre = p; // 更新 pre
    }

    // 对外接口：执行线索化
    void CreateInThread() {
        pre = nullptr;
        if (root != nullptr) {
            _InThreading(root);
            
            // 【注意】处理最后一个节点的右线索
            // 中序遍历的最后一个节点，其右指针原本就是空，
            // 循环结束时 pre 指向最后一个节点，将其 rtag 设为 1，right 设为 nullptr
            if (pre->right == nullptr) {
                pre->rtag = 1;
                pre->right = nullptr;
            }
        }
    }

    // 寻找以 p 为根的子树中，中序遍历的第一个节点
    ThreadNode* FirstNode(ThreadNode* p) {
        while (p->ltag == 0) {
            p = p->left;
        }
        return p;
    }

    // 寻找 p 的后继节点
    ThreadNode* NextNode(ThreadNode* p) {
        if (p->rtag == 0) return FirstNode(p->right);
        else return p->right;
    }

    // 遍历
    void InOrderTraverse() {
        if (root == nullptr) return;
        for (ThreadNode* p = FirstNode(root); p != nullptr; p = NextNode(p)) {
            cout << p->val << " ";
        }
        cout << endl;
    }
};

int main() {
    ThreadedTree t;
    t.createSampleTree();
    
    // 线索化
    t.CreateInThread();

    // 遍历
    cout << "中序线索二叉树遍历结果: ";
    t.InOrderTraverse(); // 预期输出: B D A C

    return 0;
}