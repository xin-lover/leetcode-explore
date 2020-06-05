//1353. 最多可以参加的会议数目

#include <cstdio>
#include <vector>
#include <set>

using namespace std;

int maxEvents(vector<vector<int>>& events) {
    //思路：可以排序，策略就是每次都参加最靠前的会议
    //但如果开始日期相同，那么我们需要挑选最早结束的

    //这种策略有问题，对于一些跨度较大的区域，无法确定用其低位还是高位
    //增加复杂度，再加一个循环，开始时间确定后，如果有多个区域可选，选择最早结束的，但多了一层循环，还需要标记该会议是否参加过了
    //可以考虑不排序了

    // sort(events.begin(),events.end(),[](vector<int>& a,vector<int>& b)
    // {
    //     if(a[0] == b[0])
    //     {
    //         return a[1] < b[1];
    //     }

    //     return a[0] < b[0];
    // });

    // vector<bool> flags(events.size(),false);
    // int lastDay = events[0][0];
    // flags[0] = true;
    // int res = 1;
    // for(int i=1;i<events.size();++i)
    // {
    //     for(int i=0;i<)
    //     int t = max(events[i][0],lastDay+1);
    //     if(t <= events[i][1])
    //     {
    //         lastDay = t;
    //         ++res;
    //     }
    // }

    //策略：先参加短会议，再参加长会议,这个策略的问题是选择短会议的哪个时间参加
    sort(events.begin(),events.end(),[](vector<int>& a,vector<int>& b)
    {
        int len1 = a[1]-a[0];
        int len2 = b[1]-b[0];
        if(len1 == len2)
        {
            if(a[0] == b[0])
            {
                return a[1] < b[1];
            }
        
            return a[0] < b[0];
        }
        
        return len1 < len2;
        
    });

    vector<bool> flags(100000,false);
    int res = 0;
    for(int i=0;i<events.size();++i)
    {
        for(int j=events[i][0];j<=events[i][1];++j)
        {
            if(!flags[j])
            {
                flags[j] = true;
                ++res;
                break;
            }
        }
    }

    return res;
}

int maxEvents2(vector<vector<int>>& events) {
    //思路：贪心算法，选择第i天中可参加会议中endday最小的那个会议

    multiset<pair<int,int>> S;
    int N = 100010;
    vector<vector<int>> in(N),out(N);

    int mx = 0;
    for(int i=0;i<events.size();++i)
    {
        int l = events[i][0],r=events[i][1];
        in[l].push_back(i);
        out[r+1].push_back(i);
        mx = max(mx,r);
    }

    int res = 0;
    for(int i=1;i<=mx;++i)
    {
        for(auto a : in[i]) 
        {
            S.insert({events[a][1],a});
        }
        for(auto a : out[i])
        {
            auto it = S.find({events[a][1],a});
            if(it != S.end())
            {
                S.erase(it);
            }
        }

        if(!S.empty())
        {
            S.erase(S.begin()); //这个不是清空，而是选择最小的那个
            ++res;
        }
    }

    return res;

}

int main()
{
    vector<vector<int>> events = {{1,2},{2,3},{3,4}}; //3
    // events = events= {{1,2},{2,3},{3,4},{1,2}};//4
    // events = {{1,1},{1,2},{1,3},{1,4},{1,5},{1,6},{1,7}}; //7
    // events = {{1,2},{1,2},{3,3},{1,5},{1,5}};
    // events={{1,5},{1,5},{1,5},{2,3},{2,3}}; //5
    events = {{1,3},{1,3},{1,3},{3,4}}; //4
    events = {{1,2},{1,2},{3,3},{1,5},{1,5}};//5

    printf("%d\n",maxEvents2(events));
    return 0;
}