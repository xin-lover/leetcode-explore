//leetcode 877. 石子游戏

#include <cstdio>
#include <vector>

using namespace std;

int stoneGame(vector<int>& piles,vector<vector<int>>& dp, int sum,int start,int end)
{
    printf("%d %d\n",start,end);
    if(start == end)
    {
        return piles[start];
    }   

    if(dp[start][end] == -1)
    {
        dp[start][end] =max(sum - stoneGame(piles,dp,sum - piles[start],start+1,end),sum - stoneGame(piles,dp,sum - piles[end],start,end-1));
    }


    return dp[start][end];
}

bool stoneGame(vector<int>& piles) {
    //思路：可以递归
    //保证先拿的人能赢的情况就是先拿一堆
    //加上动归，不然重复计算太多

    int sum = 0;
    for(auto a : piles)
    {
        sum += a;
    }

    int n = piles.size();
    vector<vector<int>> dp(n,vector<int>(n,-1));
    int p = stoneGame(piles,dp,sum,0,piles.size()-1);
    return p > sum - p;


}

int main()
{
    vector<int> piles = {5,3,4,5};
    piles = {7,7,12,16,41,48,41,48,11,9,34,2,44,30,27,12,11,39,31,8,23,11,47,25,15,23,4,17,11,50,16,50,38,34,48,27,16,24,22,48,50,10,26,27,9,43,13,42,46,24};
    printf(stoneGame(piles) ? "true\n" : "false\n");
    return 0;
}