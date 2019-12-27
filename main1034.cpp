//1034. 边框着色

#include <cstdio>
#include <vector>

using namespace std;

void dfs(vector<vector<int>>& grid, int r, int c, int orgColor,int color)
{
    int m = grid.size();
    int n = grid[0].size();

    if(r < 0 || r >= m || c < 0 || c >= n)
    {
        return;
    }

    if(grid[r][c] != orgColor)
    {
        return;
    }

    grid[r][c] = -color;

    dfs(grid,r+1,c,orgColor,color);
    dfs(grid,r-1,c,orgColor,color);
    dfs(grid,r,c+1,orgColor,color);
    dfs(grid,r,c-1,orgColor,color);
}

vector<vector<int>> colorBorder(vector<vector<int>>& grid, int r0, int c0, int color) {
    //思路：着色只要dfs即可，但因为只要边界，所以遍历时是否着色加上这个条件即可
    //但如果采用不着色前方式那么就很容易陷入死循环，除非记录哪个网格被遍历过
    //但这样很浪费内存，采用着色两次的办法，第一次先按边界和非边界着两中颜色，然后再把非边界着回原来的颜色
    //注意，还可以用同一种颜色来画边界。。。。。。。还可以用其它已有的颜色来着边界颜色
    //所以先把连通分量着色，然后再区分边界

    if(grid.empty())
    {
        return grid;
    }
    int orgColor = grid[r0][c0];
    dfs(grid,r0,c0,orgColor,color);

    //着非边界颜色
    for(int i=1;i<grid.size()-1;++i)
    {
        for(int j=1;j<grid[i].size()-1;++j)
        {
            if(grid[i][j] == -color && grid[i-1][j] < 0 && grid[i+1][j] < 0
                && grid[i][j-1] < 0  && grid[i][j+1] < 0)
            {
                grid[i][j] = -orgColor; //非边界
            }
        }
    }

    for(int i=0;i<grid.size();++i)
    {
        for(int j=0;j<grid[i].size();++j)
        {
            grid[i][j] =abs(grid[i][j]);
        }
    }

    return grid;
}

//dfs + 回溯思想的写法
int dirs[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
bool valid(int r, int c, int R, int C) {
    return r >= 0 && r < R && c >= 0 && c < C;
}
void dfs2(vector<vector<int> >& grid, int r, int c, int R, int C, int color, vector<vector<int> >& res) {
    res[r][c] *= -1;
    bool is_edge = false;
    for (int k = 0; k < 4; ++k) {
        int nr = r + dirs[k][0];
        int nc = c + dirs[k][1];
        if (!valid(nr, nc, R, C) || grid[nr][nc] != grid[r][c]) {
            is_edge = true;
        }
        if (valid(nr, nc, R, C) && res[nr][nc] == grid[r][c]) {   
            dfs2(grid, nr, nc, R, C, color, res);
        }
    }
    res[r][c] *= -1; //这里就相当于回溯了,非常巧妙，使用一个edge来标识，就不同想我那样需要grid再次判断了，相当于使用另一个grid来标识边界
    if (is_edge) {
        res[r][c] = color;
    }
}
vector<vector<int>> colorBorder2(vector<vector<int>>& grid, int r0, int c0, int color) {
    int R = grid.size();
    int C = grid[0].size();
    vector<vector<int> > res = grid;
    dfs2(grid, r0, c0, R, C, color, res);
    return res;
}

int main()
{
    // vector<vector<int>> grid={{1,1},{1,2}};
    // vector<vector<int>> res = colorBorder(grid,0,0,3);
    // vector<vector<int>> grid={{1,2,1},{1,2,2},{2,2,1}};
    // vector<vector<int>> res = colorBorder(grid,1,1,2);
    // vector<vector<int>> grid={{1,2,1,2,1,2},{2,2,2,2,1,2},{1,2,2,2,1,2}};
    // vector<vector<int>> res = colorBorder(grid,1,3,1);
    // vector<vector<int>> grid={{2,1,3,2,1,1,2},{1,2,3,1,2,1,2},{1,2,1,2,2,2,2},{2,1,2,2,2,2,2},{2,3,3,3,2,1,2}};
    // vector<vector<int>> res = colorBorder(grid,4,4,3);
    vector<vector<int>> grid={{3,3,3,3,1,2},{3,2,1,1,1,3},{3,3,3,1,1,3},{3,1,3,1,1,2},{3,3,3,2,3,1},{1,2,1,2,3,2}};
    vector<vector<int>> res = colorBorder(grid,4,1,1);
    
    for(auto a : res)
    {
        for(auto b : a)
        {
            printf("%d ",b);
        }
        printf("\n");
    }

    return 0;
}