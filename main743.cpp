//leetcode 743. 网络延迟时间

#include <cstdio>
#include <vector>
#include <set>
#include <queue>

using namespace std;

int networkDelayTime(vector<vector<int>>& times, int N, int K) {

    //思路：图的问题，就是图如果从K点开始遍历，能到达所有点则返回最长时间，否则返回-1，即不连通
    //问题就是如何构建图和遍历，
    //简单的做法就是给每个节点构建一个邻接节点列表，然后深度或广度遍历
    //双向图，

    vector<int> delays(N+1,INT_MAX);
    vector<vector<pair<int,int>>> graph(N+1);

    for(int i=0;i<times.size();++i)
    {
        int src = times[i][0];
        int dst = times[i][1];
        int cost = times[i][2];

        graph[src].push_back({dst,cost});
    } 

    delays[K] = 0;
    vector<int> updating(N+1,false);
    updating[K] = true;

    queue<int> qu;
    qu.push(K);
    while(!qu.empty())
    {
        int cur = qu.front();
        qu.pop();
        updating[cur] = false;
        for(int i=0;i<graph[cur].size();++i)
        {
            int d = graph[cur][i].first;
            int c = graph[cur][i].second;
            if(delays[d] > delays[cur] + c)
            {
                printf("d:%d\n",d);
                if(!updating[d])
                {
                    qu.push(d);
                    updating[d] = true;
                }
                    
                delays[d] = delays[cur]+c;
            }
        }
    }


    int maxDelay = 0;
    for(int i=1;i<delays.size();++i)
    {
        if(maxDelay < delays[i])
        {
            maxDelay = delays[i];
        }
    }

    return maxDelay == INT_MAX ? -1 : maxDelay;
}

int main()
{
    vector<vector<int>> v = {{1,2,1},{2,3,1}};
    // v = {{1,2,1},{2,3,2},{1,3,4}};
    // v = {{1,2,1},{2,3,7},{1,3,4},{2,1,2}};
    printf("%d\n",networkDelayTime(v,3,1));
    return 0;
}

