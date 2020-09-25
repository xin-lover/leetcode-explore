//1578. 避免重复字母的最小删除成本

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

int minCost(string s, vector<int>& cost) {
    //思路：如何使相邻元素不同，考虑s[i]==s[i+1]
    //可选择的有删除s[i]或s[i+1]，选择哪个？
    //可以考虑贪心算法，那贪心会产生最优解吗？
    //假设s[i]==s[i+1]==s[i+2],产生的使最优的

    int curMax = 0;
    int start = 0;
    int res= 0;
    for(int i=1;i<=s.size();++i)
    {
        if(s[i] == s[start])
        {
            res += cost[i];
            printf("%d\n",cost[i]);
            if(cost[i] > cost[curMax])
            {
                curMax = i;
            }
        }
        else
        {
            if(i-start > 1)
            {
                printf("res:%d\n",res);
                res -= abs(cost[curMax]-cost[start]);
            }
            start = i;
            curMax = i;
        }
    }

    return res;
}

int main()
{
    string s = "abc";
    vector<int> cost = {1,2,3}; //0

    s = "aabaa", cost = {1,2,3,4,1};    //2
    // s = "abaac", cost = {1,2,3,4,5}; //3

    printf("%d\n",minCost(s,cost));

    return 0;
}