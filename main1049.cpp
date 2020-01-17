//1049. 最后一块石头的重量 II

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

int lastStoneWeightII(vector<int>& stones) {
    //思路：因为一直是两块石头碰，所以把所有石头都分为两个阵营
    //其实就是求两个阵营的差，也就是说分组，使两组的重量最接近
    //如果我们把前面i个元素都分好组了，那么到第i个的时候，可能引发前面元素的重新分组
    //我们这么想，如果有一个元素大于整个数组和的半数，那么分组直接出来
    //否则，最大的元素应该和其它元素组成一个最靠近半数的数
    //那么问题又可以变为背包问题，也就是一个半数容量的口袋，如何最大限度装满
    //问题，每个石子只能用一次，

    sort(stones.begin(),stones.end());
    int sum = 0;
    for(auto a : stones)
    {
        sum += a;
    }

    if(stones.back() * 2 >= sum)
    {
        return stones.back() * 2 - sum;
    }
    int half = sum / 2;
    printf("half:%d\n",half);
    vector<int> dp(half+1,0);
    for(int i=0;i<stones.size();++i)
    {
        for(int j=half;j>=0;--j)
        {
            if(j>=stones[i])
            {
                dp[j] = max(dp[j],dp[j-stones[i]]+stones[i]);
            }
        }
    }

    return abs(sum - 2 * dp[half]);
}

//不用背包算法的话，可以使用一个集合来存储所有的和，然后不断的把新的石头和这些和相加，得到新的和，选取最靠近sum/2的和即可
//其实还是穷举的意思，只不过也是借助了动归的思想

int main()
{
    vector<int> stones = {2,7,4,1,8,1}; //1
    stones = {31,26,33,21,40};//5
    printf("%d\n",lastStoneWeightII(stones));
    return 0;
}