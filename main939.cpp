//leetcode 939. 最小面积矩形

#include<cstdio>
#include <vector>
#include <map>
#include <set>

using namespace std;

int minAreaRect(vector<vector<int>>& points) {
    //思路：整体的想法是先确定构成矩形的点，然后求取面积
    //构成矩形的点我们可以先确定一行的两个点，然后找另外两个点
    //为了快速找到，对points进行排序，排序后查找部分可有优化为二分查找
    //如何分行?用另一个数组记录索引，这样数据结构紧凑一点
    //使用map也可以

    map<int,set<int>> mp;
    for(int i=0;i<points.size();++i)
    {
        mp[points[i][0]].insert(points[i][1]);
    }

    int len = mp.size();
    int res = INT_MAX;
    auto it = mp.begin();
    for(int i=0;i<len;++i,++it)
    {
        if(it->second.size() < 2)
        {
            continue;
        }

        auto next = it;
        for(++next;next != mp.end();++next)
        {
            if(next->second.size() < 2)
            {
                continue;
            }

            for(auto curNumIt = it->second.begin();curNumIt != it->second.end();++curNumIt)
            {
                if(next->second.find(*curNumIt) == next->second.end())
                {
                    continue;
                }
                auto nextNumIt=curNumIt;
                for(++nextNumIt;nextNumIt != it->second.end();++nextNumIt)
                {
                    if(next->second.find(*nextNumIt) != next->second.end())
                    {
                        int area = (next->first - it->first) * (*nextNumIt - *curNumIt);
                        if(area < res)
                        {
                            res = area;
                        }
                        else
                        {
                            //直接退出，因为面积只会更大
                            break;
                        }
                    }
                }

            }
        }
    }

    return res == INT_MAX ? 0 : res;
}

//其它思路
//1.枚举对角线，即先确定两个点，以这两个点为对角线，找另外两个点是否在集合中。这里有个技巧，就是{x,y}表现的坐标转换为一个整数
//因为每个点不同，而0<=x,y<=40000，所以让c = 40001 * x + y;这样c就能表示这个坐标，所以用set或map就可以实现

int main()
{
    vector<vector<int>> v = {{1,1},{1,3},{3,1},{3,3},{2,2}}; //4
    v = {{1,1},{1,3},{3,1},{3,3},{4,1},{4,3}};//2
    printf("%d\n",minAreaRect(v));
    return 0;
}