#include <cstdio>
#include <vector>

using namespace std;

bool dfs(vector<int> &nums,int curLen)
{
    
    if(curLen==0) return true;
    for(int i=0;i<nums.size();++i)
    {
        if(nums[i]>curLen)  return false;
        if(nums[i]>0)
        {
            nums[i]=-nums[i];                   //标记访问数据
            if(dfs(nums,curLen-abs(nums[i])))
                return true;
            nums[i]=abs(nums[i]);               //恢复
        }
    }
    return false;
    
}

bool backtrace(vector<int>& nums,int len)
{
    if(len == 0)
    {
        return true;
    }

    
    for(int i=0;i<nums.size();++i)
    {
        if(nums[i] > len)
        {
            return false;
        }
        if(nums[i] > 0)
        {
            nums[i] = -nums[i];
            if(backtrace(nums,len + (nums[i])))
            {
                return true;
            }
            nums[i] = abs(nums[i]);
        }
    }

    return false;   
}
bool makesquare(vector<int>& nums) {
    //思路：如果能拼成正方形，边的长度可以确定
    //使用回溯法

    if(nums.size() < 4)
    {
        return false;
    }

    int sum = 0;
    for(int i=0;i<nums.size();++i)
    {
        sum += nums[i];
    }

    if(sum % 4 != 0)
    {
        return false;
    }

    sort(nums.rbegin(),nums.rend());
    int side = sum / 4;
    for(int i=0;i<3;++i)
    {
        if(!backtrace(nums,side))
        {
            return false;
        }
    }

    for(auto a : nums)
    {
        printf("%d ",a);
    }
    printf("\n");
    return true;
    
}

int main()
{
    // vector<int> v = {1,1,2,2,2};
    // vector<int> v = {2,2,2,3,4,4,4,5,6};
    vector<int> v = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    printf(makesquare(v) ? "true\n":"false\n");
    return 0;
}