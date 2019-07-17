#include <vector>

using namespace std;

int backtrace(vector<int>& nums,int target)
{
    if(target < 0)
    {
        return 0;
    }
    if(target == 0)
    {
        return 1;
    }

    int res = 0;
    for(int i=0;i<nums.size();++i)
    {
        res += backtrace(nums,target - nums[i]);
    }

    return res;
}

int main()
{
    vector<int> nums = {5,1,8};
    printf("%d\n",backtrace(nums,24));
    return 0;
}