//leetcode 886. 可能的二分法

#include <cstdio>
#include <vector>
#include <set>
#include <queue>

using namespace std;

bool possibleBipartition(int N, vector<vector<int>>& dislikes) {
    
    //思路：维持两个集合，对于每一组，对其中一个人，判断是否在其中一个集合
    //则情况有：
    //1.两个人在同一个集合，返回false
    //2.否则，插入集合继续
    //如果使用set，虽然二分，但查找还是费时，因为数量固定，所以使用一个数组表示每个人的分组
    //对于两个数字都没分组的情况，我们可以随意分组，但同时也就有两种情况
    //可以用回溯法解决，也可用图的方式解决，

    vector<vector<int>> graph(N+1);
    for(auto a : dislikes)
    {
        graph[a[0]].push_back(a[1]);
        graph[a[1]].push_back(a[0]);
    }

    vector<int> flags(N+1,-1);
    int states[] = {1,0};
    int group = 0;
    for(int i=1;i<=N;++i)
    {
        if(flags[i] != -1)
        {
            continue;
        }
        queue<int> qu;
        qu.push(i);
        while(!qu.empty())
        {
            int sz = qu.size();
            for(int j=0;j<sz;++j)
            {
                int t = qu.front();
                qu.pop();

                if(flags[t] == -1)
                {
                    flags[t] = group;
                    for(auto a : graph[t])
                    {
                        qu.push(a);
                    }
                }
                else
                {
                    if(flags[t] != group)
                    {
                        return false;
                    }
                }
            }

            group = states[group];
        }
    }

    // for(int i=0;i<N;++i)
    // {
    //     printf("%d ",flags[i]);
    // }
    // printf("\n");
    return true;
}

//思路：运用种类并查集的思想，开两倍的数组，前半部分存放可以分在一组的人，后半部分存放自己不喜欢的人
// class Solution {
//     int N;  //共多少人
//     int[] father;   //并查集
//     public boolean possibleBipartition(int _N, int[][] dl) {
//         N = _N+1;   
//         father = new int[N*2+5];    //开两倍的数组
//         for(int i = 1; i < N*2+5; i++) //初始化并查集
//             father[i] = i;
//         for(int i = 0; i < dl.length; i++){
//             int x = find(dl[i][0]); //查找自己的根节点
//             int y = find(dl[i][1]);
//             int a = find(dl[i][0] + N); //查找自己不喜欢的人的根节点
//             int b = find(dl[i][1] + N); 
//             if(x == y) return false; //发现这俩人已经在一组
//             else{
//                 father[a] = y;  //将不喜欢的人合并
//                 father[b] = x;
//             }
//         }
//         return true;
//     }
//     private int find(int x){ //寻找根节点
//         if(x != father[x])  
//             father[x] = find(father[x]); //路径压缩
//         return father[x];
//     }
// }

int main()
{
    vector<vector<int>> v = {{1,2},{1,3},{2,4}};
    printf(possibleBipartition(4,v) ? "true\n" : "false\n");

    v = {{1,2},{1,3},{2,3}};
    printf(possibleBipartition(4,v) ? "true\n" : "false\n");

    v = {{1,2},{2,3},{3,4},{4,5},{1,5}};
    printf(possibleBipartition(5,v) ? "true\n" : "false\n");

    return 0;
}