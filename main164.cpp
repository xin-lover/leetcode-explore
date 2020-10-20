//164. 最大间距

#include <cstdio>
#include <vector>
#include <stack>

using namespace std;



void sort(vector<int>& nums)
{
    int n = nums.size();

    auto maxBit=[](vector<int>& nums)
    {
        int c = 0;
        int p = 1;
        for(int i=0;i<nums.size();++i)
        {
            while(nums[i] >= p)
            {
                p*=10;
                ++c;
            }
        }

        return c;
    };

    int d = maxBit(nums);

    int exp = 1;
    int radix = 10;
    vector<int> tmp(n);
    vector<int> count(10,0);
    for(int i=0;i<d;++i)
    {
        for(int j=0;j<count.size();++j)
        {
            count[j] = 0;
        }
        for(int j=0;j<nums.size();++j)
        {
            int k= (nums[j] / exp) % radix;
            count[k]++;
        }

        for(int j=1;j<count.size();++j)
        {
            count[j] = count[j-1]+count[j];
        }

        for(int j=n-1;j>=0;--j)
        {
            int k = (nums[j] / exp) % radix;
            tmp[count[k]-1] = nums[j];
            count[k]--;
        }

        swap(nums,tmp);

        exp *= 10;
    }
}

class Bucket
{
public:
    bool used = false;
    int maxval = numeric_limits<int>::min();
    int minval = numeric_limits<int>::max();
};

int maximumGap(vector<int>& nums) {
    //思路：如何不排序
    //常数时间遍历我们可达最大值和最小值
    //借鉴桶排序
    //把区间分成n-1份，把数字放入这n-1个桶中，然后比较桶间距
    //为什么只需要比较桶间距？
    //桶内最大间距不会超过桶的容积，而桶的容积取决于最大最小值
    //假设nums是等差数列，那么最大间距是最小的，否则我们让nums[i]+t,很明显会得到一个更大的间距nums[i]+t-nums[i-1]
    //也就是说nums的最小最大间距是b，大于桶内最大间距,桶的容积mx-min=b,mx-mn<b

    //想到了桶，卡在了如何避免桶内比较这一步

    int n= nums.size();
    if(n < 2)
    {
        return 0;
    }

    int maxi = *max_element(nums.begin(),nums.end());
    int mini = *min_element(nums.begin(),nums.end());

    int bucketSize = max(1,(maxi - mini) / (n-1));
    int bucketNum = (maxi - mini) / bucketSize + 1;

    vector<Bucket> buckets(bucketNum);
    for(int i=0;i<n;++i)
    {
        int k = (nums[i] - mini) / bucketSize;

        buckets[k].used = true;
        buckets[k].maxval = max(buckets[k].maxval,nums[i]);
        buckets[k].minval= min(buckets[k].minval,nums[i]);
    } 

    int maxGap =0; 
    int preMax = mini;
    for(int i=0;i<bucketNum;++i)
    {
        if(!buckets[i].used)
        {
            continue;
        }

        maxGap = max(maxGap,buckets[i].minval - preMax);
        preMax = buckets[i].maxval;
    }

    return maxGap;

}

int main()
{
    vector<int> nums = {3,6,9,1};
    // nums = {11,23,98,35,46};
    // nums = {2,100,34,19,3,2,1};
    // sort(nums);

    // for(auto a : nums)
    // {
    //     printf("%d ",a);
    // }
    // printf("\n");

    printf("%d\n",maximumGap(nums));
    return 0;
}