//1391. 检查网格中是否存在有效路径

#include <cstdio>
#include <vector>

using namespace std;

bool hasValidPath(vector<vector<int>>& grid,int out_x,int out_y)
{
    int m = grid.size();
    int n = m==0 ? 0 : grid[0].size();

    vector<vector<bool>> flags(m,vector<bool>(n,false));
    static vector<vector<int>> dirs = {{0,-1,0,1},{1,0,-1,0},{0,-1,1,0},{1,0,0,1},{0,-1,-1,0},{-1,0,0,1}};

    int i=0,j=0;
    flags[0][0] = true;
    while(i!=m-1 || j != n-1)
    {
        i+=out_x;
        j+=out_y;

        if(i<0 || i>=m || j<0 || j >= n || flags[i][j] )
        {
            return false;
        }

        flags[i][j] = true;

        int p = grid[i][j]-1;
        if(dirs[p][0] == -out_x && dirs[p][1] == -out_y)
        {
            out_x = dirs[p][2];
            out_y = dirs[p][3];
        }
        else if(dirs[p][2] == -out_x && dirs[p][3] == -out_y)
        {
            out_x = dirs[p][0];
            out_y = dirs[p][1];
        }
        else 
        {
            return false;
        }
    }

    return true;
}

bool hasValidPath(vector<vector<int>>& grid) {
    //思路：这个有点像拼图，我们直接按要求步进即可
    //注意环的存在，记录走过的路径
    //每一个街道都有一个入口，一个出口，上一个街道的出口和本当前街道得入口需要匹配，下一个街道由当前出口确定
    //而出口和入口又是相对的,这些出口入口本质都是方向,也就是两个方向

    int m = grid.size();
    int n = m==0 ? 0 : grid[0].size();
    if(m == 0 || n == 0)
    {
        return true;
    }

    static vector<vector<int>> dirs = {{0,-1,0,1},{1,0,-1,0},{0,-1,1,0},{1,0,0,1},{0,-1,-1,0},{-1,0,0,1}};

    int p = grid[0][0]-1;
    if(hasValidPath(grid,dirs[p][0],dirs[p][1]) || hasValidPath(grid,dirs[p][2],dirs[p][3]))
    {
        return true;
    }

    return false;   
}


//其它思路：类比为图，使用dfs或并查集都行，并查集是吧点放到集合中，每个点可以连接两个点，二维点可以通过(x*m+y)的方式变成一个唯一的id

int main()
{
    vector<vector<int>> grid = {{1,2,1},{1,2,1}}; //false;
    // grid = {{2,4,3},{6,5,2}}; //true
    // grid = {{1,1,1,1,1,1,3}}; //true
    printf(hasValidPath(grid) ? "true\n" : "false\n");
    return 0;
}