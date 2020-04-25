//1254. 统计封闭岛屿的数目

#include <cstdio>
#include <vector>

using namespace std;

void dfs(vector<vector<int>>& grid,int x,int y,int oldflag,int newflag)
{
    int m = grid.size();
    int n = grid[0].size();

    if(x >= 0 && x < m && y >=0 && y < n)
    {
        if(grid[x][y] == oldflag)
        {
            grid[x][y] = newflag;
            dfs(grid,x-1,y,oldflag,newflag);
            dfs(grid,x+1,y,oldflag,newflag);
            dfs(grid,x,y-1,oldflag,newflag);
            dfs(grid,x,y+1,oldflag,newflag);
        }
    }
}

int closedIsland(vector<vector<int>>& grid) {
    //思路：使用dfs+标记即可
    //包含数组边缘的不算岛屿,那么简单的做法就是再从边缘dfs，标记这些区域
    //不多遍dfs，可以让dfs返回是否到数组边缘

    int res = 0;
    for(int i=0;i<grid.size();++i)
    {
        for(int j=0;j<grid[i].size();++j)
        {
            if(grid[i][j] == 0)
            {
                ++res;
                dfs(grid,i,j,0,2);
            }
        }
    }

    int m = grid.size();
    int n = m == 0 ? 0 : grid[0].size();
    for(int i=0;i<m;++i)
    {
        if(grid[i][0] == 2)
        {
            --res;
            dfs(grid,i,0,2,0);
        }
        if(grid[i][n-1] == 2)
        {
            --res;
            dfs(grid,i,n-1,2,0);
        }
    }

    for(int i=0;i<n;++i)
    {
        if(grid[0][i] == 2)
        {
            --res;
            dfs(grid,0,i,2,0);
        }
        if(grid[m-1][i] == 2)
        {
            --res;
            dfs(grid,m-1,i,2,0);
        }
    }
    return res;
}

int main()
{
    //2
    vector<vector<int>> grid = {{1,1,1,1,1,1,1,0},{1,0,0,0,0,1,1,0},{1,0,1,0,1,1,1,0},{1,0,0,0,0,1,0,1},{1,1,1,1,1,1,1,0}};
    //2
    grid = {{1,1,1,1,1,1,1},
        {1,0,0,0,0,0,1},
        {1,0,1,1,1,0,1},
        {1,0,1,0,1,0,1},
        {1,0,1,1,1,0,1},
        {1,0,0,0,0,0,1},
        {1,1,1,1,1,1,1}};
    printf("%d\n",closedIsland(grid));
    return 0;
}