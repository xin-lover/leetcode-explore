//leetcode 781. 森林中的兔子

#include <cstdio>
#include <vector>
#include <unordered_map>

using namespace std;

int numRabbits(vector<int>& answers) {
    //思路：根据题目的假设，所有的兔子回答都是真实且正确的
    //所以如果两次兔子颜色相同，则它们的回答肯定相同，因为求的是最少数量，所以如果回答相同，则可判定它们是同一种颜色
    //策略：找相同的数字，这个数字+1则是这种颜色兔子的数量，如果相同数字的数量超过这个数字，则表示有其它颜色的兔子也是这个数量

    unordered_map<int,int> um;
    for(int a : answers)
    {
        ++um[a];
    }

    int res = 0;
    for(auto it = um.begin();it!=um.end();++it)
    {
        // printf("%d %d\n",it->first,it->second);
        // if(it->first == 0)
        // {
        //     res+=it->second;
        // }
        // else
        // {
        //     int c = it->first + 1;
        //     int p = it->second / c;
        //     int q = it->second - c * p;
        //     // printf("p:%d q:%d\n",p,q);
        //     res += p * c + (q == 0 ? 0 : it->first + 1);
        // }
        
        int c = it->first + 1;
        int t = it->second;
        while(t >= c)
        {
            t-=c;
            res += c;
        }

        if(t != 0)
        {
            res += it->first + 1;
        }
    }

    return res;
}

int main()
{
    vector<int>  v = {1,1,2};
    // v = {10,10,10};
    // v = {};
    // v = {2,2,2,2};
    // v = {1,0,1,0,0};
    // v = {0,0,1,1,1};
    printf("%d\n",numRabbits(v));
    return 0;
}