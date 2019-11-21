//leetcode 957. N 天后的牢房

#include <cstdio>
#include <vector>
#include <unordered_map>

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
    //思路：对上面思路的优化，观察可以发现，第i个位置取决于上一行的第i-1和i+1位置
    //在往上推是取决于i-2，2*（i），i+2，往后递推会有（1，1），（1，2，1），（1，3，3，1），（1，4，6，4，1）
    //如果只有8列，那么只能到(1,3,3,1)这一层，我们考察（1，2，1）这一层，对于2个相同的数对结果没有影响（除非只有两个数），
    //计算公式，可以发现A(i,0)=0,A(i,1)=1-A(i-1,2),A(i,2) = 1-A(i-2,4),一次类推
    //再代入求解，可得转换公式A(i,0)=0,A(i,1)=A(i-3,4),A(i,2)=A(i-6,6),A(i,3)=A(i-5,2),A(i,4)=A(i-5,5),A(i,5)=A(i-6,1)
    //A(i,6)=A(i-3,3),A(i,7)=0

    //这样周期性就有了，对于A(i,1),可发现等于A(i-3-5-6,1),也就是周期是14
    //计算后发现所有周期都为14

    if(N == 0)
    {
        return cells;
    }

    int n = cells.size();
    vector<int> tmp(n,0);
    for(int i=1;i<n-1;++i)
    {
        tmp[i] = 1 - ((cells[i-1] + cells[i+1]) & 1);
    }

    if(N == 1)
    {
        return tmp;
    }

    N-=1;
    //cycle 14
    int cycle = 14;
    N%=cycle;

    //还可优化，少做几次，使用1，2，1的特性，可以使次数/2
    vector<int> res = tmp;
    for(int i=0;i<N;++i)
    {
        for(int j=1;j<n-1;++j)
        {
            tmp[j] = 1 - ((res[j-1] + res[j+1]) & 1);
        }
        swap(tmp,res); 
    }

    return res;
}

int state(const vector<int>& cells)
{
    int s = 0;
    for(auto x : cells)
    {
        s <<= 1;
        s |= x;
    }

    return s;
}

void next(vector<int>& cells)
{
    for(int i=1;i<cells.size()-1;++i)
    {
        cells[i] |=(1-((cells[i-1]&1) ^ (cells[i+1]&1))) << 1; //相当于把结果存到第二位，
    }

    cells[0]=0;
    cells.back()=0;
    for(int i=1;i<cells.size()-1;++i)
    {
        cells[i] >>= 1; //把结果取出来
    }
}

vector<int> prisonAfterNDays3(vector<int>& cells,int N)
{
    //还是利用周期性，8个数字，最多256种组合，但因为两侧都为0，所以周期不一定是256，直接存储每一种转换结果，求周期
    unordered_map<int,int> um;

    int s = state(cells);
    um[s] = 0;
    while(N > 0)
    {
        --N;
        next(cells);
        s = state(cells);
        if(um.count(s))
        {
            break;
        }
        else
        {
            um[s] = um.size();
        }
        
    }

    int loop = um.size() - um[s];
    N %= loop;
    while(N > 0)
    {
        next(cells);
        --N;
    }

    return cells;
}

int main()
{
    vector<int> cells = {0,1,0,1,1,0,0,1};
    int N = 7;  //0 0 1 1 0 0 0 0
    cells = {1,0,0,1,0,0,1,0};
    N = 1000000000;
    vector<int> res = prisonAfterNDays3(cells,N);
    for(auto a : res)
    {
        printf("%d ",a);
    }
    printf("\n");
    return 0;
}