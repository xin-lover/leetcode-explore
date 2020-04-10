//1222. 可以攻击国王的皇后

#include <cstdio>
#include <vector>

using namespace std;

vector<vector<int>> queensAttacktheKing(vector<vector<int>>& queens, vector<int>& king) {
    //思路：不能越子行棋，那就意味着只能离国王最近棋子攻击，这样的棋子最多8个
    //也就是8个方向

    vector<vector<int>> grid(8,vector<int>(8,false));
    for(int i=0;i<queens.size();++i)
    {
        int x = queens[i][0];
        int y = queens[i][1];
        grid[x][y] = true;
    }

    for(auto a : grid)
    {
        for(auto b : a)
        {
            printf("%d ",b);
        }
        printf("\n");
    }

    vector<vector<int>> res;
    vector<vector<int>> dirs = {{-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1}};

    //一个方向一个方向查看
    for(int i=0;i<dirs.size();++i)
    {
        int dx = dirs[i][0];
        int dy = dirs[i][1];

        for(int j=1;j<8;++j)
        {
            int x = king[0] + dx * j;
            int y = king[1] + dy * j;
            printf("x:%d y:%d\n",x,y);
            if(x <0 || x >= 8 || y < 0 || y >= 8)
            {
                break;
            }
            if(grid[x][y])
            {
                res.push_back({x,y});
                break;
            }
            
        }
    }

    return res;
}

int main()
{
    vector<vector<int>> queens = {{0,1},{1,0},{4,0},{0,4},{3,3},{2,4}};
    vector<int> king = {0,0}; //[[0,1],[1,0],[3,3]]

    queens = {{0,0},{1,1},{2,2},{3,4},{3,5},{4,4},{4,5}};
    king = {3,3};//[[2,2],[3,4],[4,4]]

    queens = {{5,6},{7,7},{2,1},{0,7},{1,6},{5,1},{3,7},{0,3},{4,0},{1,2},{6,3},{5,0},{0,4},{2,2},{1,1},{6,4},{5,4},{0,0},{2,6},{4,5},{5,2},{1,4},{7,5},{2,3},{0,5},{4,2},{1,0},{2,7},{0,1},{4,6},{6,1},{0,6},{4,3},{1,7}};
    king = {3,4};   //[[2,3],[1,4],[1,6],[3,7],[4,3],[5,4],[4,5]]

    queens = {{0,1},{6,4},{4,7},{0,0},{3,3},{7,7},{2,1},{1,6},{0,4},{4,3},{2,4},{3,7},{3,4},{1,1}};
    king = {7,2};

    queens = {{4,7},{7,7},{0,7},{5,1},{0,3},{4,0},{6,7},{2,2},{0,4},{6,4},{6,5},{3,5},{4,6},{6,1},{3,1},{0,6},{2,0},{4,3},{1,7},{5,2}};
    king = {2,4};   //[[0,4],[0,6],[2,2],[5,1],[6,4],[3,5]]

    queens = {{7,3},{4,7},{1,3},{3,0},{6,2},{1,6},{5,1},{3,7},{7,2},{4,0},{3,3},{5,5},{4,4},{6,3},{1,5},{4,1},{1,1},{6,4},{2,6},{0,0},{7,1},{4,5},{6,0},{7,5},{0,5},{6,5},{3,5},{2,7},{0,1},{5,3},{7,0},{4,6},{5,7},{7,4},{0,6},{2,0},{4,3},{3,4}};
    king = {0,2};


    auto dd = queensAttacktheKing(queens,king);
    for(auto a : dd)
    {
        printf("{");
        for(auto b : a)
        {
            printf("%d,",b);
        }
        printf("},");
    }
    printf("\n");

    return 0;
}