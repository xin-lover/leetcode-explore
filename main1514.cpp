//1514. 概率最大的路径

#include <cstdio>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
    //思路：跟最短路径一个思路，使用动归

    vector<vector<double>> dp(n,vector<double>(n,0.0));
    for(int i=0;i<n;++i)
    {
        dp[i][i] = 1.0;
    }
    for(int i=0;i<edges.size();++i)
    {
        dp[edges[i][0]][edges[i][1]] = succProb[i];
        dp[edges[i][1]][edges[i][0]] = succProb[i];
    }

    for(int k=0;k<n;++k)
    {
        for(int i=0;i<n;++i)
        {
            for(int j=0;j<n;++j)
            {
                dp[i][j] = max(dp[i][j],dp[i][k]*dp[k][j]);
            }
        }

    }

    return dp[start][end];
}

double maxProbability2(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
    //思路：最短路径是O(n^3)，性能超时
    //因为可能是稀疏矩阵，我们考虑bfs,dfs;

    vector<vector<pair<int,double>>> graphic(n,vector<pair<int,double>>());
    for(int i=0;i<edges.size();++i)
    {
        graphic[edges[i][0]].push_back({edges[i][1],succProb[i]});
        graphic[edges[i][1]].push_back({edges[i][0],succProb[i]});
    }

    queue<int> qu;
    qu.push(start);

    vector<double> dp(n,0.0);
    dp[start] = 1.0;

    while(!qu.empty())
    {
        //推进一步
        int sz = qu.size();
        for(int k=0;k<sz;++k)
        {
            int p = qu.front();
            qu.pop();

            for(int i=0;i<graphic[p].size();++i)
            {
                int end = graphic[p][i].first;
                double prob = graphic[p][i].second;

                double t = dp[p] * prob;
                if(t > dp[end])
                {
                    dp[end] = t;
                    qu.push(end);
                }
            }
        }
    }

    return dp[end];
}

//Dijkstra算法,把节点分为已确认和未确认的两类，每次从未确定的集合中选择一个与起点距离最短的点
//将它归类为已确定的点，并用它更新从起点到其他所有未确定点的距离。直到所有的点都归为已确定点
//Dijstra不能处理负权图
double maxProbability3(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
    vector<vector<pair<double, int>>> graph(n);
    for (int i = 0; i < edges.size(); i++) {
        auto& e = edges[i];
        graph[e[0]].emplace_back(succProb[i], e[1]);
        graph[e[1]].emplace_back(succProb[i], e[0]);
    }

    priority_queue<pair<double, int>> que;
    vector<double> prob(n, 0);

    que.emplace(1, start);
    prob[start] = 1;
    while (!que.empty()) {
        auto [pr, node] = que.top();
        que.pop();
        if (pr < prob[node]) {
            continue;
        }
        for (auto& [prNext, nodeNext] : graph[node]) {
            if (prob[nodeNext] < prob[node] * prNext) {
                prob[nodeNext] = prob[node] * prNext;
                que.emplace(prob[nodeNext], nodeNext);
            }
        }
    }
    return prob[end];
}

int main()
{
    int n = 3, start = 0, end = 2;
    vector<vector<int>> edges = {{0,1},{1,2},{0,2}};
    vector<double> succProb = {0.5,0.5,0.2};    //0.25

    //0.3
    n = 3, edges = {{0,1},{1,2},{0,2}}, succProb = {0.5,0.5,0.3}, start = 0, end = 2;

    // n = 3, edges = {{0,1}}, succProb = {0.5}, start = 0, end = 2; //0

    // //0.2139
    // n = 5, edges = {{1,4},{2,4},{0,4},{0,3},{0,2},{2,3}}, succProb={0.37,0.17,0.93,0.23,0.39,0.04},start=3, end=4;
    printf("%f\n",maxProbability2(n,edges,succProb,start,end));

    return 0;
}