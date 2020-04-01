//1191. K 次串联后最大子数组之和

#include <cstdio>
#include <vector>
#include <math.h>

using namespace std;

int kConcatenationMaxSum(vector<int>& arr, int k) {
    //思路：arr全为正数和全为负数，结果很明显
    //主要处理两者都有的情况，可以简单归纳为
    //1.-ab,如果a>b，结果就是b,否则就是(b-a)*(k-1)+b
    //2.-ab-c,如果b>a+c,结果是(b-a-c)*k+a+c, 否则还是b
    //3.a-b，a>b,结果（a-b）*k + b, a < b ,结果 a
    //4.a-bc，a+c>b，（a+c-b）*k+(a-b>0 ? 0 : b-a) + (c-b>0 ? 0 : b-c)
    //5.-ab-c,同理
    //也就是我们需要把arr分成3个部分，因为中间的部分也是多个元素，所以处理还要再复杂点
    //不考虑重复，arr的最大子数组之和可以用dp算法，得到dp1[i]表示包含i时0到i的元素中的最大子数组和
    //dp2[i]表示i到后面的元素中包含i元素的最大子数组之和
    //而重复，只有不重复，重复一次，重复k的三种情况
    //方案：计算这三种情况下的最大值

    int kMax = pow(10,9)+7;

    int n = arr.size();
    vector<int> dp(n+1,0);

    int pre_min = INT_MAX,suf_min = INT_MAX;
    int pre_max = INT_MIN,suf_max = INT_MIN;
    int sum = 0;
    int mx1 = INT_MIN;
    for(int i=1;i<=n;++i)
    {
         dp[i] = max(dp[i-1]+arr[i-1],arr[i-1]);
         mx1 = max(mx1,dp[i]);

         sum += arr[i-1];
         pre_min = min(pre_min,sum);
         pre_max = max(pre_max,sum);
    }

    sum = 0;
    for(int i=n-1;i>=0;--i)
    {
        sum += arr[i];
        suf_min = min(suf_min,sum);
        suf_max = max(suf_max,sum);
    }

    //重复一次
    long long mx2= k > 1 ? static_cast<long long>(suf_max)+pre_max : 0;

    printf("sum:%d %d %d\n",sum,pre_min,suf_min);
    //重复k次
    long long mx3 = static_cast<long long>(sum) * k - min(pre_min,0) - min(suf_min,0);

    printf("%d %d %d\n",mx1,mx2,mx3);

    long long res= 0;
    res = max(max(res,static_cast<long long>(mx1)),max(mx2,mx3));
    return res % kMax;
}

int main()
{
    vector<int> arr = {1,2};
    int k=3; //9

    // arr={1,-2,1};
    // k=5;    //2

    // arr={-1,-2};
    // k=7; //0

    // arr={1,-1};
    // k=1;

    arr= {1,2};
    k=1;

    arr = {-5,4,-4,-3,5,-3};
    k=3;
    printf("%d\n",kConcatenationMaxSum(arr,k));
    return 0;
}