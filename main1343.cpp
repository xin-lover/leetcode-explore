//1343. 大小为 K 且平均值大于等于阈值的子数组数目

#include <cstdio>
#include <vector>

using namespace std;

int numOfSubarrays(vector<int>& arr, int k, int threshold) {
    //思路：子数组是连续的，所以确定起点，长度为k的子数组也就确定了
    //方案：简单遍历即可，优化点可以使用前缀和

    vector<int> preSum(arr.size()+1,0);
    for(int i=1;i<=arr.size();++i)
    {
        preSum[i] = preSum[i-1]+arr[i-1];
    }

    int res = 0;
    for(int i=0;i<=arr.size()-k;++i)
    {
        if(preSum[i+k] - preSum[i] >= threshold * k)
        {
            ++res;
        }
    }
    
    return res;
}

int numOfSubarrays2(vector<int>& arr, int k, int threshold) {
    //思路：计算前缀和稍显空间浪费，其实这是一个固定窗口，简单遍历即可

    if(k > arr.size())
    {
        return 0;
    }
    int sum = 0;
    for(int i=0;i<k;++i)
    {
        sum += arr[i];
    }

    int res = sum >= threshold * k ? 1 : 0;
    for(int i=1;i<=arr.size()-k;++i)
    {
        sum -= arr[i-1];
        sum += arr[i+k-1];
        if(sum >= threshold*k)
        {
            ++res;
        }
    }

    return res;
}

int main()
{
    vector<int> arr = {2,2,2,2,5,5,5,8};
    int k = 3, threshold = 4;   //3

    // arr = {1,1,1,1,1}, k = 1, threshold = 0;    //5

    // arr = {11,13,17,23,29,31,7,5,2,3}, k = 3, threshold = 5;    //6

    printf("%d\n",numOfSubarrays2(arr,k,threshold));
    return 0;
}