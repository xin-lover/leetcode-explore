//leetcode 959. 由斜杠划分区域

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

void dfs(vector<string>& grid, vector<vector<vector<int>>>& graph,int x,int y,int z)
{
    int n = graph.size();
    if(x < 0 || x >= n || y < 0 || y>=n)
    {
        return;
    }

    if(graph[x][y][z] == 0)
    {
        return;
    }

    graph[x][y][z] = 0;
    if(grid[x][y] == '/')
    {
        if(z == 0)
        {
            graph[x][y][1] = 0;
            dfs(grid,graph,x-1,y,3);
            dfs(grid,graph,x,y-1,2);
        }
        else if(z == 1)
        {
            graph[x][y][0] = 0;
            dfs(grid,graph,x,y-1,2);         
            dfs(grid,graph,x-1,y,3);         
        }
        else if(z == 2)
        {
            graph[x][y][3] = 0;
            dfs(grid,graph,x+1,y,1);
            dfs(grid,graph,x,y+1,0);
        }
        else
        {
            graph[x][y][2] = 0;
            dfs(grid,graph,x,y+1,0);
            dfs(grid,graph,x+1,y,1);
        }
    }
    else if(grid[x][y] == '\\')
    {
        if(z == 0)
        {
            graph[x][y][3] = 0;
            dfs(grid,graph,x+1,y,1);
            dfs(grid,graph,x,y-1,2);
        }
        else if(z == 1)
        {
            graph[x][y][2] = 0;
            dfs(grid,graph,x,y+1,0);         
            dfs(grid,graph,x-1,y,3);         
        }
        else if(z == 2)
        {
            graph[x][y][1] = 0;
            dfs(grid,graph,x-1,y,3);
            dfs(grid,graph,x,y+1,0);
        }
        else
        {
            graph[x][y][0] = 0;
            dfs(grid,graph,x,y-1,2);
            dfs(grid,graph,x+1,y,1);
        }
    }
    else
    {
        graph[x][y][0]=0;
        graph[x][y][1]=0;
        graph[x][y][2]=0;
        graph[x][y][3]=0;

        dfs(grid,graph,x-1,y,3);
        dfs(grid,graph,x+1,y,1);
        dfs(grid,graph,x,y-1,2);
        dfs(grid,graph,x,y+1,0);
    }
}

int regionsBySlashes(vector<string>& grid) {
    //思路：斜杆和反斜杆都是把原来的小方块切分为两块，而需要处理的情况就是两个区域可以合并
    //所以问题是如何处理合并？合并最快的方式就是并查集，那这里就演变为如何定义点了
    //这里的点就是一个区域，因为有两种斜杆，所以把正方形分为4分，每一份一个点，然后把这些点连接起来，也就是合并
    //问题是4个点如何表示？如何定义可合并条件？
    //最左侧三角为0，顺时针编号，则我们可能遇到的合并情况是（3，0），（0，1），（0，2），（2，1），

    //这里没有用到并查集，直接是dfs
    int res = 0;
    int n = grid.size();
    vector<vector<vector<int>>> graph(n,vector<vector<int>>(n,vector<int>(4,-1)));
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            for(int k=0;k<4;++k)
            {
                if(graph[i][j][k] == -1)
                {
                    ++res;
                    printf("i:%d j:%d k:%d\n",i,j,k);
                    dfs(grid,graph,i,j,k);
                }
            }
        }
    }

    return res;
}

class disjoinSet
{
public:
    vector<int> ay_;
    disjoinSet(int n):ay_(n)
    {
        for(int i=0;i<n;++i)
        {
            ay_[i]=i;
        }
    }

    int find(int x)
    {
        if(ay_[x] != x) ay_[x] = find(ay_[x]);
        return ay_[x];
    }

    void union2(int x,int y)
    {
        ay_[find(x)]=find(y);
    }
};

int regionsBySlashes2(vector<string>& grid) {
    //思路：并查集思路，把正方形分成4个三角形，然后把相邻的三角形相连，正方形内的三角形相连根据斜杆来

    int n = grid.size();
    disjoinSet ds(4*n*n);
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            int root = (i*n+j)*4;
            if(grid[i][j] != '\\')  //注意是！=
            {
                ds.union2(root+0,root+1);
                ds.union2(root+2,root+3);
            }
            if(grid[i][j] != '/')
            {
                ds.union2(root+0,root+3);
                ds.union2(root+1,root+2);
            }

            if(i+1<n)
            {
                ds.union2(root+3,(root+4*n)+1);
            }
            if(i-1>=0)
            {
                ds.union2(root+1,(root-4*n)+3);
            }
            if(j+1<n)
            {
                ds.union2(root+2,(root+4)+0);
            }
            if(j-1>=0)
            {
                ds.union2(root+0,(root-4)+2);
            }
        }
    }
    int res =0;
    for(int i=0;i<4*n*n;++i)
    {
        if(ds.find(i)==i)
        {
            ++res;
        }
    }

    return res;
}

int main()
{
    vector<string> s = {" \\","/ "};//2
    s = {" /","  "};//1
    // s ={"\\/","/\\"};//4
    // s={"/\\","\\/"};//5
    printf("%d\n",regionsBySlashes(s));
    return 0;
}