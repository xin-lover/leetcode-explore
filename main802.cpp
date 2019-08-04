//leetcode 802 找到最终的安全状态

#include <cstdio>
#include <vector>

using namespace std;

int safe(vector<vector<int>>& graph,vector<bool>& visited, vector<int>& safeNodes,int p)
{
    if(safeNodes[p] > -1)
    {
        return safeNodes[p];
    }
    
    if(visited[p])
    {
        safeNodes[p] = 0;
        return 0;
    }
    
    visited[p] = true;
    int ret = 1;
    for(int i=0;i<graph[p].size();++i)
    {
        if(!safe(graph,visited,safeNodes,graph[p][i]))
        {
            ret = 0;
            break;
        }
    }
    
    safeNodes[p] = ret;
    return ret;
}

vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
    
    //思路：终点肯定是安全节点
    //题目表达不清楚，其实意思是从任何一个节点出发，走任何一条路径都能到达终点
    //比如示例中：0->1->3->0是一个环，就不能到达终点
    //所以安全节点就是从这个节点出发，走任何一条路线都能到达终点
    //策略：如果一个节点不是安全的，则任何一个到达这个节点的都是不安全的，而一个节点是安全的则需要所有路线最后都能到达终点
    
    vector<bool> visited(graph.size(),false);
    vector<int> safes(graph.size(),-1); //记录安全节点，避免重复计算
    vector<int> res;
    for(int i=0;i<graph.size();++i)
    {
        if(safe(graph,visited,safes,i) == 1)
        {
            res.push_back(i);
        }
    }
    
    return res;
}

int main()
{
    vector<vector<int>> graph = {{1,2},{2,3},{5},{0},{5},{},{}};
    for(auto a : eventualSafeNodes(graph))
    {
        printf("%d ",a);
    }
    printf("\n");

    return 0;
}
