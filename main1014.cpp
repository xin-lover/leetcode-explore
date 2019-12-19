//1014. 最佳观光组合

#include <cstdio>
#include <vector>

using namespace std;

int maxScoreSightseeingPair(vector<int>& A) {
    //思路：A(i,j)=A[i]+A[j]+i-j;
    //A(j,k)=A[j]+A[k]+j-k;
    //两者相加得:A[i]+2*A[j]+A[k]+i-k = A(i,k)+2*A[j]
    //在考虑一下A(i,j)=A[i]+A[j]+i-j = A[i]+i + A[j]-j
    //也就是说对于j，只要A[i]+i最大即可
    //方案：使用一个数组记录当前位置i前的最大A[i]+i，然后再次遍历A求值最大和即可

    if(A.empty())
    {
        return 0;
    }

    vector<int> B(A.size(),0);
    int mxi = A[0];
    for(int i=1;i<A.size();++i)
    {
        mxi = max(mxi,A[i-1]+i-1);
        B[i] = mxi;
    }

    int res = 0;
    for(int i=1;i<A.size();++i)
    {
        res = max(res,B[i] + A[i]-i);
    }

    return res;
}

int maxScoreSightseeingPair2(vector<int>& A) {
    //优化：空间复杂度O(1)

    int premax = 0;
    int res = 0;
    for(int i=1;i<A.size();++i)
    {
        premax = max(premax,A[i-1] + i-1);
        res = max(res,premax + A[i]-i);
    }

    return res;
}
int main()
{
    vector<int> A = {8,1,5,2,6};
    printf("%d\n",maxScoreSightseeingPair2(A));
    return 0;
}

