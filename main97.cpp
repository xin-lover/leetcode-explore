//97. 交错字符串

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

bool isInterleave(string& s1,int left1,string& s2, int left2, string& s3, int left3)
{
    if(left3 >= s3.size())
    {
        return true;
    }

    if(left1 >= s1.size())
    {
        return left2 < s2.size() && s2[left2] == s3[left3] && isInterleave(s1,left1,s2,left2+1,s3,left3+1);
    }

    if(left2 >= s2.size())
    {
        return left1 < s1.size() && s1[left1] == s3[left3] && isInterleave(s1,left1+1,s2,left2,s3,left3+1);
    }


    if(s1[left1] == s2[left2])
    {
        if(s1[left1] != s3[left3])
        {
            return false;
        }

        return isInterleave(s1,left1+1,s2,left2,s3,left3+1) || isInterleave(s1,left1,s2,left2+1,s3,left3+1);
    }
    else
    {
        if(s1[left1] == s3[left3])
        {
            return isInterleave(s1,left1+1,s2,left2,s3,left3+1);
        }

        if(s2[left2] == s3[left3])
        {
            return isInterleave(s1,left1,s2,left2+1,s3,left3+1);
        }
    }

    return false;
    
}

bool isInterleave(string s1, string s2, string s3) {
    //思路：交错的意思就是要保持单词原来的顺序
    //考虑第一个字符，如果s1的和s2的不同，那么根据s3的当前字符是可以确定用哪个字符串的
    //所以要处理的就是s1和s2的当前位置字符相同且与s3当前字符一致。。。
    //考虑回溯法

    //超时

    if(s1.size() + s2.size() != s3.size())
    {
        return false;
    }

    return isInterleave(s1,0,s2,0,s3,0);
}

bool isInterleave2(string s1, string s2, string s3) {
    //思路：这里有个复杂度，就是对于长度为n的s3字符串，s1,和s2的组合有n+1种
    //而排列就更多了，而换一个想法，把s1分开s1.size个区间，我们可以选择在这些区间中放s2的字符
    //这个排列也太多了，所以这到题的难点在于选择太多了，复杂度高
    //还是要考虑动归
    //dp[i][j]表示s1前面i个字符和s2的前面j个字符是否能组成s3前面的i+j个字符
    //转换方程：dp[i][j] = （dp[i-1][j] && s1[i] == s3[i+j]) || (dp[i][j-1] && s2[j] == s3[i+j])

    int m = s1.size();
    int n = s2.size();
    int mn = s3.size();
    if(m+n != mn)
    {
        return false;
    }

    vector<vector<bool>> dp(m+1,vector<bool>(n+1,false));
    dp[0][0] = true;
    for(int i=0;i<=m;++i)
    {
        for(int j=0;j<=n;++j)
        {
            if(i>0)
            {
                dp[i][j] = dp[i][j] || (dp[i - 1][j] && s1[i - 1] == s3[i+j-1]);
            }
            if(j>0)
            {
                dp[i][j] = dp[i][j] ||(dp[i][j-1] && s2[j-1] == s3[i+j-1]);
            }
        }
    }

    return dp[m][n];
}

int main()
{
    string s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"; //true
    // s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc";  //false;
    printf(isInterleave2(s1,s2,s3) ? "true\n" : "false\n");

    return 0;
}