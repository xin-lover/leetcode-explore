//493. 翻转对

//可参考：327. 区间和的个数

#include <cstdio>
#include <vector>
#include <set>
#include <map>

using namespace std;

int mergeSort(vector<int>& nums, int left,int right)
{
    if(left >= right)
    {
        return 0;
    }
    int mid = left + (right-left) / 2;
    int lc = mergeSort(nums,left,mid);
    int rc = mergeSort(nums,mid+1,right);

    int ret = lc + rc;
    int j = left;
    for(int i=mid+1;i<=right;++i)
    {
        long long a = nums[j];
        long long b = nums[i];
        // while(j<=mid && nums[j] <= nums[i]*2)
        while(j<=mid && a <= b*2)
        {
            ++j;
            a = nums[j];
        }

        if(a > b*2)
        {
            ret+=mid-j+1;
        }
        else
        {
            break;
        }
        
    }

    //合并
    vector<int> tmp(right-left+1);
    int l=left,r=mid+1;
    int p = 0;
    while(l <= mid || r <= right)
    {
        if(l > mid)
        {
            tmp[p++] = nums[r++];
        }
        else if(r > right)
        {
            tmp[p++]=nums[l++];
        }
        else
        {
            if(nums[r] > nums[l])
            {
                tmp[p++] = nums[l++];
            }
            else
            {
                tmp[p++] = nums[r++];
            }
            
        }
    }

    for(int i=0;i<tmp.size();++i)
    {
        nums[left+i] = tmp[i];
    }

    return ret;
}

int reversePairs(vector<int>& nums) {
    //思路：暴力解决就是O(n^2)，但很明显，一定会超时
    //该问题重新定义就是一个序列中，找位于元素i之前的元素中大于2i的元素数量,有点单调栈的感觉，但又不是单调栈的问题
    //我们考虑排序，归排序
    //还可以用树状数组。。。。。


    return mergeSort(nums,0,nums.size()-1);

}

int main()
{
    vector<int> nums = {1,3,2,3,1}; //2
    // nums = {2,4,3,5,1};    //3
    nums = {5,4,3,2,1}; //4
    // nums ={1,3,2,3,1};   //2
    printf("%d\n",reversePairs(nums));

    return 0;
}
