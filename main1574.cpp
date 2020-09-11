//1574. 删除最短的子数组使剩余数组有序

#include <cstdio>
#include <vector>

using namespace std;

int findLengthOfShortestSubarray(vector<int>& arr) {
    //思路：删除的是子数组，所以可以理解为分为3段，前后两段有序且递增
    //中间这段删除，所以问题在于找到两个索引:i,j，arr[i]<=arr[j]
    //0到i递增，j到n也递增
    //不考虑arr[i]<=arr[j],很简单
    //所以现在的问题又变成了对于arr[i],在最后一段找到不小于arr[j]的数
    //这个可以用二分，整体复杂度不超过O(logN)

    int n = arr.size();
    int k=0;
    for(k=1;k<arr.size();++k)
    {
        if(arr[k] < arr[k-1])
        {
            break;
        }
    }

    if(k == n)
    {
        return 0;
    }

    int res = n-k;
    for(int i=n-1;i>=k-1;--i)
    {
        if(i+1<n && arr[i] > arr[i+1])
        {
            break;
        }

        int left=0,right=k-1;
        while(left<right)
        {
            int mid = left+(right-left)/2;
            if(arr[mid] > arr[i])
            {
                right=mid;
            }
            else
            {
                left=mid+1;
            }
        }

        printf("arr[%d]:%d left:%d\n",i,arr[i],left);
        if(arr[left] > arr[i])
        {
            if(left>0)
            {
                res = min(res,n-left-(n-i));
            }
            else
            {
                res = min(res,n-(n-i));
            }
        }
        else
        {
            res = min(res,i-left-1);
        }
        
        
    }

    return res == n ? 1 : res;
}

int main()
{
    vector<int> arr = {1,2,3,10,4,2,3,5}; //3
    // arr = {5,4,3,2,1};  //4;
    // arr = {1,2,3};  //0
    // arr={1};//0
    // arr = {6,3,10,11,15,20,13,3,18,12}; //8
    arr ={10,13,17,21,15,15,9,17,22,22,13}; //7
    printf("%d\n",findLengthOfShortestSubarray(arr));

    return 0;
}