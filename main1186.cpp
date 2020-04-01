//1186. 删除一次得到子数组最大和

#include <cstdio>
#include <vector>

using namespace std;

void divide(vector<int>& arr,int left,int right,int& noDelMax,int& delMax) {

    if(left == right)
    {
        noDelMax = arr[left];
        delMax = INT_MIN;
        return;
    }
    int mid = left + (right-left)/2;

    int left_no_del_max,left_del_max,right_no_del_max,right_del_max;
    divide(arr,left,mid,left_no_del_max,left_del_max);
    divide(arr,mid+1,right,right_no_del_max,right_del_max);

    int i= mid;
    int tmp = arr[i];
    int min_val = arr[i];
    int left_no_del = arr[i]; 
    int left_del = 0;
    --i;
    while(i >= left)
    {
        tmp += arr[i];
        min_val = min(min_val,arr[i]);

        left_no_del = max(left_no_del,tmp);
        left_del = max(left_del,tmp - min_val);
        --i;
    }

    i = mid+1;
    tmp = arr[i];
    min_val = arr[i];
    int right_no_del = arr[i];
    int right_del = 0;
    ++i;
    while(i <= right)
    {
        tmp += arr[i];
        min_val = min(min_val,arr[i]);

        right_no_del = max(right_no_del,tmp);
        right_del = max(right_del,tmp - min_val);
        ++i;
    }

    delMax = max(max(left_del + right_no_del,left_no_del + right_del),max(left_del_max,right_del_max));
    noDelMax = max(max(left_no_del_max,right_no_del_max),left_no_del + right_no_del);
    // printf("%d %d %d %d %d %d\n",left_no_del_max,left_del_max,right_no_del_max,right_del_max, delMax,noDelMax);
}
int maximumSum(vector<int>& arr) {
    //思路：可以考虑分治，因为是子数组，也就是说把数组分成两部分，最大和会出现在左侧，右侧者中间

    if(arr.size() == 1)
    {
        return arr[0];
    }
    int no_del,del;
    divide(arr,0,arr.size()-1,no_del,del);
    return max(no_del,del);
}

int maximumSum2(vector<int>& arr) {
    //分治算法有些低效，回溯也差不多
    //应该是一种O(n)的算法
    //利用前缀和的思想

    vector<int> presum(arr.size(),0);
    int sum =0;
    int res = INT_MIN;
    for(int i=0;i<arr.size();++i)
    {
        sum += arr[i];
        presum[i] = sum;
        res = max(res,sum);
        if(sum < 0)
        {
            sum = 0;
        }
    }

    sum =0 ;
    vector<int> lastsum(arr.size(),0);
    for(int i=arr.size()-1;i>=0;--i)
    {
        sum += arr[i];
        lastsum[i] = sum;
        res = max(res,sum);
        if(sum < 0)
        {
            sum = 0;
        }
    }

    for(int i=1;i<arr.size()-1;++i) {
        if(arr[i] < 0)
            res = max(res, presum[i-1] + lastsum[i+1]);
    }

    return res;
}

//动态规划
// 做出2个数组prefixDp 和 suffixDp
// prefixDp[i] 表示 从前往后 最后一个下标为i的 最大子数组和
// suffixDp[i] 表示 从后往前 最后一个下标为i的 最大子数组和
// 同时保存 中间过程中 最大的值

int main()
{
    vector<int> arr = {1,-2,0,3};//4
    arr = {1,-2,-2,3};//3
    // arr = {-1,-1,-1,-1};//-1
    arr = {0,-5,-6,5,0,-5};
    printf("%d\n",maximumSum2(arr)); 

    return 0;
}