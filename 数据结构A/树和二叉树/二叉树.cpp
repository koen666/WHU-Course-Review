#include <iostream>
#include <string>
#include <stack>

using namespace std;

// 节点结构体
struct Node {
    char val;
    Node* left;
    Node* right;
    Node(char x) : val(x), left(nullptr), right(nullptr) {}
};

class Tree {
private:
    Node* root;

    // 递归销毁树（用于删除功能）
    void destroy(Node*& t) {
        if (!t) return;
        destroy(t->left);
        destroy(t->right);
        delete t;
        t = nullptr;
    }

    // 递归查找节点
    Node* findNode(Node* t, char target) {
        if (!t) return nullptr;
        if (t->val == target) return t;
        
        Node* l = findNode(t->left, target);
        if (l) return l;
        
        return findNode(t->right, target);
    }

    // 递归获取父节点（用于删除功能）
    Node* findParent(Node* t, Node* child) {
        if (!t || !child || t == child) return nullptr;
        if (t->left == child || t->right == child) return t;
        
        Node* l = findParent(t->left, child);
        if (l) return l;
        return findParent(t->right, child);
    }

    // 递归输出括号表示法
    void dispTree(Node* t) {
        if (!t) return;
        cout << t->val;
        if (t->left || t->right) {
            cout << "(";
            if (t->left) dispTree(t->left);
            if (t->right) {
                cout << ",";
                dispTree(t->right);
            }
            cout << ")";
        }
    }

public:
    Tree() : root(nullptr) {}

    // 1. 【构建】利用括号法字符串建立二叉树
    void createFromBracket(string s) {
        // 先清空旧树
        destroy(root);
        
        stack<Node*> st;
        Node* p = nullptr; // 当前新建立的节点
        int k = 0; // 1代表处理左孩子，2代表处理右孩子
        
        for (int i = 0; i < s.length(); i++) {
            char c = s[i];
            
            if (c == '(') {
                st.push(p); // 刚才那个节点变成了父节点，入栈
                k = 1;      // 接下来是左孩子
            } else if (c == ')') {
                st.pop();   // 父节点处理完毕，出栈
            } else if (c == ',') {
                k = 2;      // 接下来是右孩子
            } else {
                // 是字母，创建节点
                p = new Node(c);
                if (root == nullptr) {
                    root = p; // 第一个字符是根
                } else {
                    // 根据 k 的值挂在栈顶父节点下面
                    Node* parent = st.top();
                    if (k == 1) parent->left = p;
                    else if (k == 2) parent->right = p;
                }
            }
        }
    }

    // 2. 【查】查找节点是否存在
    Node* search(char val) {
        return findNode(root, val);
    }

    // 3. 【改】修改节点的值
    bool modify(char oldVal, char newVal) {
        Node* target = findNode(root, oldVal);
        if (target) {
            target->val = newVal;
            return true;
        }
        return false;
    }

    // 4. 【增】在指定节点下插入子节点
    // parentVal: 在谁下面插
    // childVal: 插入的值
    // isLeft: true插左边，false插右边
    bool insert(char parentVal, char childVal, bool isLeft) {
        Node* p = findNode(root, parentVal);
        if (!p) return false; // 父节点不存在

        if (isLeft) {
            if (p->left != nullptr) return false; // 左边已经有人了，插入失败
            p->left = new Node(childVal);
        } else {
            if (p->right != nullptr) return false; // 右边已经有人了
            p->right = new Node(childVal);
        }
        return true;
    }

    // 5. 【删】删除指定节点及其子树
    bool remove(char val) {
        if (!root) return false;
        
        // 如果删的是根节点
        if (root->val == val) {
            destroy(root);
            return true;
        }

        Node* target = findNode(root, val);
        if (!target) return false;

        // 找到父亲，断开连接
        Node* parent = findParent(root, target);
        if (parent->left == target) parent->left = nullptr;
        if (parent->right == target) parent->right = nullptr;

        // 销毁子树
        destroy(target);
        return true;
    }

    // 显示树
    void print() {
        if (!root) cout << "空树";
        else dispTree(root);
        cout << endl;
    }
};

int main() {
    Tree t;
    string input;
    
    // 示例：A(B(D,E),C(F))
    cout << "请输入括号表示法字符串 (如: A(B(D),C) ): ";
    cin >> input;

    // 1. 建树
    t.createFromBracket(input);
    cout << "当前树结构: ";
    t.print();

    // 2. 查找
    char findVal;
    cout << "\n请输入要查找的值: ";
    cin >> findVal;
    if (t.search(findVal)) cout << "找到了!" << endl;
    else cout << "没找到!" << endl;

    // 3. 增加
    char pVal, cVal;
    int lr;
    cout << "\n【增加】输入父节点值，新节点值，位置(1左/0右): ";
    cin >> pVal >> cVal >> lr;
    if (t.insert(pVal, cVal, lr == 1)) {
        cout << "插入成功: ";
        t.print();
    } else {
        cout << "插入失败(父节点不存在或位置已被占用)" << endl;
    }

    // 4. 修改
    char oldV, newV;
    cout << "\n【修改】输入旧值和新值: ";
    cin >> oldV >> newV;
    if (t.modify(oldV, newV)) {
        cout << "修改成功: ";
        t.print();
    } else {
        cout << "修改失败(节点不存在)" << endl;
    }

    // 5. 删除
    char delVal;
    cout << "\n【删除】输入要删除的节点值: ";
    cin >> delVal;
    if (t.remove(delVal)) {
        cout << "删除成功: ";
        t.print();
    } else {
        cout << "删除失败" << endl;
    }

    return 0;
}