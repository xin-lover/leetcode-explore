//leetcode 822. 翻转卡片游戏

#include <cstdio>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

int flipgame(vector<int>& fronts, vector<int>& backs) {
    //思路：其实可以理解为从后一个数组中选一个数字，这个数字与fronts数组中的元素都不同，我们可以交换两个数组同一个位置的数
    //一个思路是每一个卡片都试一下，比如选择第一张卡片，如果某个位置出现重复的了，翻转一下，如果还重复则不符合要求
    //优化一下就是两个数组是对等的，因为可以翻转，所以对于每一张卡片的数字，只要其它卡片的两个数字又一个与它不同就可以
    //同时我们记录当前找到的最小值，大于最小值的都可以不考虑
    //如果一个数不符合要求，则说明一张卡片的正面和背面相同且与这个数相等
    //所以另一个思路就是，如果一个数只出现一次，则肯定的是符合要求的数，出现两次以上，但不在同一张卡片上，
    //即每一张卡片的正面和背面不同时是这个数，则符合要求
    //策略：记录每个数字的状态，出现一次、多次，多次有正反面相同的情况

    unordered_map<int,int> um;
    for(int i=0;i<fronts.size();++i)
    {
        if(backs[i] == fronts[i])
        {
            um[fronts[i]] =-1;
        }
        else
        {
            if(um.find(fronts[i]) == um.end())
            {
                um[fronts[i]] = 1;
            }

            if(um.find(backs[i]) == um.end())
            {
                um[backs[i]] = 1;
            }
        }
    }

    const int imax = (1 << 30) - 1;
    int res = imax;
    for(auto it = um.begin();it!=um.end();++it)
    {
        if(res > it->first && it->second > 0)
        {
            res = it->first;
        }
    }

    return res == imax ? 0 : res;

    //优化：不需要计数，只要看看卡片正背面是否相同,set比map慢
    // const int imax = (1 << 30) - 1;
    // int res = imax;
    // set<int> dumb;
    // vector<int> valids;
    // for(int i=0;i<fronts.size();++i)
    // {
    //     if(fronts[i] == backs[i])
    //     {
    //         dumb.insert(fronts[i]);
    //     }
    //     else
    //     {
    //         valids.push_back(fronts[i]);
    //         valids.push_back(backs[i]);
    //     }
        
    // }

    // for(int i=0;i<valids.size();++i)
    // {
    //     if(dumb.find(valids[i]) == dumb.end())
    //     {
    //         res = min(res,valids[i]);
    //     }
    // }

    // return res == imax ? 0 : res;
}

int main()
{
    vector<int> fronts = {1,2,4,4,7};
    vector<int> backs = {1,3,4,1,3};

    // fronts = {2,1,1,2,1};
    // backs = {2,1,2,1,2};

    fronts = {1,1};
    backs = {2,1};

    printf("%d\n",flipgame(fronts,backs));
    return 0;
}