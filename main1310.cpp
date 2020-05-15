//1310. 子数组异或查询

#include <cstdio>
#include <vector>

using namespace std;

vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
    //思路：根据异或的运算的特性，两次异或同一个数，将得到本身，也就是axor0=a
    //可以考虑动归,dp[i]表示第0位到第i位的异或值，dp[i][j]=dp[i]xordp[i]

    vector<int> dp(arr.size()+1,0);
    for(int i=1;i<dp.size();++i)
    {
        dp[i] = (dp[i-1] ^ arr[i-1]);
    }

    vector<int> res(queries.size());
    for(int i=0;i<queries.size();++i)
    {
        res[i] = dp[queries[i][1]+1] ^ dp[queries[i][0]];
    }

    return res;
}

int main()
{
    vector<int> arr = {1,3,4,8};
    vector<vector<int>> queries = {{0,1},{1,2},{0,3},{3,3}};    //[2,7,14,8] 

    arr = {4,8,2,10};
    queries = {{2,3},{1,3},{0,0},{0,3}};    //[8,0,4,4]
    for(auto a : xorQueries(arr,queries))
    {
        printf("%d ",a);
    }
    printf("\n");

    return 0;
}