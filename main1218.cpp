//1218. 最长定差子序列

#include <cstdio>
#include <vector>

using namespace std;

int longestSubsequence(vector<int>& arr, int difference) {
    //思路：简单的方式就是确定首数字，然后等差序列就确定了
    //但这样遍历比较次数较多
    //可以考虑动归，dp[i]表示以arr[i]结尾的等差数列

    //超时

    vector<int> dp(arr.size(),1);
    int res = 1;
    for(int i=1;i<arr.size();++i)
    {
        for(int j=i-1;j>=0;--j)
        {
            if(arr[i] - arr[j] == difference)
            {
                dp[i] = max(dp[i],dp[j] + 1);
                res = max(dp[i],res);
            }
        }
    }

    return res;
}

int longestSubsequence2(vector<int>& arr, int difference) {
    //思路：因为只要确定一个数字，等差数列就可以确定了
    //我们用动归思路，dp[i]表示最后一项是i的等差数列长度

    int kMax = 40000;
    int res = 0;
    vector<int> dp(kMax * 2 + 1,0);
    for(int i=0;i<arr.size();++i)
    {
        int cur = arr[i];
        cur = cur + kMax;
        int last = cur - difference;
        if(last >=0 && last < dp.size())
        {
            dp[cur] =max(dp[cur], dp[last] + 1);
        }
        else    
        {
            dp[cur] = 1;
        }
        
        
        res = max(dp[cur],res);
    }
    // for(auto a : dp)
    // {
    //     printf("%d,",a);
    // }
    // printf("\n");

    return res;
}

int main()
{
    vector<int> arr = {1,2,3,4};
    int difference = 1; //4

    arr = {1,3,5,7};
    difference = 1; //1

    arr = {1,5,7,8,5,3,4,2,1};
    difference = -2;//4

    printf("%d\n",longestSubsequence2(arr,difference));
    return 0;
}