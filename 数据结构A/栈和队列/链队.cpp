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
class LinkQueue
{
public:
    LinkNode<T>* front; // 队头指针 
    LinkNode<T>* rear;  // 队尾指针 
    LinkQueue() // 构造函数 
    {
        front = rear = new LinkNode<T>(); // 创建头结点，队头队尾均指向头结点 
    }
    ~LinkQueue() // 析构函数 
    {
        LinkNode<T>* p;
        while (front) // 释放所有结点 
        {
            p = front;
            front = front->next;
            delete p;
        }
    }
    bool EnQueue(const T& x) {
        LinkNode<T>* p = new LinkNode<T>(x); // 新建结点 
        rear->next = p; // 新结点插入队尾 
        rear = p;       // 修改队尾指针 
        return true;
    }
    //这里我们认为front指向null
    bool DeQueue(T& x) {
        if (front == rear) return false; // 队空判断 
        LinkNode<T>* p = front->next; // p指向待删除的首结点 
        x = p->data;                  // 取出数据 
        front->next = p->next;        // 头结点跳过p指向下一个 
        if (rear == p)                // 若删除的是队尾结点 
            rear = front;             // 修改队尾指针 
        delete p;                     // 释放结点空间 
        return true;
    }
};

int main()
{
    return 0;
}