//leetcode 931. 下降路径最小和

#include <cstdio>
#include <vector>

using namespace std;

int minFallingPathSum(vector<vector<int>>& A) {
    //思路：可以思考两行的情况，我们可以求出一行结果，这个结果是以第二行的元素为结尾的下降列最小值，
    //新加一行，与上面的结果又组成两行，可以看出，这两行计算的结果和原来三行的结果是一样的，

    if(A.empty() || A[0].empty())
    {
        return 0;
    }

    int n = A.size();
    vector<int> dp = A[0]; 
    vector<int> tmp(n,0);   //可优化，不使用tmp，求新的行三个候选数的最小值加到dp中，而不是dp中三个候选的最小值加到新行元素中

    for(int i=1;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            tmp[j] =A[i][j] + min(min(j > 0 ? dp[j-1] : dp[j],dp[j]), j+1 < n ? dp[j+1]:dp[j]);
        }

        swap(dp,tmp);
    }

    int res = dp[0];
    for(int i=0;i<n;++i)
    {
        res = min(res,dp[i]);
    }

    return res;
}

int main()
{
    vector<vector<int>> A = {{1,2,3},{4,5,6},{7,8,9}};//12
    A = {{17,82},{1,-44}};
    printf("%d\n",minFallingPathSum(A));
    return 0;
}