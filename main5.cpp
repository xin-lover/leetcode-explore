#include <vector>
#include <cstdio>
#include <map>
#include <set>

using namespace std;

void findSequences(vector<int>& nums,vector<int>& sequences,int len,int index,vector<int>& subSeq,vector<vector<int>>& res)
{
    // printf("sub sz:%d\n",subSeq.size());
    if(subSeq.size() == len)
    {
        bool valid = res.empty() || subSeq.size() != res.back().size();
        if(!valid)
        {
            auto bk = res.back();
            for(int i=0;i<subSeq.size();++i)
            {
                if(subSeq[i] != bk[i])
                {
                    // printf("get %d %d\n",subSeq[i],bk[i]);
                    valid = true;
                }
            }
        }
        if(valid)
        {
            res.push_back(subSeq);
        }
        
        return;
    }
    if(index >= sequences.size())
    {
        return;
    }
    for(int i=index;i<sequences.size();++i)
    {
        subSeq.push_back(nums[sequences[i]]);
        findSequences(nums,sequences,len,i+1,subSeq,res);
        subSeq.pop_back();
    }
}

vector<vector<int>> findSubsequences(vector<int>& nums) {
    
    map<int,bool> mp;   //mark index and visited
    for(int i=0;i<nums.size();++i)
    {
        mp[i] = false;
    }
    
    vector<vector<int>> res;
    
    for(int i=0;i<nums.size();++i)
    {
        if(mp[i])
        {
            continue;
        }
        
        vector<int> sq; //sequences start with current index
        for(int j=i;j<nums.size();++j)
        {
            if(sq.empty() || nums[j] >= nums[sq.back()])
            {
                sq.push_back(j);
            }
        }
        printf("sq:");
        for(auto a : sq)
        {
            printf("%d ",nums[a]);
        }
        printf("\n");
        
        for(int len = 2;len<=sq.size();++len) //push len vector
        {
            for(int j=0;j+len <= sq.size();++j)
            {
                if(mp[sq[j]])
                {
                    continue;
                }
                
                vector<int> subSeq(1,nums[sq[j]]);
                findSequences(nums,sq,len,j+1,subSeq,res);
            }
        }
        
        for(int j=0;j<sq.size();++j)
        {
            mp[sq[j]] = true;
        }
    }
    
    return res;
}


class Solution {
public:
    void rec(vector<int>& nums,int start,vector<int>& stack,set<vector<int>>& ans){
        if(stack.size()>=2)ans.insert(stack);
        for(int i=start;i<nums.size();i++){{
            if(!stack.empty()&&stack.back()>nums[i])
                continue;
            stack.push_back(nums[i]);
            rec(nums,i+1,stack,ans);
            stack.pop_back();
        }}
    }
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        set<vector<int>>ans;
        vector<int>stack;
        rec(nums,0,stack,ans);
        return vector<vector<int>>(ans.begin(),ans.end());
    }
};

int main()
{
    // vector<int> nums = {4,6,7,7};
    // vector<int> nums = {2,6,7,3,8,9};
    // vector<int> nums = {2,3};
    vector<int> nums = {2,6,3,8};
    Solution s;
    auto res = findSubsequences(nums);
    // auto res = s.findSubsequences(nums);
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