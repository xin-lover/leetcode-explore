//1292. 元素和小于等于阈值的正方形的最大边长

#include <cstdio>
#include <vector>

using namespace std;

int maxSideLength(vector<vector<int>>& mat, int threshold) {
    //思路：一种思路还是用动归记录自矩阵和，然后列举所有对正方形

    int m = mat.size();
    int n = m == 0 ? 0 : mat[0].size();
    vector<vector<int>> dp(m+1,vector<int>(n+1,0));

    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            dp[i][j] = dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1]+mat[i-1][j-1];
        }
    }

    //优化：可以把两个循环合并在一起
    int res = 0;
    for(int i=0;i<m;++i)
    {
        for(int j=0;j<n;++j)
        {
            for(int k=res;i+k-1<m&&j+k-1<n;++k)//边长
            {
                int bottom = i+k-1;
                int right = j+k-1;

                int s = dp[bottom+1][right+1]-dp[bottom+1][j]-dp[i][right+1] + dp[i][j];
                if(s <= threshold)
                {
                    res = max(k,res);
                }
            }
        }
    }

    return res;
}

int maxSideLength2(vector<vector<int>>& mat, int threshold) {
    //思路：还是动归思路，但配合二分法，通过动归求某一个矩阵的元素和是O(1)
    //然后根据边长二分，边长最大min(m,n),最小1，也就是确定边长后，求所有的以n为边长的子正方形的元素和
    //若找到一个即认为符合要求
    int m = mat.size();
    int n = m == 0 ? 0 : mat[0].size();
    vector<vector<int>> dp(m+1,vector<int>(n+1,0));

    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            dp[i][j] = dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1]+mat[i-1][j-1];
        }
    }

    int left=1,right=min(m,n);
    int res = 0;
    while(left < right)
    {
        int mid = left + (right-left)/2;
        bool find = false;
        for(int i=0;i+mid<=m;++i)
        {
            for(int j=0;j+mid<=n;++j)
            {
                int bottom = i+mid-1;
                int right = j+mid-1;
                int s = dp[bottom+1][right+1]-dp[bottom+1][j]-dp[i][right+1] + dp[i][j];
                if(s <= threshold)
                {
                    find = true;
                    res = max(res,mid);
                    break;
                }

            }
            if(find)
            {
                break;
            }
        }
        if(find)
        {
            left = mid+1;
        }
        else
        {
            right = mid;
        }
        
    }

    return res;
}

int main()
{
    vector<vector<int>> mat = {{1,1,3,2,4,3,2},{1,1,3,2,4,3,2},{1,1,3,2,4,3,2}};
    int threshold = 4; //2

    mat = {{2,2,2,2,2},{2,2,2,2,2},{2,2,2,2,2},{2,2,2,2,2},{2,2,2,2,2}};
    threshold = 1; //0
    printf("%d\n",maxSideLength2(mat,threshold));
    return 0;
}