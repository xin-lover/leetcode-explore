//87. 扰乱字符串

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

bool isScramble(string& s1,int start1,int end1,string s2,int start2,int end2)
{
    if(start1 == end1)
    {
        return s1[start1] == s2[start2];
    }
    printf("is:%s %s\n",s1.substr(start1,end1-start1+1).c_str(),s2.substr(start2,end2-start2+1).c_str());
    vector<int> words(26,0);
    for(int i=start1,j=start2;i<=end1;++i,++j)
    {
        words[s1[i]-'a']++;
        words[s2[j]-'a']--;
    }

    for(auto a : words)
    {
        if(a != 0)
        {
            printf("%s %s\n",s1.substr(start1,end1-start1+1).c_str(),s2.substr(start2,end2-start2+1).c_str());
            return false;
        }
    }

    for(int i=start1;i<end1;++i)
    {
        if(isScramble(s1,start1,i,s2,start2,start2+i-start1)
            && isScramble(s1,i+1,end1,s2,start2+i-start1+1,end2))
        {
            printf("get 1\n");
            return true;
        }

        if(isScramble(s1,start1,i,s2,end2-(i-start1),end2)
            && isScramble(s1,i+1,end1,s2,start2,end2-(i-start1)-1))
            {
                printf("get 2\n");
                return true;
            }
    }

    return false;
}

bool isScramble(string s1, string s2) {
    //思路：根据题意，所有分割都可以
    //扰乱只是交换了前后部分，所以判断条件就是两个部分的字符相同
    //不用考虑顺序，使用递归
    //超时,递归相当于穷举，按照现在的递归，是自下而上的，而实际上，如果上面的不符合要求，下面的肯定就不行
    //所以应该提前判断上面的分割是否合法，再看下面的

    if(s1.size() != s2.size())
    {
        return false;
    }
    
    return isScramble(s1,0,s1.size()-1,s2,0,s2.size()-1);
}

bool isScramble2(string s1,string s2)
{
    //动归写法，dp[i][j][k]表示s1.substr(i,k) == s2.substr(j,k)
    //状态转移公式:dp[i][j][k] = (dp[i][j][w] && dp[i+w][j+w][k-w])
    // || (dp[i][j+k-w][w] && dp[i+w][j][k-w])

    if(s1.size() != s2.size())
    {
        return false;
    }

    int n = s1.size();
    bool dp[n][n][n+1];

    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            for(int k=0;k<=n;++k)
            {
                dp[i][j][k] = false;
            }
        }
    }

    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            dp[i][j][1] = s1[i] == s2[j];
        }
    }

    for(int len=2;len<=n;++len)
    {
        for(int i=0;i+len<=n;++i)
        {
            for(int j=0;j+len<=n;++j)
            {
                for(int k=1;k<len;++k)
                {
                    dp[i][j][len] |= dp[i][j][k] && dp[i+k][j+k][len-k];
                    dp[i][j][len] |= dp[i][j+len-k][k] && dp[i+k][j][len-k];
                }
            }
        }
    }

    return dp[0][0][n];
}

int main()
{
    string s1 = "great", s2 = "rgeat"; //true;
    // s1 = "abcde", s2 = "caebd"; //false;
    // s1="abcdefghijklmnopq", s2="efghijklmnopqcadb"; //false

    printf(isScramble2(s1,s2) ? "true\n" : "false\n");
    return 0;
}