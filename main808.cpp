//leetcode 808. 分汤

#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

double soupServings(int A,int B)
{
    if(A <= 0)
    {
        if(B > 0)
        {
            return 1.0;
        }
        else
        {
            return 0.5;
        }
        
    }
    
    if(A > 0)
    {
        if(B <= 0)
        {
            return 0.0;
        }
        
    }

    double res = 0;
    return 0.25 * soupServings(A-100,B)
    + 0.25 * soupServings(A-75,B-25)
    + 0.25 * soupServings(A-50,B-50)
    + 0.25 * soupServings(A-25,B-75);

}

int factorial(int N)
{
    int r = 1;
    for(int i=N;i>1;--i)
    {
        r *= i;
    }

    return r;
}

double soupServings(int N) {
    //思路：对于不够一次分配的情况，很简单，所以问题是针对多次分配的情况
    //策略：采用递归的方式

    //超时，每一次有4条分支，如果分10层，也就是4的10次方
    // return soupServings(N,N);

    //优化：
    //根据分配方式，如果A>B,B>50，则按前三种方式分配，则肯定是A先结束
    //所以问题是否可以表示为各项选择的组合

    //偏小，少计算了，先2再1之类的情况，比如100,我们可以先选择2，再选择1或3
    int max_choice = N / 50 + (N % 50 > 0 ? 1 : 0);

    vector<int> flags(4,0);
    double res = 0;
    int max1 = N / 100 + (N%100 > 0 ? 1 : 0);
    for(int i=0;i<=max1;++i)
    {
        int rt = N-i*100;
        int max2 = rt <=0 ? 0 : (rt / 75 + (rt % 75 > 0 ? 1 : 0));
        for(int j=0;j<=max2 ;++j)
        {
            rt = N - i * 100 - j * 75;
            int max3 = rt <=0 ? 0 : (rt / 50 + (rt % 50 > 0 ? 1 : 0));
            for(int k=0;k<=max3;++k)
            {
                int A = N - i * 100 - j * 75 - k * 50;
                int B = N - j*25 - k * 50;

                int c = 0;
                if(A >= 0 && B >= 0)
                {
                    c = min(A / 25, B / 75);
                    A -= c * 25;
                    B -= c * 75;

                    if(A > 0 && B > 0)
                    {
                        A -= 25;
                        B -= 75;
                        c += 1;
                    }            
                }
                
                int t = i + j + k + c;
                printf("%d %d %d %d\n",i,j,k,c);
                if(A <= 0)
                {
                    //溢出
                    double p = pow(0.25,t) * factorial(t) / (factorial(i) * factorial(j) * factorial(k) * factorial(c));
                    if(B <= 0)
                    {
                        p *= 0.5;
                    }
                    printf("p:%f\n",p);

                    res += p;
                }
            }
        }
    }

    return res;
}

double soupServings2(vector<vector<double>>& dp,int A,int B)
{
    if(A>=0 && B>= 0 && dp[A][B] > -1.0)
    {
        return dp[A][B];
    }

    if(A <= 0)
    {
        if(B > 0)
        {
            return 1.0;
        }
        else
        {
            return 0.5;
        }
    }
    
    if(A > 0)
    {
        if(B <= 0)
        {
            return 0.0;
        }
    }

    dp[A][B] = 0.25 * soupServings2(dp,A-100,B)
            + 0.25 * soupServings2(dp,A-75,B-25)
            + 0.25 * soupServings2(dp,A-50,B-50)
            + 0.25 * soupServings2(dp,A-25,B-75);
    
    return dp[A][B];
}

double soupServings2(int N)
{
    //考虑动归
    if(N > 4800)
    {
        return 1.0;
    }
    vector<vector<double>> dp(N+1,vector<double>(N+1,-1.0));
    return soupServings2(dp,N,N);
}

double soupServings3(int N)
{
    if(N >= 4800)
    {
        return 1;
    }
    int mN = static_cast<int>(ceil(N/25.0));
    vector<vector<double>> dp(mN+1,vector<double>(mN+1,0.0));
    dp[0][0] = 0.5;
    
    for(int i=1;i<mN+1;++i)
    {
        dp[i][0] = 0.0;
        dp[0][i] = 1.0;
    }
    
    for(int i=1;i<=mN;++i)
    {
        int a1 = i > 4 ? i-4 : 0;
        int a2 = i > 3 ? i-3 : 0;
        int a3 = i > 2 ? i-2 : 0;
        int a4 = i > 1 ? i-1 : 0;
        for(int j=1;j<=mN;++j)
        {
            int b1 = j;
            int b2 = j > 1 ? j-1:0;
            int b3 = j > 2 ? j-2:0;
            int b4 = j > 3 ? j-3 : 0;
            
            dp[i][j] = 0.25 * (dp[a1][b1] + dp[a2][b2] + dp[a3][b3] + dp[a4][b4]);
        }
    }
    
    return dp[mN][mN];
}

int main()
{
    printf("%f\n",soupServings2(800));
    return 0;
}