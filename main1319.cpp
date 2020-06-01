//1319. 连通网络的操作次数

#include<cstdio>
#include <vector>

using namespace std;

int getRoot(const vector<int>& djset,int i)
{
    while(djset[i] != -1)
    {
        i = djset[i];
    }

    return i;
}
int makeConnected(int n, vector<vector<int>>& connections) {
    //思路：可以考虑不相交集的思路，最后都变为一个集合
    //要把n台电脑链接起来，至少要n-1条线缆
    //连接两个集合只需要一条线缆，所以只要计算出几个集合就行

    if(connections.size() < n-1)
    {
        return -1;
    }

    int groups = n;
    vector<int> djset(n,-1);
    for(int i=0;i<connections.size();++i)
    {
        int r1 = getRoot(djset,connections[i][0]);
        int r2 = getRoot(djset,connections[i][1]);

        if(r1 != r2)
        {
            djset[r1]  = r2;
            --groups;
        }
    }

    return groups - 1;
}

int main()
{
    int n = 4;
    vector<vector<int>> connections = {{0,1},{0,2},{1,2}}; //1

    n = 6, connections = {{0,1},{0,2},{0,3},{1,2},{1,3}}; //2
    printf("%d\n",makeConnected(n,connections));
    return 0;
}