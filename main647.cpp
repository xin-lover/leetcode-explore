//leetcode 647 回文子串

#include <cstdio>
#include <string>
#include <vector>

using namespace std;

int countSubstrings(string s) {
    //思路：暴力破解会超时
    //使用动归，dp[i][j]表示[i,j]是否是回文字符串，则dp[i][j] = s[i]==s[j]&&dp[i+1][j-1]

    int n = s.size();
    vector<vector<bool>> dp(n,vector<bool>(n,false));

    int res = 0;
    for(int i=n-1;i>=0;--i)
    {
        for(int j=i;j<n;++j)
        {
            if(s[i] == s[j] && (i+1>=j-1 || dp[i+1][j-1]))
            {
                dp[i][j] = true;
                printf("i:%d j:%d\n",i,j);
                ++res;
            }
            else
            {
                dp[i][j] = false;
            }
        }
    }

    return res;
}

int main()
{
    printf("%d\n",countSubstrings("aaaa"));
    return 0;
}