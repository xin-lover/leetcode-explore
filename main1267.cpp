//1267. 统计参与通信的服务器

#include <cstdio>
#include <vector>

using namespace std;

int countServers(vector<vector<int>>& grid) {
    //思路：一个点一个点的遍历没有问题，就是重复遍历的有点多
    //可以按行和按列遍历两次，只要同一行或列的数据超过1个，那么他们都是符合要求的
    //但因为行和列在某点可能重复，可以使用一个额外的空间来标记

    int m = grid.size();
    int n = m == 0 ? 0 : grid[0].size();

    vector<vector<bool>> flags(m,vector<bool>(n,false));

    for(int i=0;i<m;++i)
    {
        int t = 0;
        for(int j=0;j<n;++j)
        {
            t += grid[i][j];
        }
        if(t > 1)
        {
            for(int j=0;j<n;++j)
            {
                flags[i][j] = grid[i][j]==1;
                printf("row i:%d j:%d\n",i,j);
            }
        }
    }

    for(int i=0;i<n;++i)
    {
        int t = 0;
        for(int j=0;j<m;++j)
        {
            t+= grid[j][i];
        }

        if(t > 1)
        {
            for(int j=0;j<m;++j)
            {
                flags[j][i] = grid[j][i] == 1;
                printf("col i:%d j:%d\n",j,i);
            }
        }
    }

    int res =0;
    for(int i=0;i<m;++i)
    {
        for(int j=0;j<n;++j)
        {
            res += flags[i][j] ? 1 : 0;
        }
    }

    return res;
}

int countServers2(vector<vector<int>>& grid) {
    //思路：另一个思路，使用行首列首标记，问题在于处理行首和列首以及每一行和每一列的1的数量大于2才计数的问题
    //所以我们还是标记，免的重复计算，使用原地标记,使用位思想，加2,也就是使用第二位

    //不行，行首列首不单独处理，没法搞，借鉴这种做法，可以用两个单独的数组记录行首列首情况

    // for(int i=1;i<grid.size();++i)
    // {
    //     for(int j=1;j<grid[i].size();++j)
    //     {
    //         if(grid[i][j] == 1)
    //         {
    //             if(grid[i][0] >= 2 || grid[0][j] >= 2)
    //             {
    //                 if(grid[i][0] == 2)
    //                 {
    //                     grid[i][0] |= 1;
    //                 }
                    
    //                 if(grid[0][j] == 2)
    //                 {
    //                     grid[0][j] |=1;
    //                 }
                    
    //                 grid[i][j] |= 2;
    //             }

    //             grid[i][0] |= 2;
    //             grid[0][j] |= 2;
    //         }
    //     }
    // }

    // int res = 0;
    // for(int i=0;i<grid.size();++i)
    // {
    //     for(int j=0;j<grid[i].size();++j)
    //     {
    //         printf("%d ",grid[i][j]);
    //         if(grid[i][j] == 3)
    //         {
    //             ++res;
    //         }
    //     }
    //     printf("\n");
    // }

    // return res;
}
int main()
{
    vector<vector<int>> grid = {{1,1,0,0},{0,0,1,0},{0,0,1,0},{0,0,0,1}}; //4
    // grid = {{1,0},{1,1}}; //3
    grid = {{1,0},{0,1}};//0
    printf("%d\n",countServers2(grid));
    return 0;
}