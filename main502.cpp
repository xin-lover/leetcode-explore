//502. IPO

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

//超时
void backtrace(int k,int W,vector<int>& profits,vector<int>& capital,vector<bool>& flags, int completeCount,int& res)
{
    if(completeCount >= k || completeCount == flags.size())
    {
        return;
    }

    for(int i=0;i<flags.size();++i)
    {
        if(flags[i] && capital[i]<=W)
        {
            flags[i] = false;
            W += profits[i];
            res = max(W,res);
            backtrace(k,W,profits,capital,flags,completeCount+1,res);
            W -= profits[i];
            flags[i] = true;
        }
    }
}

int findMaximizedCapital(int k, int W, vector<int>& Profits, vector<int>& Capital) {
    //思路：k和启动资本是限制，一个方案就是回溯，但项目很多，可能超时

    // vector<bool> flags(Profits.size(),true);
    // int res = 0;
    // backtrace(k,W,Profits,Capital,flags,0,res);
    // return res;

    //贪心思路：肯定优先选择可启动项目中利润最大的项目，所以问题变成了如何找可启动项目中利润最大的项目
    //利润可排序，但又会有成本限制
    //暴力查找还是超时,我们考虑启动成本这个维度，那么我们能否找到某个启动成本之类能完成的项目的最大利润
    //这个是完全可以的，但这里会有个问题，就是最大利润的项目完成后不能再次用了。。。。
    //可以用优先队列，在成本之内的项目我们都放入优先队列中，选择利润最大的，不断重复。。。。

    vector<vector<int>> projects(Profits.size());
    for(int i=0;i<Profits.size();++i)
    {
        projects[i] = {Profits[i],Capital[i]};
    }

    sort(projects.begin(),projects.end(),[](vector<int> a,vector<int> b){
        if(a[0] == b[0])
        {
            return a[1] < b[1];
        }

        return a[0] > b[0];
    });

    vector<bool> flags(projects.size(),true);
    int completeCount=0;
    bool canStart=true;
    while(completeCount<k && canStart)
    {
        canStart = false;
        for(int j=0;j<projects.size();++j)
        {
            if(flags[j] && projects[j][1]<=W)
            {
                printf("j:%d cc:%d\n",j,completeCount);
                canStart = true;
                flags[j] = false;
                completeCount += 1;
                W+=projects[j][0];
                break;
            }
        }

    }

    return W;

}

int findMaximizedCapital2(int k, int W, vector<int>& Profits, vector<int>& Capital) 
{
    //思路：优先队列
    auto cmp = [](vector<int>& a, vector<int>& b){
        return a[0] < b[0];
    };
    priority_queue<vector<int>,vector<vector<int>>,decltype(cmp)> pq(cmp);

    vector<vector<int>> projects(Profits.size());
    for(int i=0;i<Profits.size();++i)
    {
        projects[i] = {Profits[i],Capital[i]};
    }

    sort(projects.begin(),projects.end(),[](vector<int> a,vector<int> b){
        return a[1] < b[1];
    });

    int completeCount = 0;
    for(int i=0;i<projects.size() && completeCount < k;++i)
    {
        if(projects[i][1] <= W)
        {
            pq.push(projects[i]);
        }
        else
        {
            if(pq.empty())
            {
                return W;
            }

            W += pq.top()[0];
            pq.pop();
            ++completeCount;
            --i;
        }
    }

    while(completeCount < k && !pq.empty())
    {
        W += pq.top()[0];
        pq.pop();
        ++completeCount;
    }

    return W;
}

//思路是一样的，但没用排序，而是另一个堆，比排序快
int findMaximizedCapital3(int k, int W, vector<int>& Profits, vector<int>& Capital)
{
    priority_queue<int> p;                                                    // 利润 大根堆
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> c;   // 资本 小根堆
    for (int i = 0; i < Capital.size(); i++) {
        c.emplace(make_pair(Capital[i], Profits[i]));
    }

    for (int i = 0; i < k; i++) {
        while (!c.empty() && c.top().first <= W) {  // 资本小于等于W的项目，存入利润大根堆
            p.emplace(c.top().second);
            c.pop();
        }
        if(p.empty()) break;
        W += p.top();                         // 每次选利润最大的
        p.pop();
    }
    return W;
}
int main()
{
    int k=2, W=0;
    vector<int> Profits={1,2,3}, Capital={0,1,1}; //4
    // k=10,W= 0,Profits= {1,2,3}, Capital={0,1,2}; //6
    // k=2, W=0,Profits= {1,2,3}, Capital={0,9,10}; //1
    printf("%d\n",findMaximizedCapital2(k,W,Profits,Capital));
    return 0;
}