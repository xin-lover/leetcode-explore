//983. 最低票价

#include <cstdio>
#include <vector>

using namespace std;

int mincostTickets(vector<int>& days, vector<int>& costs) {
    //思路：考虑动归，如果第i天不旅行，那么dp[i]=dp[i-1]
    //否则dp[i] = min(dp[i-1]+cost[0],dp[i-7]+cost[1],dp[i-30]+const[2])

    vector<int> dp(366);
    dp[0]=0;
    for(int i=1,j=0;i<dp.size() && j<days.size();++i)
    {
        if(i==days[j])
        {
            ++j;
            int c1 =(i-1>=0 ? dp[i-1] : 0) + costs[0];
            int c2 =(i-7>=0 ? dp[i-7] : 0) + costs[1];
            int c3=(i-30>=0 ? dp[i-30] : 0) + costs[2];
            dp[i] = min(c3,min(c1,c2));
        }
        else
        {
            dp[i]=dp[i-1];
        }
    }

    return dp[days.back()];
}

int main()
{
    vector<int> days = {1,4,6,7,8,20};
    vector<int> costs = {2,7,15};
    days = {1,2,3,4,5,6,7,8,9,10,30,31};
    costs = {2,7,15};

    printf("%d\n",mincostTickets(days,costs));
    return 0;
}