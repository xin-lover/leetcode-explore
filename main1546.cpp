//1546. 和为目标值的最大数目不重叠非空子数组数目

#include <cstdio>
#include <vector>
#include <unordered_map>

using namespace std;

int maxNonOverlapping(vector<int>& nums, int target) {
    //思路：先使用动归的方式试试，先记录前缀和
    //dp[i]表示以0到i的区间符合要求的子数组数目
    //那么dp[i] = max(dp[i], dp[j] + 1 or 0 pre[i]-pre[j] == target)
    //这个是O(n^2)的复杂度

    int n = nums.size();
    vector<int> preSums(n+1,0);
    for(int i=1;i<=n;++i)
    {
        preSums[i] = preSums[i-1] + nums[i-1];
    }

    vector<int> dp(n+1,0);
    for(int i=1;i<preSums.size();++i)
    {
        for(int j=i-1;j>=0;--j)
        {
            dp[i] = max(dp[i],dp[j] + (preSums[i] - preSums[j] == target ? 1 : 0));            
        }
    }

    return dp[n];
}

int maxNonOverlapping2(vector<int>& nums, int target) {
    //思路：借助两数之和的思路，同时维持一个数组arr,arr[i]表示到nums[i]时符合要求的最大数量
    //那么如果sum{nums[i+1],nums[j])==target,就让arr[i]+1
    //两数之和我们会在map中存储预期遇到的数，如果map中已经存在了，我们使用贪心策略，存储能使结果最大化的值

    unordered_map<int,int> um;
    um[target] = 0;
    vector<int> dp(nums.size()+1,0);
    int tmp = 0;
    int res = 0;
    for(int i=1;i<=nums.size();++i)
    {
        tmp += nums[i-1];
        dp[i] = res;
        if(um.find(tmp) != um.end())
        {
            // printf("tmp:%d v:%d\n",tmp,nums[i-1]);
            dp[i] = max(dp[i],dp[um[tmp]]+1);
            // printf("dp[i]:%d\n",dp[i]);
            res = max(res,dp[i]);
        }

        int tt = tmp + target;
        if(um.find(tt) != um.end() || dp[um[tt]] < dp[i])
        {
            um[tt] = i;
        }
        
    }

    return res;
}

//贪心策略，用hashmap优化了
// int maxNonOverlapping(vector<int>& nums, int target) {
//     int size = nums.size();
//     int ret = 0;
//     int i = 0;
//     while (i < size) {
//         unordered_set <int> s = {0};
//         int sum = 0;
//         while (i < size) {
//             sum += nums[i];
//             if (s.find(sum - target) != s.end()) {
//                 ret++;
//                 break;
//             } else {
//                 s.insert(sum);
//                 i++;
//             }
//         }
//         i++;
//     }
//     return ret;
// }

int main()
{
    vector<int> nums = {1,1,1,1,1};
    int target = 2; //2

    // nums = {-1,3,5,1,4,2,-9}, target = 6; //2

    // nums = {-2,6,6,3,5,4,1,2,8}, target = 10;   //3

    // nums = {0,0,0}, target = 0; //3
    nums = {-1,-2,8,-3,8,-5,5,-4,5,4,1},target=5;

    printf("%d\n",maxNonOverlapping2(nums,target));

    return 0;
}