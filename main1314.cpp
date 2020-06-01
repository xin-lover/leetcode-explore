//1314. 矩阵区域和

#include <cstdio>
#include <vector>

using namespace std;

vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int K) {
    //思路：这个题可以暴力求解，但重复计算会很多，考虑动归来规避
    //其实还是子矩阵和，就是以[i,j]为中心2K+1为边长的正方形矩阵和

    int m = mat.size();
    int n = m== 0 ? 0 : mat[0].size();
    vector<vector<int>> dp(m+1,vector<int>(n+1,0));
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            dp[i][j] = dp[i-1][j] + dp[i][j-1]-dp[i-1][j-1]+mat[i-1][j-1];
        }
    }

    vector<vector<int>> res(m,vector<int>(n,0));
    for(int i=0;i<m;++i)
    {
        for(int j=0;j<n;++j)
        {
            int left = j-K < 0 ? 0 : j-K;
            int right = j+K >= n ? n-1 : j+K;
            int bottom = i+K >= m ? m-1 : i+K;
            int up = i-K < 0 ? 0 : i-K;

            res[i][j] = dp[bottom+1][right+1] -dp[bottom+1][left]-dp[up][right+1] + dp[up][left];
        }
    }

    return res;
}

int main()
{
    vector<vector<int>> mat = {{1,2,3},{4,5,6},{7,8,9}};
    int K = 1;  //[[12,21,16],[27,45,33],[24,39,28]]

    auto res = matrixBlockSum(mat,K);
    for(auto a : res)
    {
        for(auto b : a)
        {
            printf("%d ",b);
        }
        printf("\n");
    }

    return 0;
}