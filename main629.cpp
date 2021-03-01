//629. K个逆序对数组

#include <cstdio>
#include <vector>

using namespace std;

int kInversePairs(int n, int k) {
    //思路：构建序列的思路没想清楚，换一个
    //比如我们已经直到f(n,k)的结果，能否推导f(n+1,k)的结果？
    //把n+1加入到已有序列，n+1有n+1个位置可选，对于这些选择，很明显，逆序对很容易计算出来
    //那么f(n+1,k)如何计算？对于f(n,k)的序列，n+1只能放到最后，否则会有新的逆序对出来
    //对于f(n,k-1)，那么需要1个新的逆序对，那么n+1只能放到倒数第二位置
    //所以公式出来了:f(n+1,k)=f(n,k)+f(n,k-1)+f(n,k-2)+……+f(n,k-n){k-n>=0}
    //f(n+1,k-1)=f(n,k-1)+f(n,k-1-1)+……+f(n,k-1-n){k-1-n>=0}
    //有以下三种情况
    //假设k-1>=n,可推得: f(n+1,k) = f(n,k)+f(n+1,k-1)-f(n,k-1-n);
    //假设k<=n，可推得：f(n+1,k)=f(n,k)+f(n+1,k-1)

    if(k == 0)
    {
        return 1;
    }

    if(n < 2)
    {
        return 0;
    }

    const int kLimit = 1000000007;

    vector<vector<long long>> dp(n+1,vector<long long>(k+1,0));
    for(int i=2;i<=n;++i) //0逆序序列就1个
    {
        dp[i][0]=1;
    }
    dp[2][1]=1;
    for(int i=3;i<=n;++i)
    {
        for(int j=1;j<=k;++j)
        {
            if(j >= i)
            {
                if(j <= (i*(i-1)/2))
                {
                    dp[i][j]=dp[i-1][j]+dp[i][j-1]-dp[i-1][j-i];
                }
            }
            else
            {
                dp[i][j]=dp[i-1][j]+dp[i][j-1];
            }
            
            dp[i][j] = (dp[i][j]+kLimit) % kLimit;
        }
    }

    return dp[n][k];
}

int main()
{
    // printf("%d\n",kInversePairs(3,0)); //1
    // printf("%d\n",kInversePairs(3,1)); //2
    // printf("%d\n",kInversePairs(3,3)); //1
    // printf("%d\n",kInversePairs(10,4)); //440
    // printf("%d\n",kInversePairs(4,4)); //5
    // printf("%d\n",kInversePairs(10,5)); //1068
    // printf("%d\n",kInversePairs(4,5)); //3
    
    printf("%d\n",kInversePairs(1000,1000)); //1068
    return 0;
}