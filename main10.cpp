#include <cstdio>
#include <vector>

using namespace std;

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        
        //思路：dfs
        if(obstacleGrid.empty() || obstacleGrid[0].empty())
        {
            return 0;
        }
        int res = 0;
        dfs(obstacleGrid,0,0,res);
        return res;
    }
    
    void dfs(vector<vector<int>>& obstacleGrid,int x,int y,int& res)
    {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        
        if(x == m-1 && y == n-1)
        {
            ++res;
            printf("get:%d\n",res);
            // ++res;
            return;
        }
        
        if(x > m-1 || y > n-1)
        {
            return;
        }
        
        if(obstacleGrid[x][y] == 1)
        {
            return;
        }
        
        dfs(obstacleGrid,x+1,y,res);
        dfs(obstacleGrid,x,y+1,res);
    }
};

int main()
{
    Solution s;
    vector<vector<int>> obstacle={
        {0,0,0},
        {0,1,0},
        {0,0,0}
    };
    int res = 0;
    res = s.uniquePathsWithObstacles(obstacle);
    printf("res:%d\n",res);
    return 0;
}