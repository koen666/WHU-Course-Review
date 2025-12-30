#include<iostream>
using namespace std;

const int MAXSIZE=100;

template<typename T>
class SqStack
{
public:
    T*data;
    int top;
    SqStack()
    {
        data=new T[MAXSIZE];
        top=-1;
    }
    ~SqStack()
    {
        delete []data;
    }
    bool Push(const T&x)
    {
        if(top==MAXSIZE-1)
            return false;
        data[++top]=x;
        return true;
    }
    bool Pop(T&x)
    {
        if(top==-1)
            return false;
        x=data[top--];
        return true;
    }
};

int main()
{
    
    return 0;
}