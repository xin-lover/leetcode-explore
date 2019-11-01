//leetcode 947. 移除最多的同行或同列石头

#include <cstdio>
#include <vector>
#include <queue>
#include <set>

using namespace std;

int removeStones(vector<vector<int>>& stones) {
    //思路：如果一个石头没有同行或同列的其它石头，那么它就是一个孤岛，我们的目标是使孤岛越少越好
    //我们可以建立一个连接图，如果一个点有最多的连接点，那么我们优先删除它的连接点，对于要删除的连接点也是这样一个想法
    //这样需要排序，可以另外考虑一个情况，在什么时候移除一块石头肯定正确？它是叶子节点，也就是说我们把它看成四叉树
    //离它最近的上下左右四个点就是它的儿子节点，那么一个树最后就只能是一个节点，那么结果就是看有多少棵树

    vector<vector<int>> graph(10001);
    for(int i=0;i<stones.size();++i)
    {
        //这里有问题，这里的stones[i][0]是一个点，题目中的点是坐标点，即stone[i]才是一个点
        graph[stones[i][0]].push_back(stones[i][1]);
        graph[stones[i][1]].push_back(stones[i][0]);
    }

    vector<bool> flags(10001,false);

    int res = 0;
    queue<int> qu;
    for(int i=0;i<graph.size();++i)
    {
        if(graph[i].empty() || flags[i])
        {
            continue;
        }

        ++res;
        qu.push(i);
        while(!qu.empty())
        {
            int t = qu.front();
            qu.pop();
            if(!flags[t])
            {
                flags[t] = true;
                for(int j=0;j<graph[t].size();++j)
                {
                    if(!flags[graph[t][j]])
                    {
                        qu.push(graph[t][j]);
                    }
                }
            }
        }
    }

    return stones.size() - res;
}

int removeStones2(vector<vector<int>>& stones) {
    //思路：上面的思路是对的，划分为树，其实就是分组
    //简化一点就是，一个坐标点，它所在的行和列都是一组，但要考虑组合并,可以使用相交集

    vector<int> rowFlags(10001,-1);
    vector<int> colFlags(10001,-1);
    vector<int> groups;
    for(int i=0;i<stones.size();++i)
    {
        int row = stones[i][0];
        int col = stones[i][1];
        //新的组
        if(rowFlags[row]==-1 && colFlags[col]==-1)
        {
            int group = groups.size();
            rowFlags[row] = group;
            colFlags[col] = group;
            groups.push_back(group);
        }
        else if(rowFlags[row] == -1 && colFlags[col] != -1)
        {
            rowFlags[row] = colFlags[col];
        }
        else if(rowFlags[row] != -1 && colFlags[col] == -1)
        {
            colFlags[col] = rowFlags[row];
        }
        else if(rowFlags[row] != colFlags[col])
        {
            int j = rowFlags[row];
            while(groups[j] != j)
            {
                j = groups[j];
            }

            int k = colFlags[col];
            while(groups[k] != k)
            {
                k = groups[k];
            }
            groups[k] = j;
        }
    }

    int res = 0;
    for(int i=0;i<groups.size();++i)
    {
        printf("%d ",groups[i]);
        if(groups[i] == i)
        {
            ++res;
        }
    }
    printf("\n");
    printf("res:%d\n",res);
    return stones.size() - res;
}

int main()
{
    vector<vector<int>> v = {{0,0},{0,1},{1,0},{1,2},{2,1},{2,2}};//5
    v = {{0,0},{0,2},{1,1},{2,0},{2,2}}; //3
    // v = {{0,0}}; //0
    // v = {{0,1},{1,0}}; //0
    // v = {{0,1},{1,0},{1,1}};
    // v = {{3,3},{4,4},{1,4},{1,5},{2,3},{4,3},{2,4}}; //6
    v = {{3,2},{0,0},{3,3},{2,1},{2,3},{2,2},{0,2}}; //6
    printf("%d\n",removeStones2(v));
    return 0;
}