//leecode 797. 所有可能的路径

#include <cstdio>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
    //思路：已经是邻接表，直接使用深度或广度遍历即可
    //广度遍历需要存储当前所有的路径，所以这次我们使用深度遍历

    //回溯法也是不错的想法，思路是一样的

    int n = graph.size();
    // vector<bool> visited(graph.size(),false);
    vector<int> cur_path;
    vector<int> indices;
    vector<vector<int>> res;
    // int tmp = 0;
    cur_path.push_back(0);
    indices.push_back(0);
    while(!cur_path.empty())
    {
        while(graph[cur_path.back()].size() > indices.back())
        {
            int next = graph[cur_path.back()][indices.back()];
            cur_path.push_back(next);
            indices.push_back(0); 

            if(next == n-1)
            {
                res.push_back(cur_path);
                break;  //因为无环
            }
        }

        cur_path.pop_back();
        indices.pop_back();
        if(!indices.empty())
            indices.back() += 1;
    }

    return res;
}

int main()
{
    vector<vector<int>> graph = {{1,2},{3},{3},{}};
    auto res = allPathsSourceTarget(graph);

    for(auto a : res)
    {
        for(auto b : a)
        {
            printf("%d ",b);
        }
        printf("\n");
    }

    return 0;
}