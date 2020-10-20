//174. 地下城游戏

#include <cstdio>
#include <vector>

using namespace std;

void dfs(vector<vector<int>>& dungeon,int x,int y,int hp, int minHP,int& resMinHP)
{
    int m = dungeon.size();
    int n = m == 0 ? 0 : dungeon[0].size();

    if(x < 0 || x >=m || y < 0 || y >= n)
    {
        return;
    } 

    hp += dungeon[x][y];
    minHP = min(hp,minHP);
    if(x == m-1 && y == n-1)
    {
        resMinHP = max(resMinHP,minHP);
    }
 
    dfs(dungeon,x+1,y,hp,minHP,resMinHP);
    dfs(dungeon,x,y+1,hp,minHP,resMinHP);
}

int calculateMinimumHP(vector<vector<int>>& dungeon) {
    //思路：用dfs或bfs

    //超时

    int res = INT_MIN;
    dfs(dungeon,0,0,0,0,res);
    return -res + 1;
}

int calculateMinimumHP2(vector<vector<int>>& dungeon) {
    //思路：根据行进路线方向，对于dungeon[i][j]只能从dungeon[i-1][j]或dungeon[i][j-1]过来
    //这样就给动归一个推导思路了
    //假设minHP[i][j]表示从{0,0}到{i,j}需要的最小生命值，HP[i][j]表示到{i,j}位置时的hp，那么
    //minHP[i][j] = max(minHP([i-1][j],HP[i-1][j]+dungeon[i][j]), min(minHP[i][j-1],HP[i][j-1]+ dungeon[i][j]))；
    //现在的问题来了，HP[i][j]如何确定,如果草率的选择让minHP[i][j]最大，那么HP[i][j]可能不是最大，导致后面可能出现更小的minHP[i][j]
    //也就是只能是局部最优，而不是全局最优
    //考虑右下到左上的思考，令dp[i][j]表示dungeon[i][j]到右下角的最小血量
    //那么dp[i][j]=max(min(dp[i+1][j],dp[i][j+1])-dungeon[i][j],1)

    int res = INT_MIN;
    
    int m = dungeon.size();
    int n = m == 0 ? 0 : dungeon[0].size();

    vector<vector<int>> minHP(m+1,vector<int>(n+1,INT_MAX));
    minHP[m][n-1] = 1;
    minHP[m-1][n] = 1;
    for(int i=m-1;i>=0;--i)
    {
        for(int j=n-1;j>=0;--j)
        {
            minHP[i][j] = max(min(minHP[i+1][j],minHP[i][j+1])-dungeon[i][j],1);
        }
    }

    return minHP[0][0];
}


int main()
{
    vector<vector<int>> dungeon = {{-2,-3,3},{-5,-10,1},{10,30,-5}}; //7

    printf("%d\n",calculateMinimumHP2(dungeon));
    return 0;
}