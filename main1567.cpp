//1567. 乘积为正数的最长子数组长度

#include <cstdio>
#include <vector>

using namespace std;

int getMaxLen(vector<int>& nums) {
    //思路：正数没影响，0不能要，所以关键在于负数的数量
    //我们可以记录当前遇到负数的数量，如果数量是偶数，可以计算一次长度
    //但需要注意全是正数的情况，所以我们同时记录一个正数的数量，这个数量在遇到负数后重新开始计数
    //还有一种没处理的情况，{-1,-1,-1,1,1}，这种情况可以反向再处理一次解决
    //我们也可以记录两个开始位置，一个是正数开始位置，一个是负数开始位置，当前是负数时，选择负数开始位置

    int res = 0;
    int pos_start = 0,neg_start=-1;
    int negtive=0,positive=0;
    for(int i=0;i<nums.size();++i)
    {
        if(nums[i] < 0)
        {
            ++negtive;
            positive = 0;
            if(neg_start < 0)
            {
                neg_start = i;
            }


        }
        else if(nums[i] > 0)
        {
            ++positive;
            res = max(res,positive);
            if(pos_start < 0)
            {
                pos_start = i;
            }
        }
        else
        {
            negtive = 0;
            positive = 0;
            
            neg_start = -1;
            pos_start = i+1;
            
        }

        if(!(negtive & 1))
        {
            res = max(res, i- pos_start + 1);
        }
        else
        {
            if(neg_start > -1)
            {
                res = max(res, i- neg_start);
            }
            
        }
    }

    return res;
}


int getMaxLen2(vector<int>& nums) 
{
    int res = 0;
    int pos_start = 0,neg_start=-1;
    bool isNeg = false;
    for(int i=0;i<nums.size();++i)
    {
        if(nums[i] < 0)
        {
            isNeg = !isNeg;
            if(neg_start < 0)
            {
                neg_start = i;
            }
        }
        else if(nums[i] > 0)
        {
            if(pos_start < 0)
            {
                pos_start = i;
            }
        }
        else
        {
            neg_start = -1;
            pos_start = i+1; 
            isNeg = false;

            continue;
        }

        if(!isNeg)
        {
            if(pos_start > -1)
            {
                res = max(res, i- pos_start + 1);
            }
        }
        else
        {
            if(neg_start > -1)
            {
                res = max(res, i- neg_start);
            }
            
        }
    }

    return res;
}

//动归思路
int getMaxLen3(vector<int>& nums) 
{
        int size = nums.size();
        
        vector<int> p_dp(size);
        vector<int> n_dp(size);
        
        p_dp[0] = nums[0] > 0 ? 1 : 0;
        n_dp[0] = nums[0] < 0 ? 1 : 0;      
        
        int result = p_dp[0];
        
        for (int i = 1; i < size; i++) {
            if (nums[i] > 0) {
                p_dp[i] = p_dp[i - 1] + 1;
                n_dp[i] = n_dp[i - 1] > 0 ? n_dp[i - 1] + 1 : 0;
            } else if (nums[i] < 0) {
                p_dp[i] = n_dp[i - 1] > 0 ? n_dp[i - 1] + 1 : 0;
                n_dp[i] = p_dp[i - 1] + 1;
            } else {
                p_dp[i] = 0;
                n_dp[i] = 0;
            }
            
            result = max(result, p_dp[i]);
        }
        
        return result;
}

int main()
{
    vector<int> nums = {1,-2,-3,4}; //4
    nums = {0,1,-2,-3,-4}; //3
    // nums = {-1,-2,-3,0,1}; //2
    // nums = {1,2,3,5,-6,4,0,10};//4

    // nums = {-1,2};  //1
    nums = {-1,-1};  //2

    // nums ={5,-20,-20,-39,-5,0,0,0,36,-32,0,-7,-10,-7,21,20,-12,-34,26,2};//8

    printf("%d\n",getMaxLen2(nums));

    return 0;
}