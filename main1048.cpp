//1048. 最长字符串链

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

bool isSub(const string& a, const string& b)
{
    if(b.size() != a.size()+1)
    {
        return false;
    }
    int i=0;
    for(int j=0;j<b.size();++j)
    {
        if(a[i] == b[j])
        {
            ++i;
        }
    }

    return i >= a.size();
}

int longestStrChain(vector<string>& words) {
    //思路：前身有相对顺序，还是考虑动归
    //前身的长度肯定小，所以先排序，按长度
    //dp[i]表示以第i个词结尾的词链的最长长度
    //注意是添加一个字母
    //这样的话其实可以按长度分组，这样复杂度没变，但摊还的复杂度会低一些

    sort(words.begin(),words.end(),[](const string& a, const string& b)
    {
        return a.size() < b.size();
    });

    vector<int> dp(words.size(),1);
    for(int i=0;i<words.size();++i)
    {
        for(int j=i+1;j<words.size();++j)
        {
            if(isSub(words[i],words[j]))
            {
                dp[j] = max(dp[j],dp[i]+1);
            }
        }
    }

    int res = 0;
    for(int i=0;i<dp.size();++i)
    {
        res = max(res,dp[i]);
    }

    return res;
}

int main()
{
    printf(isSub("a","ba") ? "true\n" : "false\n");
    vector<string> words = {"a","b","ba","bca","bda","bdca"};//4
    words = {"bqtmbnugq","bjqtmbnuwsgq","m"}; //1
    printf("%d\n",longestStrChain(words));
    return 0;
}

