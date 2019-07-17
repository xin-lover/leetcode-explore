#include <cstdio>
#include <vector>

using namespace std;

// int dfs(vector<vector<int>>& matrix,vector<vector<int>>& flags,int x,int y)
// {
//     printf("x:%d y:%d\n",x,y);
//     int m = matrix.size();
//     int n = m > 0 ? matrix[0].size() : 0;

//     if(x < 0 || y < 0)
//     {
//         return 1;
//     }

//     if(x >=m || y>=n)
//     {
//         return 2;
//     }

//     int g = 0;
//     if(flags[x][y] == -1)
//     {
//         printf("in\n");
//         flags[x][y] = 0;    //信息丢失，有些依赖（x,y）点的信息的位置不正确
//         if(x-1 < 0 || matrix[x][y] >= matrix[x-1][y])
//             g|=dfs(matrix,flags,x-1,y);
//         if(y-1 < 0 || matrix[x][y] >= matrix[x][y-1])    
//             g|=dfs(matrix,flags,x,y-1);
//         if(x+1 >=m || matrix[x][y] >= matrix[x+1][y])
//             g|=dfs(matrix,flags,x+1,y);
//         if(y+1 >=n || matrix[x][y] >= matrix[x][y+1])
//             g|=dfs(matrix,flags,x,y+1);
        
//         printf("g:%d\n",g);
//         flags[x][y] = g;
//     }

//     return flags[x][y];
// }

void dfs(vector<vector<int>>& matrix,vector<vector<int>>& flags,int x,int y)
{
    //从海向陆地扩张，不管水流如何走，最后都是通过矩阵边缘入海，我们反推，从海往陆地扩张
    int m = matrix.size();
    int n = m > 0 ? matrix[0].size() : 0;
    if(x > 0 && matrix[x-1][y] >= matrix[x][y] && flags[x-1][y] != flags[x][y])
    {
        flags[x-1][y] |= flags[x][y];
        dfs(matrix,flags,x-1,y);
    }

    if(y > 0 && matrix[x][y-1] >= matrix[x][y] && flags[x][y-1] != flags[x][y])
    {
        flags[x][y-1] |= flags[x][y];
        dfs(matrix,flags,x,y-1);
    }

    if(x+1 < m && matrix[x+1][y] >= matrix[x][y] && flags[x+1][y] != flags[x][y])
    {
        flags[x+1][y] |= flags[x][y];
        dfs(matrix,flags,x+1,y);
    }

    if(y+1 < n && matrix[x][y+1] >= matrix[x][y] && flags[x][y+1] != flags[x][y])
    {
        flags[x][y+1] |= flags[x][y];
        dfs(matrix,flags,x,y+1);
    }
}

vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
    //思路：往左和往上是太平洋，往下和往右是大西洋，使用dfs，同时使用一个矩阵保存中间结果

    int m = matrix.size();
    int n = m > 0 ? matrix[0].size() : 0;
    vector<vector<int>> flags(m,vector<int>(n,0));
    vector<pair<int,int>> res;
    for(int i=0;i<m;++i)
    {
        for(int j=0;j<n;++j)
        {
            if(i==0 || j==0)
            {
                flags[i][j]|=1;
            }

            if(i==m-1 || j==n-1)
            {
                flags[i][j] |=2;
            }
        }
    }
    for(int i=0;i<m;++i)
    {
        for(int j=0;j<n;++j)
        {
            if(i==0 || j == 0 || i==m-1 || j == n-1)
            {
                dfs(matrix,flags,i,j);
            }
        }
    }
    
    for(int i=0;i<m;++i)
    {
        for(int j=0;j<n;++j)
        {
            printf("%d ",flags[i][j]);
            if(flags[i][j] == 3)
            {
                res.push_back({i,j});
            }
        }
        printf("\n");
    }
    return res;
}

int main()
{
    vector<vector<int>> matrix={
        {1,2,2,3,5},
        {3,2,3,4,4},
        {2,4,5,3,1},
        {6,7,1,4,5},
        {5,1,1,2,4}
        // {10,10,10},
        // {10,1,10},
        // {10,10,10}
    };

    auto res = pacificAtlantic(matrix);
    for(auto p : res)
    {
        printf("%d %d\n",p.first,p.second);
    }

    return 0;
}