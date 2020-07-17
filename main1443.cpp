//1443. 收集树上所有苹果的最少时间

#include <cstdio>
#include <vector>

using namespace std;

bool traverse(vector<vector<int>>& graphic,vector<bool>& hasApple,int node,int parent,int& cost)
{
    bool have = false;
    printf("i:%d sz:%d\n",node,graphic[node].size());
    for(int i=0;i<graphic[node].size();++i)
    {
        if(graphic[node][i] == parent)
        {
            continue;
        }
        bool r = traverse(graphic,hasApple,graphic[node][i],node,cost);
        if(r)
        {
            cost+=2;
        }

        have |= r;
    }

    return have | hasApple[node];
}

int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) {
    //思路：这个用图的方式遍历即可，使用深度广度遍历都可以
    //对于一个节点，如果孩子节点有苹果，则一来一回，花费+2
    //而对于这个节点，如果以这个节点为根的子树有苹果，则它有苹果
    //使用递归
    //问题是无向边。。。如何避免循环,用一个visted的记录

    vector<vector<int>> graphic(n);
    for(auto a : edges)
    {
        graphic[a[0]].push_back(a[1]);
        graphic[a[1]].push_back(a[0]);
    }

    int cost = 0;
    traverse(graphic,hasApple,0,-1,cost);
    return cost;

}

int main()
{
    int n = 7;
    vector<vector<int>> edges = {{0,1},{0,2},{1,4},{1,5},{2,3},{2,6}};
    vector<bool> hasApple = {false,false,true,false,true,true,false}; //8

    n = 7, edges = {{0,1},{0,2},{1,4},{1,5},{2,3},{2,6}}, hasApple = {false,false,true,false,false,true,false}; //6

    printf("%d\n",minTime(n,edges,hasApple));

    return 0;
}