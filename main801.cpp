//leetcode 801. 使序列递增的最小交换次数

#include <cstdio>
#include <vector>

using namespace std;

int minSwap(vector<int>& A, vector<int>& B) {
    //思路：动归，记录两个状态，dp1[i]表示在i位置进行交换的次数，dp2表示未交换的次数

    if(A.empty())
    {
        return 0;
    }

    int n = A.size();
    vector<int> dp1(A.size(),n);
    vector<int> dp2(A.size(),n);

    dp1[0] = 0;
    dp2[0] = 1;

    for(int i=1;i<A.size();++i)
    {
        if(A[i]>A[i-1] && B[i] > B[i-1])
        {
            dp1[i] = min(dp1[i],dp1[i-1]);
            dp2[i] = min(dp2[i],1+dp2[i-1]);
        }

        if(A[i] > B[i-1] && B[i] > A[i-1])
        {
            dp1[i] = min(dp1[i],dp2[i-1]);
            dp2[i] = min(dp2[i],1+dp1[i-1]);
        }

        printf("%d %d\n",dp1[i],dp2[i]);
    }

    return min(dp1[n-1],dp2[n-1]);
}

int main()
{
    vector<int> A = {1,3,5,4};
    vector<int> B = {1,2,3,7};
    A = {0,3,5,8,9};
    B = {2,1,4,6,9};
    // A = {0,4,4,5,9};
    // B = {0,1,6,8,10};
    // A = {3,3,8,9,10};
    // B = {1,7,4,6,8};
    // A = {2,3,2,5,6};    //1
    // B = {0,1,4,4,5};
    // A = {0,3,5,8,9}; //1
    // B = {2,1,4,6,9};
    printf("%d\n",minSwap(A,B));
    return 0;
}



