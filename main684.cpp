//leetcode 684. 冗余连接

#include <cstdio>
#include <vector>
#include <unordered_map>
#include <set>
#include <stack>
#include <queue>

using namespace std;

vector<int> findRedundantConnection_111(vector<vector<int>>& edges) {


    //思路：关键在于如何判断环的存在，
    //根据题意可知，如果把[u,v]表示v的一个入度，一个节点的入度为2时可能成环，这个时候把另外的两个节点看乘两颗子树的话
    //只要子树中有两个节点相连就可以成环
    //所以策略就是：
    //遍历的同时，存储节点的临接节点，同时计算节点入度，如果为2，则记录另外两个节点为子树
    //对于新的边，判断是否把两个子树相连


    unordered_map<int,vector<int>> um;
    unordered_map<int,int> em;
    set<vector<int>> possibleEdges;

    vector<int> res;
    for(auto v : edges)
    {
        um[v[0]].push_back(v[1]);
        um[v[1]].push_back(v[0]); 
    }

    // vector<int> res(2);
    for(auto v : edges)
    {
        if(possibleEdges.find(v) != possibleEdges.end())
        {
            return v;
        }
        
        if(em.find(v[1]) == em.end())
        {
            em[v[1]] = v[0];
        }
        else
        {
            //
             //只记录了[4,2],没记录[2,4],所以对于[2,5],[3,5],[2,4],[3,4]的情况没法辨别
             //改为记录两个方向

            //v[1]点可能成环,使用dfs
            // stack<int> sk;
            // sk.push(v[1]);
            // printf("v[1]:%d\n",v[1]);
            // set<int> visited;
            // while(!sk.empty())
            // {
            //     int t = sk.top();
            //     sk.pop();
            //     visited.insert(t);

            //     for(auto it = um[t].begin();it!=um[t].end();++it)
            //     {
            //         if(*it == v[1] && t != v[1])
            //         {
            //             res = v;
            //         }

            //         if(visited.find(*it) == visited.end())
            //         {
            //             sk.push(*it);
            //         }
            //     }
            // }

            //记录可能成环的边
            vector<int> nodes1;
            set<int> visited;
            for(auto it = um[v[0]].begin();it!=um[v[0]].end();++it)
            {

            }
        }
    }

    return res;
    // return {};

    //思路：构造
}

// //查找val是否在树中
// bool find(unordered_map<int,set<int>>& tree,int root,int val)
// {
//     if(tree[root].find(val) == tree[root].end())
//     {
//         for(auto it = tree[root].begin();it!=tree[root].end();++it)
//         {
//             if(find(tree,*it,val))
//             {
//                 return true;
//             }
//         }

//         return false;
//     }
//     else
//     {
//         return true;
//     }
    
// }

vector<int> findRedundantConnection(vector<vector<int>>& edges) {

    //思路：每新加入一条边，更新每一个节点能到达的节点，如果该节点已经能到达，说明存在环
    //不能只更新两个点，需要更新的是两条路径，比如[1,2],[3,4],[1,3]，对于[1,3]不能只更新1和3的连接点，需要更新的是[1,2],[3,4]两条路径
    //这样其实就是不断的更新图，复杂度高

    //使用不相交集
    int n = edges.size();
    vector<int> flags(n+1,0);
    for(int i=0;i<n+1;++i)
    {
        flags[i] = i;
    }

    for(auto v : edges)
    {
        // for(int i=1;i<=n;++i)
        // {
        //     printf("%d ",flags[i]);
        // }
        // printf("\n");
        //在同一集合，说明成环
        if(flags[v[0]] == flags[v[1]])
        {
            return v;
        }
        else
        {
            //合并两个集合,优化，把根合并，就不用遍历了
            int f = flags[v[1]];
            for(int i=1;i<=n;++i)
            {
                if(flags[i] == f)
                {
                    flags[i] = flags[v[0]];   
                }
            }
        }
    }

    return {};
}


vector<int> findRedundantConnection2(vector<vector<int>>& edges) {

    //思路：每新加入一条边，更新每一个节点能到达的节点，如果该节点已经能到达，说明存在环
    //不能只更新两个点，需要更新的是两条路径，比如[1,2],[3,4],[1,3]，对于[1,3]不能只更新1和3的连接点，需要更新的是[1,2],[3,4]两条路径
    //这样其实就是不断的更新图，复杂度高

    //使用不相交集
    int n = edges.size();
    vector<int> flags(n+1,0);
    for(int i=0;i<n+1;++i)
    {
        flags[i] = -1;
    }

    for(auto v : edges)
    {
        for(int i=1;i<=n;++i)
        {
            printf("%d ",flags[i]);
        }
        printf("\n");
        int r1 = v[0];
        while(flags[r1] != -1)
        {
            r1 =flags[r1];
        }
        int r2 = v[1];
        while(flags[r2] != -1)
        {
            r2 = flags[r2];
        }
        if(r1 == r2)
        {
            return v;
        }
        else
        {
            //合并两个集合,优化，把根合并，就不用遍历了
            flags[r2] = r1;
        }
    }

    return {};
}

int main()
{
    vector<vector<int>> v = {{1,2},{1,3},{2,3}};
    v = {{1,2}, {2,3}, {3,4}, {1,4}, {1,5}};
    v = {{1,4},{3,4},{1,3},{1,2},{4,5}};
    v = {{3,4},{1,2},{2,4},{3,5},{2,5}};
    // v = {{1,3},{1,2},{2,5},{3,4},{2,4}};
    v = {{3,7},{1,4},{2,8},{1,6},{7,9},{6,10},{1,7},{2,3},{8,9},{5,9}};
    // v = {{3,7},{2,8},{7,9},{1,7},{2,3},{8,9},{5,9}};
    // sort(v.begin(),v.end());
    for(auto a : findRedundantConnection2(v))
    {
        printf("%d ",a);
    }
    printf("\n");
    return 0;
}