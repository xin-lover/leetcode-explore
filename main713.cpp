//leetcode 713. 乘积小于K的子数组

#include <cstdio>
#include <vector>

using namespace std;

int numSubarrayProductLessThanK(vector<int>& nums, int k) {
    
    //思路：1.暴力破解
    //2.如果[i,j]中的数的乘积小于k，则其子数组肯定都小于k，

    int left = 0;
    int right = 0;
    int p = 1;
    int res = 0;
    while(right < nums.size())
    {
        p *= nums[right];
        printf("p:%d\n",p);
        if(p<k)
        {
            ++right;
        }
        else
        {
            if(right > left)
            {
                int c = right - left;
                printf("c:%d\n",c);
                res += c;

                p /= nums[left];
                ++left;
                p /= nums[right];
            }
            else
            {
                printf("get:%d %d\n",left,right);
                ++left;
                right = left;
                p = 1;
            }
        }
        
    }

    printf("left:%d\n",left);
    for(int i=left;i<right;++i)
    {
        res += right - i;
    }

    return res;
}

int main()
{
    vector<int> nums = {10,5,2,6};
    nums = {1,1,8,1};
    printf("res:%d\n",numSubarrayProductLessThanK(nums,5));
    return 0;
}