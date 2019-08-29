//leetcode 851. 喧闹和富有

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

int findMinQuiet(const vector<vector<int>>& flags,int index,const vector<int>& quiets,vector<int>& minQuiets)
{
    if(minQuiets[index] >= minQuiets.size())
    {
        minQuiets[index] = index;
        //还是重复计算了，没有动归
        // queue<int> qu;
        // qu.push(index);
        // while(!qu.empty())
        // {
        //     int p =qu.front();
        //     qu.pop();

        //     if(quiets[p] < quiets[minQuiets[index]])
        //     {
        //         minQuiets[index] = p;
        //     }

        //     for(int a : flags[p])
        //     {
        //         qu.push(a);
        //     }
        // }

        for(int i=0;i<flags[index].size();++i)
        {
            int minIndex = findMinQuiet(flags,flags[index][i],quiets,minQuiets);
            if(quiets[minQuiets[index]] > quiets[minIndex])
            {
                minQuiets[index] = minIndex;
            }
        }


    }

    return minQuiets[index];

}

vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
    //思路：recher给出了富有的状态，可以使用一个数组记录当前比他富有的拥有的最小安静值，然后更新
    //但问题在于更新，及x>b,b>c可以推导x>c,这种情况也必须更新,同时，不比c富有的那些也应该更新
    //暴力方法，是给每个人记录比他富有的人，quiet的上限是500，空间复杂度是O(n^2)
    //优化，使用不相交集的思路，记录直接富有情况，间接的可以dfs或bfs查询到
    //这个有点像图的解法 

    vector<vector<int>> flags(quiet.size());

    for(auto a : richer)
    {
        flags[a[1]].push_back(a[0]);
    }

    int n = quiet.size();
    vector<int> minQuiets(n,n);
    for(int i=0;i<quiet.size();++i)
    {
        findMinQuiet(flags,i,quiet,minQuiets);
    }

    return minQuiets;
}

int main()
{
    vector<vector<int>> richer = {{1,0},{2,1},{3,1},{3,7},{4,3},{5,3},{6,3}};
    vector<int> quiet = {3,2,5,4,6,1,7,0};

    auto res = loudAndRich(richer,quiet);
    for(auto a : res)
    {
        printf("%d ",a);
    }
    printf("\n");

    return 0;
}