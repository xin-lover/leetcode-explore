//600. 不含连续1的非负整数

#include <cstdio>
#include <vector>

using namespace std;

int findIntegers(int num) {
    //思路：转换一下问题，假设有n位，没有连续1的可能数
    //假设第一位是0，那么后面n-1位符合要求的数都可以与这个0连接成不含连续1的整数
    //假设第一位是1，那么后面只能跟0，所以后面n-2位符合要求的数都可以和10组成不含连续1的整数
    //也就是:num[i]==0, dp[i] = dp[i-1]; num[i]==1,dp[i] = dp[i-2]
    //综合得：dp[n]=dp[n-1]+dp[n-2]
    //这里还要额外处理不能大于num的情况，首先我们已经确定最高位了，所以最高位取0的情况我们可以很快得出
    //关键在于取1的时候，根据要求，我们需要看第二高位的1的位置，而考虑第二高位1的位置时，这个情况和最高位1的情况是一样的。。。

    vector<int> dp(32,1); //对于int类型，最多考虑31位
    dp[1]=2;
    dp[2]=3;
    for(int i=3;i<32;++i)
    {
        dp[i] = dp[i-1]+dp[i-2];
        printf("i:%d dd:%d\n",i,dp[i]);
    }

    vector<bool> flags(32,false);
    int high = 0;
    for(int i=0;i<32;++i)
    {
        if((1<<i)&num)
        {
            flags[i] = true;
            printf("i:%d\n",i);
        }
    }

for(int i=30;i>=0;--i)
{
        printf("%d",flags[i] ? 1 : 0);
}
printf("\n");
    int res = 0;
    for(int i=30;i>0;--i) //注意不考虑符号位
    {
        if(flags[i])
        {
            if(i+1<31 && flags[i+1])
            {
                res += dp[i];
                return res;
            }
            else
            {
                res += dp[i];
            }
        }
    }
    printf("%d\n",flags[0] ? 1: 0);

    if(!flags[1])
    {
        res += flags[0] ? 2 : 1;
    }
    else
    {
        res +=1;
    }
    
    return res;
}

int main()
{
    // printf("%d\n",findIntegers(5)); //5
    // printf("%d\n",findIntegers(4)); //4
    // printf("%d\n",findIntegers(2)); //3
    printf("\n%d\n",findIntegers(50)); //21
    return 0;
}