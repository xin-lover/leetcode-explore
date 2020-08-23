//1509. 三次操作后最大值与最小值的最小差

#include <cstdio>
#include <vector>
#include <map>

using namespace std;

int minDifference(vector<int>& nums) {
    //思路：假设nums没有重复数字，把nums排序
    //有4中情况：
    //1.改最小的连续3个数
    //2.改2小1大
    //3.改1小2大
    //4.改最大3个连续数
    //而现在有重复数字，那么我们需要统计重复数字
    //使用map，自带排序

    int c = 3;
    if(nums.size() <= c+1)
    {
        return 0;
    }

    map<int,int> mp;
    for(auto a : nums)
    {
        mp[a]++;
    }

    auto start = mp.begin();
    auto end = mp.end();
    --end;
    int res = end->first - start->first;
    int count = c;
    //简化写法,每次选择改最小数字
    for(int i=0;i<=c && count >= 0;++i)
    {
        int t = count;
        auto it = end;
        while(t >= it->second)
        {
            t-=it->second;
            --it;
        }

        res = min(res,it->first-start->first);
        count -= start->second;
        ++start;
    }

    return res;

    // auto start = mp.begin(),end = mp.end()-1;
    // //1
    // while(c >= start->second)
    // {
    //     c-=start->second;
    //     ++start;
    // }
    
    // res = min(res,end->first - start->first);

    // //2
    // c=3;
    // start = mp.begin(),end = mp.end()-1;
    // if(c >= start->second)
    // {
    //     c -= start->second;
    //     while(c >= end->second)
    //     {
    //         c-=end->second;
    //         end--;
    //     }
    //     res = min(res,end->first - start->first);
    // }
    
    // //3
    // c=3;
    // start = mp.begin(),end = mp.end()-1;
    // if(c >= end->second)
    // {
    //     c -= end->second;
    //     while(c >= start->second)
    //     {
    //         c-=start->second;
    //         ++start;
    //     }
    //     res = min(res,end->first - start->first);
    // }

    // //4
    // while(c >= end->second)
    // {
    //     c-=end->second;
    //     --end;
    // }
    
    // res = min(res,end->first - start->first);

    // return res;
}

int minDifference2(vector<int>& nums) {

    //思路：直接排序试试

    int c = 3;
    if(nums.size() <= c+1)
    {
        return 0;
    }
    sort(nums.begin(),nums.end());

    int n = nums.size();
    int res = INT_MAX;
    for(int i=0;i<=c;++i)
    {
        res = min(res,nums[n-c-1+i] - nums[i]);
    }

    return res;
}

//用堆优化，维护4个最大值，4个最小只
int minDifference3(vector<int>& nums) {
    int n = nums.size();
    if (n <= 4) {
        return 0;
    }

    vector<int> maxn(4, -1e9), minn(4, 1e9);
    for (int i = 0; i < n; i++) {
        int add = 0;
        while (add < 4 && maxn[add] > nums[i]) {
            add++;
        }
        if (add < 4) {
            for (int j = 3; j > add; j--) {
                maxn[j] = maxn[j - 1];
            }
            maxn[add] = nums[i];
        }
        add = 0;
        while (add < 4 && minn[add] < nums[i]) {
            add++;
        }
        if (add < 4) {
            for (int j = 3; j > add; j--) {
                minn[j] = minn[j - 1];
            }
            minn[add] = nums[i];
        }
    }
    int ret = 2e9;
    for (int i = 0; i < 4; i++) {
        ret = min(ret, maxn[i] - minn[3 - i]);
    }
    return ret;
}

int main()
{
    vector<int> nums = {5,3,2,4}; //0
    nums = {1,5,0,10,14};   //1
    nums = {6,6,0,1,1,4,6}; //2
    // nums = {20,66,68,57,45,18,42,34,37,58};//31
    sort(nums.begin(),nums.end());
    for(auto a : nums)
    {
        printf("%d ",a);
    }
    printf("\n");
    printf("%d\n",minDifference2(nums));

    return 0;
}