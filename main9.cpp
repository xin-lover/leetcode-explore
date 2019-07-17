#include <cstdio>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        
        //思路：考虑最终的结果是2个2，3个3，4个4类型的结果，考虑暴力破解
        
        vector<vector<int>> res;
        vector<int> curComb;
        
        combinationSum(candidates,target,0,curComb,res);
        return res;
    }
    
    void combinationSum(vector<int>& candidates,int target,int index,vector<int>& curComb, vector<vector<int>>& res)
    {
        if(target == 0)
        {
            res.push_back(curComb);
            return;
        }
        
        if(target < 0)
        {
            return;
        }
        
        if(index >= candidates.size())
        {
            return;
        }
        
        int num = candidates[index];
        int end = target / num + 1;
        for(int i=0;i<end;++i)
        {
            printf("insert: %d %d\n",i,candidates[index]);
            curComb.insert(curComb.end(),i,candidates[index]);
            printf("after %lu\n",curComb.size());
            combinationSum(candidates,target - i * candidates[index],index+1,curComb,res);
            if(i > 0)
            {
                curComb.erase(curComb.end() - i,curComb.end());
                printf("erase:%lu\n",curComb.size());
            }
            
        }
    }
};

int main()
{
    Solution s;
    vector<int> v = {2,3,6,7};
    // v.erase(v.end());
    auto res = s.combinationSum(v,7);
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