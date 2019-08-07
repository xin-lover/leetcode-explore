//leetcode 807. 保持城市天际线

#include <cstdio>
#include <vector>

using namespace std;

int maxIncreaseKeepingSkyline(vector<vector<int>>& grid) {
    //思路：首先要找到轮廓点，四个方向都一样，意味着其它的点不能超过轮廓点
    //每一个位置都需要考虑纵向和横向两个轮廓点

    int m = grid.size();
    int n = m == 0 ? 0 : grid[0].size();
    vector<int> row(m);
    vector<int> col(n);

    for(int i=0;i<m;++i)
    {
        for(int j=0;j<n;++j)
        {
            row[i] = max(row[i],grid[i][j]);
        }
    } 

    for(int i=0;i<n;++i)
    {
        for(int j=0;j<m;++j)
        {
            col[i] = max(col[i],grid[j][i]);
        }
    } 

    int res = 0;
    for(int i=0;i<m;++i)
    {
        for(int j=0;j<n;++j)
        {
            res += min(row[i],col[j]) - grid[i][j];
        }
    }

    return res;
}

int main()
{
    vector<vector<int>> grid = { {3, 0, 8, 4}, 
    {2, 4, 5, 7},
    {9, 2, 6, 3},
    {0, 3, 1, 0} };

    printf("%d\n",maxIncreaseKeepingSkyline(grid));
    return 0;
}