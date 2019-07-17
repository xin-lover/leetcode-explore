#include <vector>
#include <cstdio>

using namespace std;

class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        
        //思路：子序列，可以不连续，只是集合中的有序子集
        //其实就是找有多少个波峰波谷
        
        if(nums.size() < 2)
        {
            return nums.size();
        }

        int first = -1;
        for(int i=0;i<nums.size()-1;++i)
        {
            if(nums[i] != nums[i+1])
            {
                first = i;
                break;
            }
        }

        if(first == -1)
        {
            return 1;
        }

        int lastDir = 0;
        int res = 2;
        for(int i=first+1;i<nums.size();++i)
        {
            if(nums[i] == nums[i-1])
            {
                continue;
            }
            else if(nums[i] < nums[i-1])
            {
                if(lastDir > 0)
                {
                   ++res;
                }

                lastDir = -1;
            }
            else
            {
                if(lastDir < 0)
                {
                    ++res;
                }

                lastDir = 1;
            }
        }
        
        return res;
    }
};

int main()
{
    Solution s;
    vector<int> nums = {1,7,4,9,2,5};
    printf("%d\n",s.wiggleMaxLength(nums));
    return 0;
}