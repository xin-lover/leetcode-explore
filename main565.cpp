//leetcode 565 数组嵌套

#include <vector>
#include <cstdio>

using namespace std;

int arrayNesting(vector<int>& nums) {
    //思路：暴力破解，这个应该会超时
    //优化：使用标记，对每一个遍历后的位置标记为已遍历
    //每个数字是唯一的，也有事说同一个位置不会有两个数指向它

    vector<bool> states(nums.size(),false);
    int res = 0;
    for(int i=0;i<states.size();++i)
    {
        if(!states[i])
        {
            int pos = i;
            int len = 0;
            while(!states[pos])
            {
                ++len;
                states[pos] = true;
                pos = nums[pos];
            }

            res = max(res,len);
        }
    }

    return res;
}

int main()
{
    vector<int> v = {5,4,0,3,1,6,2};
    printf("%d\n",arrayNesting(v));
    return 0;
}