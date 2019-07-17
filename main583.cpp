#include <string>
#include <cstdio>
#include <unordered_map>
#include <vector>

using namespace std;

void backtrace(const string& word1,const string& word2,int p1,int p2,int len,int& res)
{
    if(p1 >= word1.size() || p2 >= word2.size())
    {
        res = max(res,len);
        return ;
    }

    //剪枝
    if(len + word1.size() - p1 <= res || len + word2.size() - p2 <= res)
    {
        return;
    }

    //p1位置留下
    for(int i=p2;i<word2.size();++i)
    {
        if(word1[p1] == word2[i])
        {
            backtrace(word1,word2,p1+1,i+1,len+1,res);
            break;
        }
    }

    //p1位置去掉
    backtrace(word1,word2,p1+1,p2,len,res);
}

int minDistance(string word1, string word2) {
    
    //思路：找取两个字符串的距离，也就是不同字符数
    //但需要处理顺序，即ea和ae是不同的
    //使用回溯法暴力破解

    // int res = 0;
    // backtrace(word1,word2,0,0,0,res);
    // return word1.size() + word2.size() - 2 * res;

    //动归,dp[i][j]表示word1前i个字符和word2前j个字符的最长公共子序列

    int m = word1.size();
    int n = word2.size();

    vector<vector<int>> dp(m+1,vector<int>(n+1,0));
    int mxLen = 0;
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(word1[i-1] == word2[j-1])
            {
                dp[i][j] = dp[i-1][j-1] + 1;
            }
            else
            {
                dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
            }

            mxLen = max(mxLen,dp[i][j]);
        }
    }

    return m+n-2*mxLen;


}

int main()
{
    printf("%d\n",minDistance("sea","eat"));
    printf("%d\n",minDistance("acd","acd"));
    printf("%d\n",minDistance("acdvhiud","acd"));
    printf("%d\n",minDistance("abcd","acebchdf"));
    return 0;
}