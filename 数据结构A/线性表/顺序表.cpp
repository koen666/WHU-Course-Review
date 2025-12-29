#include<iostream>
using namespace std;

template<typename T>
class SeqList
{
private:
    T* data;
    int maxSize;
    int length;//当前线性表长度
public:
    SeqList(int size)
    {
        data = new T[size];
        maxSize = size;
        length = 0;
    }
    ~SeqList()
    {
        delete[] data;
    }

    void recap(int newsize)
    {
        if (newsize <= maxSize)
            return;
        T* newdata = new T[newsize];
        for (int i = 0; i < length; i++)
            newdata[i] = data[i];
        delete[] data;
        data = newdata;
        maxSize = newsize;
    }

    bool insert(int i, const T& x)
    {
        if (i<0 || i>length)
            return false;
        if (length == maxSize)
            recap(2 * maxSize);
        for (int j = length - 1; j >= i; j--)
            data[j + 1] = data[j];
        data[i] = x;
        length++;
        return true;
    }

    bool remove(int i)
    {
        if (i<0 || i >= length)
            return false;
        for (int j = i; j < length - 1; j++)
            data[j] = data[j + 1];
        length--;
        return true;
    }
};

int main()
{

    return 0;
}