//1091. 二进制矩阵中的最短路径
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
    //这个考虑动态规划，到达每个点的路线有8种，按常规的遍历方式，我们只需要考虑4个方向
    //这里注意的是，可不可能先到右侧的点，即竖直向下让后向左拐的情况
    //这种情况右侧的点必须先计算，对于这种情况我们的遍历方式不行
    //考虑bfs，每次步进一步

    int n = grid.size();
    if(grid[0][0] != 0 || grid[n-1][n-1]!=0)
    {
        return 0;
    }

    vector<vector<int>> dirs = {{-1,1},{0,1},{1,1},{-1,0},{1,0},{-1,-1},{0,-1},{1,-1}};
    queue<pair<int,int>> qu;

    int count = 1;
    qu.push({0,0});
    while(!qu.empty())
    {
        int sz = qu.size();
        for(int k=0;k<sz;++k)
        {
            pair<int,int> p = qu.front();
            qu.pop();
            int x = p.first;
            int y = p.second;
            if(x == n-1 && y == n-1)
            {
                return count;
            }

            for(int i=0;i<dirs.size();++i)
            {
                int nx = x + dirs[i][0];
                int ny = y + dirs[i][1];

                if(nx < 0 || nx >=n || ny < 0 || ny >=n)
                {
                    continue;
                }

                if(grid[nx][ny] == 0)
                {
                    grid[nx][ny] = 2;
                    qu.push({nx,ny});
                }
            }
        }

        ++count;
    }

    return -1;
}

