#include <cstdio>
#include <vector>

using namespace std;

bool canPartition(vector<int>& nums,int index,int sum,int cur)
{
    if(cur == sum - cur)
    {
        return true;
    }

    if(cur > sum-cur)
    {
        return false;
    }

    if(index >= nums.size())
    {
        return false;
    }

    return canPartition(nums,index+1,sum,cur) || canPartition(nums,index+1,sum,cur + nums[index]);
}

bool canPartition(vector<int>& nums) {
    //思路：使用回溯法
    int n = nums.size();
    vector<bool> flags(n,false);

    int sum = 0;
    for(int i=0;i<nums.size();++i)
    {
        sum += nums[i];
    }

    return canPartition(nums,0,sum,0);
}

int main()
{
    vector<int> v = {1,5,11,5};
    printf(canPartition(v) ? "true\n" : "false\n");
    v = {1,2,3,5};
    printf(canPartition(v) ? "true\n" : "false\n");
    v = {1,2,3,4};
    printf(canPartition(v) ? "true\n" : "false\n");
    v = {1};
    printf(canPartition(v) ? "true\n" : "false\n");
    v = {1,2};
    printf(canPartition(v) ? "true\n" : "false\n");
    return 0;
}