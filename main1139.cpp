//1139. 最大的以 1 为边界的正方形

#include <cstdio>
#include <vector>

using namespace std;

int largest1BorderedSquare(vector<vector<int>>& grid) {
    //思路：使用动归，dp[i][j]={x,y},x表示包含这个点时横向边最长的长度，y表示竖直方向的
    //那么我们先从左上到右下，然后再从右下到左上遍历，得到这些横向边和纵向边
    //最后我们相当于确定左上角和右下角的点以及边长来确定正方形

    //优化：不用记录一张表即可，dp[i][j]-dp[i][j-d]可以知道j到j-d之间1的个数
    //还有一种思路：记录dp1[i]表示到i位置时1的数量，那么dp1[i]-dp1[j]就可以知道i到j的1的个数

    int m = grid.size();
    int n = m==0 ? 0 : grid[0].size();
    if(m== 0 || n == 0)
    {
        return 0;
    }
    vector<vector<pair<int,int>>> dp1(m+1,vector<pair<int,int>>(n+1,{0,0}));
    vector<vector<pair<int,int>>> dp2(m+1,vector<pair<int,int>>(n+1,{0,0}));

    if(grid[0][0] == 1)
    {
        dp1[1][1] = {1,1};
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(grid[i-1][j-1] == 1)
            {
                dp1[i][j] = {dp1[i-1][j].first+1,dp1[i][j-1].second+1};
            }
        }
    }

    if(grid[m-1][n-1] == 1)
    {
        dp2[m-1][n-1] = {1,1};
    }

    int res = 0;
    for(int i=m-1;i>=0;--i)
    {
        for(int j=n-1;j>=0;--j)
        {
            if(grid[i][j] == 1)
            {
                int h = dp2[i+1][j].first+1;
                int v = dp2[i][j+1].second+1;
                dp2[i][j] = {h,v};
            }
            //现在相当于是左上角的点
            int ww = min(dp2[i][j].first,dp2[i][j].second);
            for(int k =0;k<ww;++k)
            {
                int ww2 = min(dp1[i+k+1][j+k+1].first,dp1[i+k+1][j+k+1].second);
                if(ww2 >= k+1)
                {
                    res = max((k+1)*(k+1),res);
                }
            }
        }
    } 

}

int main()
{
    vector<vector<int>> grid ={
        {1,1,1},
        {1,0,1},
        {1,1,1},
    };
    // grid = {{1,1,0,0}};

    // grid = {
    //     {1,1,0},
    //     {1,1,1},
    //     {1,1,1},
    //     {0,1,0},
    //     {1,1,1},
    //     {0,1,1},
    //     {1,1,1}};
    // grid = {
    //     {1,0,1,1},
    //     {0,0,0,1},
    //     {1,0,1,1},
    //     {1,1,1,0},
    //     {0,1,1,1},
    //     {1,1,1,0},
    //     {0,1,1,1},
    //     {0,1,1,1},
    //     {1,1,0,1}};

    // grid = {
    //     {0,1,1,1,1,1,1,0},
    //     {1,1,1,1,1,1,1,1},
    //     {1,0,1,1,1,0,1,1},
    //     {1,1,1,1,0,1,1,1},
    //     {1,0,1,0,0,1,1,1},
    //     {0,1,1,1,1,0,1,1}};
    std::printf("%d\n",largest1BorderedSquare(grid));
    return 0;
}