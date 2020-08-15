//1488. 避免洪水泛滥

#include <cstdio>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

vector<int> avoidFlood(vector<int>& rains) {
    //思路：湖泊要两次下雨才会发洪水，而下雨时我们什么也不能干
    //唯一要处理的就是不下雨时抽干哪个湖泊，很明显方案就是选择后面会再次下雨的湖泊
    //所以我们到再次下雨的时候再决定
    //那么遍历的时候遇到不下雨的时间，先记录，到再次下雨的时候再使用
    //这里没有处理先后顺序，也就是在某个湖泊下雨前抽干某个湖泊并没有用
    //可以看出，我们应该选择下完雨后最近的没下雨天抽干这个湖泊

    vector<int> res(rains.size(),-2);
    unordered_map<int,int> emptyFlags;  //记录湖泊哪天下雨

    for(int i=0;i<rains.size();++i)
    {
        if(rains[i] > 0)
        {
            res[i] = -1;    //什么都不能干
                printf("dd:%d %d\n",rains[i],i);
            if(emptyFlags.find(rains[i]) == emptyFlags.end() || emptyFlags[rains[i]] == -1)   //空的，不用管
            {
                emptyFlags[rains[i]] = i;
                printf("y:%d %d\n",rains[i],i);
            }
            else
            {
                //湖泊有水且又下雨了
                int d = emptyFlags[rains[i]];
                for(int j=emptyFlags[rains[i]]+1;j<i;++j)
                {
                    if(rains[j] == 0 && res[j] == -2)
                    {
                        res[j] = rains[i];
                        emptyFlags[rains[i]] = i;
                        break;
                    }
                }
                
                if(emptyFlags[rains[i]] == d)
                {
                    return {};
                }
            }
        }
        
    }

    for(int i=0;i<res.size();++i)
    {
        if(res[i] == -2)
        {
            res[i] = 1;
        }
    }

    return res;
}

vector<int> avoidFlood2(vector<int>& rains) {
    //思路：湖泊要两次下雨才会发洪水，而下雨时我们什么也不能干
    //唯一要处理的就是不下雨时抽干哪个湖泊，很明显方案就是选择后面会再次下雨的湖泊
    //所以我们到再次下雨的时候再决定
    //那么遍历的时候遇到不下雨的时间，先记录，到再次下雨的时候再使用
    //这里没有处理先后顺序，也就是在某个湖泊下雨前抽干某个湖泊并没有用
    //可以看出，我们应该选择下完雨后最近的没下雨天抽干这个湖泊

    vector<int> res(rains.size(),-2);
    unordered_map<int,int> emptyFlags;  //记录湖泊哪天下雨

    vector<int> sunnys;

    for(int i=0;i<rains.size();++i)
    {
        if(rains[i] > 0)
        {
            res[i] = -1;    //什么都不能干
            if(emptyFlags.find(rains[i]) == emptyFlags.end() || emptyFlags[rains[i]] == -1)   //空的，不用管
            {
                emptyFlags[rains[i]] = i;
            }
            else
            {
                //湖泊有水且又下雨了
                int d = emptyFlags[rains[i]];
                //使用二分优化，预先记录所有晴天的日期  
                // for(int j=emptyFlags[rains[i]]+1;j<i;++j)
                // {
                //     if(rains[j] == 0 && res[j] == -2)
                //     {
                //         res[j] = rains[i];
                //         emptyFlags[rains[i]] = i;
                //         break;
                //     }
                // }
                
                // if(emptyFlags[rains[i]] == d)
                // {
                //     return {};
                // }

                int left=0,right=sunnys.size()-1;
                while(left < right)
                {
                    int mid = left+(right-left)/2;
                    if(sunnys[mid] < emptyFlags[rains[i]])
                    {
                        left = mid+1;
                    }
                    else
                    {
                        right = mid;
                    }
                }

                printf("left:%d %d %d\n",left,rains[i],emptyFlags[rains[i]]);
                if(sunnys.empty() || sunnys[left] <= emptyFlags[rains[i]])
                {
                    return {};
                }

                res[sunnys[left]] = rains[i];
                emptyFlags[rains[i]] = i;
                sunnys.erase(sunnys.begin() + left);
            }
        }
        else
        {
            sunnys.push_back(i);
        }
        
    }

    for(int i=0;i<res.size();++i)
    {
        if(res[i] == -2)
        {
            res[i] = 1;
        }
    }

    return res;
}

//还是使用set。。。。。
vector<int> avoidFlood3(vector<int>& rains)
{
    vector<int> ans(rains.size(), 1);
        unordered_map<int, int> water;
        set<int> zero;

        for (int i = 0; i < rains.size(); i++) {
            int r = rains[i];

            if (r == 0) {
                zero.insert(i);
                continue;
            }

            if (water.count(r) != 0) {
                auto it = zero.lower_bound(water[r]);
                if (it == zero.end()) return {};
                ans[*it] = r;
                zero.erase(it);
            }
            water[r] = i;
            ans[i] = -1;
        }

        return ans;
}

//并查集的思路，记录连续雨天后的第一个晴天。。。。。
// class Solution {
// public:
//     int find(int fa[], int i) {
//         return (fa[i] == i)? i : (fa[i] = find(fa, fa[i]));
//     }
//     vector<int> avoidFlood(vector<int>& rains) {
//         int n = rains.size(), fa[n], idx[n];
//         unordered_map<int, int> occur;
//         vector<int> res(rains.size(), 1);
//         for(int i = 0; i < rains.size(); ++i) {
//             if(rains[i]) {
//                 if(i && rains[i-1])
//                     fa[i] = fa[i-1];
//                 else
//                     fa[i] = i, idx[i] = 1000000;
//                 if(occur.count(rains[i])) {
//                     int last = occur[rains[i]], f = find(fa, last);
//                     if(idx[f] >= i)
//                         return {};
//                     res[idx[f]++] = rains[i];
//                     if(idx[f] < rains.size() && rains[idx[f]])
//                         fa[f] = find(fa, idx[f]);
//                 }
//                 occur[rains[i]] = i;
//                 res[i] = -1;
//             } else if(i && rains[i-1]) {
//                 idx[find(fa, i-1)] = i;
//             }
//         }
//         return res;
//     }

int main()
{
    vector<int> rains = {1,2,3,4}; //[-1,-1,-1,-1]
    rains = {1,2,0,0,2,1};//[-1,-1,2,1,-1,-1]
    // rains = {1,2,0,1,2};//[]
    // rains = {69,0,0,0,69};  //[-1,69,1,1,-1]
    // rains = {10,20,20}; //[]
    rains = {2,3,0,0,3,1,0,1,0,2,2};//[]
    for(auto a : avoidFlood2(rains))
    {
        printf("%d ",a);
    }
    printf("\n");

    return 0;
}