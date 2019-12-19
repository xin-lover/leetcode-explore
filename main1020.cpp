//1020. 飞地的数量

#include <cstdio>
#include <vector>

using namespace std;

void dfs(vector<vector<int>>& A,int row,int col)
{
    int m = A.size();
    int n = A[0].size();
    
    if(row < 0 || row >= m || col < 0 || col >= n)
    {
        return;
    }

    if(A[row][col]==1)
    {
        A[row][col] = 2;
        dfs(A,row+1,col);
        dfs(A,row-1,col);
        dfs(A,row,col+1);
        dfs(A,row,col-1);
    }
}

int numEnclaves(vector<vector<int>>& A) {
    //思路：dfs即可

    if(A.empty() || A[0].empty())
    {
        return 0;
    }

    for(int i=0;i<A.size();++i)
    {
        dfs(A,i,0);
        dfs(A,i,A[i].size()-1);        
    }

    for(int i=1;i<A[0].size()-1;++i)
    {
        dfs(A,0,i);
        dfs(A,A.size()-1,i);
    }

    int res= 0;
    for(int i=0;i<A.size();++i)
    {
        for(int j=0;j<A[i].size();++j)
        {
            if(A[i][j] == 1)
            {
                ++res;
            }
        }
    }

    return res;
}

int main()
{
    vector<vector<int>> v =
    {
        {0,0,0,0},
        {1,0,1,0},
        {0,1,1,0},
        {0,0,0,0}
    }; //3

    v = 
    {
        {0,0,0,1,1,1,0,1,0,0},
        {1,1,0,0,0,1,0,1,1,1},
        {0,0,0,1,1,1,0,1,0,0},
        {0,1,1,0,0,0,1,0,1,0},
        {0,1,1,1,1,1,0,0,1,0},
        {0,0,1,0,1,1,1,1,0,1},
        {0,1,1,0,0,0,1,1,1,1},
        {0,0,1,0,0,1,0,1,0,1},
        {1,0,1,0,1,1,0,0,0,0},
        {0,0,0,0,1,1,0,0,0,1}
        };//3

    v = {
        {1,0,1,0,0},
        {0,1,0,1,0},
        {1,0,0,1,0},
        {1,1,1,0,1},
        {0,1,1,1,1}
    };

    printf("%d\n",numEnclaves(v));
    return 0;

}