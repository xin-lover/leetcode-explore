//363. 矩形区域不超过 K 的最大数值和

#include <cstdio>
#include <vector>
#include <set>

using namespace std;

int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
    //思路：使用动归可以很快求出某个矩形的和，但遍历所有矩形将会是O(MN^2)的复杂度
    //考虑只有一行的情况下，如何求这一行连续区间的最大值？
    //我们可以求前缀和，如果前缀和小于0，那么前缀和置0，重新开始
    //如果换成不大于k的最大值，那么还有点麻烦，使用set，复杂度不是O(N)，而是O(NlogN)
    //对于矩形，可以仿照这个方式，能把复杂度降低到O(M*N^2*logN)或O(M^2 *logM * N)

    int m = matrix.size();
    int n = m == 0 ? 0 : matrix[0].size();

    vector<vector<int>> dp(m,vector<int>(n+1,0));

    for(int i=0;i<m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            dp[i][j] = dp[i][j-1] + matrix[i][j-1];
        }
    }

    int res = INT_MIN;
    for(int len=1;len<=n;++len)
    {
        for(int j=len-1;j<n;++j)
        {
            int tmp = 0;
            set<int> st;
            st.insert(0);
            for(int i=m-1;i>=0;--i)
            {
                tmp += dp[i][j+1]-dp[i][j+1-len];
                auto a = st.lower_bound(tmp-k);
                if(a != st.end())
                {
                    res = max(res,tmp-(*a));
                }
                st.insert(tmp);
            }
        }
    }

    return res;
}

int main()
{
    vector<vector<int>> matrix = {{1,0,1},{0,-2,3}}; //2
    int k = 2;

    // matrix = {{2,2,-1}};
    // k = 0;

    matrix = {{5,-4,-3,4},{-3,-4,4,5},{5,1,5,-4}};
    k = 8;

    matrix = {{2,2,-1}};
    k=3;
    printf("%d\n",maxSumSubmatrix(matrix,k));
    return 0;
}