//leetcode 698. 划分为k个相等的子集

#include <cstdio>
#include <vector>

using namespace std;

bool findSubsets(vector<int>& nums,vector<int>& buckets,int index,int target)
{
    if(index >= nums.size())
    {
        return true;
    }

    for(int i=0;i<buckets.size();++i)
    {
        //提前剪枝
        if(buckets[i] + nums[index] <= target)
        {
            buckets[i] += nums[index];
            if(findSubsets(nums,buckets,index+1,target))
            {
                return true;
            }
            buckets[i] -= nums[index];
        }
    }

    return false;
}

bool canPartitionKSubsets(vector<int>& nums, int k) {
    //思路：先求和，如果和不能被k整除，则肯定不能
    //如果存在多种分法，则表示其中有几种组合是等价的，我们任选一种都可以

    if(nums.size() < k )
    {
        return false;

    }

    int sum = 0;
    for(int i=0;i<nums.size();++i)
    {
        sum += nums[i];
    }

    if(sum % k != 0)
    {
        return false;
    }

    int ag = sum / k;
    //这个排序很关键，能提前剪枝很多
    sort(nums.begin(),nums.end());
    if(nums.back() > ag)
    {
        return false;
    }

    //接下来的策略是，每次从剩余数中选取最大的数
    vector<int> buckets(k,0);
    return findSubsets(nums,buckets,0,ag);
}

int main()
{
    vector<int> nums = {4, 3, 2, 3, 5, 1};
    // nums = {10,10,10,7,7,7,7,7,7,6,6,6};
    // nums = {5,2,5,5,5,5,5,5,5,5,5,5,5,5,5,3};
    printf(canPartitionKSubsets(nums,3) ? "true\n" : "false\n");
    return 0;
}