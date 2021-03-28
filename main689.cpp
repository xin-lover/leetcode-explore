//689. 三个无重叠子数组的最大和

#include <cstdio>
#include <vector>

using namespace std;

vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
    //思路：因为k确定，所以我们可以计算出每一个可能的子数组的和
    //假设我们用贪心策略，每次都选择最大的子数组的和，那么，很明显，可能并不能得到最优解
    //设dp[i][j]表示区间{i,j}中子数组的最大和
    //那么dp[i][j+1] = max(dp[i][j],sum[j+1-k-1][j+1])

    if(k*3 > nums.size())
    {
        return {};
    }

    int n = nums.size();
    vector<int> sums(n+1,0);
    for(int i=0;i<n;++i)
    {
        sums[i+1] = sums[i] + nums[i];
    }


    vector<vector<int>> dp(n,vector<int>(n,-1));    //记录最大子数组的开始索引
    for(int i=0;i+k-1<n;++i)
    {
        for(int j=i+k-1;j<n;++j)
        {
            if(j-i+1 == k)
            {
                dp[i][j] = i;
            }
            else
            {
                int t = dp[i][j-1];
                if(sums[j+1]-sums[j+1-k] > sums[t+k]-sums[t])
                {
                    dp[i][j] = j-k+1;
                }
                else
                {
                    dp[i][j] = t;
                }
            }
        }
    }

    int maxSum = 0;
    vector<int> res;
    for(int i=k-1;i+2*k<n;++i)
    {
        for(int j=i+k;j+k<n;++j)
        {
            int h1 = dp[0][i];
            int h2 = dp[i+1][j];
            int h3 = dp[j+1][n-1];
            int sum1 = sums[h1+k]-sums[h1];
            int sum2 = sums[h2+k]-sums[h2];
            int sum3 = sums[h3+k]-sums[h3];
            if(sum1 + sum2 + sum3 > maxSum)
            {
                res = {h1,h2,h3};
                maxSum = sum1 + sum2 + sum3;
            }
        }
    }

    return res;
}

vector<int> maxSumOfThreeSubarrays2(vector<int>& nums, int k) {
    //思路：动规，考虑如果一个子数组的时候，我们很简单就能得到结果
    //我们用dp1[i]表示一个子数组时的结果,dp1[i+1] = max(dp1[i],sum(nums[i+1-k],...,nums[i+1]))
    //然后考虑两个子数组，假设dp2[i]表示两个子数组时的结果，那么对于dp2[i+1]，nums[i+1]如果不再第二个数组，那么dp2[i+1]=dp2[i],否则dp2[i+1]=dp1[i+1-k-1]+sum(nums[i+1-k]...,nums[i+1])
    //同理对3个子数组。。。

    int n = nums.size();
    if(n<3*k)
    {
        return {};
    }

    vector<int> preSums(n+1,0);
    for(int i=0;i<n;++i)
    {
        preSums[i+1] = preSums[i]+nums[i];
    }

    auto SumK=[&preSums,k](int i){
        return preSums[i+1]-preSums[i+1-k];
    };

    //一个数组的情况
    vector<int> dp1(n,-1);
    dp1[k-1] = 0;
    for(int i=k;i<n;++i)
    {
        int t = dp1[i-1];
        // if(preSums[t+k] - preSums[t] < preSums[i+1] - preSums[i+1-k])
        if(SumK(t+k-1) < SumK(i))
        {
            dp1[i] = i-k+1;
        }
        else
        {
            dp1[i] = t;
        }
    }

    vector<vector<int>> dp2(n,vector<int>(2,-1));
    dp2[2*k-1] = {0,k};
    for(int i=2*k;i<n;++i)
    {
        int a = dp2[i-1][0],b=dp2[i-1][1];
        int c = dp1[i-k];
        // if(preSums[a+k]-preSums[a] + preSums[b+k] - preSums[b] < preSums[i+1]-preSums[i+1-k] + preSums[c+k]-preSums[c])
        if(SumK(a+k-1) + SumK(b+k-1) < SumK(i) + SumK(c+k-1))
        {
            dp2[i] = {c,i-k+1};
        }
        else
        {
            dp2[i] = {a,b};
        }
    }

    vector<vector<int>> dp3(n,vector<int>(3,-1));
    dp3[3*k-1] = {0,k,2*k};
    for(int i=3*k;i<n;++i)
    {
        int a = dp3[i-1][0],b=dp3[i-1][1],c=dp3[i-1][2];
        int e = dp2[i-k][0],f=dp2[i-k][1];
        // if(preSums[a+k]-preSums[a]+preSums[b+k]-preSums[b]+preSums[c+k]-preSums[c] < preSums[i+1]-preSums[i+1-k] + preSums[e+k]-preSums[e])

        if(SumK(a+k-1)+SumK(b+k-1)+SumK(c+k-1) < SumK(i) + SumK(e+k-1) + SumK(f+k-1))
        {
            dp3[i] = {e,f,i-k+1};
        }
        else
        {
            dp3[i] = {a,b,c};
        }
    }    

    return dp3.back();
}


int main()
{
    vector<int> nums = {1,2,1,2,6,7,5,1};
    int k = 2; //[0, 3, 5]

    nums = {7,13,20,19,19,2,10,1,1,19};
    k=3;    //[1,4,7]

    auto res = maxSumOfThreeSubarrays2(nums,k);
    printf("%d %d %d\n",res[0],res[1],res[2]);

    return 0;
}