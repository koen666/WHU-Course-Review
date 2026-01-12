#include<iostream>
#include<vector>
#include<string>
using namespace std;

void GetNext(string t,int* next)
{
    int j=0;
    int k=-1;
    next[0]=-1;
    while (j<t.length()-1)
    {
        if(k==-1||t[j]==t[k])
        {
            j++;
            k++;
            next[j]=k;
        }
        else
            k=next[k];   
    }
}

void GetNextval(string t,int*nextval)
{
    int j=0;
    int k=-1;
    nextval[0]=-1;
    while(j<t.length()-1)
    {
        if(k==-1||t[j]==t[k])
        {
            j++;
            k++;
            if(t[j]!=t[k])
                nextval[j]=k;
            else
                nextval[j]=nextval[k];
        }
        else
            k=nextval[k];
    }
}

int kmp(string s,string t)
{
    int i=0;
    int j=0;
    int* next=new int[t.length()];
    GetNext(t,next);
    while(i<s.length()&&j<t.length())
    {
        if(j==-1||s[i]==t[j])
        {
            i++;
            j++;
        }
        else
            j=next[j];
    }
    if(j==t.length())
        return i-j;
    else
        return -1;
}