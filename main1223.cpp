//1223. 掷骰子模拟

#include <cstdio>
#include <vector>

using namespace std;

int dieSimulator(int n, vector<int>& rollMax) {
    //思路：总的可能是6的n次方，减去不符合要求的就是最后的结果
    //不符合要求的就是连续出现的序列，对于其中一个数字很简单
    //但问题在于重复的如何计算?
    //可以考虑动归，dp[i][j]表示数字为i，连续次数为j的数字总数
    //我们每次递进一次，也就是掷一次，那么如果这一次与上一次的数字相同
    //那么dp[i][j+1] = dp[i][j]
    //如果不同,假设新掷的是k，那么dp[k][1] = sum(dp[ii!=i][1],dp[ii!=i][1]...)

    int kMod = 1e9 + 7;
    vector<vector<int>> dp(6,vector<int>(16,0));
    vector<int> total(6,0); //表示以i结尾的序列的总数
    for(int i=0;i<6;++i)
    {
        dp[i][1] = 1;
        total[i] = 1;
    }

    for(int k=2;k<=n;++k)
    {
        vector<vector<int>> tmp(6,vector<int>(16,0));
        for(int i=0;i<6;++i)    //当前掷的i
        {
            for(int j=0;j<6;++j) //上一次掷的j
            {
                if(i != j)
                {
                    tmp[i][1] = (tmp[i][1] + total[j])%kMod;
                }
            }

            for(int x=2;x<=rollMax[i];++x)
            {
                tmp[i][x] = dp[i][x-1];
            }
        }

        for(int j=0;j<6;++j)
        {
            total[j] = 0;
            for(int x =1;x<=rollMax[j];++x)
            {
                total[j] = (total[j] + tmp[j][x]) % kMod;
            }
        }
        swap(dp,tmp);
    }

    int res = 0;
    for(int i=0;i<6;++i)
    {
        res = (res + total[i]) % kMod;
    }

    return res;

}

int main()
{
    int n=2;
    vector<int> rollMax = {1,1,2,2,2,3};    //34

    // n=2;
    // rollMax = {1,1,1,1,1,1}; //30

    // n = 3;
    // rollMax = {1,1,1,2,2,3}; //181

    printf("%d\n",dieSimulator(n,rollMax));
    return 0;
}