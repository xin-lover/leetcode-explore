//1334. 阈值距离内邻居最少的城市

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
    //思路：按最直观的思路就是统计每个城市在阈值范围内的城市集合，然后排序
    //这个的关键在于图的遍历，这个可以使用广度遍历即可
    //但里面有个问题就是最短路径，如何获取最短路径

    vector<vector<pair<int,int>>> graph(n); //图，邻接矩阵

    for(int i=0;i<edges.size();++i)
    {
        graph[edges[i][0]].push_back({edges[i][1],edges[i][2]});
        graph[edges[i][1]].push_back({edges[i][0],edges[i][2]});
    }

    vector<pair<int,int>> arriveInfo;
    for(int i=0;i<n;++i)
    {
        vector<int> visited(n,INT_MAX);
        queue<pair<int,int>> qu;
        qu.push({i,0});

        while(!qu.empty())
        {
            auto cur = qu.front();
            qu.pop();

            visited[cur.first] = min(visited[cur.first],cur.second);
            for(int j=0;j<graph[cur.first].size();++j)
            {
                //这里有个问题，就是到达某个点的距离有长有短，我们需要的是最短的那个路径，我们需要更新
                int t = cur.second + graph[cur.first][j].second;
                if(t <= distanceThreshold && t < visited[graph[cur.first][j].first])  //短路径出现
                {
                    qu.push({graph[cur.first][j].first,t});
                }
            }
        }

        int count=0;
        for(int j=0;j<visited.size();++j)
        {
            count += (visited[j] <= distanceThreshold ? 1 : 0);
        }

        arriveInfo.push_back({i,count-1});
    }

    sort(arriveInfo.begin(),arriveInfo.end(),[](pair<int,int>& a,pair<int,int>& b){
        if(a.second == b.second)
        {
            return a.first > b.first;
        }

        return a.second < b.second;
    });

    // for(auto a : arriveInfo)
    // {
    //     printf("%d %d\n",a.first,a.second);
    // }

    return arriveInfo[0].first;
}

int findTheCity2(int n, vector<vector<int>>& edges, int distanceThreshold) {
    //思路：上面的思路一个是邻接矩阵，一个是排序
    //可以的优化排序，不用排序的方式是记录当前连接城市的数量，记录最小值，如果遇到相同的就更新序号
    vector<vector<pair<int,int>>> graph(n); //图，邻接矩阵

    for(int i=0;i<edges.size();++i)
    {
        graph[edges[i][0]].push_back({edges[i][1],edges[i][2]});
        graph[edges[i][1]].push_back({edges[i][0],edges[i][2]});
    }

    int minCount = n;
    int res = 0;
    for(int i=0;i<n;++i)
    {
        vector<int> visited(n,INT_MAX);
        queue<pair<int,int>> qu;
        qu.push({i,0});

        while(!qu.empty())
        {
            auto cur = qu.front();
            qu.pop();

            if(cur.second < visited[cur.first])
            {
                visited[cur.first] = cur.second;
                for(int j=0;j<graph[cur.first].size();++j)
                {
                    //这里有个问题，就是到达某个点的距离有长有短，我们需要的是最短的那个路径，我们需要更新
                    int t = cur.second + graph[cur.first][j].second;
                    if(t <= distanceThreshold && t < visited[graph[cur.first][j].first])  //短路径出现
                    {
                        qu.push({graph[cur.first][j].first,t});
                    }
                }
            }
        }

        int count=0;
        for(int j=0;j<visited.size();++j)
        {
            count += (visited[j] <= distanceThreshold ? 1 : 0);
        }

        if(count <= minCount)
        {
            minCount = count;
            res = i;
        }
    }

    return res;
}

//弗洛伊德法
// class Solution {
// public:
//     int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
//         vector<vector<int>> d(n, vector<int>(n, 10000));
//         for (auto& edge : edges)
//             d[edge[0]][edge[1]] = d[edge[1]][edge[0]] = edge[2];

//         //floyd算法求距离数组
//         for (int k = 0; k < n; ++k)
//             for (int i = 0; i < n; ++i)
//                 for (int j = i + 1; j < n; ++j)
//                         if(i != k && k != j) d[i][j] = d[j][i] = min(d[i][j], d[i][k] + d[k][j]);

//         int ans = 0, minNum = n; //编号最大城市，最少到达城市数量
//         for (int i = 0; i < n; ++i) {
//             int cnt = 0;
//             for (int j = 0; j < n; ++j)
//                 if (i != j && d[i][j] <= distanceThreshold) ++cnt;

//             if (cnt <= minNum) {
//                 minNum = cnt;
//                 ans = i;
//             }
//         }
//         return ans;
//     }

int main()
{
    int n = 4;
    vector<vector<int>> edges = {{0,1,3},{1,2,1},{1,3,4},{2,3,1}};
    int distanceThreshold = 4; //3

    n = 5, edges = {{0,1,2},{0,4,8},{1,2,3},{1,4,2},{2,3,1},{3,4,1}}, distanceThreshold = 2; //0

    // n =8;
    // edges = {{3,5,9558},{1,2,1079},{1,3,8040},{0,1,9258},{4,7,7558},{5,6,8196},{3,4,7284},{1,5,6327},{0,4,5966},{3,6,8575},{2,5,8604},{1,7,7782},{4,6,2857},{3,7,2336},{0,6,6},{5,7,2870},{4,5,5055},{0,7,2904},{1,6,2458},{0,5,3399},{6,7,2202},{0,2,3996},{0,3,7495},{1,4,2262},{2,6,1390}};
    // distanceThreshold= 7937;

    printf("%d\n",findTheCity(n,edges,distanceThreshold));
    return 0;
}