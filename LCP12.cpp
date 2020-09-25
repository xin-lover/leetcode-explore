//LCP 12. 小张刷题计划

#include <cstdio>
#include <vector>

using namespace std;

int minTime(vector<int>& time, int m) {
    //思路：关键在于要按顺序刷题，同时可以求助一道题
    //根据贪心策略，求助的肯定是费时最长的那道
    //这道题又可以考虑二分。。。。。

    int left=0,right=INT_MAX;
    while(left < right)
    {
        int mid = left + (right-left) / 2;
        int count = 0;
        int sum = 0;
        int mx = 0;
        for(int i=0;i<time.size();++i)
        {
            sum += time[i];
            mx = max(mx,time[i]);
            if(sum - mx > mid)
            {
                ++count;
                if(count > m)
                {
                    break;
                }
                mx = time[i];
                sum = time[i];
            }
        }

        ++count;

        if(count > m)
        {
            left = mid+1;
        }
        else
        {
            right = mid;
        }
    }

    return left;
}

int main()
{
    vector<int> time = {999,999,999};
    int m = 4; //0

    // time = {1,2,3,3}, m = 2; //3

    printf("%d\n",minTime(time,m));

    return 0;
}