int main()
{
    vector<vector<int>> grid = {{0,1},{1,0}};//2
    grid = {{0,0,0},{1,1,0},{1,1,0}}; //4
    grid = {{0,1,0,1,1,0,1,0,1,0,1,1,1,1,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,1,0,1,1,0,1,1,0,0,0,0,1,1,1,0,1,1,0,0,1,1,1,0,1,0,1,0,1,1,0,0,0,0,0,1,1,1,0,1,1,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1},{1,0,0,0,1,0,0,1,0,0,1,1,0,1,1,1,1,1,1,1,0,1,0,0,0,1,1,1,1,0,1,0,1,0,1,1,1,1,1,1,1,0,0,0,1,1,0,0,1,0,0,0,0,1,1,0,1,0,0,0,1,1,1,0,0,0,0,1,0,1,1,1,1,0,1,0,0,1,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,0,0,0,0,1,1},{0,0,1,0,1,1,1,1,1,1,0,1,0,0,0,0,0,1,1,0,1,0,1,1,1,1,0,1,1,0,0,1,1,0,0,0,0,0,1,0,0,1,1,1,0,1,1,1,1,1,0,1,0,1,1,1,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,1,1,0,1,0,0,1,0,1,1,1,0,0,1,1},{0,0,1,1,0,1,1,1,1,0,0,1,0,1,1,1,1,0,1,0,1,0,0,1,0,1,1,0,1,0,0,1,1,1,1,1,1,0,0,1,1,0,1,1,0,1,1,1,0,1,0,0,1,1,0,1,0,1,0,0,0,1,0,0,0,0,0,0,1,1,1,0,0,1,0,1,1,0,1,0,0,1,1,1,1,1,1,0,0,1,0,1,0,0,0,0,0,1,0,0},{0,0,1,1,1,0,1,1,1,1,0,1,1,0,1,1,1,0,1,1,1,1,0,1,0,1,1,0,0,1,1,0,0,0,1,0,0,1,1,0,0,0,0,1,1,0,1,1,0,1,1,0,0,1,1,0,0,1,1,0,1,0,1,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,1,1,0,1,0,1,0,1,1,0,1,0,1,0,0,1,0,1,1,0,1,0},{1,0,1,1,1,1,0,0,0,0,0,1,0,0,0,1,1,0,1,1,1,0,1,1,0,0,0,0,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,1,1,0,0,1,1,1,1,0,0,0,0,0,1,1,0,1,0,1,0,1,1,1,1,0,0,0,0,0,1,1,1,0,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,1},{0,0,0,0,1,0,0,1,1,0,0,1,0,1,0,0,1,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,1,0,1,1,1,0,1,0,0,0,1,0,0,1,0,1,0,0,0,0,0,1,1,1,0,0,1,0,1,1,1,0,0,0,1,0,1,1,1,0,0,1,0,0,0,1,1,1,1,0,1,0,0,1,0,0,0,1,1,0,1,0,1,0,0,0,0,0},{1,0,1,0,0,1,0,0,1,0,0,1,0,0,1,1,0,1,0,0,0,0,1,0,1,0,0,1,1,1,0,1,0,1,0,0,0,1,0,1,0,0,1,1,0,1,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,1,1,1,1,0,1,1,1,0,0,1,0,1,0,1,1,0,1,1,1,0,1,1,0,1,1,0,1,0,0,0,1,0,0,1,0,1,1,1},{1,1,1,0,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,1,0,1,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,1,0,1,1,0,0,1,0,1,0,0,1,1,0,0,1,0,0,1,0,1,1,0,1,0,1,0,1,0,1,1,1,0,0,1,0,1,0,1,1,0,1,0,0,0,0,1,1,1,1,0,1,0,1,0,0,0,0,1,1,0},{0,1,0,1,1,0,1,1,1,0,0,0,1,0,0,1,1,1,0,0,1,1,1,0,1,1,0,1,0,1,0,0,0,0,0,1,0,1,1,0,0,1,0,1,1,1,0,1,0,0,0,1,0,0,1,0,0,0,1,0,1,1,1,0,0,1,1,1,1,0,0,0,1,1,1,0,1,0,1,0,0,1,0,1,1,0,1,0,1,0,1,0,1,0,1,0,0,1,0,1},{1,0,0,1,0,0,0,0,1,0,0,0,1,0,1,1,0,0,1,0,0,1,1,1,0,0,0,1,1,0,1,0,1,0,0,0,1,0,1,1,0,0,0,0,0,1,0,0,1,1,0,1,0,0,1,0,1,0,1,0,0,0,1,1,1,1,0,0,1,1,0,1,1,0,1,1,0,0,1,0,1,1,0,0,1,0,1,1,0,0,1,1,0,0,0,0,1,0,0,1},{0,1,1,1,1,1,0,0,0,1,0,0,1,0,1,0,1,0,1,1,1,0,1,0,0,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,0,0,1,1,0,1,1,1,1,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,1,0,0,0,1,1,0,1,0,1,1,0,1,0,1,0,0,0,0,0,0,0,1,0},{0,0,0,0,0,1,1,1,0,1,0,0,0,1,0,1,1,0,0,0,0,1,1,1,1,1,0,0,0,1,0,1,0,0,0,1,1,1,0,1,1,0,1,0,1,1,1,0,1,1,1,1,1,0,0,1,0,1,1,1,0,0,1,1,1,1,0,0,1,0,0,1,0,1,1,1,1,0,1,0,1,1,0,0,1,0,0,0,1,1,1,1,0,1,0,0,1,1,1,0},{1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,0,0,1,0,1,0,0,1,1,0,0,0,0,1,1,1,0,1,1,1,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,1,1,1,1,1,0,1,1,1,1,0,0,1,0,1,0,0,1,1,0,0,0,0,0,1,1,0,1,1,1,1,0,0,0,1,0,1,0,1,0,1,0,1,1,1,1,1},{0,0,1,1,1,0,0,0,1,0,0,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,0,0,1,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,1,0,1,0,1,0,1,0,0,1,1,0,1,0,1,1,1,1,0,1,1,0,1,1,1,1,0,1,0,0,1,1,1,1,1,0,0,0,1,0,1,1,1,0,1,0,0,0,0},{0,0,1,1,0,1,1,0,0,1,1,1,1,0,0,1,0,1,0,0,0,1,1,1,0,1,0,0,1,0,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,1,0,1,0,0,0,1,0,0,0,1,1,0,0,1,1,0,1,0,0,1,1,0,0,0,1,1,0,1,1,0,0,1,1,1,1,0,1,1,1,0,1,1,0,1,0,1,1,0,0,1,1,0,0,0},{0,1,1,0,1,0,0,0,1,0,1,0,1,0,0,1,0,1,0,0,0,0,1,1,0,1,0,1,1,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,1,1,1,0,0,1,0,0,1,0,1,1,1,0,1,1,1,0,0,0,0,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,0,0,1,1,0,1,1,1,0,1,0,0,1,0,0,0,1,0},{0,0,1,0,0,1,1,1,1,0,0,0,1,1,0,1,1,0,1,1,0,1,1,0,0,0,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,1,0,1,0,1,1,1,1,1,1,1,0,1,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,1,0,1,1,1,1,0,0,0,1,0,1,0,0,1,0,0,1,1,0,1,0,0,1,0,0,0,1,0},{1,0,0,1,1,0,1,0,0,0,1,0,0,0,1,1,1,1,0,0,0,1,1,0,1,1,0,1,0,1,1,1,1,1,1,0,0,0,1,0,1,0,0,0,1,1,1,0,0,1,0,1,1,0,0,0,0,0,0,0,1,1,1,0,1,1,0,0,0,0,0,0,0,1,0,1,1,0,0,1,1,1,1,1,0,1,0,1,0,1,1,1,1,0,0,1,0,1,1,1},{0,1,1,1,1,0,0,0,1,1,0,1,1,0,1,0,1,0,0,0,0,0,0,1,1,0,1,1,0,1,0,0,0,1,0,1,1,0,0,1,1,0,1,1,0,0,1,0,1,0,1,1,1,0,1,0,0,0,1,0,1,0,1,1,1,0,1,0,0,0,1,0,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,1,0,0,1,0,1,0,0,0,0},{1,1,1,1,0,1,0,1,0,0,1,1,1,1,1,0,1,1,1,1,0,1,0,1,0,1,1,0,1,0,1,1,1,1,0,0,1,1,1,0,1,1,1,0,1,1,0,0,0,0,0,0,1,1,0,1,0,0,1,0,1,0,1,1,1,0,1,0,1,0,0,0,0,1,0,1,0,0,0,1,0,1,1,0,0,0,1,0,1,0,1,0,1,1,0,1,0,0,0,0},{0,0,0,1,1,1,0,0,0,1,1,1,1,1,0,1,0,0,1,0,1,0,1,0,1,1,1,0,1,1,0,0,1,1,0,1,0,1,0,0,1,1,0,0,1,1,1,0,1,1,1,1,0,0,0,1,0,0,0,1,1,0,1,0,1,0,1,1,1,1,0,0,1,1,0,1,1,0,1,1,0,1,0,0,1,0,1,0,0,1,1,0,0,0,1,0,0,0,1,0},{1,1,1,1,0,1,1,0,1,0,1,0,1,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,1,0,0,0,0,1,0,1,1,0,0,1,0,0,1,0,1,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,1,0,1,0,1,0,1,0,1,1,1},{1,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,1,1,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,1,0,1,1,0,0,1,0,0,1,1,1,1,1,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,0,1,1,0,0,1,1,1,0,0,1,1,0,1,1,1,1,1,0,1,0,0,1,0,0,1},{1,1,0,1,1,0,1,1,1,0,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,0,1,0,1,0,0,1,1,1,0,1,1,0,0,1,1,1,1,0,1,0,1,0,0,1,1,1,1,1,0,0,0,0,0,1,0,1,1,0,1,0,1,1,0,1,1,1,0,1,1,0,0,0,0,1,1,1,1,0,1,0,1,1,1,0,1,0,0,1,0,0,1,1},{0,1,0,0,1,0,1,1,0,0,1,1,1,0,0,1,1,0,1,1,0,0,1,1,1,1,1,0,0,1,1,1,1,0,1,1,1,1,0,0,1,1,0,0,0,0,1,0,1,1,0,0,1,0,1,0,1,1,0,1,1,0,1,0,0,1,0,1,1,0,0,0,0,1,0,0,0,0,1,1,0,0,1,0,1,0,1,0,1,1,0,1,1,1,1,0,0,0,1,1},{0,1,0,0,0,1,0,0,0,1,1,0,0,0,1,1,1,1,0,1,0,1,1,1,0,1,1,0,0,0,1,1,0,0,0,0,1,0,1,0,1,1,0,1,1,0,0,1,0,1,1,0,0,0,0,0,1,0,0,0,1,0,1,0,1,1,1,0,0,1,0,0,0,0,1,1,0,1,0,1,0,0,1,1,0,1,1,0,0,0,0,1,1,0,1,0,1,1,0,1},{1,1,0,0,0,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1,0,1,0,0,0,1,1,1,0,0,0,0,0,0,1,0,1,1,0,1,0,1,0,0,0,1,1,1,1,1,0,0,0,1,1,0,0,0,1,0,0,0,1,1,1,1,1,0,1,1,1,1,1,1,0,1,0,1,1,0,0,1,1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,1},{1,0,0,0,0,1,1,0,1,0,1,1,0,1,1,1,0,1,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,1,0,1,0,1,0,1,1,0,1,0,1,0,0,0,1,1,1,1,0,0,0,0,1,1,0,0,0,0,1,0,1,1,1,1,0,0,0,1,1,0,1,0,0,0,0,0,0,1,0,0,1,1,0,1,1,0,1,0,0,0,0,1,1,0,1,0},{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,1,1,1,1,0,1,0,1,0,0,0,1,0,0,1,1,0,1,0,1,1,0,1,0,0,1,0,1,0,0,1,0,0,0,0,0,1,1,0,0,0,0,1,0,0,1,1,1,1,0,0,1,0,0,1,1,0,0,0,1,1,0,1,0,0,1,0,0,0,1,1,1,0,0,1,0,0,0,0},{1,0,1,1,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,1,0,1,1,1,1,1,1,1,0,1,0,1,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,0,1,1,0,1,0,0,0,0,1,1,1,0,0,1,0,1,0,0,1,1,1,0,0,1,1,1,0,1,0,1,0,1,0,1,1,1,1,0,0,0,0,1,1,0,1},{1,0,0,1,1,1,0,1,0,0,1,1,1,0,0,1,0,0,1,1,0,1,1,0,0,0,0,0,1,0,0,0,1,0,0,1,1,0,0,0,1,1,1,0,0,1,0,0,0,0,1,1,0,0,1,0,1,1,0,1,0,1,1,0,0,1,0,0,0,0,1,1,0,0,1,1,1,0,1,0,1,1,1,1,1,1,0,0,1,0,0,1,0,1,1,0,0,1,0,0},{0,0,1,1,1,0,1,1,0,0,0,1,0,1,1,0,0,1,1,0,1,1,0,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,1,1,0,1,1,1,0,0,1,0,1,0,1,0,0,0,1,1,0,1,1,0,0,1,0,0,0,0,0,1,1,1,1,0,1,0,0,0,0,0,1,0,1,1,0,0,1,0,1,0,0,1,0,0,0,0,1},{0,1,0,1,0,0,0,0,0,0,1,0,1,0,0,0,1,1,1,0,0,1,0,1,0,1,1,0,1,1,1,0,1,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,0,1,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,0,1,0,1,1,0,1,1,0,1,0,0},{0,1,1,1,0,1,0,1,0,1,0,1,0,0,0,1,1,0,0,1,1,1,1,1,0,0,1,1,0,1,1,0,1,0,1,0,0,1,1,0,0,1,1,1,0,0,1,0,1,1,1,1,1,0,0,0,0,1,1,1,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,1,0,1,0,0,1,1,1,1,1,0,0,1,1,1,0,1,0},{1,0,0,1,0,1,0,1,0,1,1,0,1,0,1,0,1,0,1,1,1,1,0,0,0,1,0,0,1,1,1,0,1,1,0,1,0,0,1,0,1,0,1,1,0,1,0,1,1,0,1,1,0,1,0,1,1,1,0,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,0,0,1,0,1,0,0,1,0,1,1,1,1,1,0,1,1},{1,0,0,1,0,1,1,0,0,1,1,0,1,1,0,1,0,0,0,1,1,0,1,0,0,1,1,0,0,0,1,0,1,0,0,0,0,1,1,1,0,1,0,0,0,0,1,1,0,0,0,0,1,0,0,1,1,1,0,1,0,0,0,1,0,1,1,0,1,1,0,1,1,0,0,1,0,1,1,1,0,0,1,0,0,0,0,0,1,1,0,1,1,0,1,0,1,0,0,0},{0,1,0,0,0,1,0,1,1,1,1,1,1,0,1,1,0,1,0,0,1,0,1,1,1,0,0,0,0,0,1,1,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,0,0,1,1,0,0,0,0,1,0,1,0,0,1,0,1,0,1,0,0,1,0,1,0,0,0,1,0,0,1,0,0,1,0,1,1,0,1,1,0,1,0,0,0,0,1},{0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,0,1,0,0,0,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,1,1,0,0,0,1,1,1,0,1,1,0,1,0,1,0,0,1,0,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,1},{1,1,1,0,1,0,1,0,1,0,1,1,1,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,0,0,1,1,0,0,1,0,1,1,1,1,0,1,0,0,0,1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,1,1,1},{0,0,0,1,0,1,0,1,0,1,0,0,1,1,0,0,1,0,1,1,1,0,1,1,0,1,1,1,1,1,1,1,0,0,0,1,1,1,0,1,1,0,0,1,1,0,1,0,1,1,0,1,1,0,0,1,1,0,1,1,0,1,1,0,1,1,1,1,0,1,1,1,0,1,0,0,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,1,0,1,0,0,0,0,0,1},{1,0,1,1,0,0,0,1,1,1,0,0,1,0,1,1,1,0,1,0,1,1,1,0,0,0,0,0,1,1,1,0,1,0,1,0,0,0,0,1,0,0,1,1,0,0,0,0,0,1,1,1,1,0,0,1,0,0,0,1,0,1,0,1,0,1,1,1,0,1,0,0,1,0,1,1,1,1,0,0,0,1,0,0,0,1,1,0,1,0,0,0,0,1,1,1,1,0,1,1},{1,1,0,0,0,0,1,0,0,1,0,1,1,1,1,0,0,1,0,0,1,0,0,1,0,0,1,1,1,0,1,0,1,0,1,1,0,0,1,0,1,0,1,0,1,0,0,1,0,1,0,1,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,1,0,1,1,0,1,1,1,0,0,1,0,0,1,0,1,0,0,0,1,1,1,1,1,1,0,1},{0,1,0,0,1,0,0,1,0,1,0,0,1,1,1,0,1,1,1,1,0,1,0,0,0,1,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,1,1,0,1,1,0,0,1,1,1,0,1,1,0,0,1,0,1,1,0,0,1,0,1,0,1,0,0,0,0,1,1,1,0,1,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{1,0,0,0,1,1,0,1,1,1,1,1,1,1,0,1,1,0,0,1,1,1,0,0,0,1,0,1,1,0,1,0,0,1,0,0,1,0,0,1,1,1,0,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,0,0,1,1,0,0,1,1,0,1,0,0,1,0,1,1,1,0,1,1,0,0,1,0,0,0,0,0,0,0,1,1,0,0,1,1,1,1,0,1,1,0},{1,1,0,1,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1,1,0,0,1,0,1,1,0,1,0,0,1,1,1,0,1,1,1,0,1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,1,1,0,0,0,0,1,0,1,1,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,1,0},{0,1,1,0,1,1,0,0,0,1,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,1,1,0,1,0,0,0,1,0,0,0,1,1,0,0,0,0,1,1,0,1,0,0,1,0,0,0,0,0,1,1,1,0,0,1,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,1,1,0,0,0,1,1,1,0,0,0,1,0,0,0,1,0,0,0,0,1,1,1,0,0},{1,1,1,0,1,0,1,1,1,0,0,0,0,1,0,1,1,1,1,1,1,0,0,1,0,1,1,0,1,0,0,1,1,0,0,0,0,0,1,0,1,0,1,1,1,0,1,0,0,0,1,0,1,1,0,0,0,1,0,0,1,0,1,1,1,1,0,0,0,0,1,1,0,1,1,1,1,1,0,0,1,0,1,0,1,0,1,0,0,0,1,1,1,1,1,1,0,1,1,0},{0,1,0,0,0,0,0,1,1,1,0,1,1,1,1,0,1,1,0,1,1,1,1,0,1,1,1,0,0,1,1,1,0,1,0,0,0,1,0,1,1,1,0,0,0,1,1,1,0,0,1,1,1,0,0,1,0,1,1,1,0,0,1,0,0,1,1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,1,0,0,1,0,1,1,1,1,0,0,0,1,1,1,1,1,0},{1,1,1,0,1,0,0,1,0,0,0,0,0,1,1,0,0,0,0,1,0,1,0,0,1,0,0,1,0,1,1,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,1,1,0,0,0,1,0,0,1,0,1,1,0,1,1,1,0,1,0,1,0,0,1,0,1,0,1,0,1,1,0,1,1,0,0,1,0,1,1,0,0,1,0},{1,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,1,1,1,1,0,1,0,0,1,0,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,1,1,0,1,0,0,1,0,1,1,0,1,0,0,0,0,0,1,0,0,0,0,0,1,1,0,1,1,1,0,1,0,0,1,0,1,0,1,1,1,1,1},{0,0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,1,1,0,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,0,1,1,1,1,0,0,1,0,1,0,1,0,1,1,1,1,1,1,0,1,0,1,0,1,1,0,0,0,0,1,1,0,0,0,1,0,1,1,1,1,0,0,1,0,0,0,0,0,1,1,1,0,1,1,1,1,0,1,0,0,1,1,0},{1,0,1,0,0,0,0,0,1,1,1,0,1,0,0,0,1,1,0,1,0,1,1,1,1,0,1,1,1,0,0,0,1,0,1,1,1,0,0,1,1,0,1,1,0,0,1,0,0,0,0,0,1,1,1,1,0,1,1,1,1,1,0,0,0,1,0,1,0,1,1,0,0,1,0,1,0,0,0,1,0,0,0,1,0,1,0,1,1,0,1,0,0,0,0,0,1,1,1,1},{1,1,0,1,0,1,1,0,1,0,0,0,1,1,0,1,1,1,1,0,0,0,1,1,1,0,1,0,0,0,1,1,0,0,0,0,0,1,0,0,1,0,1,0,0,0,1,0,0,1,0,0,1,1,0,0,1,1,1,0,1,0,0,1,1,0,1,0,0,0,1,0,0,0,0,0,1,1,0,0,1,1,1,0,0,1,1,0,1,0,1,1,0,1,0,0,1,1,1,1},{1,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,1,1,1,1,1,0,1,1,1,1,1,0,1,0,0,1,1,0,0,0,0,0,0,1,0,0,0,1,1,1,0,0,1,0,0,0,0,0,1,0,0,1,1,1,1,0,1,1,1,1,0,1,1,0,1,0,1,1,0,1,1,1,0,0,0,1,1,1,0,1,0,0,1,0,0,0,1,0,1},{1,1,0,0,0,1,1,1,0,1,1,0,0,0,0,1,0,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,0,1,1,0,1,0,1,1,0,1,1,0,1,0,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,0,1,1,0,0,0,1,0,0,0,1,0,1,1,1,0,1,1,0,1,0,1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,1,0,0,1,1,0,1,1,0,1,0,0,0,1,0,1,1,1,0,1,1,1,0,1,1,0,0,0,1,0,1,1,1,1,1,1,1,1,0,1,0,0,1,1,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1,0,1,0,1,0,1},{0,0,1,1,1,1,0,1,0,0,1,0,0,1,0,0,1,0,1,1,0,0,1,1,0,0,1,1,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,1,1,0,1,1,0,1,0,1,1,0,0,1,0,0,1,0,1,0,0,1,1,0,0,0,0,1,1,1,0,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,0,0,1,1,0,0,0,1,1,1},{1,0,0,0,1,1,1,0,1,0,0,0,0,0,0,0,1,0,1,0,1,0,1,1,0,1,0,1,1,1,0,1,1,1,1,0,1,1,1,0,0,1,0,0,1,1,1,1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,1,0,1,0,1,1,1,1,1,0,1,0,0,0,1,1,0,0,0,0,1,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},{0,1,1,1,0,0,0,1,0,0,0,0,1,1,1,1,1,0,0,1,0,1,0,0,1,1,0,0,0,0,0,0,1,1,1,0,1,0,1,1,0,0,0,0,0,1,0,1,0,1,1,0,1,0,0,1,1,1,1,0,1,0,0,0,1,1,0,0,0,0,1,1,1,1,0,1,0,0,1,1,1,1,1,1,0,1,1,0,1,0,1,0,0,1,1,1,0,0,0,0},{0,1,1,0,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,1,0,1,1,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,1,0,0,0,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,0,0,1,0,0,0,1,0,1,1},{0,0,1,1,0,0,1,0,1,0,1,0,1,0,1,1,1,1,1,0,0,0,0,1,0,1,0,0,1,1,0,1,0,0,0,0,1,0,1,1,0,1,1,0,1,0,1,1,1,1,1,1,0,1,1,1,1,1,0,0,1,1,1,1,1,1,0,1,1,0,1,0,1,0,1,1,1,0,1,0,0,0,0,0,1,0,1,1,0,0,1,0,1,0,1,1,0,0,0,1},{0,1,0,1,0,0,1,0,0,0,0,0,0,1,1,0,1,0,0,0,1,0,1,1,1,0,1,1,0,1,1,0,1,0,1,0,0,1,0,1,0,0,1,0,1,1,0,1,1,1,1,0,0,1,1,0,0,1,0,0,1,1,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,0,1,1,1,1,0,0,1,1,0,0,1,1,1,0,1,1,1,0,0,0,1,0},{0,0,0,1,1,1,1,0,1,1,0,0,1,0,0,1,0,0,1,1,1,1,1,1,1,0,1,1,1,0,0,1,1,0,0,0,1,1,0,1,0,1,0,1,0,1,1,0,0,0,1,0,0,0,1,0,0,0,1,1,0,1,0,0,1,0,0,1,1,0,1,0,1,1,0,0,1,0,1,0,0,1,0,1,0,1,0,1,1,0,1,1,1,0,0,0,0,1,1,1},{0,1,0,0,0,1,0,1,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0,1,0,0,0,1,0,1,1,0,1,1,1,0,1,0,1,1,1,1,0,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,0,1,1,1,0,0,1,0,1,1,0,0,1,0,1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,0,0},{0,1,0,1,0,1,1,1,0,1,1,1,1,0,0,0,1,1,1,0,1,0,1,0,1,0,0,0,1,0,1,1,0,0,1,0,0,0,0,1,1,1,0,0,1,1,0,0,1,0,1,0,1,0,0,1,0,0,0,1,1,0,0,1,0,0,0,1,0,1,1,0,0,0,1,1,1,1,1,1,0,1,1,0,0,0,0,1,1,1,0,1,0,1,1,1,1,1,0,1},{0,0,0,1,0,0,0,0,1,0,0,1,1,0,1,1,0,1,1,1,1,0,1,0,1,0,1,0,0,1,1,1,1,1,1,0,0,1,0,0,1,0,0,0,0,0,1,1,1,0,0,0,1,1,0,0,0,0,1,0,1,1,1,1,1,0,1,0,1,0,1,1,0,0,0,0,1,0,0,1,0,1,0,0,0,0,1,0,1,1,0,0,0,0,0,1,0,1,0,0},{0,0,0,1,1,0,0,1,0,1,1,0,0,1,0,1,0,0,1,1,1,0,1,0,1,1,0,0,1,0,1,0,0,1,0,1,0,1,0,0,1,1,0,0,0,0,0,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,1,0,1,1,1,0,1,1,1,1,0,0,0,1,0,1,1,1,0,0,0,1,1,1,1,0,1,1,0,0,1,0,1,1},{1,0,0,0,1,1,0,0,0,1,1,0,0,0,0,1,1,1,0,0,1,1,0,1,0,1,0,1,1,1,0,1,1,0,0,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,1,0,0,1,1,0,1,0,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,1,0,0,0,0,0,1,1,0,1,0,0,0,0,0,0,1,1,1,1,0,1,0,0},{0,0,1,0,0,0,1,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,1,0,1,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,1,1,1,1,1,0,1,1,0,1,0,1,1,1,0,0,0,0,0,1,0,0,0},{1,0,1,0,1,0,1,0,1,1,1,1,0,0,1,0,0,1,1,1,0,1,0,0,1,0,1,0,0,0,1,0,1,0,1,1,1,0,1,1,1,0,0,1,1,1,0,0,1,1,0,0,1,0,0,0,0,1,1,0,1,0,1,1,1,1,0,1,0,0,0,1,1,0,0,0,1,0,1,1,0,0,1,0,1,0,1,1,1,0,1,1,0,0,0,0,1,1,0,1},{1,1,0,1,0,1,1,1,1,1,0,0,0,0,1,0,1,1,0,0,0,0,1,1,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,1,0,1,0,1,1,1,1,0,0,1,1,0,1,0,1,1,1,0,1,0,0,0,0,0,1,1,1,0,0,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0,0,1,1,1,1,0,0,0,1,1,0,1,0},{1,0,1,0,1,1,1,0,0,1,1,0,0,0,1,0,1,0,1,1,1,0,1,0,0,0,1,0,0,1,1,0,0,1,0,1,0,1,0,0,1,0,1,0,0,1,1,1,0,0,1,1,1,1,1,0,1,0,0,0,1,0,0,0,1,0,1,1,1,0,1,1,1,0,0,1,1,1,1,0,1,1,0,0,1,1,0,0,1,0,0,0,0,0,1,0,0,0,1,1},{0,1,1,1,1,0,1,0,1,1,1,0,0,0,1,1,1,1,0,0,0,0,1,0,1,1,1,1,1,1,0,0,1,1,1,0,0,1,0,1,1,1,1,1,0,1,0,0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,1,1,0,1,1,1,0,0,0,0,1,1,1,1,1,0,0,1,1,0,1,0,0,0,1,0,0,0,1,0,0,1,0,0,0},{0,0,1,0,1,1,0,1,0,0,0,0,1,0,0,1,1,0,0,1,0,1,1,1,0,0,0,0,1,0,1,1,0,1,0,0,0,0,1,0,1,1,1,0,0,0,0,1,1,0,1,1,1,1,1,0,0,1,0,1,1,1,1,1,1,1,0,0,1,0,1,0,0,1,1,1,0,0,0,1,1,0,0,1,0,0,1,1,0,1,0,0,1,1,1,0,0,0,1,0},{1,0,1,1,1,0,0,1,1,1,1,1,0,0,1,1,0,1,1,1,0,0,1,0,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,1,1,0,0,1,1,0,1,0,0,0,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,0,1,0,1,0,0,1,0,1,1,1,0,0,0,1,1,1,1,1,0,1,0,1,0,0,1,0,1,1,0,0,0,0,0},{1,0,1,0,1,0,0,0,0,1,0,1,1,1,0,1,1,1,0,1,0,0,0,1,0,1,1,1,1,1,0,1,1,1,1,0,1,0,0,1,0,1,1,0,1,1,1,0,0,0,1,0,1,0,0,0,0,1,0,1,0,1,0,0,1,0,1,1,0,1,1,0,1,0,1,1,1,0,0,0,1,1,0,0,1,1,1,1,0,0,0,1,1,0,1,0,0,1,1,1},{0,0,1,1,1,1,0,0,0,0,0,0,1,0,1,1,1,1,0,0,1,1,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,1,1,1,1,0,0,0,1,0,1,0,1,0,1,0,1,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1,0,0,1,1,0,0,1,1,0,1,0,0,0,1,0,1,0,0,0,0,1,1,0,0,1,1,0},{0,0,0,0,1,0,0,0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,0,0,0,0,1,0,1,1,0,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1,0,1,0,1,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0,1,1,1,0,1,1,1,1,1,0,1,0,1,0,1,0},{0,1,0,0,0,0,0,0,1,1,1,1,1,1,0,1,0,0,0,1,1,1,1,0,0,1,0,1,1,0,1,0,1,1,1,1,1,0,0,1,0,1,1,1,1,1,0,1,1,1,1,0,0,1,0,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,0,1,1,1,1,0,0,1,0,1,1,1,0,0,1,1,0},{0,1,0,0,0,1,1,1,1,0,0,1,0,1,1,1,0,1,1,1,0,0,0,0,1,0,1,1,1,1,1,0,0,0,1,0,0,1,0,0,1,0,1,0,0,1,0,1,0,1,0,0,0,0,0,1,0,1,1,1,1,1,1,0,0,1,1,0,1,1,1,1,0,1,0,1,0,1,0,1,0,0,1,1,1,1,1,0,1,0,1,1,0,1,0,0,0,0,0,1},{1,1,0,0,0,0,1,1,0,0,1,1,0,0,1,0,0,1,1,0,1,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,1,1,1,1,1,0,0,0,1,0,0,0,0,0,1,1,0,1,0,1,1,1,1,1,0,1,1,0,1,0,1,1,0,0,0,0,0,1,1,1,0,1,0,1,1,1,1},{0,0,1,0,0,1,1,0,1,0,0,0,1,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,1,0,1,0,0,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,0,0,0,0,1,1,1,0,1,0,1,1,1,0,0,1,1,1,1,0,1,1,0,0,1,0,1,1,1,0,1,1,0,0,1,1,0,0,0,1,0,1,1,1},{1,1,1,1,0,1,1,0,0,0,1,0,1,1,0,1,1,1,0,1,1,0,0,1,0,0,0,0,0,1,1,0,1,0,0,1,1,0,1,0,0,1,0,1,1,1,1,0,1,1,1,0,0,0,1,1,1,1,0,0,1,0,0,1,1,1,1,1,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0},{1,0,1,0,1,1,0,1,0,1,1,1,0,1,1,1,0,0,1,0,0,0,0,0,0,1,0,1,1,1,1,0,0,1,1,1,0,0,0,0,1,0,1,0,0,0,1,1,1,0,1,1,0,0,1,1,1,1,0,0,1,1,0,1,1,0,0,0,1,0,1,0,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,0,1,1,1,0,0,0,1,0,0,1,1,0},{0,0,1,0,1,1,1,1,1,1,1,1,0,0,0,1,1,0,0,1,1,1,0,1,1,1,1,0,0,0,0,0,1,1,1,0,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,1,1,0,0,1,0,1,0,0,0,1,0,0,0,1,1,1,1,0,1,1,0,0,0,1,1,0,1,1,1,1,1,0,1,0,0,1,1,1,1},{0,1,0,1,0,0,1,1,0,1,0,1,0,1,0,1,0,0,0,0,1,0,1,1,1,0,0,0,1,0,0,1,1,0,0,0,0,0,1,1,1,1,0,1,0,0,0,0,0,1,1,0,1,1,1,1,1,1,0,1,1,0,1,0,0,0,1,0,1,1,0,1,0,0,1,1,0,1,1,1,0,0,1,0,1,1,1,1,0,1,0,0,0,1,1,1,1,0,1,1},{1,1,1,1,1,1,0,0,1,0,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,0,1,1,0,1,0,1,1,0,1,1,1,1,0,0,1,0,0,1,1,1,0,1,1,0,0,0,0,1,0,0,0,1,0,1,1,0,0,1,1,0,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1,0,1,0,0,1,1,1,1,0,0,0,0,0,0,0},{1,1,0,1,1,1,0,0,0,1,1,1,1,1,0,0,1,1,0,0,0,1,0,0,0,1,0,0,1,1,0,1,1,0,1,0,0,0,0,0,0,1,0,1,0,1,1,1,0,0,0,1,1,0,1,1,1,1,0,0,1,1,0,0,1,0,1,1,1,1,0,0,0,1,0,0,0,1,0,1,0,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,1,0,0},{1,1,0,0,0,0,1,1,1,1,0,1,0,1,0,1,1,0,1,0,0,0,1,1,1,1,1,1,1,1,1,0,0,1,0,1,1,1,1,1,1,1,1,0,1,0,1,0,1,1,1,1,0,1,0,1,0,0,1,1,0,0,1,1,1,0,1,1,0,1,0,0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,1,0,0,1},{0,0,1,1,1,1,0,0,1,0,1,0,1,1,0,0,0,0,0,0,1,0,1,0,0,1,1,1,0,0,1,1,1,1,1,1,1,0,0,1,1,0,0,0,1,1,1,1,1,0,0,1,1,0,0,1,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,1,1,1,0,1,1,0,0,1,1,1,1,0,1,0,0,0,0,0,0,1,1,1,0,1,1,0,1,1},{1,0,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,1,1,0,1,0,0,0,0,0,0,1,0,1,1,1,0,0,1,0,1,1,0,1,0,0,0,0,0,1,0,0,1,0,1,0,0,1,1,0,1,0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,0,1,0,1,0,1,1,1,0,0,1,1,1,0,1,1,0,1,1,1,1,1,1,1},{0,1,0,0,1,1,0,1,1,1,1,1,1,0,1,1,0,0,1,0,0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,0,0,0,0,0,0,0,1,1,1,0,1,0,1,1,0,0,1,1,1,0,0,0,1,1,1,0,1,0,0,1,0,1,0,1,1,0,1,0,1,0,0,0,1,1,1,0,1,1,0,1,1,1,1,0,1,1},{1,1,0,1,0,0,1,1,1,1,0,1,0,0,1,0,1,1,1,0,1,1,1,0,0,0,0,0,0,0,1,1,0,1,1,1,0,1,0,0,1,1,1,0,0,1,0,1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,0,1,0,0,0,0,0,1,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0},{0,0,1,0,0,1,0,1,1,1,1,0,0,1,0,1,0,0,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,1,1,0,1,1,1,1,1,0,1,0,1,0,1,0,1,1,0,1,1,1,0,0,0,0,1,1,1,0,0,0,1,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,1,0,1,0,1,1,0,0,0,0,1,0,0,1,0,1},{0,0,1,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,1,0,0,0,0,0,0,0,0,1,1,0,1,1,0,1,1,1,0,0,0,1,0,0,0,1,0,1,0,0,1,1,0,1,0,0,1,0,0,0,1,0,1,0,1,0,1,0,0,0,1,1,0,1,1,1,1,1,0,0,0,1,1,0,1,0,1,0,1,1,0,0,1,0,1,0,1,0,1,0,1,1},{0,0,0,1,0,1,1,0,1,0,0,0,1,1,0,0,1,1,0,0,1,0,0,0,0,1,1,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,1,1,0,0,1,1,0,1,1,0,0,0,1,1,0,0,0,1,1,1,0,1,1,0,1,1,0,0,0,1,1,0,0,1,0,1,0,1,0,0,0,1,0,0,0,0,1,0,0,1,0,1,1,0,1,0,0,0},{0,1,0,1,0,1,0,1,1,1,0,0,0,1,0,0,1,0,1,0,1,1,0,0,0,1,1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,1,1,0,0,1,0,0,1,1,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,1,1,0,1,0,1,1,0,0,0,0,1,1,0,0,0,1,0,1,0,0,1,1,0,1,0,1,1},{0,1,1,0,1,0,0,0,1,0,1,0,0,0,0,1,0,1,1,1,1,0,1,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,0,1,1,0,1,1,0,1,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,1,1,0,1,0,1,0,1,0,1,1,1,1,0,0,0,1,0,1,1,0,0,1,1,0,1,0,0},{0,0,1,1,0,0,0,1,1,0,1,0,0,0,0,0,1,1,0,1,0,1,1,0,1,0,1,0,0,1,0,0,0,0,0,1,1,0,1,1,0,1,1,1,0,0,1,1,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,0,0,1,1,0,0,0,0,1,1,0,0,1,0,0,1,0,1,1,1,0,0,0,0,1,1,1,1,0,1,0}};
    printf("%d\n",shortestPathBinaryMatrix(grid));
    return 0;
}