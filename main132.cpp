//132. 分割回文串 II

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

int minCut(string s) {
    //思路：简化问题，先不考虑最少，那么切分为单个字符就行
    //考虑最少的话，我们可以考虑动归
    //假设dp[i]是s前i个字符的最少切割数，那么dp[i+1]是min{dp[j]+1 |sub(j+1,i+1)是回文)
    //这样我们会产生一个O(n^2)的算法，而且重复遍历会很多


    int n = s.size();
    vector<int> dp(n+1,n);
    dp[0] = 0;
    for(int i=1;i<=n;++i) //长度
    {
        for(int j=0;j<=i;++j) //起始位置
        {
            int t = 1;
            int len = i-j;
            int halfLen= len / 2;
            for(int k=0;k<halfLen;++k)  //这里可以优化，利用预处理存储dp[i][j]是否是回文。。。。
            {
                if(s[j+k] != s[j+len-k-1])
                {
                    t = len;
                    break;
                }
            }
            dp[i] = min(dp[i],dp[j]+t);
        }
    }

    return dp[n]-1;
}

//判断回文，中心判断法，在s[i]时，我们判断s[i-1]和s[i+1],s[i-2]和s[i+2]等等
//当然还有以s[i],s[i+1]为中心的方法。。。。

int main()
{
    string s = "aab"; //2
    printf("%d\n",minCut(s));
    return 0;
}

