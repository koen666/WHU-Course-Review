#include<iostream>
using namespace std;

struct Node
{
    char val;
    Node* left;
    Node* right;
    Node(char x) : val(x), left(nullptr), right(nullptr) {}
};

class Tree
{
public:
    Node* root;
    Tree() : root(nullptr) {}

    /* 二叉树构建原理说明：
    * 
    * 无论使用哪种遍历序列组合（前序+中序 或 后序+中序），核心思想相同：
    * 
    * 1. 定位根节点：
    *    - 前序遍历：根节点在序列最前面
    *    - 后序遍历：根节点在序列最后面
    *    - 层序遍历：根节点在序列最前面
    * 
    * 2. 划分左右子树（利用中序遍历）：
    *    - 在中序序列中找到根节点的位置
    *    - 根节点左侧为左子树的中序序列
    *    - 根节点右侧为右子树的中序序列
    * 
    * 3. 计算子树长度：
    *    - 通过中序序列确定左子树节点数量
    *    - 这是切分其他序列的关键依据
    * 
    * 4. 递归构建：
    *    - 根据子树长度切分前序/后序/层序序列
    *    - 分别递归构建左右子树
    */

    // 【核心构建函数】 => 就是拿到左右子树的中序和前序/后序，然后递归构建
    Node* createRecrusive(string level,string medium)
    {
        if(level.length()==0) return nullptr;
        char rootVal=level[0];
        Node* root=new Node(rootVal);
        int index=medium.find(rootVal);
        
        string leftMedium=medium.substr(0,index);
        string rightMedium=medium.substr(index+1);
        string leftLevel="";
        string rightLevel="";

        for(int i=1;i<level.length();i++)
        {
            char c=level[i];
            if(leftMedium.find(c)!=string::npos)
            {
                leftLevel+=c;
            }
            else
            {
                rightLevel+=c;
            }
        }

        root->left=createRecrusive(leftLevel,leftMedium);
        root->right=createRecrusive(rightLevel,rightMedium);

        return root;
    }

    void Create(string level,string medium)
    {
        root=createRecrusive(level,medium);
    }

    void preorder()
    {
        preorderRecursive(root);
    }

    void preorderRecursive(Node* t)
    {
        if (t == nullptr) return;
        cout << t->val << " ";
        preorderRecursive(t->left);
        preorderRecursive(t->right);
    }

    
};

int main()
{
    int n;cin>>n;
    char* level=new char[n];
    char* medium=new char[n];
    for(int i=0;i<n;i++) cin>>level[i];
    for(int i=0;i<n;i++) cin>>medium[i];
    Tree tree;
    tree.Create(string(level,n),string(medium,n));
    tree.preorder();
    return 0;
}