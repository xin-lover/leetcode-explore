//leetcode 957. N 天后的牢房

#include <cstdio>
#include <vector>

using namespace std;

vector<int> prisonAfterNDays(vector<int>& cells, int N) {
    //思路：暴力解法简单，优化一下试试
    //不能使用if判断，方案：可以发现两侧的和为0或2，自己才能为1，某则为0，所以直接使用位运算
    //N可能很大，放弃

    if(cells.empty())
    {
        return vector<int>();
    }

    vector<int> res = cells;
    if(N == 0)
    {
        return cells;
    }

    int n = cells.size();
    vector<int> tmp(n);
    for(int i=1;i<n-1;++i)
    {
        tmp[i] = 1 - ((res[i-1] + res[i+1]) & 1);
    }

    tmp[0] = 0;
    tmp[n-1] = 0;
    swap(tmp,res);
    tmp[0]=0;
    tmp[n-1]=0;
    if(n > 2)
    {
        for(int j=2;j<=N;++j)
        {
            for(int i=1;i<n-1;++i)
            {
                tmp[i] = 1 - ((res[i-1] + res[i+1]) & 1);
            }
            swap(tmp,res);
        }
    }

    return res;
}

vector<int> prisonAfterNDays2(vector<int>& cells, int N) {
    //思路：
}

int main()
{
    vector<int> cells = {0,1,0,1,1,0,0,1};
    int N = 7;  //0 0 1 1 0 0 0 0
    N = 10;
    // cells = {1,0,0,1,0,0,1,0};
    // N = 1000000000;
    vector<int> res = prisonAfterNDays(cells,N);
    for(auto a : res)
    {
        printf("%d ",a);
    }
    printf("\n");
    return 0;
}