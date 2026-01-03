#include<iostream>
#include<vector>
using namespace std;

//二叉排序树(BST)
struct BSTNode
{
    int data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(int val) : data(val), left(NULL), right(NULL) {}
};

BSTNode *search(BSTNode* root, int k)
{
    if (root == NULL || root->data == k)
    {
        return root;
    }
    else if (k < root->data)
    {
        return search(root->left, k);
    }
    else
    {
        return search(root->right, k);
    }
}

BSTNode* insert(BSTNode* root, int val)
{
    if (root == NULL)
    {
        return new BSTNode(val);
    }
    if (val < root->data)
    {
        root->left = insert(root->left, val);
    }
    else if (val > root->data)
    {
        root->right = insert(root->right, val);
    }
    return root;
}

/*
删除节点时需要考虑三种情况：
   a. 被删除节点是叶子节点，直接删除即可。
   b. 被删除节点只有一个子节点，用子节点替代被删除节点。
   c. 被删除节点有两个子节点，找到其右子树的最小节点（或左子树的最大节点）替代被删除节点，然后删除该最小节点（或最大节点）。
*/

bool deleteNode(BSTNode*& root, int key)
{
    if (root == NULL)
    {
        return false;
    }
    if (key < root->data)
    {
        return deleteNode(root->left, key);
    }
    else if (key > root->data)
    {
        return deleteNode(root->right, key);
    }
    else
    {
        if (root->left == NULL)
        {
            BSTNode* temp = root;
            root = root->right;
            delete temp;
        }
        else if (root->right == NULL)
        {
            BSTNode* temp = root;
            root = root->left;
            delete temp;
        }
        else
        {
            BSTNode* successor = root->right;//找到右子树的最小节点
            while (successor->left != NULL)
            {
                successor = successor->left;
            }
            root->data = successor->data;
            deleteNode(root->right, successor->data);
        }
        return true;
    }
}

//平衡二叉树(AVL树)

struct AVLNode
{
    int data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int val) : data(val), left(NULL), right(NULL), height(1) {}
};

int getHeight(AVLNode* node)
{
    return node ? node->height : 0;
}




int main()
{
    vector<int> nums={3,1,4,1,5,9,2,6,5,3,5};
    int n=nums.size();
    return 0;
}