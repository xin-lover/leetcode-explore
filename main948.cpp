//leetcode 948. 令牌放置

#include <cstdio>
#include <vector>

using namespace std;

int bagOfTokensScore(vector<int>& tokens, int P) {
    //思路：获取最大分数，其实就是把P最有效率的用掉,也就是用低能量获取分，然后换取高能量，再换取分
    //即200能量可以获取1分，1分又可以获取400能量，400能量又可以兑换100和300的令牌而获得2分
    //假设我们是先有1分，那我们可以有两种情况，如果少于三块令牌，则最后得1分，某则，我们选择置换能量点最大的
    //这样能获得最多的成本
    //如果先有能量，我们选择最小的能量令牌换取一分，这样这个一分能换取的能量+上剩余能量才能是最大成本
    //策略：先排序，然后从左边的令牌获取分，右边的令牌获取能量，令牌数少于3的时候，只换分
    //剩下的问题就是，在有能量也有分的情况下，是获取能量还是获取分，这里选择先获取分，也就是用最低的成本先获取分总是不亏的

    if(tokens.empty())
    {
        return 0;
    }

    sort(tokens.begin(),tokens.end());
    if(P < tokens[0])
    {
        return 0;
    }

    int score = 0;
    int left=0,right = tokens.size()-1;
    while(left <= right)
    {
        while(left <= right && P >= tokens[left])
        {
            ++score;
            P-=tokens[left];
            ++left;
        }

        if(left+1 >= right)
        {
            break;
        }
        P+=tokens[right];
        --right;
        --score;
        
    }

    return score;
}

int main()
{
    vector<int> tokens = {100};
    printf("%d\n",bagOfTokensScore(tokens,50));//0

    tokens = {100,200};
    printf("%d\n",bagOfTokensScore(tokens,150)); //1

    tokens = {100,200,300,400};
    printf("%d\n",bagOfTokensScore(tokens,200));//2

    tokens = {26};
    printf("%d\n",bagOfTokensScore(tokens,51));//2

    return 0;
}