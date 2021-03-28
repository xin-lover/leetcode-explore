//685. 冗余连接 II

#include <cstdio>
#include <vector>

using namespace std;

int findRoot(vector<int>& parents,int p)
{
    int n = parents.size()-1;
    int step = 0;
    int t = p;
    while(parents[t] != -1 && parents[t] != p && step < n)
    {
        t = parents[t];
        ++step;
    }

    return parents[t] == -1 ? t : p;
}

vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
    //思路：回归到图，如果用出度和入度，没有办法解决环的问题
    //除根之外的节点有且只有一个父节点。。这个与并查集很像啊。。。

    int n = edges.size();

    vector<int> parents(n+1,-1);
    int conflict = -1;
    for(int i=0;i<n;++i)
    {
        if(parents[edges[i][1]] != -1)
        {
            conflict = i;
            continue;
        }
        parents[edges[i][1]] = edges[i][0];
    }

    //处理一个节点有两个父节点的情况。。。
    if(conflict != -1)
    {
        //看当前保留的边的点能否到达根节点和冲突的边的点也能到达根节点
        int p = edges[conflict][1];
        int root1 = findRoot(parents,edges[conflict][0]);
        int root2= findRoot(parents,parents[p]);
        vector<int> tmp = {parents[p],p};
        return root1 == root2 ? edges[conflict] : tmp;
    }

    //处理没有根的情况，这时，根成环了。。。
    for(int i=n-1;i>=0;--i)
    {
        int p = edges[i][1];
        //尝试断开这条边,那么p就是root
        parents[p] =-1;
        if(findRoot(parents,edges[i][0]) == p)
        {
            return edges[i];
        }
    }

    return {};
}

//通过并查集和额外的一个数组，这样可以通过并查集来找环的存在。。。
// struct UnionFind {
//     vector <int> ancestor;

//     UnionFind(int n) {
//         ancestor.resize(n);
//         for (int i = 0; i < n; ++i) {
//             ancestor[i] = i;
//         }
//     }

//     int find(int index) {
//         return index == ancestor[index] ? index : ancestor[index] = find(ancestor[index]);
//     }

//     void merge(int u, int v) {
//         ancestor[find(u)] = find(v);
//     }
// };

// class Solution {
// public:
//     vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
//         int nodesCount = edges.size();
//         UnionFind uf = UnionFind(nodesCount + 1);
//         auto parent = vector<int>(nodesCount + 1);
//         for (int i = 1; i <= nodesCount; ++i) {
//             parent[i] = i;
//         }
//         int conflict = -1;
//         int cycle = -1;
//         for (int i = 0; i < nodesCount; ++i) {
//             auto edge = edges[i];
//             int node1 = edge[0], node2 = edge[1];
//             if (parent[node2] != node2) {
//                 conflict = i;
//             } else {
//                 parent[node2] = node1;
//                 if (uf.find(node1) == uf.find(node2)) {
//                     cycle = i;
//                 } else {
//                     uf.merge(node1, node2);
//                 }
//             }
//         }
//         if (conflict < 0) {
//             auto redundant = vector<int> {edges[cycle][0], edges[cycle][1]};
//             return redundant;
//         } else {
//             auto conflictEdge = edges[conflict];
//             if (cycle >= 0) {
//                 auto redundant = vector<int> {parent[conflictEdge[1]], conflictEdge[1]};
//                 return redundant;
//             } else {
//                 auto redundant = vector<int> {conflictEdge[0], conflictEdge[1]};
//                 return redundant;
//             }
//         }
//     }
// };


int main()
{
    vector<vector<int>> edges = {{1,2},{1,3},{2,3}};   
    edges = {{1,2},{2,3},{3,4},{4,1},{1,5}};

    auto res = findRedundantDirectedConnection(edges);
    printf("%d %d\n",res[0],res[1]);
    return 0;
}