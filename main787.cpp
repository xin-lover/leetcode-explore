//leetcode 787. K 站中转内最便宜的航班

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
    
    //思路：图从目的地往出发地按层遍历
    //使用动归的思路，记录可以到达目的地的站的花费，当某个站能以更少的花费到达目的地的时候，更新路径

    vector<int> dp(n,INT_MAX);   //存储各个站到目的地的当前最短花费
    dp[dst]=0;
    vector<vector<int>> graph(n,vector<int>(n,-1));

    for(auto e : flights)
    {
        graph[e[1]][e[0]] = e[2];
    }

    int res = INT_MAX;
    int level = 0;
    queue<int> qu;
    qu.push(dst);
    while(level <= K)
    {
        int sz = qu.size();
        for(int i=0;i<sz;++i)
        {
            auto t = qu.front();
            qu.pop();

            for(int j=0;j<graph[t].size();++j)
            {
                int cost = graph[t][j];
                if(cost == -1)
                {
                    continue;
                }
                if(cost + dp[t] < dp[j])
                {
                    qu.push(j);
                    dp[j] = cost + dp[t];
                }
                
                if(j == src)
                {
                    res = min(res,dp[j]);
                }
            }
        }
        ++level;
    }

    return res == INT_MAX ? -1 : res;
}

int findCheapestPrice2(int n, vector<vector<int>>& flights, int src, int dst, int K){
    //直接使用动归,dp[i][k]表示i站到到达目的地的站不超过k时的最少花费
    //这样，每次迭代k时，dp[i][k] = cost[i][j] + dp[j][k-1],const[i][j]表示j到j的花费
    
    vector<vector<int>> dp(n, vector<int>(K+1, 0x7fffffff));
    // dp[i][k]表示经过不超过k次中转到达第i个城市的最低代价
    dp[src][0] = 0;
    for(auto vals : flights){
        if(vals[0]==src){
            dp[vals[1]][0] = vals[2];
        }
    }
    for(int k=1; k<=K; ++k){
        for(int i=0; i<n; i++) dp[i][k] = dp[i][k-1];
        for(auto vals : flights){   //这一步效率非常低，如果把flights跟上面的算法一样做一下处理，不比较，其实两个算法的本质就一样了，写法不同而已
            if(dp[vals[0]][k-1]!=0x7fffffff)
                dp[vals[1]][k] = min(dp[vals[0]][k-1]+vals[2], dp[vals[1]][k]);
        }
    }
    return dp[dst][K]==0x7fffffff?-1:dp[dst][K];
}

int main()
{
    vector<vector<int>> edges = {{0,1,100},{1,2,100},{0,2,500}};
    printf("%d\n",findCheapestPrice(3,edges,0,2,1));
    printf("%d\n",findCheapestPrice(3,edges,0,2,0));
    edges = {{1,0,5}};
    printf("%d\n",findCheapestPrice(2,edges,0,1,1));

    edges = {{0,12,28},{5,6,39},{8,6,59},{13,15,7},{13,12,38},{10,12,35},{15,3,23},{7,11,26},{9,4,65},{10,2,38},{4,7,7},{14,15,31},{2,12,44},{8,10,34},{13,6,29},{5,14,89},{11,16,13},{7,3,46},{10,15,19},{12,4,58},{13,16,11},{16,4,76},{2,0,12},{15,0,22},{16,12,13},{7,1,29},{7,14,100},{16,1,14},{9,6,74},{11,1,73},{2,11,60},{10,11,85},{2,5,49},{3,4,17},{4,9,77},{16,3,47},{15,6,78},{14,1,90},{10,5,95},{1,11,30},{11,0,37},{10,4,86},{0,8,57},{6,14,68},{16,8,3},{13,0,65},{2,13,6},{5,13,5},{8,11,31},{6,10,20},{6,2,33},{9,1,3},{14,9,58},{12,3,19},{11,2,74},{12,14,48},{16,11,100},{3,12,38},{12,13,77},{10,9,99},{15,13,98},{15,12,71},{1,4,28},{7,0,83},{3,5,100},{8,9,14},{15,11,57},{3,6,65},{1,3,45},{14,7,74},{2,10,39},{4,8,73},{13,5,77},{10,0,43},{12,9,92},{8,2,26},{1,7,7},{9,12,10},{13,11,64},{8,13,80},{6,12,74},{9,7,35},{0,15,48},{3,7,87},{16,9,42},{5,16,64},{4,5,65},{15,14,70},{12,0,13},{16,14,52},{3,10,80},{14,11,85},{15,2,77},{4,11,19},{2,7,49},{10,7,78},{14,6,84},{13,7,50},{11,6,75},{5,10,46},{13,8,43},{9,10,49},{7,12,64},{0,10,76},{5,9,77},{8,3,28},{11,9,28},{12,16,87},{12,6,24},{9,15,94},{5,7,77},{4,10,18},{7,2,11},{9,5,41}};
    printf("%d\n",findCheapestPrice(17,edges,13,4,13));

    edges = {{0,1,5},{1,2,5},{0,3,2},{3,1,2},{1,4,1},{4,2,1}};
    printf("%d\n",findCheapestPrice(5,edges,0,2,2));


    return 0;
}