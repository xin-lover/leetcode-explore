//leetcode 714. 买卖股票的最佳时机含手续费


#include <vector>
#include <cstdio>

using namespace std;

int maxProfit(vector<int>& prices, int fee) {
    //思路：使用动态规划，那buy[i]就表示第i天持有股票的最大收益，sell[i]表示第i天不持有股票最大收益

    // vector<int> buy(prices.size(),0);
    // vector<int> sell(prices.size(),0);

    // buy[0] = -prices[0];
    // int res = 0;
    // for(int i=1;i<prices.size();++i)
    // {
    //     buy[i] = max(buy[i-1],sell[i-1] - prices[i]);
    //     sell[i] = max(sell[i-1],buy[i-1] + prices[i] - fee);

    //     res = max(res,sell[i]);
    // }

    // return res;

    //优化，只需要记录sell和buy就行

    int buy = -prices[0];
    int sell = 0;
    // int res = 0;
    for(int i=1;i<prices.size();++i)
    {
        int lastBuy = buy;
        buy = max(buy,sell - prices[i]);
        sell = max(sell,lastBuy + prices[i] - fee);
        // res = max(res,sell);//sell一直是最大的
    }

    return sell;
}

int main()
{
    vector<int> prices = {1, 3, 2, 8, 4, 9};
    printf("%d\n",maxProfit(prices,2));

    return 0;
}