#include <iostream>
#include <vector>
using namespace std;

// 1. 定义链表结点
struct Node {
    int key;
    Node* next;
    
    Node(int k) : key(k), next(NULL) {}
};

// 2. 定义哈希表类
class HashTable {
private:
    vector<Node*> table; // 这是一个指针数组
    int size;            // 哈希表的大小（通常是质数）

    // 哈希函数：除留余数法
    int hashFunction(int key) {
        return key % size;
    }

public:
    // 构造函数：初始化表大小，并将所有槽位这是为 NULL
    HashTable(int tableSize) {
        this->size = tableSize;
        table.resize(size, NULL);
    }

    // 析构函数：释放内存
    ~HashTable() {
        for (int i = 0; i < size; i++) {
            Node* current = table[i];
            while (current != NULL) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }

    // 【插入操作】
    void insert(int key) {
        int index = hashFunction(key); // 1. 计算下标
        
        // 2. 创建新结点
        Node* newNode = new Node(key);
        
        // 3. 头插法：将新结点插到对应链表的头部（这比尾插法快，O(1)）
        // 即使发生冲突，也只是把新结点放在链表最前面
        newNode->next = table[index];
        table[index] = newNode;
        
        cout << "Inserted " << key << " at index " << index << endl;
    }

    // 【查找操作】
    bool search(int key) {
        int index = hashFunction(key); // 1. 计算下标
        
        // 2. 遍历该下标对应的链表
        Node* current = table[index];
        while (current != NULL) {
            if (current->key == key) {
                return true; // 找到了
            }
            current = current->next;
        }
        return false; // 链表走完了都没找到
    }

    // 【删除操作】
    void remove(int key) {
        int index = hashFunction(key);
        
        Node* current = table[index];
        Node* prev = NULL;

        // 遍历链表寻找目标
        while (current != NULL && current->key != key) {
            prev = current;
            current = current->next;
        }

        // 没找到
        if (current == NULL) {
            cout << "Key " << key << " not found, cannot remove." << endl;
            return;
        }

        // 找到了，开始删除
        if (prev == NULL) {
            // 情况1：要删的是头结点
            table[index] = current->next;
        } else {
            // 情况2：要删的是中间或尾部结点
            prev->next = current->next;
        }
        delete current;
        cout << "Removed " << key << " from index " << index << endl;
    }
};

int main() {
    // 创建一个大小为 7 的哈希表
    HashTable ht(7);

    // 插入数据（模拟冲突：15, 8, 1 都会映射到下标 1）
    ht.insert(15); // 15 % 7 = 1
    ht.insert(8);  // 8 % 7 = 1
    ht.insert(22); // 22 % 7 = 1
    ht.insert(10); // 10 % 7 = 3

    // 查找
    if (ht.search(8)) cout << "Found 8!" << endl;
    else cout << "8 not found." << endl;

    if (ht.search(99)) cout << "Found 99!" << endl;
    else cout << "99 not found." << endl;

    // 删除
    ht.remove(8);
    if (ht.search(8)) cout << "Found 8!" << endl;
    else cout << "8 not found (deleted)." << endl;

    return 0;
}