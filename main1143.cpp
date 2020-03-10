//1143. 最长公共子序列

#include <cstdio>
#include <string>
#include <vector>

using namespace std;


int longestCommonSubsequence(string text1, string text2) {
    //考虑动归，dp[i][j]表示text前i个字符和text2前j个字符的最长公共子序列长度
    //则dp[i][j] = max(dp[i][j-1],dp[i-1][j], dp[i-1][j-1] + (text1[i] == text2[j]))

    //优化，可以使用一维数组滚动

    int m = text1.size();
    int n = text2.size();

    vector<vector<int>> dp(m+1,vector<int>(n+1,0));

    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
            dp[i][j] = max(dp[i][j],dp[i-1][j-1] + (text1[i-1] == text2[j-1] ? 1 : 0));
        }
    }

    return dp[m][n];
}

int main()
{
    string text1 = "abcde", text2 = "ace" ;//3
    text1 = "abc", text2 = "abc";   //3
    // text1 = "abc", text2 = "def"; //0
    printf("%d\n",longestCommonSubsequence(text1,text2));
    return 0;
}