//1140. 石子游戏 II

#include <cstdio>
#include <vector>

using namespace std;

int stoneGameII(vector<int>& piles,int left,int m,int sum) {
    //
    if(piles.size() - left <= 2 * m)
    {
        return sum;
    }

    int res = 0;
    int t=0;
    for(int i=1;i<=2*m;++i)
    {
        t+= piles[left+i-1];
        int r = sum - t - stoneGameII(piles,left+i,max(i,m),sum-t);
        res = max(res,t + r);
    }

    return res;
}
int stoneGameII(vector<int>& piles) {
    //思路：简单的就是回溯递归，但复杂度还要超过O(n^2)
    //我们思考这里面的情况：
    //1.如果有一堆超过半数，那么必须考虑怎么样拿到这一堆，然而我们会发现第一个人不一定能拿到
    //所以，这道题问的是最多能拿到，比一定是比第二个人多
    //那这个时候就需要制定一个策略了，还是从简单的开始
    //1.数组只有1个或2个与元素时，全部拿到
    //2.数组有3个元素时，选择前两个；
    //3.4个元素时，选择{1，2},{1，4}中大的那个；
    //4.5个元素时，我们会发现，有{1,2},{1,3,4},{1,4,5},这里有两部步，但第二步不由第一个人决定
    //也就是我们所说的递归情况,先实现一版，应该是超时

    int sum = 0;
    for(auto a : piles)
    {
        sum += a;
    }

    return stoneGameII(piles,0,1,sum);
    
}

int stoneGameII2(vector<int>& piles,int left,int m,int sum,vector<vector<int>>& dp) {
    //

    if(dp[left][m] != -1)
    {
        return dp[left][m];
    }

    int res = 0;
    if(piles.size() - left <= 2 * m)
    {
        res = sum;
    }
    else 
    {
        int t=0;
        for(int i=1;i<=2*m;++i)
        {
            t+= piles[left+i-1];
            int r = sum - t - stoneGameII2(piles,left+i,max(i,m),sum-t,dp);
            res = max(res,t + r);
        }
    }

    dp[left][m] = res;
    return res;
}

int stoneGameII2(vector<int>& piles) {
    //上面的思路会有很多重复计算，可以考虑动归，但因为会涉及到m，我们需要把m的最大值确定
    //假设数组是n，那么m不会超过n，在细想，肯定也不会超过n/2，简单起见，使用n

    int n = piles.size();
    vector<vector<int>> dp(n,vector<int>(n,-1));
    int sum = 0;
    for(auto a : piles)
    {
        sum += a;
    }

    return stoneGameII2(piles,0,1,sum,dp);
}

int main()
{
    vector<int> piles = {2,7,9,4,4};
    printf("%d\n",stoneGameII2(piles));
    return 0;
}