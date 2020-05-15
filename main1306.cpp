//1306. 跳跃游戏 III

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

bool canReach(vector<int>& arr, int start) {
    //思路：根据题意，可能有多个0存在，我们可以用相交集的的思路思考
    //也就是说把相连的点放到一个集合中，而最终跟0是一个集合的点都能到达0
    //现在的问题是，按照不像交集标记的方式，一个点能属于两个集合
    //我们可以考虑图的方法，也就是遍历图

    int n = arr.size();
    vector<vector<int>> graph(n);
    for(int i=0;i<n;++i)
    {
        if(i+arr[i] < n)
        {
            graph[i].push_back(i+arr[i]);
        }
        if(i - arr[i] >= 0)
        {
            graph[i].push_back(i-arr[i]);
        }
    }

    vector<bool> visited(n,false);
    queue<int> qu;
    qu.push(start);

    while(!qu.empty())
    {
        int p = qu.front();
        qu.pop();

        visited[p] = true;
        if(arr[p] == 0)
        {
            return true;
        }

        for(int i=0;i<graph[p].size();++i)
        {
            if(!visited[graph[p][i]])
            {
                qu.push(graph[p][i]);
            }
        }
    }

    return false;
}

// bool canReach2(vector<int>& arr, int start) {
//     //思路：图的思路，非常直观，就是回溯，性能不高
//     //每个点能到达左右两个点，如果这两个点能到达0，它就能到达0
//     //我们先从左到右遍历，假定只走一步，对于i，我们能够用i-arr[i]是否能到达0，初步判断
//     //无法继续。。
// }

int main()
{
    vector<int> arr = {4,2,3,0,3,1,2};
    int start = 5;  //true;

    arr = {3,0,2,1,2};
    start = 2;//false;
    printf(canReach(arr,start) ? "true\n" : "false\n");
    return 0;
}