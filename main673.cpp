//leetcode 673. 最长递增子序列的个数

#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

void findNumberOfLIS(vector<int>& nums,vector<int>& cur,int index,int& maxLen,int& count)
{
    if(cur.size() > maxLen)
    {
        maxLen = cur.size();
        count = 1;
    }
    else if(cur.size() == maxLen)
    {
        ++count;
    }

    if(cur.size() + nums.size() -index < maxLen)
    {
        return;
    }

    //优化，剪枝
    for(int i=index;i<nums.size();++i)
    {
        if(nums[i] > cur.back())
        {
            //选择加入
            cur.push_back(nums[i]);
            for(auto a : cur)
            {
                printf("%d ",a);
            }
            printf("\n");
            findNumberOfLIS(nums,cur,i+1,maxLen,count); //这个地方相当于再加了一个for循环
            cur.pop_back();
        }       
    }

}

int findNumberOfLIS(vector<int>& nums) {
    
    //思路：记录以nums每一个元素开始的递增序列，记录最长的长度
    //结果：超时
    // vector<int> curVec;
    // int mxLen =0;
    // int count = 0;
    // for(int i=0;i<nums.size();++i)
    // {
    //     curVec.push_back(nums[i]);
    //     findNumberOfLIS(nums,curVec,i+1,mxLen,count);
    //     curVec.pop_back();   
    // }

    // return count;

    //另一种思路：使用动归，存储中间结果，dp[i]不是以第i个元素结束的递增序列个数
    vector<int> dp(nums.size(),1);
    vector<int> dpLen(nums.size(),1);
    int mxLen = 1;
    for(int i=1;i<nums.size();++i)
    {
        for(int j=i-1;j>=0;--j)
        {
            if(nums[j] < nums[i])
            {
                if(dpLen[i] == dpLen[j] + 1)
                {
                    dp[i] += dp[j];
                }
                else if(dpLen[i] < dpLen[j] + 1)
                {
                    dp[i] = dp[j];
                    dpLen[i] = dpLen[j]+1;
                    mxLen = max(mxLen,dpLen[i]);
                }
            }
        }
    }

    printf("mxLen:%d\n",mxLen);
    int res = 0;
    for(int i=0;i<dpLen.size();++i)
    {
        printf("%d\n",dpLen[i]);
        if(dpLen[i] == mxLen)
        {
            res+= dp[i];
        }
    }

    return res;
}

int main()
{
    // vector<int> nums = {1,3,5,4,7};
    // vector<int> nums = {2,2,2,2,2};
    // vector<int> nums = {1,2,1,2};
    vector<int> nums ={1,2,4,3,5,4,7,2};
    printf("%d\n",findNumberOfLIS(nums));
    return 0;
}