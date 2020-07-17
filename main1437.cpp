//1437. 是否所有 1 都至少相隔 k 个元素

#include <cstdio>
#include <vector>

using namespace std;

bool kLengthApart(vector<int>& nums, int k) {
    //思路：先用最直观的解法试试，复杂度O(n)

    int start = -k-1;
    for(int i=0;i<nums.size();++i)
    {
        if(nums[i] == 1)
        {
            if(i-start-1 >= k)
            {
                start = i;
            }
            else
            {
                return false;
            }
            
        }
    }

    return true;
}

int main()
{
    vector<int> nums = {1,0,0,0,1,0,0,1};
    int k = 2;

    nums = {1,0,0,1,0,1};
    k = 2;

    printf(kLengthApart(nums,k) ? "true\n" : "false\n");

    return 0;
}