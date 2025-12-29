#include<iostream>
using namespace std;

template <typename T>
struct LinkNode {
    T data;                 // 存放数据元素
    LinkNode<T>* next;      // 指向下一个节点的指针

    LinkNode(): next(NULL) {} // 构造函数
    LinkNode(T d): data(d), next(NULL) {} // 带参构造函数
};

template<typename T>
class CycleLinkList {
private:
    LinkNode<T>* head;
public:
    CycleLinkList() {
        head = new LinkNode<T>(); // 创建头节点
        head->next = head; // 头节点指向自己，形成环
    }
    ~CycleLinkList() {
        LinkNode<T>* current = head->next;
        while (current != head) {
            LinkNode<T>* temp = current;
            current = current->next;
            delete temp;
        }
        delete head; // 删除头节点
    }
    bool insert(int i, const T& x) {
        if (i < 0) return false;
        LinkNode<T>* p = head;
        for (int j = 0; j < i; j++) {
            p = p->next;
            if (p == head) return false; // 超出范围
        }
        LinkNode<T>* newNode = new LinkNode<T>(x);
        newNode->next = p->next;
        p->next = newNode;
        return true;
    }
    bool remove(int i) {
        if (i < 0) return false;
        LinkNode<T>* p = head;
        for (int j = 0; j < i; j++) {
            p = p->next;
            if (p->next == head) return false; // 超出范围
        }
        LinkNode<T>* temp = p->next;
        if (temp == head) return false; // 无节点可删除
        p->next = temp->next;
        delete temp;
        return true;
    }

    void createCycleList(int n) {
        LinkNode<T>* tail = head;
        for (int i = 0; i < n; i++) {
            LinkNode<T>* newNode = new LinkNode<T>(i);
            tail->next = newNode;
            tail = newNode;
        }
        tail->next = head;
    }
};