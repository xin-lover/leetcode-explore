//1296. 划分数组为连续数字的集合

#include <cstdio>
#include <vector>
#include <map>

using namespace std;

bool isPossibleDivide(vector<int>& nums, int k) {
    //思路：一个思路就是排序，遍历的时候配合map
    //第二个是统计次数，但最后还是会需要排序,两者本质相同

    map<int,int> mp;
    for(int i=0;i<nums.size();++i)
    {
       ++mp[nums[i]]; 
    }

    for(auto v : mp)
    {
        if(v.second == 0)
        {
            continue;
        }
        for(int j=0;j<k;++j)
        {
            int next = v.first + j;
            if(mp.find(next) == mp.end() || mp[next] < v.second)
            {
                return false;
            }
            else
            {
                mp[next]-=v.second;
            }
            
        }
    }
    return true;
}

int main()
{
    vector<int> nums = {3,3,1,2,5,4};
    int k = 2; //false;

    // nums = {1,2,3,3,4,4,5,6}, k = 4; //true;
    nums = {3,2,1,2,3,4,3,4,5,9,10,11}, k = 3; //true
    // nums = {1,2,3,4}, k = 3; //false
    // nums = {3,3,2,2,1,1},k=3;//true
    printf(isPossibleDivide(nums,k) ? "true\n" : "false\n");
    return 0;
}