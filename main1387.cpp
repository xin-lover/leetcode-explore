//1387. 将整数按权重排序

#include <cstdio>
#include <vector>

using namespace std;

int getHeight(int i,vector<int>& dp)
{
    if(i == 1)
    {
        return 0;
    }
    if(dp[i] == -1)
    {
        if(i&1)
        {
            dp[i] = getHeight((i*3+1)/2,dp)+2;
        }
        else
        {
            dp[i] = getHeight(i/2,dp)+1;
        }
    }

    return dp[i];
}

int getHeight2(int i)
{
    int res = 0;
    while(i!=1)
    {
        if(i&1)
        {
            i=3*i+1;
        }
        else
        {
            i/=2;
        }
        ++res;
        
    }

    return res;
}

int getKth(int lo, int hi, int k) {
    //思路：如何快速的计算权重是关键，假设要让i要变成1，我们会发现
    //i要变成一个2^n次方的数，也就是某一步是3*i+1 = 2^n才行
    //因为是整数，n的取值只有31个，所以i是可以确定的
    //因为最大数只有1000，先用动归试试
    //动归的问题在于需要存储的空间会很大，就算最大值1000，也可能需要100000的空间
    //动归不一定用数组，可以用map，一些不需要的数也就不需要空间了。。。。。

    vector<int> dp(4096,-1);
    vector<pair<int,int>> arr_;
    for(int i=lo;i<=hi;++i)
    {
        arr_.push_back({i,getHeight2(i)});
    }

    sort(arr_.begin(),arr_.end(),[](pair<int,int>& a,pair<int,int>& b)
    {
        if(a.second == b.second)
        {
            return a.first < b.first;
        }

        return a.second < b.second;
    });

    return arr_[k-1].first;
}

int main()
{
    printf("%d\n",getKth(12,15,2)); //13
    printf("%d\n",getKth(10,20,5)); //13
    printf("%d\n",getKth(1,1000,777));  //570
    return 0;
}