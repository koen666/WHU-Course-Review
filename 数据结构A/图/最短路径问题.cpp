#include<iostream>
using namespace std;

/*
代码中使用三个关键数组来维护算法状态
dist[]：保存从源点 v 到每个顶点的当前最短路径长度 
path[]：保存最短路径上顶点的前驱顶点，用于反向推导路径
S[]：标记集合状态。S[i]=1 表示顶点 i 已并入 S 集合，S[i]=0 表示在 U 集合中
*/

const int MAX_V = 100;
const int INF = 0x3f3f3f3f;

void Dijkstra(int v, int n, int graph[][MAX_V], int dist[], int path[], bool S[])
{
    // 初始化
    for(int i = 0; i < n; i++)
    {
        dist[i] = graph[v][i];
        S[i] = false;
        if(graph[v][i] < INF)
            path[i] = v;
        else
            path[i] = -1;
    }
    
    S[v] = true;
    dist[v] = 0;
    
    // 循环 n-1 次，每次选择一个顶点加入 S 集合
    for(int i = 1; i < n; i++)
    {
        int minDist = INF;
        int u = -1;
        
        // 在 U 集合中找到距离最小的顶点
        for(int j = 0; j < n; j++)
        {
            if(!S[j] && dist[j] < minDist)
            {
                minDist = dist[j];
                u = j;
            }
        }
        
        if(u == -1) break;
        
        S[u] = true;
        
        // 更新 U 集合中顶点的距离
        for(int j = 0; j < n; j++)
        {
            if(!S[j] && graph[u][j] < INF)
            {
                if(dist[u] + graph[u][j] < dist[j])
                {
                    dist[j] = dist[u] + graph[u][j];
                    path[j] = u;
                }
            }
        }
    }
}

void Floyd(int n, int graph[][MAX_V], int dist[][MAX_V], int path[][MAX_V])
{
    // 初始化
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            dist[i][j] = graph[i][j];
            if(i != j && graph[i][j] < INF)
                path[i][j] = i;
            else
                path[i][j] = -1;
        }
    }
    
    // 依次考虑每个顶点作为中转点
    for(int k = 0; k < n; k++)
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[k][j];
                }
            }
        }
    }
}
