#include<iostream>
using namespace std;

// 稀疏矩阵三元组顺序表表示法
struct TupElem {
    int r;    // 行号
    int c;    // 列号
    int d;    // 元素值
    TupElem() {}
    TupElem(int r1, int c1, int d1) { r = r1; c = c1; d = d1; }
};

class TupClass {
    int rows;       // 矩阵总行数
    int cols;       // 矩阵总列数
    int nums;       // 非零元素总个数
    TupElem* data;  // 动态分配的三元组顺序表，通常按行优先排列 
};

//十字链表示法
template<typename T>
struct MatNode {
    int row;        // 行号 
    int col;        // 列号 
    struct MatNode *right, *down; // 行指针和列指针 
    union {
        T value;                // 非零元素值 
        struct MatNode *link;   // 指向下一个头结点（仅用于头结点） 
    } tag;
};



int main()
{

    return 0;
}