//1371. 每个元音包含偶数次的最长子字符串

#include <cstdio>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

int findTheLongestSubstring(string s) {
    //思路：用位的思路，异或运算可以知道字符是否出现偶数次
    //利用前缀和的思路，在每个出现元音字符出现的点记录
    //O(n^2)的复杂度，性能太低,我们发现，我们要找的就是相同的flag，而对这个flag我们只需要最早出现和最晚出现的地方
    //所以可以使用map记录flag和它的最早出现位置，这样可以实现O(n)的复杂度

    vector<int> dp(s.length()+1,0);
    vector<bool> vowel(26,false);
    vowel['a'-'a']=true;
    vowel['e'-'a']=true;
    vowel['i'-'a']=true;
    vowel['o'-'a']=true;
    vowel['u'-'a']=true;

    int flag = 0;
    for(int i=0;i<s.length();++i)
    {
        if(vowel[s[i]-'a'])
        {
            flag ^= (1 << (s[i]-'a'));
        }
        dp[i+1] = flag;
    }

   
    int res = 0;
    for(int i=0;i<dp.size();++i)
    {
        for(int j=dp.size()-1;j>=0;--j)
        {
            int t = (dp[j] ^ dp[i]);
            if(dp[i]==dp[j])
            {
                res = max(res,j-i);
                break;
            }
        }
    }

    return res;
}

int findTheLongestSubstring2(string s) {
    //思路：用位的思路，异或运算可以知道字符是否出现偶数次
    //利用前缀和的思路，在每个出现元音字符出现的点记录

    vector<bool> vowel(26,false);
    vowel['a'-'a']=true;
    vowel['e'-'a']=true;
    vowel['i'-'a']=true;
    vowel['o'-'a']=true;
    vowel['u'-'a']=true;

    int res = 0;
    int flag = 0;
    unordered_map<int,int> um;
    um[0]=-1;
    for(int i=0;i<s.length();++i)
    {
        if(vowel[s[i]-'a'])
        {
            flag ^= (1 << (s[i]-'a'));            
        }

        if(um.find(flag) == um.end())
        {
            um[flag] = i;
        }
        else
        {
            res = max(res,i-um[flag]);
        }
    }

    return res;
}

int main()
{
    printf("%d\n",findTheLongestSubstring2("eleetminicoworoep"));    //13
    printf("%d\n",findTheLongestSubstring2("leetcodeisgreat"));    //5
    printf("%d\n",findTheLongestSubstring2("bcbcbc"));//6
    return 0;
}