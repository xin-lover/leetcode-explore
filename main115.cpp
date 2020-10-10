//115. 不同的子序列


#include <cstdio>
#include <vector>
#include <string>

using namespace std;

int numDistinct(string& s,int index, string& t, int cur)
{
    if(index >= s.size())
    {
        return 0;
    }

    if(cur >= t.size())
    {
        return 1;
    }

    if(s[index] == t[cur])
    {
        return numDistinct(s,index+1,t,cur+1);
    }
}

int numDistinct(string s, string t) {
    //思路：穷举法应该会超时
    //考虑动归，dp[i][j]表示t的前j位在s的前i位的字符串中的数量
    //那么dp[i][j] = (dp[i-1][j-1] | s[i] == t[(j-1+m)mod m]) + dp[i-1][j]
    //

    int m = s.size();
    int n = t.size();

    vector<vector<int>> dp(m+1,vector<int>(n+1,0));
    dp[0][0] = 1;
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            dp[i][j] = dp[i-1][j];
            if(t[j-1] == s[i-1])
            {
                dp[i][j] += dp[i-1][(j-2 + n)%n];
            }
            printf("i:%d j:%d  %d\n",i,j,dp[i][j]);
        }
    }

    return dp[m][n];
}

int main()
{
    string S = "rabbbit", T = "rabbit"; //3
    S = "babgbag", T = "bag";   //5

    printf("%d\n",numDistinct(S,T));

    return 0;
}