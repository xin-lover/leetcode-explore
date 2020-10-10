//123. 买卖股票的最佳时机 III

#include <cstdio>
#include <vector>

using namespace std;

int maxProfit(vector<int>& prices) {
    //思路：假定当前总利润为0，那么对于利润，买入是负数，卖出是正数
    //我们先考虑一次交易，那么我们只需要考虑当天之前利润最大的那天买入即可
    //也就是记录当前最大的利润，而现在可以进行两笔交易
    //那么第二笔交易会基于第一笔交易的日期来定
    //一个思路就是反过来遍历，记录一个最佳选择，这样其实就是前后两个空间的选择
    //使用动归

    if(prices.empty())
    {
        return 0;
    }

    int n = prices.size();
    vector<int> dp1(n,0),dp2(n,0);

    int minBuy = prices[0];
    for(int i=1;i<n;++i)
    {
        dp1[i] = max(dp1[i-1],prices[i] - minBuy);
        printf("dp[%d]:%d\n",i,dp1[i]);
        minBuy = min(minBuy,prices[i]);
    }

    int maxSell = prices.back();
    for(int i=n-2;i>=0;--i)
    {
        dp2[i] = max(dp2[i+1],maxSell - prices[i]);
        maxSell = max(maxSell,prices[i]);
    }

    int res = 0;
    for(int i=0;i<n-1;++i)
    {
        res = max(res, dp1[i]+dp2[i+1]);
    }

    res = max(res,dp1.back());

    return res;
}

//思路：动态规划+空间优化
int maxProfit2(vector<int> prices) {
    if(prices.empty())
    {
        return 0;
    }

    int n = prices.size();
    //定义5种状态，并初始化第一天的状态
    int dp0 = 0;
    int dp1 = -prices[0];
    int dp2 = 0;
    int dp3 = -prices[0];
    int dp4 = 0;
    for(int i=1;i<n;++i) {
        //这里省略dp0，因为dp0每次都是从上一个dp0来的相当于每次都是0
        //处理第一次买入、第一次卖出
        dp1 = max(dp1,dp0-prices[i]);
        dp2 = max(dp2,dp1+prices[i]);
        //处理第二次买入、第二次卖出
        dp3 = max(dp3,dp2-prices[i]);
        dp4 = max(dp4,dp3+prices[i]);
    }
    //返回最大值
    return max(0,max(max(dp1,dp2),max(dp3,dp4)));
}

int main()
{
    vector<int> prices = {3,3,5,0,0,3,1,4}; //6
    prices = {1,2,3,4,5};  //4
    // prices = {7,6,4,3,1};  //0
    // prices ={3,2,6,5,0,3}; //7

    printf("%d\n",maxProfit2(prices));

    return 0;
}