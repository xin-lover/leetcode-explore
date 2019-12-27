//1035. 不相交的线

#include <cstdio>
#include <vector>
#include <unordered_map>
#include <stack>

using namespace std;

int maxUncrossedLines(vector<int>& A, vector<int>& B) {
    //思路：一个点只能连一条线，所以我们遍历A数组中的点，选择B中的点相连
    //使用贪心策略，尽量使B中的点索引小，这样A中的点可选择的范围就更大
    //因为点只能被用一次，所以采用贪心策略即可，即选择b中的最左侧的可用的点
    //这种策略还是不行，比如A1与B3相连，后面的A3,A4,都能与B1,B2相连，这个时候如果选择A3，明显不对
    //我们发现，如果要使线不相交，那么每条线对应的B点应该符合原先的排列顺序，即如果有线(Ai,Bj),(Am,Bn),那么当Ai>Bi时，Am>Bn
    //所以我们使用一个递增栈，比较的是B点索引的大小
    //这里需要注意两点，如果新的线不与之前的线相交，那么安全添加，否则。。。
    //这个也不行，不能简单的出栈，因为最后可能是这条线不需要
    //动归，dp[i][j]表示不相交线的数量，i和j表示A和B的索引，如果i与j相连则dp[i][j] = dp[i-1][j-1]+1,否则dp[i][j] = max(dp[i][j-1],dp[i-1][j])
    // unordered_map<int,vector<int>> um;
    // for(int i=0;i<B.size();++i)
    // {
    //     um[B[i]].push_back(i);
    // }

    if(A.empty() || B.empty())
    {
        return 0;
    }

    int m = A.size(),n = B.size();
    vector<vector<int>> dp(m+1,vector<int>(n+1));
    dp[0][0] = 0;
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(A[i-1] == B[j-1])
            {
                dp[i][j] = dp[i-1][j-1]+1;
            }
            else
            {
                dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
            }
            
        }
    }
    return dp[m][n];
}

int main()
{
    vector<int> A = {1,4,2}, B = {1,2,4}; //2
    A = {2,5,1,2,5}, B = {10,5,2,1,5,2}; //3
    A = {1,3,7,1,7,5}, B = {1,9,2,5,1}; //2
    printf("%d\n",maxUncrossedLines(A,B));
    return 0;
}