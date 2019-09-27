//leetcode 910. 最小差值 II

#include <cstdio>
#include <vector>

using namespace std;

int smallestRangeII(vector<int>& A, int K) {
    //思路：构建一个新数组，然后看最大和最小值的差值
    //如何构建是问题
    //每一个数都要+k或-k，所以对于原数组的一个差，要么是不变，要么-2k
    //因为是最大、最小的差，所以对于差，我们要看这两个数能否成为最大和最小，也就是与最大值差2k的都不可能成为最大值，同理最小值也是
    //如果我们先排序，当前最大值和最小值确定，接下来我们只能变最大值，都则差不可能变小（即最大值再+k的情况），所以当前最大值-k
    //看是否比第二大的小，如果大则结束，否则第二大的数只能+k，不然它成不了最大的数，这个时候最小值只能在max-k,min+k,secondmin-k间选

    if(A.size() == 1)
    {
        return 0;
    }

    sort(A.begin(),A.end());

    int n = A.size();
    int res = A[n-1] - A[0];
    // if(A[n-1]-K >= A[n-2]+K && A[n-1] - K >= A[0]+K)
    // {
    //     // res = min(res,abs(res-2*K));
    //     printf("Get\n");
    //     res -= 2*K;
    //     return res;
    // }
    for(int i=n-1;i>=0;--i)
    {
        if(i+1 < n && A[i] == A[i+1])
        {
            continue;
        }

        // if(A[i] + K < A[n-1] - K)
        // {
        //     break;
        // }

        //A[i] as max value
        int mx = max(A[i] + K,A[n-1]-K);
        //min value
        int mn = min((i+1 < n) ? A[i+1]-K : A[0]+K,A[0]+K);
        res = min(res,mx - mn);
        // printf("res:%d\n",res);
    }

    return res;
}

int main()
{
    vector<int> A = {0,10};
    printf("%d\n",smallestRangeII(A,2));
    A = {1};
    printf("%d\n",smallestRangeII(A,2));
    A = {1,3,6};
    printf("%d\n",smallestRangeII(A,3));
    A = {7,8,8,5,2};//5
    printf("%d\n",smallestRangeII(A,4));
    A = {10,7,1};//3
    printf("%d\n",smallestRangeII(A,3));

    A = {1,3,6};//3
    printf("%d\n",smallestRangeII(A,3));
    A = {3,1,10};//2
    printf("%d\n",smallestRangeII(A,4));
    A = {2,7,2};//3
    printf("%d\n",smallestRangeII(A,1));
    return 0;
}