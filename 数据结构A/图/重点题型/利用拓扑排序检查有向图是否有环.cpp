#include<iostream>
#include<vector>
#include<stack>
using namespace std;

struct ArcNode
{
    int adjvex;
    ArcNode* nextarc;
    ArcNode(int v):adjvex(v),nextarc(nullptr){}
};

struct Hnode
{
    ArcNode* firstarc;
    Hnode():firstarc(nullptr){}
};

class Graph
{
public:
    int n; 
    int m; 
    vector<Hnode> adjlist;
    Graph(int nodes,int edges):n(nodes),m(edges),adjlist(nodes){}

    void insert(int u,int v)
    {
        ArcNode*newNode=new ArcNode(v);
        newNode->nextarc=adjlist[u].firstarc;
        adjlist[u].firstarc=newNode;
    }

    bool is_cycle()
    {
        stack<int> stk;
        vector<int> indegree(n,0);

        for(int i=0;i<n;i++)
        {
            ArcNode* p=adjlist[i].firstarc;
            while(p)
            {
                indegree[p->adjvex]++;
                p=p->nextarc;
            }
        }

        for(int i=0;i<n;i++)
        {
            if(indegree[i]==0)
                stk.push(i);
        }

        while (!stk.empty())
        {
            int u=stk.top();
            stk.pop();
            ArcNode* p=adjlist[u].firstarc;
            while(p)
            {
                indegree[p->adjvex]--;
                if(indegree[p->adjvex]==0)
                    stk.push(p->adjvex);
                p=p->nextarc;
            }
        }
        for(int i=0;i<n;i++)
        {
            if(indegree[i]>0)
                return true;
        }
        return false;
    }
};


int main()
{
    int n,m;cin>>n>>m;
    Graph graph(n,m);
    for(int i=0;i<m;i++)
    {
        int u,v;cin>>u>>v;
        u--;v--;
        graph.insert(u,v);
    }
    cout << (graph.is_cycle() ? "Yes" : "No") << endl;
    return 0;
}