//1277. 统计全为 1 的正方形子矩阵

#include <cstdio>
#include <vector>

using namespace std;

int countSquares(vector<vector<int>>& matrix) {
    //思路：可以暴力求解，就是重复遍历太多
    //可以借鉴动归思路，dp[i][j]表示以以matrix[0][0],matrix[i][j]为左上，右下顶点的矩形中的1的个数
    //那么任意的矩形内1的个数都能用以下方式求解：
    //M(a,b,c,d)=(dp[c][d] - dp[a][d] - dp[c][b] + dp[a][b]))
    //然后遍历所有正方形子矩阵即可
    
    int m = matrix.size();
    int n = m ==0 ? 0 : matrix[0].size();

    vector<vector<int>> dp(m+1,vector<int>(n+1,0));
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            dp[i][j] = dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1]+matrix[i-1][j-1];
        }
    }

    int res = 0;
    for(int i=0;i<m;++i)
    {
        for(int j=0;j<n;++j)
        {
            if(matrix[i][j] != 1)
            {
                continue;
            }
            int mxLen = min(m-i,n-j);
            for(int k=1;k<=mxLen;++k)   
            {
                int right = j+k;
                int bottom = i+k;

                int count = dp[bottom][right] - dp[i][right] - dp[bottom][j] + dp[i][j];
                if(count == k*k)
                {
                    ++res;
                }
                else
                {
                    break;  //剪枝
                }
                
            }
        }
    }

    return res;
}   

//同样动归，f[i][j]表示以matrix[i][j]为右下角顶点的正方形最大边长，那么f[i][j] = min(f[i-1][j],f[i][j-1],f[i-1][j-1])+1
//确定最大边长x，包含这个点的正方形个数就是x，即(1,2,3,……,x)的边长各一个
int countSquares(vector<vector<int>>& matrix) {
    int m = matrix.size(), n = matrix[0].size();
    vector<vector<int>> f(m, vector<int>(n));
    int ans = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == 0 || j == 0) {
                f[i][j] = matrix[i][j];
            }
            else if (matrix[i][j] == 0) {
                f[i][j] = 0;
            }
            else {
                f[i][j] = min(min(f[i][j - 1], f[i - 1][j]), f[i - 1][j - 1]) + 1;
            }
            ans += f[i][j];
        }
    }
    return ans;
}

int main()
{
    vector<vector<int>> matrix =
    {
    {0,1,1,1},
    {1,1,1,1},
    {0,1,1,1}
    }; //15

    matrix = 
    {
    {1,0,1},
    {1,1,0},
    {1,1,0}
    };//7

    printf("%d\n",countSquares(matrix));
    return 0;
}