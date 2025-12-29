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
class LinkList {
private:
    LinkNode<T>* head;
public:
    LinkList() {
        head = new LinkNode<T>(); // 创建头节点
    }

    ~LinkList() {
        LinkNode<T>* current = head;
        while (current) {
            LinkNode<T>* temp = current;
            current = current->next;
            delete temp;
        }
    }

    bool insert(int i, const T& x) {
        if (i < 0) return false;
        LinkNode<T>* p = head;
        for (int j = 0; j < i; j++) {
            if (!p->next) return false; // 超出范围
            p = p->next;
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
            if (!p->next) return false; // 超出范围
            p = p->next;
        }
        LinkNode<T>* temp = p->next;
        if (!temp) return false; // 无节点可删除
        p->next = temp->next;
        delete temp;
        return true;
    }

};