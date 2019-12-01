//991. 坏了的计算器

#include <cstdio>
#include <vector>

using namespace std;

int brokenCalc(int X, int Y) {
    //思路：如果x比y小，只能减
    //主要处理增加的情况，可以使用动规
    //dp[i]表示x到i需要的操作次数，那么dp[i]=min(dp[i-1]+1,dp[i/2]+1)

    if(Y < X)
    {
        return X - Y;
    }
    vector<int> dp(Y+1,0);
    for(int i=X+1;i<=Y;++i)
    {
        int half = i / 2;
        int c =0;
        if(half <= X)
        {
            c = X - half;
        }
        else
        {
            c = dp[c];
        }

        dp[i] = min(dp[i-1],c)+1;
    }

    return dp[Y];
}

int main()
{
    printf("%d\n",brokenCalc(2,3));//2
    printf("%d\n",brokenCalc(5,8));//2
    printf("%d\n",brokenCalc(3,10));//3
    printf("%d\n",brokenCalc(1024,1));//1023
    return 0;
}