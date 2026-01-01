#include<iostream>
#include<vector>
#include<string>
#include<stack>
using namespace std;

struct BTNode {
    char data;              // 数据域
    BTNode* lchild;         // 左孩子指针
    BTNode* rchild;         // 右孩子指针

    // 构造函数：初始化为空
    BTNode() : lchild(NULL), rchild(NULL) {}
    
    // 重载构造函数：初始化数据
    BTNode(char d) {
        data = d;
        lchild = rchild = NULL;
    }
};

class BTree{
    BTNode* root;
public:
    BTree() { root = NULL; };
    void CreateBTree(string str) {
        stack<BTNode*> st;      // 定义栈
        BTNode* p;              // 临时节点指针
        bool flag;              // true处理左孩子，false处理右孩子
        int i = 0;
        
        while (i < str.length()) {
            switch (str[i]) {
                case '(':       // 刚创建的结点有孩子，进栈
                    st.push(p);
                    flag = true;
                    break;
                case ')':       // 栈顶结点的子树处理完，出栈
                    st.pop();
                    break;
                case ',':       // 开始处理右孩子
                    flag = false;
                    break;
                default:        // 遇到数据字符
                    p = new BTNode(str[i]); // 创建新结点
                    if (root == NULL)          // 若根为空，设为根
                        root = p;
                    else {                  // 否则链入栈顶结点
                        if (flag && !st.empty())
                            st.top()->lchild = p;
                        else if (!st.empty())
                            st.top()->rchild = p;
                    }
                    break;
            }
            i++;
        }
    }
    // 公有接口
    void DispBTree() {
        DispBTree1(root);
    }

    // 内部递归函数
    void DispBTree1(BTNode* b) {
        if (b != NULL) {
            cout << b->data; // 输出根结点值
            
            // 如果有孩子，开始构造括号
            if (b->lchild != NULL || b->rchild != NULL) {
                cout << "(";
                DispBTree1(b->lchild); // 递归输出左子树
                
                if (b->rchild != NULL) // 有右孩子才输出逗号
                    cout << ",";
                    
                DispBTree1(b->rchild); // 递归输出右子树
                cout << ")";
            }
        }
    }
        // 公有接口
    BTNode* FindNode(char x) {
        return FindNode1(root, x);
    }

    // 内部递归函数
    BTNode* FindNode1(BTNode* b, char x) {
        if (b == NULL) return NULL;
        
        if (b->data == x) return b; // 找到返回当前结点
        
        // 先在左子树找
        BTNode* p = FindNode1(b->lchild, x);
        if (p != NULL) return p;
        
        // 左子树没找到，去右子树找
        return FindNode1(b->rchild, x);
    }
        // 公有接口
    int Height() {
        return Height1(root);
    }

    // 内部递归函数
    int Height1(BTNode* b) {
        if (b == NULL) 
            return 0; // 递归出口
        else 
            // 左、右子树中较大的高度加1
            return max(Height1(b->lchild), Height1(b->rchild)) + 1;
    }
};

