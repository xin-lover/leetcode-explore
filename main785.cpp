// leetcode  785. 判断二分图

#include <cstdio>
#include <vector>
#include <queue>
#include <set>

using namespace std;

//超时
bool isBipartite(vector<vector<int>>& graph,int index,vector<int>& flags,int group)
{
    for(auto a : flags)
    {
        printf("%d ",a);
    }
    printf("\n");
    if(flags[index] == 1-group)
    {
        return false;
    }

    for(auto a : graph[index])
    {
        if(flags[a] == group)
        {
            return false;
        }
    }
    
    flags[index] = group;
    for(auto a : graph[index])
    {
        flags[a] = 1 - group;
    }

    ++index;
    if(index < graph.size())
    {
        if(flags[index] == -1)
        {
            vector<int> tmp = flags;
            if(isBipartite(graph,index,flags,0))
            {
                return true;
            }

            swap(flags,tmp);
            if(isBipartite(graph,index,flags,1))
            {
                return true;
            }

            return false;
        }
        else
        {
            if(isBipartite(graph,index,flags,flags[index]))
            {
                return true;
            }

            return false;
        }
    }

    return true;
}

bool isBipartite(vector<vector<int>>& graph) {
    //思路：二分的话，同一集合的点不能相连；
    //每个节点要就属于A，要就属于B
    //图是以邻接表给出的，所以这个点和与其相连的点属于两个集合
    //所以策略就是遍历图，每次为点标注其所属集合，每次标注有两种选择，使用回溯法

    // if(graph.empty())
    // {
    //     return true;
    // }
    // vector<int> flags(graph.size(),-1);
    // return isBipartite(graph,0,flags,0);

    //回溯超时，那我们就不回溯，因为后面的分组可以通过前面的分组确定，所以可以提前剪枝，先把0节点和其邻接节点分组，然后这些邻接节点中再重复这个过程即可
    //处理孤立的点或子图
    //时间还是一般
    queue<int> qu;
    // vector<int> visited(graph.size(),false);//优化，比使用set快
    vector<int> flags(graph.size(),-1);
    for(int i=0;i<graph.size();++i)
    {
        if(flags[i] == -1)
        {
            flags[i] = 0;
            qu.push(i);
            while(!qu.empty())
            {
                int t = qu.front();
                qu.pop();
                // visited[t] = true;

                for(auto a : graph[t])
                {
                    if(flags[a] == flags[t])
                    {
                        return false;
                    }

                    if(flags[a] == -1)
                    {
                        qu.push(a);
                    }
                    flags[a] = 1 - flags[t];
                }
            }
        }
    }


    return true;
}

int main()
{
    vector<vector<int>> v = {{1,3}, {0,2}, {1,3}, {0,2}};
    // v = {{1,2,3}, {0,2}, {0,1,3}, {0,2}};

    printf(isBipartite(v) ? "true\n" : "false\n");
    return 0;
}
