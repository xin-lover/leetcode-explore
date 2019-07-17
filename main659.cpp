//leetcode 659. 分割数组为连续子序列

#include <cstdio>
#include <vector>

using namespace std;

// int possibleLen(vector<int>& nums,vector<bool> flags, int start, int repeat)
// {
//     int seqCount = 1;
//     flags[start] = false;
//     int j = start;
    
//     for(int i=start+1;i<nums.size();++i)
//     {
//         if(!flags[i])
//         {
//             continue;
//         }
//         if(nums[i] == nums[j])
//         {
//             int len = possibleLen(nums,flags,i);
//         }
//         else if(nums[i] == nums[j] + 1)
//         {
//             j = i;
//             ++seqCount;
//             flags[i] = false;
//         }
//         else
//         {
//             if(seqCount < 3)
//             {
//                 return false;
//             }

//             if(!isPossible(nums,flags,i))
//             {
//                 return false;
//             }
//         }
//     }

//     return seqCount;

// }
bool isPossible(vector<int>& nums) {
    //思路：已知数组有序，难点在重复数据如何分割，不能合理分割的情况就是不连续和个数少于3
    //重复数据肯定要重新开始一个序列，不连续的地方也是要重新开始
    //所以策略就是，遇到重复元素和不连续地方时，重新开始序列
    //

    if(nums.size() < 3)
    {
        return false;
    }

    vector<vector<int>> tmp={{nums[0]}};
    for(int i=1;i<nums.size();++i)
    {
        //优先新建的序列，因为新建序列肯定不会比之前的序列长
        //使用二分法优化
        // auto it = tmp.rbegin();
        // for(;it!=tmp.rend();++it)
        // {
        //     if(nums[i] == it->back() + 1)
        //     {
        //         it->push_back(nums[i]);
        //         break;
        //     }
        // }

        // if(it == tmp.rend())
        // {
        //    tmp.push_back({nums[i]}); 
        // }

        int left = 0,right = tmp.size()-1;
        while(left < right)
        {
            int mid = left + (right - left) / 2;
            if(nums[i] >= tmp[mid].back()+1)
            {
                left = mid+1;
            }
            else
            {
                right = mid-1;
            }
        }

        if(tmp[left].back()+1==nums[i])
        {
            tmp[left].push_back(nums[i]);
        }
        else if(left > 0 && tmp[left-1].back()+1==nums[i])
        {
            tmp[left-1].push_back(nums[i]);
        }
        else
        {
            tmp.push_back({nums[i]});
        }
        
    }

    for(auto it = tmp.begin();it!=tmp.end();++it)
    {
        for(auto a : *it)
        {
            printf("%d ",a);
        }
        printf("\n");
        if(it->size() < 3)
        {
            return false;
        }
    }

    return true;
}

int main()
{
    vector<int> v = {1,2,3,3,4,5};
    // vector<int> v = {1,2,3,3,4,4,5,5};
    printf(isPossible(v) ? "true\n" : "false\n");
    return 0;
}