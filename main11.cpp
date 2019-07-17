#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        
        //思路1:使用dfs+set去重解决
        //思路2:排序，给每个数判断前后元素是否相等，
        
        sort(nums.begin(),nums.end());
        vector<vector<int>> res;
        vector<int> curSet;
        subsetsWithDup(nums,0,curSet,res);
        return res;
    }
    
    void subsetsWithDup(vector<int>& nums,int index,vector<int>& curSet,vector<vector<int>>& subsets)
    {
        if(index > nums.size())
        {
            return;
        }
        printf("index:%d\n",index);
        subsets.push_back(curSet);
        for(int i=index;i<nums.size();++i)
        {
            if(i > index && nums[i] == nums[i-1])
            {
                continue;
            }
            curSet.push_back(nums[i]);
            printf("push:%d\n",nums[i]);
            subsetsWithDup(nums,i+1,curSet,subsets);
            curSet.pop_back();
        }
    }
};

int main()
{
    vector<int> nums = {1,2,2};
    Solution s;
    auto res = s.subsetsWithDup(nums);
    for(auto a : res)
    {
        for(auto b : a)
        {
            printf("%d ",b);
        }
        printf("\n");
    }
    return 0;
}