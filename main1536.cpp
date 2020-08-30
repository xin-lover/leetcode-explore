//1536. 排布二进制网格的最少交换次数

#include <cstdio>
#include <vector>

using namespace std;

int minSwaps(vector<vector<int>>& grid) {
    //思路：只能交换两个相邻的两行
    //主对角线以上，也就是右上部分，快速计算连续0，可以使用前缀和
    //整体是用贪心策略，从第一行开始，如果当前行满足要求就不交换，否则往下寻找，直到寻找到
    //这里要避免移动数组，假设j>i,把第j行交换到第i行时，j到i之间的行都下移了一行，所以我们记录下移信息即可

    int rows = grid.size();
    int cols = rows == 0 ? 0 : grid[0].size();
    int res = 0;
    //前缀和处理
    for(int i=0;i<rows;++i)
    {
        for(int j=1;j<cols;++j)
        {
            grid[i][j] = grid[i][j-1] + grid[i][j];
        }
    }

    vector<int> downs(rows,0);
    for(int i=0;i<rows;++i)
    {
        int j;
        for(j=0;j<rows;++j)
        {
            if(j+downs[j] >= i)
            {
                if(grid[j][cols-1] - grid[j][i] == 0)
                {
                    res += j+downs[j]-i;
                    downs[j] = i-j;
                    break;
                }

                downs[j]++;
            }
            
        }
        if(j == rows)
        {
            return -1;
        }
    }

    return res;
}

int main()
{   
    vector<vector<int>> grid = {{0,0,1},{1,1,0},{1,0,0}}; //3
    grid = {{0,1,1,0},{0,1,1,0},{0,1,1,0},{0,1,1,0}}; //-1
    // grid = {{1,0,0},{1,1,0},{1,1,1}}; //0
    // grid = {{1,0,0,0},{1,1,1,1},{1,0,0,0},{1,0,0,0}};   //2
    printf("%d\n",minSwaps(grid));

    return 0;
}