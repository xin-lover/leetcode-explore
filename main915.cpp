//leetcode 915. 分割数组

#include <cstdio>
#include <vector>

using namespace std;

int partitionDisjoint(vector<int>& A) {
    //思路：其实就是找一个分割点，左边的最大值小于等于右边的最小值
    //一个想法是从左到右记录最大值，然后右到左记录最小值，看那个位置符合条件

    vector<int> dp(A.size());
    int mn = A.back();
    for(int i=A.size()-1;i>=0;--i)
    {
        if(mn > A[i])
        {
            mn = A[i];
        }

        dp[i] = mn;
    }
    
    int mx = A[0];
    for(int i=0;i<A.size()-1;++i)
    {
        if(A[i] > mx)
        {
            mx = A[i];
        }

        printf("mx:%d dp[i]:%d\n",mx,dp[i]);
        if(mx <= dp[i+1])
        {
            return i+1;
        }
    }

    return A.size();
}

int main()
{
    vector<int> v = {5,0,3,8,6};
    printf("%d\n",partitionDisjoint(v));
    v = {1,1,1,0,6,12};
    printf("%d\n",partitionDisjoint(v));
    return 0;
}