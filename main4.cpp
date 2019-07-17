#include <cstdio>
#include <vector>

using namespace std;

int threeSumClosest(vector<int>& nums, int target) {
    
    if(nums.size() < 3)
    {
        return 0;
    }
    
    sort(nums.begin(),nums.end());
    int n = nums.size();
    
    long long res = INT_MAX;//max(abs(nums[n-1] + nums[n-2] + nums[n-3],abs(nums[0] + nums[1] + nums[2])));
    for(int i=0;i<nums.size() - 2;++i)
    {
        for(int j=i+1;j<n-1;++j)
        {
            int t = target - nums[i] - nums[j];
            int start = j+1,end = n-1;
            while(start < end)
            {
                int mid = start + (end - start) / 2;
                if(nums[mid] > t)
                {
                    end = mid;
                }
                else if(nums[mid] < t)
                {
                    start = mid + 1;
                }
                else
                {
                    return target;
                }
            }

            if((end == n-1 && nums[end] < t) || end == j+1)
            {
                res = abs(t-nums[n-1]) > abs(res - target) ? res : nums[i] + nums[j] + nums[end];
            }
            else
            {
                int s1 = nums[i] + nums[j] + nums[end];
                int s2 = nums[i] + nums[j] + nums[end-1];
                s1 = abs(s1-target) > abs(s2-target) ? s2 : s1;
                res = abs(res - target) > abs(s1-target) ? s1 : res;
            }
        }
    }
    
    return res;
}

int main()
{
    vector<int> v = {1,6,9,14,16,70};
    printf("%d\n",threeSumClosest(v,81));
    return 0;
}