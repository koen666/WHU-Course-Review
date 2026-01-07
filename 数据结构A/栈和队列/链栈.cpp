#include<iostream>
using namespace std;

template <typename T>
struct LinkNode {
    T data;             // 数据域 
    LinkNode* next;     // 指针域 
    LinkNode(): next(NULL) {} // 构造函数 
    LinkNode(T d): data(d), next(NULL) {} // 重载构造函数 
};

template <typename T>
class LinkStack
{
public:
    LinkNode<T>* top; // 栈顶指针 
    LinkStack() // 构造函数 
    {
        top = new LinkNode<T>(); // 创建头结点 
    }
    ~LinkStack() // 析构函数 
    {
        LinkNode<T>* p;
        while (top) // 释放所有结点 
        {
            p = top;
            top = top->next;
            delete p;
        }
    }
    bool push(T e) {
        LinkNode<T>* p = new LinkNode<T>(e); // 新建结点 
        p->next = head->next; // p的下一个指向原首结点
        head->next = p;       // 头结点指向新结点p
        return true;
    }
        
    bool pop(T& e) {
        if (head->next == NULL) return false; // 栈空判断 
        LinkNode<T>* p = head->next; // p指向待删除的首结点 
        e = p->data;                 // 取出数据 
        head->next = p->next;        // 头结点跳过p指向下一个 
        delete p;                    // 释放结点空间 
        return true;
    }
};

int main()
{
    return 0;
}