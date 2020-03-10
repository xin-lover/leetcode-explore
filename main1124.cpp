//1124. 表现良好的最长时间段

#include <cstdio>
#include <vector>
#include <unordered_map>
#include <stack>

using namespace std;

int longestWPI(vector<int>& hours,int left,int right) {
    if(left == right)
    {
        return hours[left] > 8 ? 1 : 0;
    }

    int mid = left + (right - left) / 2;
    int r1 = longestWPI(hours,left,mid);
    int r2 = longestWPI(hours,mid+1,right);

    int c = 0;
    int t = mid;
    int leftMax = 0,rightMax=0;
    while(t >= left)
    {
        c+=(hours[t] > 8 ? 1 : -1);
        if(c > 0)
        {
            leftMax = mid - t + 1;
        }
        --t;
    }

    c=0;
    t = mid+1;
    while(t <= right)
    {
        c+=(hours[t] > 8 ? 1 : -1);
        if(c > 0)
        {
            rightMax = t - mid;
        }
        ++t;
    }

    return max(leftMax+rightMax,max(r1,r2));
}

int longestWPI(vector<int>& hours) {
    //思路：可以采用分治法，把数组分为两部分
    //最长的子数组可能出现在左边、右边，或者中间
    //这种思路不行，和求最大值不一样，因为左侧大于0，右侧小于0可以组成符合要求的数组

    // return longestWPI(hours,0,hours.size()-1);

    if(hours.empty())
    {
        return 0;
    }

    int n = hours.size();
    vector<int> flags(n+1,0);
    for(int i=1;i<=n;++i)
    {
        flags[i] = flags[i-1] + (hours[i-1] > 8 ? 1 : -1);
    }

    int res = 0;
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<i;++j)
        {
            if(flags[i] - flags[j] > 0)
            {
                res = max(res,i-j);
                break;
            }
        }
    }

    return res;
}

int longestWPI2(vector<int>& hours) {
    //思路：上面是n^2的解法，应该有O(n)的解法
    //我们使用贪心策略，最长的应该就是劳累天数刚好多1天
    //我们记录劳累天数和正常天数的差值，如果出现同样的情况，则说明两者中间这段两者刚好相等
    //这种方式也不行，因为会有重复出现的差值，我们只记录第一次出现的，而结果可能是第二次出现的地方
    //改进一下，我们记录两种位置，一种是下一个值大于8的第一个位置，一种是下一个小于等于8的第一个位置

    unordered_map<int,int> um1;
    unordered_map<int,int> um2;
    int c =0;
    int res = 0;
    for(int i=0;i<hours.size();++i)
    {
        c+=(hours[i] > 8 ? 1 : -1);
        if(c > 0)
        {
            res = max(res,i+1);
        }

        if(i+1 < hours.size())
        {
            unordered_map<int,int> &uu = (hours[i+1] <= 8 ? um1 : um2);
            if(uu.find(c) == uu.end())
            {
                uu[c] = i;
            }
        }

        int j = hours.size() + 1;
        if(um1.find(c) != um1.end())
        {
            j = min(um1[c],j);
        }
        if(hours[i] <= 8)
        {
            if(um2.find(c) != um2.end())
            {
                j = min(um2[c],j);
            }
        }
        res = max(i-j-1,res);
    }

    return res;
}

int longestWPI3(vector<int>& hours) {
    //单调递减栈
    vector<int> sum(hours.size()+1,0);
    for(int i=1;i<sum.size();++i)
    {
        sum[i] = sum[i-1] + (hours[i-1] > 8 ? 1 : -1);
    }

    stack<int> sk;
    for(int i=0;i<sum.size();++i)
    {
        if(sk.empty() || sum[i] < sum[sk.top()])
        {
            sk.push(i);
        }
    }

    int res = 0;
    for(int i=sum.size()-1;i>=0;--i)
    {
        while(!sk.empty() && sum[sk.top()] < sum[i])
        {
            res = max(res,i-sk.top());
            sk.pop();
        }
    }

    return res;
}

int longestWPI4(vector<int>& hours) {
    vector<int> days;
    for (int i = 0; i < hours.size(); i++) {
        if (hours[i] > 8) {
            days.push_back(1);
        } else {
            days.push_back(-1);
        }
    }
    vector<int> sum(days.size() + 1, 0);
    for (int i = 0; i < days.size(); i++) {
        sum[i+1] = sum[i] + days[i];
    }
    stack<int> decreaseStack;
    for (int i = 0; i < sum.size(); i++) {
        if (decreaseStack.empty()) {
            decreaseStack.push(i);
        } else {
            if (sum[decreaseStack.top()] > sum[i]) {
                decreaseStack.push(i);
            }
        }
    }
    int maxDays = 0;
    for (int i = sum.size() - 1; i > 0; i--) {
        while(! decreaseStack.empty() && sum[decreaseStack.top()] < sum[i]) {
            maxDays = max(maxDays, i - decreaseStack.top());
            decreaseStack.pop();
        }
    }
    return maxDays;
}

int main()
{
    vector<int> hours = {9,9,6,0,6,6,9}; //3
    // hours = {6,6,9};
    // hours = {12,8,7,7,9,10,8,7,9,7,8,11};//5
    //29
    // hours = {11,2,4,14,2,15,7,10,1,16,9,0,2,8,4,14,6,12,2,8,6,4,14,13,7,16,14,2,3,2,8,3,12,3,3,9,14,1,5,3,12,0,15,5,0,2,3,16,7,2,1,1,4,9,0,11,9,16,15,7,0,5,6,4,12,1,1,2,13,8,3,9,12,9,3,11,4,14,7,5,16,0,11,8,8,14,1,5,0,6,5,8,10,15,9,14,16,11,1,13};
    // hours = {0,11,8,8,14,1,5,0,6,5,8,10,15,9,14,16,11,1,13};
    printf("%d\n",longestWPI3(hours));

    return 0;
}