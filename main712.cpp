//leetcode 712. 两个字符串的最小ASCII删除和

#include <cstdio>
#include <string>
#include <limits.h>
#include <vector>

using namespace std;

int backtrace(string& s1,string& s2,int index1,int index2)
{
    printf("index1:%d index2:%d\n",index1,index2);
    int x = 0; 
    int y = 0;
    int res = INT_MAX;
    if(index1 >= s1.size())
    {
        for(int i=index2;i<s2.size();++i)
        {
            x += s2[i];
        }

        printf("jjj:%d\n",x);
        return x;
    }
    for(int i=index1;i<s1.size();++i)
    {
        y=0;
        for(int j=index2;j<s2.size();++j)
        {
            if(s1[i] == s2[j])
            {
                int r = backtrace(s1,s2,i+1,j+1);
                printf("r:%d\n",r);
                if(x + y + r < res)
                {
                    res = x + y + r;
                }
            }
            y+=s2[j];
        }
        x+=s1[i];
    }

    return x+y < res ? x+y : res;
}

int minimumDeleteSum(string s1, string s2) {
    
    //思路：首先是找相同的子串，因为可以有多个不同的选择，所以使用回溯法，对于每个两者都存在的字符可以选择要或者不要
    //超时
    // return backtrace(s1,s2,0,0);

    //使用动归,dp[i][j]表示s1以第i位，s2以第j位结束时构造相同子串需要删除的最小数

    int m = s1.size();
    int n = s2.size();
    vector<vector<int>> dp(m+1,vector<int>(n+1,INT_MAX));
    dp[0][0] = 0;
    int sum = 0;
    for(int i=1;i<=n;++i)
    {
        sum += s2[i-1];
        dp[0][i] = sum;
    }

    sum = 0;
    for(int i=1;i<=m;++i)
    {
        sum += s1[i-1];
        dp[i][0] = sum;
    }

    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(s1[i-1] == s2[j-1])
            {
                dp[i][j] = min(dp[i][j],dp[i-1][j-1]);
            }
            else
            {
                dp[i][j] = min(dp[i][j],dp[i][j-1] + s2[j-1]);
                dp[i][j] = min(dp[i][j],dp[i-1][j] + s1[i-1]);
            }
            
        }
    }
    
    for(int i=0;i<=m;++i)
    {
        for(int j=0;j<=n;++j)
        {
            printf("%d ",dp[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    return dp[m][n];
}

int main()
{
    // printf("%d\n",minimumDeleteSum("delete","leet"));
    printf("%d\n",minimumDeleteSum("sea","eat"));
    return 0;
}