//1129. 颜色交替的最短路径

#include <cstdio>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

void dfs(int n,unordered_map<int,vector<int>>& first,unordered_map<int,vector<int>>& second,vector<int>& res)
{
    queue<int> flags;
    flags.push(0);

    vector<bool> group_first(n,false);
    vector<bool> group_second(n,false);
    group_first[0] = true;
    unordered_map<int,vector<int>> *cur = &first;
    vector<bool> *curGroup = &group_second;
    int step = 0;
    while(!flags.empty())
    {
        int sz = flags.size();
        for(int i=0;i<sz;++i)
        {
            int p = flags.front();
            flags.pop();

            res[p] = min(res[p],step);

            for(int j=0;j<(*cur)[p].size();++j)
            {
                int q = (*cur)[p][j];
                if(!(*curGroup)[q]) //避免环出现,环是同一个数组的同一个位置
                {
                    flags.push(q);
                    (*curGroup)[q] = true;
                }
            }
        }
        
        cur = (cur == &first ? &second: &first);
        curGroup = (curGroup == &group_first ? &group_second : &group_first);
        ++step;
    }
}

vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& red_edges, vector<vector<int>>& blue_edges) {
    //思路：图的问题，首先要处理好数据存储，另外一个问题就是遍历
    //对于这个题，我们使用map存储（也可以使用二维数组），然后使用dfs遍历
    //主要是处理两个集合切换
    
    //不实用指针，使用递归的方式代码更简洁，也就是传递参数的时候交换一下位置。。。。

    unordered_map<int,vector<int>> um_red,um_blue;
    for(int i=0;i<red_edges.size();++i)
    {
        um_red[red_edges[i][0]].push_back(red_edges[i][1]);
    }

    for(int i=0;i<blue_edges.size();++i)
    {
        um_blue[blue_edges[i][0]].push_back(blue_edges[i][1]);
    }

    vector<int> res(n,INT_MAX);
    //先从红边开始
    dfs(n,um_red,um_blue,res);
    //先从边开始
    dfs(n,um_blue,um_red,res);
    for(int i=0;i<res.size();++i)
    {
        res[i] = res[i] == INT_MAX ? -1 : res[i];
    }
    return res;
}

void dfs2(int n,unordered_map<int,vector<int>>& um,int start,vector<int>& res)
{
    vector<int> flags(2*n,false);
    queue<int> qu;
    qu.push(start);
    int step =0;
    res[0] = 0;

    while(!qu.empty())
    {
        ++step;
        int sz = qu.size();
        for(int i=0;i<sz;++i)
        {
            int p = qu.front();
            qu.pop();

            for(int j=0;j<um[p].size();++j)
            {
                int q = um[p][j];
                if(!flags[q]){
                    qu.push(q);
                    flags[q] = true;
                    res[q] = min(res[q],step);
                }
            }
        }
    }
}

vector<int> shortestAlternatingPaths2(int n, vector<vector<int>>& red_edges, vector<vector<int>>& blue_edges) {
    //思路：既然两个数组不同，那么我们把他们合为一个数组，然后dfs，就不用交替集合了

    unordered_map<int,vector<int>> um;
    for(int i=0;i<red_edges.size();++i)
    {
        um[red_edges[i][0]].push_back(red_edges[i][1] + n);
    }

    for(int i=0;i<blue_edges.size();++i)
    {
        um[blue_edges[i][0]+n].push_back(blue_edges[i][1]);
    }

    vector<int> res2(2*n,INT_MAX);
    dfs2(n,um,0,res2);
    dfs2(n,um,n,res2);

    vector<int> res(n,-1);
    for(int i=0;i<n;++i)
    {
        res[i] = min(res2[i],res2[i+n]);
        res[i] = (res[i] == INT_MAX ? -1 : res[i]);
    }

    return res;
}

int main()
{
    int n = 3;
    vector<vector<int>> red_edges = {{0,1},{1,2}}, blue_edges = {}; //0,1,-1
    red_edges = {{0,1}},blue_edges={{2,1}}; //0,1,-1
    red_edges = {{1,0}},blue_edges={{2,1}}; //0,-1,-1
    n = 5;
    red_edges = {{0,1},{1,2},{2,3},{3,4}}; //0,1,2,3,7
    blue_edges = {{1,2},{2,3},{3,1}};

    n = 5;
    red_edges = {{3,2},{4,1},{1,4},{2,4}};
    blue_edges = {{2,3},{0,4},{4,3},{4,4},{4,0},{1,0}}; //0 2 -1 -1 1 

    n = 5;
    red_edges ={{2,2},{0,4},{4,2},{4,3},{2,4},{0,0},{0,1},{2,3},{1,3}};//[0,1,2,2,1]
    blue_edges = {{0,4},{1,0},{1,4},{0,0},{4,0}};
    // red_edges={{0,0},{0,4}};
    // blue_edges = {{0,4},{0,0},{4,0}};
    vector<int> res = shortestAlternatingPaths2(n,red_edges,blue_edges);
    for(auto a : res)
    {
        printf("%d ",a);
    }
    printf("\n");
    return 0;
}