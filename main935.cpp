//leetcode 935. 骑士拨号器

#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

int knightDialer(int N) {
    //思路：总结，其实就是4个方向走两步，然后再在垂直方向走一步，总共8个位置
    //对于电话键盘数字，可以发现,5没有下一步，而4和6有三个下一步的选择，其它只有两步
    //所以这回到了一个组合的问题,但因为最后数字的选择影响后面的可选择数量，所以考虑使用动归
    //dp[i][j]表示第j 步选择i结尾时的可能，则递进公式
    //dp[i][j+1] = sum(dp[k][j]),其实k是能到达i的点,当直到当前点，递进到当前点能到达的点也是一样

    long long a = static_cast<long long>(1282144675) + 969012821;
    const int upper = pow(10,9)+7;
    vector<vector<int>> reachables = {{4,6},{6,8},{7,9},{4,8},{0,3,9},{},{0,1,7},{2,6},{1,3},{2,4}};

    vector<int> dp(10,1);
    for(int k=1;k<N;++k)
    {
        vector<int> tmp(10,0);
        for(int i=0;i<10;++i)
        {
            for(int j=0;j<reachables[i].size();++j)
            {
                int next = reachables[i][j];
                long long t = tmp[next];
                tmp[next] = (t + dp[i]) % upper;
            }
        }
        swap(dp,tmp);
    }

    int res = 0;
    for(int i=0;i<10;++i)
    {
        res += dp[i];
    }

    return res;

}

int main()
{
    printf("%d\n",knightDialer(1));//10
    printf("%d\n",knightDialer(2));//20
    printf("%d\n",knightDialer(3));//46
    return 0;
}