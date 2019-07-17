//576 出界的路径数

#include <cstdio>
#include <vector>

using namespace std;

int dfs(int m,int n,int N, int i,int j,vector<vector<long long>>& flags)
{
    if(i < 0 || i >= m || j < 0 || j >= n)
    {
        return 1;
    }
    else
    {
        if(N > 0)
        {
            if(flags[i][j] == -1)
            {
                flags[i][j] = dfs(m,n,N-1,i-1,j,flags)
                            +dfs(m,n,N-1,i+1,j,flags)
                            +dfs(m,n,N-1,i,j-1,flags)
                            +dfs(m,n,N-1,i,j+1,flags);

                int mx = 1000000000+7;
                if(flags[i][j] >= mx)
                {
                    flags[i][j] %= mx;
                }
            }

            return flags[i][j];
        }
    }

    return 0;
}

int findPaths(int m,int n,int N,int i,int j)
{
    //思路：动归，但是是三位的动归，第三位表示在（i，j）位置还剩几步
    vector<vector<vector<long long>>> dp(m,vector<vector<long long>>(n,vector<long long>(N+1,0)));

    vector<pair<int,int>> dirs = {{0,-1},{0,1},{1,0},{-1,0}};
    for(int k=1;k<=N;++k)
    {
        for(int x=0;x<m;++x)
        {
            for(int y=0;y<n;++y)
            {
                for(auto dir : dirs)
                {
                    int nx = x + dir.first;
                    int ny = y + dir.second;
                    if(nx < 0 || nx >=m || ny < 0 || ny >= n)
                    {
                        dp[x][y][k] += 1;
                    }
                    else
                    {
                        dp[x][y][k] = (dp[x][y][k] + dp[nx][ny][k-1]) % (1000000007);
                    }
                    
                }
            }
        }
    }

    return dp[i][j][N];

}

// int findPaths(int m, int n, int N, int i, int j) {
//     // //思路：dfs,结果超时
//     // vector<vector<long long>> flags(m,vector<long long>(n,-1));
//     // dfs(m,n,N,i,j,flags);
//     // return flags[i][j] == -1 ? 0 : flags[i][j];

//     //思路：四个边界，我们考虑如果先确定出界的边界，然后统计剩下的步数路径的可能数
//     //比如确定右边界出线，剩下两步，这两步保证最终不能往左边走且不出界即可

//     int step = j+1;
//     //考虑整体往左边走
//     int s1 = 

//     step = n-j;

//     step = i+1;

//     step = m-i;
// }

int main()
{
    printf("%d\n",findPaths(2,2,2,0,0));
    // printf("%d\n",findPaths(1,3,3,0,1));
    // printf("%d\n",findPaths(10,10,0,5,5));
    return 0;
}

