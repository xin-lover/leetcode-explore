//1338. 数组大小减半

#include <cstdio>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

int minSetSize(vector<int>& arr) {
    //思路：可以统计数字出现的次数，然后按次数排序
    //优先选择删除次数最多的

    unordered_map<int,int> um;
    vector<vector<int>> states;//可优化，只需要记录次数即可，不关心删除哪几个数字
    for(auto a : arr)
    {
        ++um[a];
    }

    for(auto a : um)
    {
        states.push_back({a.first,a.second});
    }

    sort(states.begin(),states.end(),[](vector<int>& a,vector<int>& b)
    {
        return a[1] > b[1];
    });

    int sum = 0;
    for(int i=0;i<states.size();++i)
    {
        sum += states[i][1];
        if(sum * 2 >= arr.size())
        {
            return i+1;
        }
    }

    return 0;
}

int minSetSize2(vector<int>& arr) {
    //思路：可以统计数字出现的次数，然后按次数排序
    //优先选择删除次数最多的，排序是耗时的关键
    //可以考虑优先队列，如果队列中的数量小于一半，则入队，否则出队最小的

    unordered_map<int,int> um;
    for(auto a : arr)
    {
        ++um[a];
    }

    //
    priority_queue<int,vector<int>,greater<int>> pq;
    int sum=0;
    for(auto a : um)
    {
        pq.push(a.second);
        sum += a.second;

        while((sum - pq.top()) * 2 >= arr.size())
        {
            sum -= pq.top();
            pq.pop();
        }
    }

    return pq.size();
}

int main()
{
    vector<int> arr = {3,3,3,3,5,5,5,2,2,7};    //2
    // arr = {7,7,7,7,7,7};//1
    arr = {1,2,3,4,5,6,7,8,9,10};  //5
    printf("%d\n",minSetSize2(arr));

    return 0;
}