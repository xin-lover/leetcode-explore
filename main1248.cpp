//1248. 统计「优美子数组」

#include <cstdio>
#include <vector>
#include <unordered_map>

using namespace std;


int numberOfSubarrays(vector<int>& nums, int k) {
    //思路：因为是子数组，所以还是排列组合
    //首先确定K个奇数，然后往这个区间的两边加其它的偶数
    //加入左侧m个偶数，右侧n个偶数，那么左侧有（m+1）个选择，右侧（n+1）个选择，总共是（m+1）*（n+1）种可能
    //方案，遍历数组，记录奇数的位置，然后用固定窗口遍历

    vector<int> flags;
    flags.push_back(-1);
    for(int i=0;i<nums.size();++i)
    {
        if(nums[i] & 1)
        {
            flags.push_back(i);
        }
    }
    flags.push_back(nums.size());

    if(flags.size() < k+2)
    {
        return 0;
    }

    int res = 0;
    for(int i=1;i+k<flags.size();++i)
    {
        //优化：在首尾插入端点值，就不用判断了
        int left = flags[i]-flags[i-1];
        int right = flags[i+k] - flags[i+k-1];

        res += left * right;
    }

    return res;
}

//前缀和思路,本质并无不同
int numberOfSubarrays2(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> arr;
    arr.push_back(0);
    for(auto x:nums) arr.push_back(arr.back() + (x&1));
    
    unordered_map<int,int> h;
    int ans = 0;
    
    for(auto x:arr) {
        ans += h[x-k];
        h[x] ++;
    }
    return ans;
}

int main()
{
    vector<int> nums = {1,1,2,1,1};
    int k = 3;//2

    // nums = {2,4,6};
    // k=1;//0

    nums = {2,2,2,1,2,2,1,2,2,2};
    k = 2;//16
    printf("%d\n",numberOfSubarrays(nums,k));
    return 0;
}