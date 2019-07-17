#include <cstdio>
#include <vector>
#include <string>

using namespace std;

int findMaxForm(vector<string>& strs, int m, int n) {
    //思路：先排序，也就是先构建长度小的字符串

    vector<vector<int>> dp(m+1,vector<int>(n+1,0));
    for(int i=1;i<=strs.size();++i)
    {
        int one=0;
        int zero =0;
        for(int j=0;j<strs[i-1].size();++j)
        {
            if(strs[i-1][j] == '0')
            {
                ++zero;
            }
            else
            {
                ++one;
            }
            
        }

        for(int j=m;j>=zero;--j)
        {
            for(int k=n;k>=one;--k)
            {
                dp[j][k] = max(dp[j][k],dp[j-zero][k-one] + 1);
            }
        }
    }

    return dp[m][n];
}

int main()
{
    vector<string> v = {"10", "0001", "111001", "1", "0"};
    // v = {"10", "0", "1"};
    // v = {"111","1000","1000","1000"};
    // int  m = 9, n = 3;
    v = {"011111","001","001"};

    printf("%d\n",findMaxForm(v,4,5));
    return 0;
}