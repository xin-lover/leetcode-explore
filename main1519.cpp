//1519. 子树中标签相同的节点数

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

vector<int> postdfs(vector<vector<int>>& graphic,int parent,int node,string& label,vector<int>& res)
{
    vector<int> tmp(26,0);
    printf("node:%d\n",node);
    for(int i=0;i<graphic[node].size();++i)
    {
        if(graphic[node][i] == parent)
        {
            continue;
        }
        auto r = postdfs(graphic,node,graphic[node][i],label,res);
        for(int j =0;j<tmp.size();++j)
        {
            tmp[j] += r[j];
        }
    }

    char cur = label[node];
    tmp[cur-'a']+=1;
    res[node] = tmp[cur-'a'];   

    return tmp;
}

void postdfs2(vector<vector<int>>& graphic,int parent,int node,string& label,vector<int>& res)
{
    static vector<vector<int>> tmp(1e5,vector<int>(26,0));

    for(int i=0;i<graphic[node].size();++i)
    {
        if(graphic[node][i] == parent)
        {
            continue;
        }
        
        int child = graphic[node][i];
        postdfs2(graphic,node,child,label,res);
        for(int j =0;j<tmp[node].size();++j)
        {
            tmp[node][j] += tmp[child][j];
                            if(tmp[child][j] > 0)
                {
                    printf("+child:%d %d\n",child,tmp[child][j]);
                }
        }
    }

    char cur = label[node];
    tmp[node][cur-'a']+=1;
    printf("node:%d yy:%d\n",node,tmp[node][cur-'a']);
    res[node] = tmp[node][cur-'a'];
}


vector<int> countSubTrees(int n, vector<vector<int>>& edges, string labels) {
    //思路：重点在于组织树和遍历，
    //使用临接矩阵来组织图，这样可以使用bfs来遍历，但重复遍历会很多，所以还是要考虑如何仿造树的后序遍历
    //考虑并查集的思路，每个点存储其父节点，从每个点往其父节点遍历,但边是无向的，如何确定谁是父节点？
    //0是根节点，所以只能从0开始构建这棵树，那么每个点存储其所有儿子的编号，然后dfs后序遍历


    vector<vector<int>> graphic(n);
    for(auto a : edges)
    {
        graphic[a[0]].push_back(a[1]);
        graphic[a[1]].push_back(a[0]);
    }

    vector<int> res(n,0);
    postdfs2(graphic,-1,0,labels,res);

    return res;
}

int main()
{
    int n = 5;
    vector<vector<int>> edges = {{0,1},{0,2},{1,3},{0,4}};
    string labels = "aabab";    //[3,2,1,1,1]

    //[2,1,1,1,1,1,1]
    // n = 7, edges = {{0,1},{0,2},{1,4},{1,5},{2,3},{2,6}}, labels = "abaedcd";

    //[6,5,4,1,3,2,1]
    // n = 7, edges = {{0,1},{1,2},{2,3},{3,4},{4,5},{5,6}}, labels = "aaabaaa";

    n=4,edges = {{0,1},{1,2},{0,3}},labels="bbbb";
    for(auto a : countSubTrees(n,edges,labels))
    {
        printf("%d ",a);
    }
    printf("\n");

    return 0;
}