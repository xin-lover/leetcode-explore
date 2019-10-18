//leetcode 934. 最短的桥

#include <cstdio>
#include <vector>

using namespace std;

// [
    // [1,1,1,1,1],
    // [1,0,0,0,1],
    // [1,0,1,0,1],
    // [1,0,0,0,1],
    // [1,1,1,1,1]]

void dps2(vector<vector<int>>& A,int x,int y){
    if(x < 0 || x >= A.size() || y <0 || y >= A[x].size())
    {
        return;
    }

    if(A[x][y] == 1)
    {
        A[x][y] = 2;
        dps2(A,x+1,y);
        dps2(A,x-1,y);
        dps2(A,x,y+1);
        dps2(A,x,y-1);
    }
}


int shortestBridge(vector<vector<int>>& A) {
    //思路：首先区分两座岛，然后对其中一个岛的所有点到另一个岛的距离求最小值
    //方案：首先标记一个岛为2，然后按步数遍历，即首先遍历一步能到达2号岛的点为-1，然后再标记到达-1点的点为-2直到能到达1点

    if(A.empty() || A[0].empty())
    {
        return 0;
    }

    for(int i=0;i<A.size();++i)
    {
        for(int j=0;j<A[i].size();++j)
        {
            if(A[i][j] == 1)
            {
                dps2(A,i,j);
                i = A.size();
                break;
            }
        }
    }

    for(int i=0;i<A.size();++i)
    {
        for(int j=0;j<A[0].size();++j)
        {
            printf("%d ",A[i][j]);
        }
        printf("\n");
    }

    int len = A.size() + A[0].size();
    int num = 2;
    vector<vector<int>> dirs = {{-1,0},{0,1},{1,0},{0,-1}};
    for(int k=1;k<len;++k)
    {
        for(int i=0;i<A.size();++i)
        {
            for(int j=0;j<A.size();++j)
            {
                if(A[i][j] == num)
                {
                    for(int p=0;p<dirs.size();++p)
                    {
                        int x = i + dirs[p][0];
                        int y = j + dirs[p][1];
                        if(x <0 || x>=A.size() || y <0 || y >= A[i].size())
                        {
                            continue;
                        }

                        if(A[x][y] == 1)
                        {
                            return k-1;
                        }
                        if(A[x][y] == 0)
                        {
                            A[x][y] = -k;
                        }
                    }
                }
            }
        }

        num = -k;
    }

    printf("------------\n\n");
    for(int i=0;i<A.size();++i)
    {
        for(int j=0;j<A[0].size();++j)
        {
            printf("%d ",A[i][j]);
        }
        printf("\n");
    }
    
    return len;
}

int main()
{
    vector<vector<int>> v = {{0,1},{1,0}};//1
    v = {{0,1,0},{0,0,0},{0,0,1}};//2
    v = {{1,1,1,1,1},{1,0,0,0,1},{1,0,1,0,1},{1,0,0,0,1},{1,1,1,1,1}};//1
    printf("%d\n",shortestBridge(v));
    return 0;
}
