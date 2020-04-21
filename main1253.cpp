//1253. 重构 2 行二进制矩阵

#include <cstdio>
#include <vector>

using namespace std;

vector<vector<int>> reconstructMatrix(int upper, int lower, vector<int>& colsum) {
    //思路：首先colsum的和应该等于upper+lower,否则是构建不了的
    //然后，如果colsum的和是2或0，结果都是确定的，所以我们只需要定和为1的时候的情况
    //如果colsum没有2的情况，那么我们的排列很简单，先排上面的，再排下面的即可
    //而对于2，我们的选择是唯一的，
    //所以方案1:遍历两遍，第一遍只处理2的情况，第二遍处理1的情况，对于1先排上面的，再排下面的

    int n = colsum.size();
    vector<vector<int>> res(2,vector<int>(n,0));

    for(int i=0;i<n;++i)
    {
        if(colsum[i] == 2)
        {
            if(upper <= 0 || lower <= 0)
            {
                return {};
            }
            --upper;
            --lower;
            res[0][i] = 1;
            res[1][i] = 1;
        }        
    }

    for(int i=0;i<n;++i)
    {
        if(colsum[i] == 1)
        {
            if(upper > 0)
            {
                --upper;
                res[0][i] = 1;
            }
            else if(lower > 0)
            {
                --lower;
                res[1][i] = 1;
            }
            else
            {
                return {};
            }
        }
    }

    if(upper + lower > 0)
    {
        return {};
    }
    return res;
}

int main()
{
    int upper = 2, lower = 1;
    vector<int> colsum = {1,1,1};   //[[1,1,0],[0,0,1]]或[[1,0,1],[0,1,0]] 或 [[0,1,1],[1,0,0]]

    upper = 2, lower = 3;
    colsum = {2,2,1,1}; //[]

    upper = 5, lower = 5;
    colsum = {2,1,2,0,1,0,1,2,0,1}; //[[1,1,1,0,1,0,0,1,0,0],[1,0,1,0,0,0,1,1,0,1]]

    upper = 4, lower = 7;
    colsum = {2,1,2,2,1,1,1};
    for(auto a : reconstructMatrix(upper,lower,colsum))
    {
        for(auto b : a)
        {
            printf("%d ",b);
        }
        printf("\n");
    }
    return 0;
}