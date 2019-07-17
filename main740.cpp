//leetcode 740. 删除与获得点数

#include <cstdio>
#include <vector>

using namespace std;

int deleteAndEarn(vector<int>& nums) {
    
    //思路：选取k，把k-1和k+1都删除，这个时候的收益是k*n,失去的是(k-1)*n1 + (k+1)*n2,
    //同时这还会影响k-2和k+2的收益
    //用贪心算法：选择k时，我们只考虑当前的收益，不去考虑下一步的收益，也可以理解为选择k,则k-2和k+2也是我们的收益
    //而且排序后，我们是从前往后决策，也就是如果k没被删除，我们就只需要考虑k+1，k-1已经不存在了
    //碰到{1,2,3,4},这种思路会得到1,4的结果，但最大是2和4，这个需要反转过来，有限考虑选取大数，所以反向遍历

    if(nums.empty())
    {
        return 0;
    }
    sort(nums.begin(),nums.end());
    // for(int i=0;i<nums.size();++i)
    // {
    //     printf("%d ",nums[i]);
    // }
    // printf("\n");

    vector<int> values;
    vector<int> counts;
    int cur = 0;
    for(int i=1;i<nums.size();++i)
    {
        if(nums[i] != nums[cur])
        {
            values.push_back(nums[cur]);
            counts.push_back(i-cur);
            cur = i;
        }
    }

    values.push_back(nums[cur]);
    counts.push_back(nums.size()-cur);

    int res = 0;
    int i;
    for(i=values.size()-1;i>=1;--i)
    {
        if(values[i] > values[i-1] + 1)
        {
            res += values[i]*counts[i];//孤立的就是纯收益
        }
        else
        {
            if(i-2<0 || values[i-2] < values[i-1]-1)
            {
                if(values[i] * counts[i] > values[i-1] * counts[i-1])
                {
                    res+=values[i] * counts[i];
                }
                else
                {
                    res += values[i-1] * counts[i-1];
                }
                --i;
            }
            else
            {
                if(values[i] * counts[i] + values[i-2] * counts[i-2] >= values[i-1] * counts[i-1])
                {
                    res += values[i] * counts[i];
                    --i;
                }
                else
                {
                    res += values[i-1] * counts[i-1];
                    i-=2;
                }
            }
            
        }
    }

    if(i == 0)
    {
        res += values[0] * counts[0];
    }

    return res;
}

int deleteAndEarn2(vector<int>& nums) 
{
    //思路：数据按值和个数整理后，使用dp

    if(nums.empty())
    {
        return 0;
    }
    sort(nums.begin(),nums.end());
    vector<int> values;
    vector<int> counts;
    int cur = 0;
    for(int i=1;i<nums.size();++i)
    {
        if(nums[i] != nums[cur])
        {
            values.push_back(nums[cur]);
            counts.push_back(i-cur);
            cur = i;
        }
    }

    values.push_back(nums[cur]);
    counts.push_back(nums.size()-cur);

    vector<int> dp(values.size(),0);
    dp[0] = values[0] * counts[0];
    for(int i=1;i<dp.size();++i)
    {
        if(values[i] > values[i-1] + 1)
        {
            dp[i] = dp[i-1] + values[i] * counts[i];
        }
        else
        {
            dp[i] = max(dp[i-1], (i-2 >= 0 ? dp[i-2] : 0) + values[i] * counts[i]);
            // if(i-2 >= 0)
            // {
            //     dp[i] = max(dp[i-1], dp[i-2] + values[i] * counts[i]);
            // }
            // else
            // {
            //     dp[i] = max(dp[i-1],values[i] * counts[i]);
            // }
            
        }
    }

    return dp.back();

}

int main()
{
    vector<int> v = {3, 4, 2};
    v= {2, 2, 3, 3, 3, 4};
    // v={1};
    // v={1,1,2,2,2,1,1};
    // v = {1,2,3,4,7,8,8,10,10,10};
    // v = {1,2,3,4};
    // v = {1,8,5,9,6,9,4,1,7,3,3,6,3,3,8,2,6,3,2,2,1,2,9,8,7,1,1,10,6,7,3,9,6,10,5,4,10,1,6,7,4,7,4,1,9,5,1,5,7,5};
    // v = {7, 7, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9, 9, 10, 10, 10};
    printf("%d\n",deleteAndEarn2(v));
    return 0;

}