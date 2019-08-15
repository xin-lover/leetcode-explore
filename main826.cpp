//leetcode 826. 安排工作以达到最大收益

#include <cstdio>
#include <vector>

using namespace std;

int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
    //思路：每个人只能完成一项工作，所以问题就变为工人选取能胜任但收益最高的工作；
    //难度有10^5个，可以构建这样一个数组，记录完成这个难度的工作的最大收益
    //优化一下就是，记录遍历的难度和其当前的最高收益，这样就会形成一个个难度的梯度，接下来就是遍历工人能力求出结果

    vector<pair<int,int>> works;
    for(int i=0;i<difficulty.size();++i)
    {
        works.push_back({difficulty[i],profit[i]});
    }

    sort(works.begin(),works.end(),[](pair<int,int>& a,pair<int,int>& b){
        return a.first < b.first;
    });

    for(int i=1;i<works.size();++i)
    {
        works[i].second = max(works[i-1].second,works[i].second);
    }

    int res = 0;
    for(int i=0;i<worker.size();++i)
    {
        int left = 0,right = works.size()-1;
        while(left < right)
        {
            printf("left:%d right:%d\n",left,right);
            int mid = left + (right - left) / 2;
            if(worker[i] < works[mid].first)
            {
                right = mid-1;
            }
            else
            {
                left = mid+1;
            }
        }

        if(worker[i] >= works[left].first)
        {
            res += works[left].second;
        }
        else if(left > 0 && worker[i] >= works[left-1].first)
        {
            res += works[left-1].second;
        }
    }

    return res;
}

int maxProfitAssignment2(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {

    //空间复杂度高的
    vector<int> states(100001,0);
    for(int i=0;i<difficulty.size();++i)
    {
        states[difficulty[i]] = max(states[difficulty[i]],profit[i]);
    }

    int mxProfit = 0;
    for(int i=1;i<states.size();++i)
    {
        states[i] = max(states[i],states[i-1]);
    }

    int res = 0;
    for(int i=0;i<worker.size();++i)
    {
        res+=states[worker[i]];
        printf("i:%d %d\n",worker[i],states[worker[i]]);
    }

    return res;
}
int main()
{
    vector<int> diffculty = {2,4,6,8,10};
    vector<int> profit = {10,20,30,40,50};
    vector<int> worker = {4,5,6,7};

    printf("%d\n",maxProfitAssignment2(diffculty,profit,worker));
    return 0;
}