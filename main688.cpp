//leetcode 688. “马”在棋盘上的概率

#include <vector>
#include <cstdio>
#include <queue>

using namespace std;

// int knightProbability(int N, int r, int c)
// {
//     int res = 0;
//     static vector<vector<int>> dirs={
//         {-2,1},
//         {-2,-1},
//         {-1,2},
//         {1,2},
//         {2,1},
//         {2,-1},
//         {-1,-2},
//         {1,-2}
//     };

//     for(int i=0;i<dirs.size();++i)
//     {
//         int nr = r + dirs[i][0];
//         int nc = c + dirs[i][1];

//         if(nr >=0 && nr < N && nc >= 0 && nc < N)
//         {
//             res+=1;
//         }
//     }

//     return res;
// }

double knightProbability(int N, int K, int r, int c) {
    //思路：概率问题，每一步有8种选择，K步就是8的k次方，留在棋盘的概率就是留在棋盘的走法占总走法的比例
    //用dfs可以得出解，但性能太低，改为直接结算每一步留在棋盘的概率，所有步的概率相乘即可
    // printf("%d %d %d %d\n",N,K,r,c);
    static vector<vector<int>> dirs={
        {-2,1},
        {-2,-1},
        {-1,2},
        {1,2},
        {2,1},
        {2,-1},
        {-1,-2},
        {1,-2}
    };

    // if(K == 0)
    // {
    //     return 1;
    // }

    // double res = 0;
    // for(int j=0;j<dirs.size();++j)
    // {
    //     int nr = r + dirs[j][0];
    //     int nc = c + dirs[j][1];
    //     if(nr >=0 && nr < N && nc >=0 && nc < N)
    //     {
    //         //分支太多，太慢了
    //         res += knightProbability(N,K-1,nr,nc);
    //     }

    // }

    // res *= 1.0 / 8.0 ;
    // return res;

    //动归，棋盘上每一个格子走一步留在棋盘中的概率是固定的
    //使用dfs，分支随着步数增加而指数增加，不合适，
    //记录每个格子走一步留在棋盘上的固定概率，否则每次都需要判断且执行除法，
    //第二个记录骑士当前在棋盘上的可能位置

    //记录步数会超过整数最大数字，改为记录概率
    vector<vector<double>> dp(N,vector<double>(N,0));
    vector<vector<double>> tdp(N,vector<double>(N,0));
    tdp[r][c] = 1;
    for(int k=0;k<K;++k)
    {
        printf("get\n");
        for(int i=0;i<N;++i)
        {
            for(int j=0;j<N;++j)
            {
                if(tdp[i][j] <= 0)
                {
                    continue;
                }

                printf("k:%d i:%d j:%d jj:%f\n",k,i,j,tdp[i][j]);
                for(int m=0;m<dirs.size();++m)
                {
                    int nr = i + dirs[m][0];
                    int nc = j + dirs[m][1];

                    if(nr >=0 && nr < N && nc >= 0 && nc < N)
                    {
                        printf("nr:%d nc:%d\n",nr,nc);
                        dp[nr][nc]+=tdp[i][j] / 8.0;
                    }
                }
            }
        }

        swap(dp,tdp);
        for(int i=0;i<dp.size();++i)
        {
            for(int j=0;j<dp[i].size();++j)
            {
                dp[i][j] = 0;
            }
        }
    }

    double res=0;
    for(int i=0;i<N;++i)
    {
        for(int j=0;j<N;++j)
        {
            printf("wy:%f\n",tdp[i][j]);
            res +=tdp[i][j];
        }
    }

    return res;


    // vector<vector<double>> dp2(N,vector<double>(N,0));
    // dp2[r][c] = 1;
    // queue<pair<int,int>> qu;
    // int step = 0;
    // while(!qu.empty() && step < K)
    // {
    //     int sz = qu.size();
    //     for(int i=0;i<sz;++i)
    //     {
    //         pair<int,int> pos = qu.front();
    //         qu.pop();
    //     }
    // }

}

int main()
{
    printf("%f\n",knightProbability(1,0,0,0));
    printf("%f\n",knightProbability(3,2,0,0));
    // printf("%f\n",knightProbability(25,100,0,0));
    return 0;
}