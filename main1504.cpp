//1504. 统计全 1 子矩形

#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

int numSubmat(vector<vector<int>>& mat) {
    //思路：一个矩形全1，那么其子矩形也全1，不能用以前正方形的思路
    //因为是矩形，这种方式会重复计算
    //先写一个o(n^3)复杂度的

    if(mat.empty() || mat[0].empty())
    {
        return 0;
    }
    int m = mat.size();
    int n = mat[0].size();
    vector<vector<int>> dp(mat.size()+1,vector<int>(mat[0].size()+1,0));
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            dp[i][j] = dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1] + mat[i-1][j-1];
        }
    }

    int res = 0;
    //计算包含mat[i][j]的个数
    for(int i=0;i<mat.size();++i)
    {
        for(int j=0;j<mat[0].size();++j)
        {
            for(int x=i;x<mat.size();++x)
            {
                for(int y = j;y<mat[0].size();++y)
                {
                    int v = dp[x+1][y+1] - dp[i][y+1]-dp[x+1][j]+dp[i][j];
                    if(v == (x-i+1)*(y-j+1))
                    {
                        ++res;
                    }
                }
            }
        }
    }

    return res;
}

int numSubmat2(vector<vector<int>>& mat) {
    //思路：统计以mat[i][j]为右下角矩形，计算全1的子矩形个数；
    //这样我们需要枚举左上角，但这个复杂度高
    //可以用row[i][j]表示矩阵行中向左到mat[i][j]位置时连续的1的个数
    //然后我们统计以mat[i][j]为右下角，左上角在第k行的全1矩形，如何确定左上角的列索引？
    //很明显，是第i到第k行之间的连续1个数的最小值，注意连续1的个数是以第j列结尾的
    //我们找到这样的矩形，因为是遍历的行，也就是矩形的高，所以，要统计的子矩形是(i-k+1,x)的形式
    //x可取(1,2,3……min(col))

    int n = mat.size();
    int m = mat[0].size();
    vector<vector<int> > row(n, vector<int>(m, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j == 0) {
                row[i][j] = mat[i][j];
            } else if (mat[i][j]) {
                row[i][j] = row[i][j - 1] + 1;
            }
            else {
                row[i][j] = 0;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int col = row[i][j];
            for (int k = i; k >= 0 && col; --k) {
                col = min(col, row[k][j]);
                ans += col;
            }
        }
    }
    return ans;
}

//优化,单调栈,利用的是，如果连续1的个数随着行递增
//那么，新加一行其实可以使用之前已计算的子矩形个数加上自己这一行的子矩形个数，也就是连续1的个数
//所以要处理的就是不递增的情况
//假设i-1行连续1的个数a，第i行的个数是b，b < a;
//根据我们的算法，以mat[i][j]为右下角的个数是由连续行中连续1的最少个数决定的
//所以第i-1行的（1，a-b）的矩形不能记录到第i行的全1子矩形的
//也就是所第0到i-1行中只有小于等b的列才会记录，这个时候符合单调栈的情况
int numSubmat3(vector<vector<int>>& mat) {
    int n = mat.size();
    int m = mat[0].size();
    vector<vector<int> > row(n, vector<int>(m, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j == 0) {
                row[i][j] = mat[i][j];
            } else if (mat[i][j]) {
                row[i][j] = row[i][j - 1] + 1;
            }
            else {
                row[i][j] = 0;
            }
        }
    }
    int ans = 0;
    for (int j = 0; j < m; ++j) { 
        int i = 0; 
        stack<pair<int, int>> Q; 
        int sum = 0; 
        while (i <= n - 1) { 
            int height = 1; 
            while (!Q.empty() && Q.top().first > row[i][j]) {
                // 弹出的时候要减去多于的答案
                sum -= Q.top().second * (Q.top().first - row[i][j]); 
                height += Q.top().second; 
                Q.pop(); 
            } 
            sum += row[i][j]; 
            ans += sum; 
            Q.push({ row[i][j], height }); 
            i++; 
        } 
    } 
    return ans;
}


int main()
{
    vector<vector<int>> mat = {
        {1,0,1},
        {1,1,0},
        {1,1,0}};

    mat = {{0,1,1,0}, {0,1,1,1}, {1,1,1,0}}; //24

    printf("%d\n",numSubmat(mat));

    return 0;
}