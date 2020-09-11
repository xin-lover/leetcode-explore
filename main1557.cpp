//1557. 可以到达所有点的最少点数目

#include <cstdio>
#include <vector>

using namespace std;

vector<int> findSmallestSetOfVertices(int n, vector<vector<int>>& edges) {
    //思路：有向无环图，要能到达所有点，可以简化问题为找到没有入度的点
    //因为没有入度，这个点肯定不能通过其它点到达，否则，总存在一个点可以到达这个点

    vector<int> inDegrees(n,0);
    for(auto a : edges)
    {
        inDegrees[a[1]]++;
    }

    vector<int> res;
    for(int i=0;i<inDegrees.size();++i)
    {
        if(inDegrees[i] == 0)
        {
            res.push_back(i);
        }
    }

    return res;
}

int main()
{
    int n = 6;
    vector<vector<int>> edges = {{0,1},{0,2},{2,5},{3,4},{4,2}};    //0,3

    n = 5, edges = {{0,1},{2,1},{3,1},{1,4},{2,4}}; //0,2,3

    for(auto a : findSmallestSetOfVertices(n,edges))
    {
        printf("%d ",a);
    }
    printf("\n");

    return 0;
}