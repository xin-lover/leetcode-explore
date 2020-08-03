//1462. 课程安排 IV

#include <cstdio>
#include <vector>
#include <set>
#include <queue>

using namespace std;

vector<bool> checkIfPrerequisite(int n, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
    //思路：重点在于如何处理先修课程，这里面很自然的想法是树
    //树的思路就是存储每棵树的直接先修课程，那么查询的时候按树遍历即可，这个的缺点就是每次都可能要遍历整棵树
    //另一种思路就是存储每个课程的所有先修课程，因为n最大为100，所以空间需求也不大
    //方案，结合两种思路，用树的思路构建整个先修课程情况，然后遍历求每个课程的所有先修课程

    vector<vector<int>> tree(n,vector<int>());

    for(int i=0;i<prerequisites.size();++i)
    {
        tree[prerequisites[i][1]].push_back(prerequisites[i][0]);
    }

    vector<set<int>> pres(n);
    for(int i=0;i<n;++i)
    {
        queue<int> qu;
        qu.push(i);

        while(!qu.empty())
        {
            int p = qu.front();
            qu.pop();

            for(int j=0;j<tree[p].size();++j)
            {
                if(pres[i].find(tree[p][j]) == pres[i].end())
                {
                    qu.push(tree[p][j]);
                    pres[i].insert(tree[p][j]);
                }
            }
        }
    }

    for(auto a : pres)
    {
        for(auto b : a)
        {
            printf("%d ",b);
        }
        printf("\n");
    }

    vector<bool> res(queries.size(),false);
    for(int i=0;i<queries.size();++i)
    {
        int a = queries[i][0];
        int b = queries[i][1];
        if(pres[b].find(a) != pres[b].end())
        {
            res[i] = true;
        }
    }

    return res;
}

int main()
{
    int n = 2;
    vector<vector<int>> prerequisites = {{1,0}}, queries = {{0,1},{1,0}};   //false true

    n = 5, prerequisites = {{0,1},{1,2},{2,3},{3,4}}, queries = {{0,4},{4,0},{1,3},{3,0}};  //[true,false,true,false]
    n = 3, prerequisites = {{1,0},{2,0}}, queries = {{0,1},{2,0}};  //false true

    for(auto a : checkIfPrerequisite(n,prerequisites,queries))
    {
        printf(a ? "true " : "false ");
    }
    printf("\n");

    return 0;
}