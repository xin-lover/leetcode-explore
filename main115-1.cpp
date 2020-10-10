//115. 不同的子序列

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

int numDistinct(string s, string t) {
    //思路：穷举法+提前剪枝
    //另外就是动归，dp[i][j]表示s中前i个数中符合t的前j个字符的子序列个数

    int m=s.size();
    int n = t.size();
    vector<vector<int>> dp(m+1,vector<int>(n,0)); //这个地方可以用滚动数组优化，不用二维数组
    for(int i=0;i<m;++i)
    {
        for(int j=0;j<n;++j)
        {
            if(s[i] == t[j])
            {
                if(j == 0)
                {
                    dp[i+1][j] = dp[i][j] + 1;
                }
                else
                {
                    dp[i+1][j] = dp[i][j] + dp[i][j-1];
                }
                // printf("%d %d %d\n",i,j,dp[i+1][j]);
            }
            else
            {
                dp[i+1][j] = dp[i][j];
            }
            
        }
    }

    return dp[m][n-1];
}

int main()
{
    string S = "rabbbit", T = "rabbit"; //3
    S = "babgbag", T = "bag";   //5
    printf("%d\n",numDistinct(S,T));

    return 0;
}