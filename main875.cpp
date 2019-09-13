//leetcode 875. 爱吃香蕉的珂珂

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

int minEatingSpeed(vector<int>& piles, int H) {
    //思路：一个小时最多吃一堆，所以H必须大于等于piles的大小
    //很明显，H等与piles大小的时候，速度必须满足1小时能吃完最大那一堆
    //同理H=piles.size +1时，多出来的一个小时肯定是分给最大那一堆，所以速度就是第二大的堆的大小和最大堆大小/2的最大值
    //所以，每一个堆最开始都要分配一个小时，剩下的时间可以一步一步的分配，每次分给最大值
    //结果超时

    auto cmp = [](const pair<int,int>& a,const pair<int,int>& b){
        int q1 = a.first / a.second;
        int q2 = b.first / b.second;
        if(q1 == q2)
        {
            //有溢出的问题，改成long long 
            long long d1 = a.first - a.second * q1;
            long long d2 = b.first - b.second * q2;
            return d1 * b.second < a.second * d2;
        }

        return q1 < q2;
    };
    priority_queue<pair<int,int>,vector<pair<int,int>>,function<bool(const pair<int,int>& a, const pair<int,int>& b)>> pq(cmp);

    for(auto a : piles)
    {
        pq.push({a,1});
    }

    int t = H - piles.size();
    while(t-- > 0)
    {
        pair<int,int> mx =  pq.top();
        pq.pop();
        pq.push({mx.first,mx.second + 1});
    }

    int q = pq.top().first;
    int p = pq.top().second;
    return q/p + (q%p == 0 ? 0 : 1);
}

int minEatingSpeed2(vector<int>& piles, int H) {
    //思路，一个小时一个小时的分配，用最大堆，操作太多，所以超时
    //也就是说H特别大的时候，如何处理
    //使用二分法，即确定最大速度，然后不断二分，判断是否能吃完

    int mx=INT_MIN;
    for(auto a : piles)
    {
        if(mx < a)
        {
            mx = a;
        }
    }

    int left = 1,right= mx;
    while(left < right)
    {
        int mid = left + (right - left)/2;
        int h = 0;
        for(auto a : piles)
        {
            if(a < mid)
            {
                ++h;
            }
            else
            {
                h+=a/mid;
                if(a % mid > 0)
                {
                    ++h;
                }
            }
            

        }

        if(h > H)
        {
            left = mid + 1;
        }
        else
        {
            right = mid;
        }
    }

    return right;
}

int main()
{
    vector<int> piles = {3,6,7,11};
    printf("%d\n",minEatingSpeed2(piles,8)); //4

    piles = {30,11,23,4,20};
    printf("%d\n",minEatingSpeed2(piles,5)); //30

    piles = {30,11,23,4,20};
    printf("%d\n",minEatingSpeed2(piles,6)); //23

    return 0;
}