//1376. 通知所有员工所需的时间

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {
    //思路：就是求最长路径，因为保证是树结构，所以用dfs或bfs都可以，因为不是二叉树，dfs实现起来麻烦一些

    vector<vector<int>> tree(n);
    for(int i=0;i<manager.size();++i)
    {
        if(manager[i] > -1)
        {
            tree[manager[i]].push_back(i);
        }
    }

    int res = 0;
    vector<int> costs(n,0);
    queue<int> qu;
    qu.push(headID);

    while(!qu.empty())
    {
        int t = qu.front();
        qu.pop();

        for(int i=0;i<tree[t].size();++i)
        {
            costs[tree[t][i]] = costs[t] + informTime[t];
            res = max(costs[tree[t][i]],res);

            qu.push(tree[t][i]);
        }
    }
    
    return res;
}

int main()
{
    int n = 6, headID = 2;
    vector<int> manager = {2,2,-1,2,2,2}, informTime = {0,0,1,0,0,0};   //1

    n = 7, headID = 6, manager = {1,2,3,4,5,6,-1}, informTime = {0,6,5,4,3,2,1}; //21

    printf("%d\n",numOfMinutes(n,headID,manager,informTime));

    return 0;
}