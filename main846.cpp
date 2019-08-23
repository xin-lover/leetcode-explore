//leetcode 846. 一手顺子

#include <cstdio>
#include <vector>
#include <unordered_map>

using namespace std;

bool isNStraightHand(vector<int>& hand, int W) {
    //思路：记录数字及其出现的次数，问题是如何知道当前的可用的最小数字
    //不实用map，使用pair

    if(W == 0 || hand.empty() || hand.size() % W != 0)
    {
        return false;
    }

    unordered_map<int,int> um;
    for(int i=0;i<hand.size();++i)
    {
        ++um[hand[i]];
    }

    vector<int> nums;
    for(auto it = um.begin();it!=um.end();++it)
    {
        nums.push_back(it->first);
    }

    sort(nums.begin(),nums.end());

    int i=0;
    while(i < nums.size())
    {
        if(um[nums[i]] != 0)
        {
            for(int j=0;j<W;++j)
            {
                if(um.find(nums[i]+j) == um.end() || um[nums[i]+j] == 0)
                {
                    printf("%d %d\n",nums[i],j);
                    return false;
                }

                --um[nums[i]+j];
            }
        }

        if(um[nums[i]] == 0)
        {
            ++i;
        }
    }

    return true;
}



bool isNStraightHand2(vector<int>& hand, int W) {
    //若是顺子，array的每一元素理应是相等的

    vector<int> nums(W,0);
    for(int i=0;i<hand.size();++i)
    {
        ++nums[hand[i]%W];
    }

    for(int i=1;i<W;++i)
    {
        if(nums[i] != nums[i-1])
        {
            return false;
        }
    }

    return true;
}


int main()
{
    vector<int> v = {1,2,3,6,2,3,4,7,8};
    // printf(isNStraightHand(v,3) ? "true\n" : "false\n");

    // v = {1,2,3,4,5};
    // printf(isNStraightHand(v,4) ? "true\n" : "false\n");

    // v = {0,0};
    // v = {1,2,3,4,5,6};
    // // v = {5,1};
    // printf(isNStraightHand(v,2) ? "true\n" : "false\n");

    v = {1,1,2,2,3,3};
    printf(isNStraightHand2(v,3) ? "true\n" : "false\n");

    return 0;
}