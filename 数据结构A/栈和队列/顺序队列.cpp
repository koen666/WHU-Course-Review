#include<iostream>
using namespace std;

const int MAXSIZE=100;

template<typename T>
class SqQueue
{
public:
    T* data;
    int front;
    int rear;
    SqQueue()
    {
        data=new T[MAXSIZE];
        front=rear=0;
    }
    ~SqQueue()
    {
        delete []data;
    }
    bool EnQueue(const T& x)
    {
        if((rear+1)%MAXSIZE==front)//循环队列队满
            return false;
        data[rear]=x;
        rear=(rear+1)%MAXSIZE;
        return true;
    }
    bool DeQueue(T& x)
    {
        if(front==rear)//循环队列队空
            return false;
        x=data[front];
        front=(front+1)%MAXSIZE;
        return true;
    }
};

int main()
{
    return 0;
}