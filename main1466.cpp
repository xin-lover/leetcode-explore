//1466. 重新规划路线

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

int minReorder(int n, vector<vector<int>>& connections) {
    //思路：只有n-1条路线，那么意味着一个城市只能去往另一个城市
    //所以，这个问题变为要去往的那个城市可以到达0
    //所以借助并查集的思想，到达0城市的为一个集合，那么接下来要修改的路线就是不在这个集合的城市之间的路线


    vector<vector<int>> ways(n,vector<int>());  //存储到达该节点的其它节点
    for(int i=0;i<connections.size();++i)
    {
        ways[connections[i][1]].push_back(connections[i][0]);
        ways[connections[i][0]].push_back(-connections[i][1]);
    }

    //bfs
    queue<int> qu;
    qu.push(0);

    vector<int> visited(n,false);
    int res = 0;
    while(!qu.empty())
    {
        int p = qu.front();
        qu.pop();
        visited[p] = true;

        for(int i=0;i<ways[p].size();++i)
        {
            int city = ways[p][i];
            if(city < 0)
            {
                city = -city;
                if(!visited[city])
                {
                    ++res;
                }
            }
            
            if(!visited[city])
            {
                qu.push(city);
            }
            
            
        }
    }

    return res;
}

int main()
{
    int n = 6;
    vector<vector<int>> connections = {{0,1},{1,3},{2,3},{4,0},{4,5}}; //3
    n = 5, connections = {{1,0},{1,2},{3,2},{3,4}}; //2
    n = 3, connections = {{1,0},{2,0}}; //0

    printf("%d\n",minReorder(n,connections));

    return 0;
}