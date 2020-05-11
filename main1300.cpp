//1300. 转变数组后最接近目标值的数组和

#include <cstdio>
#include <vector>

using namespace std;

int findBestValue(vector<int>& arr, int target) {
    //思路：对arr排序，使用二分法确定哪些数字大于value，
    //这样可快速得到转换后的数组和，同时使用二分法确定小于target时的结果和最小大于target的结果
    //选择两者间最近的值

    sort(arr.begin(),arr.end());

    int n = arr.size();
    vector<int> sums(n+1,0);
    for(int i=1;i<=n;++i)
    {
        sums[i] = sums[i-1]+arr[i-1];
    }

    int res = target;
    int dif = target;
    int left=0,right=target;
    while(left<right)
    {
        int mid = left+(right-left)/2;

        int l=0,r=n;
        while(l<r)
        {
            int d = l + (r-l)/2;
            if(arr[d] <= mid)
            {
                l = d+1;
            }
            else
            {
                r = d;
            }
        }

        int sum = sums[r] + mid * (n-r);
        if(sum == target)
        {
            return mid;
        }
        else if(sum < target)
        {
            left = mid+1;
        }
        else
        {
            right = mid;
        }

        int d = abs(sum - target);
        if(d == dif)
        {
            res = min(res,mid);
        }
        else if (d < dif)
        {
            res = mid;
            dif = d;
        }
    }
    return res;
}

int findBestValue2(vector<int>& arr, int target) {
    //思路：二分法比较暴力，观察过程可以发现，排序后可以使用前缀和加预测的方法
    //也就是说确定好value之后，最终的元素和分为两部分，前半部分为对应的元素组的和，后半部分都是一样的

    sort(arr.begin(),arr.end());

    int n = arr.size();
    int res = 0;
    int offset = target;
    // if(abs(target - n * res) > abs(target - n*(res+1)))
    // {
    //     res+=1;
    //     offset = abs(target - n*(res+1));
    // }
    // else
    // {
    //     offset = abs(target - n * res);
    // }
    
    int tmp = 0;
    bool end = false;
    for(int i=0;i<n && !end;++i)
    {
        int value = (target - tmp) / (n-i);
        if(value > arr[i])
        {
            value = arr[i];
        }
        else
        {
            end = true;
        }
        

        int t = abs(target - tmp - value * (n-i));
        if(t < offset)
        {
            res = value;
            offset = t;
        }
        if(value +1 <= arr[i])
        {
            t = abs(target - tmp - (value+1)*(n-i));
            if(t < offset)
            {
                res = value+1;
                offset = t;
            }
        }
    
        tmp += arr[i];
    }



    return res;
}

int main()
{
    vector<int> num = {4,9,3};
    int target = 10; //3

    // num = {2,3,5};
    // target = 10;    //5

    num = {60864,25176,27249,21296,20204};
    target = 56803; //11361
    printf("%d\n",findBestValue2(num,target));
    return 0;
}