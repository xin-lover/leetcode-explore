//1219. 黄金矿工

#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

void dfs(vector<vector<int>>& grid,vector<vector<bool>>& flags, int x,int y,int gold,int& maxGold)
{
    int m = grid.size();
    int n = m == 0 ? 0 : grid[0].size();

    if(x < 0 || x >= m || y <0 || y >= n)
    {
        return;
    }

    if(flags[x][y] || grid[x][y] == 0)
    {
        return ;
    }

    flags[x][y] = true;
    gold += grid[x][y];

    maxGold = max(gold,maxGold);

    dfs(grid,flags,x+1,y,gold,maxGold);
    dfs(grid,flags,x-1,y,gold,maxGold);
    dfs(grid,flags,x,y+1,gold,maxGold);
    dfs(grid,flags,x,y-1,gold,maxGold);

    flags[x][y] =false;
}

int getMaximumGold(vector<vector<int>>& grid) {
    //思路：用dfs

    int m = grid.size();
    int n = m == 0 ? 0 : grid[0].size();
    int res = 0;

    vector<vector<bool>> flags(m,vector<bool>(n,false));
    int gold = 0;
    for(int i=0;i<m;++i)
    {
        for(int j=0;j<n;++j)
        {
            dfs(grid,flags,i,j,0,res);
        }
    }

    return res;
}

int main()
{
    vector<vector<int>> grid = {{0,6,0},{5,8,7},{0,9,0}}; //24
    grid = {{1,0,7},{2,0,6},{3,4,5},{0,3,0},{9,0,20}};  //28
    printf("%d\n",getMaximumGold(grid));
    return 0;
}