//552. 学生出勤记录 II

#include <cstdio>
#include <vector>

using namespace std;

int checkRecord(int n) {
    //思维：首先记录纯P的数量1个，
    //A最多一个，纯p相当于没有A，还有就是1个A的情况，剩余P和L组合，因为L不能连续，所以L前后必须都是P
    //根据A的位置，前后可分为两段
    //对于P和L，当前位置是P，那么后面可以是P也可以是L，而如果当前是L，那么后面只能是P
    //所以使用动归，dp[i][0]表示i个字符（P或L）中以P结束的可奖励序列，而dp[i][1]表示以L结束的可奖励序列数量
    //则：dp[i][0]=dp[i-1][0]+dp[i-1][1],dp[i][1]=dp[i-1][0]
    //看错，可以两个LL，不能三个LL,那么还是同样想法,dp[i][0]表示PP结束，dp[i][1]表示PL结束,dp[i][2]表示LP结束，,dp[i][3]表示LL结束
    //dp[i][0]=dp[i-1][0]+dp[i-1][2],  dp[i][1]=dp[i-1][0] + dp[i-1][2],  dp[i][2]=dp[i-1][1] + dp[i-1][3],  dp[3]=dp[i-1][1] + dp[i-1][3]

    if(n == 1)
    {
        return 3;
    }
    const int cLimit=1000000007;

    vector<vector<int>> dp(n,vector<int>(4,0));
    dp[0][0] = 1;
    dp[0][1] = 1;
    for(int i=1;i<n;++i)
    {
        dp[i][0] = (dp[i-1][0] + dp[i-1][2])%cLimit;
        dp[i][1] = (dp[i-1][0] + dp[i-1][2])%cLimit;
        dp[i][2] = (dp[i-1][1] + dp[i-1][3])%cLimit;
        dp[i][3] = dp[i-1][1];
    }

    int res = 0;
    res += (static_cast<long long>(dp[n-1][0]) + dp[n-1][1] + dp[n-1][2] + dp[n-1][3])%cLimit; //p和l组合,没有a

    //只有一个A
    if(n>1)
    {
        res += ((static_cast<long long>(dp[n-2][0]+dp[n-2][1]) + dp[n-2][2] + dp[n-2][3])*2)%cLimit; //首尾是A
    }
    for(int i=1;i<n-1;++i)
    {
        //A把序列分为前后两部分
        int preLen = i;
        int sufLen = n-i-1;
        long long preCount = (static_cast<long long>(dp[preLen-1][0]) + dp[preLen-1][1] + dp[preLen-1][2] + dp[preLen-1][3])%cLimit;
        long long sufCount = (static_cast<long long>(dp[sufLen-1][0]) + dp[sufLen-1][1] + dp[sufLen-1][2] + dp[sufLen-1][3])%cLimit;
        res = (res + preCount * sufCount) % cLimit;
    }

    return res;
}

int RecFun(int n)
{
    const int cLimit = 1000000007;
    if(n == 0)
    {
        return 1;
    }
    else if(n == 1)
    {
        return 2;
    }
    else if( n== 2)
    {
        return  4;
    }
    else if(n == 3)
    {
        return 7;
    }

    return (2*RecFun(n-1) - RecFun(n-4)) % cLimit;
}

int checkRecord2(int n) {
    //同样递归：dp[i]表示长度为i，可奖励序列的个数（只包含P和L），那么dp[i]=2dp[i-1]-dp[i-4]
    //如何得来的？还是上面的思路，只有LLL是不行的,dp[i-1]后有两种选择，第i为放p的话，则肯定能奖励，放L则需要看前方是否是LL，而以LL结束的可奖励序列有dp[i-4]种，
    //所以得到得到：dp[i]=2dp[i]-dp[i-4]

    const int cLimit = 1000000007;

    vector<int> f(n+1,0);
    f[0]=1;
    for(int i=1;i<=n;++i)
    {
        f[i] = RecFun(i); //很明显，recfun需要动归优化
    }

    int sum = RecFun(n);
    for(int i=1;i<=n;++i)
    {
        sum += (f[i-1]*f[n-i]) % cLimit;
    }

    return sum % cLimit;
}

int checkRecord3(int n) {
    //思路：使用状态转换，因为P不影响可奖励序列，只需要根据末尾L的数量和是否包含A划分状态，就可以往下递推了，记录所有的状态数
    //axly表示长度为i包含x个a并以y个l结尾的字符串数量
    //漂亮

    const int cLimit = 1000000007;

    long long a0l0=1;
    long long a0l1=0,a0l2=0,a1l0=0,a1l1=0,a1l2=0;
    for(int i=0;i<n;++i)
    {
        long long new_a0l0 = (a0l0+a0l1+a0l2) % cLimit;
        long new_a0l1 = a0l0;
        long new_a0l2 = a0l1;
        long new_a1l0 = (a0l0 + a0l1 + a0l2 + a1l0 + a1l1 + a1l2) % cLimit;
        long new_a1l1 = a1l0;
        long new_a1l2 = a1l1;
        a0l0 = new_a0l0;
        a0l1 = new_a0l1;
        a0l2 = new_a0l2;
        a1l0 = new_a1l0;
        a1l1 = new_a1l1;
        a1l2 = new_a1l2;
    }

    return (int)((a0l0 + a0l1 + a0l2 + a1l0 + a1l1 + a1l2) % cLimit);

        //     long a0l0 = 1, a0l1 = 0, a0l2 = 0, a1l0 = 0, a1l1 = 0, a1l2 = 0;
        // for (int i = 0; i <= n; i++) {
        //     long a0l0_ = (a0l0 + a0l1 + a0l2) % M;
        //     a0l2 = a0l1;
        //     a0l1 = a0l0;
        //     a0l0 = a0l0_;
        //     long a1l0_ = (a0l0 + a1l0 + a1l1 + a1l2) % M;
        //     a1l2 = a1l1;
        //     a1l1 = a1l0;
        //     a1l0 = a1l0_;
        // }
        // return (int) a1l0;

}

int main()
{
    // printf("%d\n",checkRecord(2)); //8
    // printf("%d\n",checkRecord(1)); //3
    // printf("%d\n",checkRecord(3)); //19
    // printf("%d\n",checkRecord(4)); //43
    printf("%d\n",checkRecord2(5)); //94
    return 0;
}