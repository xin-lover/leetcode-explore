//leetcode 873. 最长的斐波那契子序列的长度

#include <cstdio>
#include <vector>
#include <unordered_map>

using namespace std;

int lenLongestFibSubseq(vector<int>& A) {
    //思路：可以暴力破解，复杂度太高
    //数组是递增的，所以查找使用二分，如果开头的两个数确定，那数组最终就能确定
    //问题是如何避免重复计算
    //考虑动归，dp[i][j]表示A[i][j]加入子序列后长度
    //则dp[i][j] = dp[A.index(A[j]-A[i])][i] + 1

    //这个其实还是相当于暴力破解

    unordered_map<int,int> um;
    for(int i=0;i<A.size();++i)
    {
        um[A[i]] = i;
    }

    int n = A.size();
    vector<vector<int>> dp(n,vector<int>(n,1));
    int res = 0;
    for(int i =0;i<n;++i)
    {
        for(int j=i+1;j<n;++j)
        {
            int t = A[j] - A[i];
            //这个操作较多，可以优化
            int left = 0,right = n-1;
            int ti = -1;
            // while(left <= right)
            // {
            //     int mid = left + (right - left) / 2;
            //     if(A[mid] > t)
            //     {
            //         right = mid - 1;
            //     }
            //     else if(A[mid] < t)
            //     {
            //         left = mid+1;
            //     }
            //     else
            //     {
            //         ti = mid;
            //         break;
            //     }
            // }

            if(um.find(t) != um.end())
            {
                ti = um[t];
            }

            if(ti == -1)
            {
                dp[i][j] = 2;
            }
            else
            {
                dp[i][j] = dp[ti][i] + 1;
            }

            res = max(dp[i][j],res);
        }
    }

    return res < 3 ? 0 : res;
}

int main()
{
    vector<int> v = {1,2,3,4,5,6,7,8};//5
    printf("%d\n",lenLongestFibSubseq(v));

    v = {1,3,7,11,12,14,18};//3
    printf("%d\n",lenLongestFibSubseq(v));

    return 0;
}