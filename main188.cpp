//188. 买卖股票的最佳时机 IV

#include <cstdio>
#include <vector>

using namespace std;

int maxProfit(int k, vector<int>& prices) {
    //思路：考虑一笔交易，我们肯定是去当前遇到的最小价格买，最大价格卖
    //dp[i][0]表示第i天状态时买入时的最大收益，dp[i][1]表示第i天状态是卖出时的最大收益
    //则dp[i][0]=max(dp[i-1][1]-prices[i],dp[i-1][0]),dp[i][1] = max(dp[i-1][0] + prices[i],dp[i-1][1])
    //如果有多笔，那么可以使用dp[i][j][0]表示第i天第j场交易买入时最大利润，dp[i][j][1]表示第i天第j场交易卖出时最大利润

    int n = prices.size();
    //提前剪枝
    k = min(k,n/2);
    if(n == 0 || k == 0)
    {
        return 0;
    }
    // vector<vector<vector<int>>> dp(n,vector<vector<int>>(k+1,vector<int>(2,0)));

    // for(int i=0;i<=k;++i)
    // {

    //     dp[0][i][0] = -prices[0];
    // }

    // for(int i=1;i<n;++i)
    // {

    // }

    // for(int i=1;i<=n;++i)
    // {
    //     for(int j=1;j<k;++j)
    //     {
    //         dp[i][j][1] = max(dp[i-1][j][0] + prices[i-1],dp[i-1][j][1]);
    //         dp[i][j][0] = max(dp[i-1][j-1][1] - prices[i-1],dp[i-1][j-1][0]);

    //         printf("dp[%d][%d]:%d %d\n",i,j,dp[i][j][0],dp[i][j][1]);
    //     }
    // }

    // return dp[n][k-1][1];

    //一笔交易
    // int minBuy = -prices[0];
    // int sell = 0;

    // for(int i=1;i<n;++i)
    // {
    //     minBuy = max(minBuy,-prices[i]);
    //     sell = max(prices[i]+minBuy,sell);
    // }

    // return sell;

    //两笔交易
    // int buy1=-prices[0],buy2=-prices[0];
    // int sell1=0,sell2=0;

    // for(int i=1;i<n;++i)
    // {
    //     buy1 = max(buy1,-prices[i]);
    //     sell1 = max(prices[i] + buy1,sell1);
    //     buy2 = max(sell1 - prices[i],buy2);
    //     sell2 = max(prices[i]+buy2,sell2);
    // }

    // return sell2;


    vector<int> dpBuy(k,-prices[0]);
    vector<int> dpSell(k,0);

    for(int i=1;i<n;++i)
    {
        for(int j=0;j<k;++j)
        {
            dpBuy[j] = max(dpBuy[j],(j==0 ? 0 : dpSell[j-1])-prices[i]);
            dpSell[j] = max(dpBuy[j] + prices[i],dpSell[j]);
        }
    }

    return dpSell[k-1];
}

int main()
{
    vector<int> prices = {2,4,1}; //2
    int k = 2;
    // prices = {3,2,6,5,0,3}, k = 2; //7
    
    // k=2;
    // prices = {6,1,3,2,4,7}; //7
    
    k=0;
    prices = {1,3};

    k=1;
    prices={1};

    printf("%d\n",maxProfit(k,prices));
    return 0;
}