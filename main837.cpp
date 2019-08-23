//leetcode 837. 新21点

#include <cstdio>
#include <vector>

using namespace std;


double new21Game(int N, int K, int W,vector<double>& dp) 
{
    if(dp[N] <= 0.0)
    {
        dp[N] = 0.0;
        for(int j=1;j<=W;++j)
        {
            dp[N] = 1.0/W * (new21Game(N-j,K-j,W,dp));
        }
    }

    return dp[N];
}

double new21Game(int N, int K, int W) {
    //思路：首先，N<K时，概率为0，因为条件时分数>=K停止；
    //定义f(N)为要求的概率
    //K=1时，N>=1,第一张就结束了，所以概率时N/W,
    //k=2时，N>=2,第一张有（w-1）/W的概率停止，第二张肯定结束,即概率1.0,所以N>=2时，（w-1)/w * (W-1 - (N-2))/(W-1) + 1/W*1
    //k=3时，N>=3,第一张有(w-2)/W的概率停止，第二张有两种情况，第一张是1第二张结束的概率是(W-1)/W,第一张是2第第二张结束的概率是1.0，所以第二张结束的概率
    //是1/W*(W-1)/W + 1/W*1.0，第三张结束的概率就是1/W*1/W*1/W;
    //最终K=3,小于N的概率：f(3) = (W-2)/W*(W-2-(N-3))/(W-2) + 1/w * (1-f(2)) + 1/W*(1-f(1)) + 1/W*1/W*(1-f(1))
    //总结就是：f(n) = (N-(K-1))/W + (1/W * f(N-1) + 1/W*f(n-2)+……+1/W*f(1)) + 1/W*(1/W*f(N-1-1)+1/W*f(N-1-2)…… + 1/W*f(1))
    //最终策略：动归，dp[K][N]表示最终分数不小于K，得分不超过N的概率
    //则dp[K][N] = 1.0/W * (sum(dp[K-1][N-1] + dp[K-2][N-2]+……+dp[1][1])

    if(N < K)
    {
        return 0.0;
    }

    if(K==0)
    {
        return 1.0;
    }

    //超时
    vector<vector<double>> dp(N+1,vector<double>(K+1,0.0));
    dp[0][0] = 0.0;
    for(int i=1;i<=N;++i)
    {
        // for(int j=1;j<=K;++j)
        // {
        //     if(i >= j)
        //     {
        //         double sum =0.0;
        //         for(int x=1;x<=W;++x)
        //         {
        //             if(x > i)
        //             {
        //                 sum += 0.0;
        //             }
        //             else if(x >=j && x <=i)
        //             {
        //                 sum += 1.0;
        //             }
        //             else
        //             {
        //                 sum += dp[i-x][j-x];
        //             }
        //         }

        //         dp[i][j] = 1.0 / W * sum;
        //     }
        // }

        for(int j=1;j<=i&&j<=K;++j)
        {
            double sum = 0.0;
            for(int x=1;x<j && x<=W;++x)
            {
                sum += dp[i-x][j-x];
            }

            int t = min(W,i)-j+1;
            sum += t < 0 ? 0 : t;
            dp[i][j] = 1.0 / W * sum;
        }
    }

    return dp[N][K];

}

double new21Game2(int N, int K, int W) {
    //思路：用背包问题的思路，dp[i]表示当前抽到的分数为i的概率，
    //则dp[i]=1/W * sum(dp[i-1],dp[i-2]……dp[i-W])
    //最后所求的概率就是sum(dp[K],dp[K+1],……dp[N])

    if(K == 0)
    {
        return 1.0;
    }

    if(K-1+W <= N)
    {
        return 1.0;
    }

    vector<double> dp(N+1,0.0);
    dp[0]=1.0;
    dp[1]=1.0/W;
    for(int i=2;i<K;++i)
    {
        //优化，不需要循环
        // double t = 0.0;
        // int q = min(i,W);
        // for(int j=1;j<=q;++j)
        // {
        //     t+=dp[i-j];
        // }

        // dp[i] = 1.0 / W * t;

        if(i > W)
        {
            dp[i] = (dp[i-1] * W - dp[i-1-W] + dp[i-1]) / W;
        }
        else
        {
            dp[i] = dp[i-1] + dp[i-1]/W;
        }
        
        
    }

    double res = 0.0;
    int start = K-W;
    start = start < 0 ? 0 : start;
    for(int i=start;i<K;++i)
    {
        int bigK=i+W-K+1;
        int bigN = i+W-N;
        bigN = bigN <0 ? 0 : bigN;
        res += (bigK-bigN)*1.0/W * dp[i];
    }

    return res;
}

double new21Game3(int N, int K, int W) {
    //思路：用背包问题的思路，dp[i]表示当前抽到的分数为i的概率，
    //则dp[i]=1/W * sum(dp[i-1],dp[i-2]……dp[i-W])
    //最后所求的概率就是sum(dp[K],dp[K+1],……dp[N])

    if(K == 0)
    {
        return 1.0;
    }

    if(K-1+W <= N)
    {
        return 1.0;
    }

    vector<double> dp(N+1,0.0);
    dp[0]=1.0;
    dp[1]=1.0/W;
    for(int i=2;i<=N;++i)
    {
        if(i > W)
        {
            dp[i] = (dp[i-1] * W - dp[i-1-W] + dp[i-1]) / W;
        }
        else
        {
            dp[i] = dp[i-1] + dp[i-1]/W;
        }
        
        
    }

    double res = 0.0;
    for(int i=K;i<=N;++i)
    {
        res += dp[i];
    }

    return res;
}

int main()
{
    // printf("%f\n",new21Game2(1,0,1));
    // printf("%f\n",new21Game2(10,4,10));
    // printf("%f\n",new21Game2(1,0,3));
    // printf("%f\n",new21Game(10,9,10));
    // printf("%f\n",new21Game2(21,13,10));
    // printf("%f\n",new21Game2(21,17,10));
    // printf("%f\n",new21Game2(9811,8776,1096));
    printf("%f\n",new21Game3(9367,7346,5344));
    return 0;
}