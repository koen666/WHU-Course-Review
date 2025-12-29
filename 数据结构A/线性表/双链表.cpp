#include<iostream>
using namespace std;

template <typename T>
struct DLinkNode {
    T data;                  // 存放数据元素
    DLinkNode<T>* prior;     // 指向前驱结点的指针
    DLinkNode<T>* next;      // 指向后继结点的指针

    DLinkNode() : next(NULL), prior(NULL) {} // 构造函数
    DLinkNode(T d) : data(d), next(NULL), prior(NULL) {} // 重载构造函数
};

template<typename T>
class DLinkList {
private:
    DLinkNode<T>* head;
public:
    DLinkList() {
        head = new DLinkNode<T>(); // 创建头节点
    }

    ~DLinkList() {
        DLinkNode<T>* current = head;
        while (current) {
            DLinkNode<T>* temp = current;
            current = current->next;
            delete temp;
        }
    }

    bool insert(int i, const T& x) {
        if (i < 0) return false;
        DLinkNode<T>* p = head;
        for (int j = 0; j < i; j++) {
            if (!p->next) return false; // 超出范围
            p = p->next;
        }
        DLinkNode<T>* newNode = new DLinkNode<T>(x);
        newNode->next = p->next;
        newNode->prior = p;
        if (p->next) {
            p->next->prior = newNode;
        }
        p->next = newNode;
        return true;
    }

    bool remove(int i) {
        if (i < 0) return false;
        DLinkNode<T>* p = head;
        for (int j = 0; j < i; j++) {
            if (!p->next) return false; // 超出范围
            p = p->next;
        }
        DLinkNode<T>* temp = p->next;
        if (!temp) return false; // 无节点可删除
        p->next = temp->next;
        if (temp->next) {
            temp->next->prior = p;
        }
        delete temp;
        return true;
    }

    //头插法建表
    void createListHead(int n) {
        for (int i = 0; i < n; i++) {
            T value;
            cin >> value;
            DLinkNode<T>* newNode = new DLinkNode<T>(value);
            newNode->next = head->next;
            newNode->prior = head;
            if (head->next) {
                head->next->prior = newNode;
            }
            head->next = newNode;
        }
    }

    //尾插法建表
    void createListTail(int n) {
        DLinkNode<T>* tail = head; // 使用tail指针指向链表的最后一个节点
        for (int i = 0; i < n; i++) {
            T value;
            cin >> value;
            DLinkNode<T>* newNode = new DLinkNode<T>(value);
            tail->next = newNode;
            newNode->prior = tail;
            tail = newNode; // 更新tail指针
        }
    }

};