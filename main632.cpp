//632. 最小区间

#include <cstdio>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

vector<int> smallestRange(vector<vector<int>>& nums) {
    //思路：要至少包含序列中的一个数
    //暴力求解，将是O(num1.size()*num2.size()*.....)
    //因为必须包含序列中的一个数，所以我们可以使用二分，先确定第一个数组包含的数a，初始化空间为{a,a},在其后的数组中找最接近这个空间的数，不断更新这个空间
    //最后得到符合要求的空间。。。。
    //这个思路有个问题是前面所选的边界会影响后面的数的选择，从而影响边界的选择，无法达到最优

    if(nums.empty())
    {
        return {};
    }

    int resLow=INT_MAX-100000,resHigh=INT_MAX;
    for(int i=0;i<nums[0].size();++i)
    {
        for(int k=0;k<nums[1].size();++k)
        {
            int low = min(nums[0][i],nums[1][k]);
            int high = max(nums[0][i],nums[1][k]);
            for(int j=2;j<nums.size();++j)
            {
                //使用二分找大于low的第一个数
                int left=0,right=nums[j].size()-1;
                while(left < right)
                {
                    int mid = left + (right-left)/2;
                    if(nums[j][mid] >= low)
                    {
                        right = mid;
                    }
                    else
                    {
                        left=mid+1;
                    }
                }

                if(nums[j][left] < low)
                {
                    low = nums[j][left];
                }
                else if(nums[j][left] > high)
                {
                    if(left > 0 && (low-nums[j][left-1] < nums[j][left] - high))
                    {
                        low = nums[j][left-1];
                    }
                    else
                    {
                        high = nums[j][left];
                    }
                }
            }

            printf("ww:%d %d\n",low,high);
            if(high-low < resHigh - resLow)
            {
                resHigh = high;
                resLow = low;
            }
            else if(high-low == resHigh-resLow && low < resLow)
            {
                resHigh = high;
                resLow = low;
            }
        }

    }

    return {resLow,resHigh};
}

vector<int> smallestRange2(vector<vector<int>>& nums) {
    //思路：用两个优先队列？把所有结果都走一遍？复杂度没变，而且还没有利用序列有序性的特点
    //考虑整体二分。。因为最大值和最小值很容易确定，所以最大空间其实我们是确定了的
    //我们选择的最终空间{a,b},b肯定大于所有数组的某个数，同理a肯定小于所有数组的某个数
    //这样我们选择一个数c，{c,max}作为一个区间使用二分来找到一个最小的b，是的每个数组都有数能小于b，同理找a
    //这个有问题，left不能这样确定

    int mn=INT_MAX,mx=INT_MIN;
    // int littlePos=0; //用于优化，选择数量最少的数组
    for(int i=0;i<nums.size();++i)
    {
        mn = min(mn,nums[i].front());
        mx = max(mx,nums[i].back());
    }
    printf("mn:%d mx:%d\n",mn,mx);

    sort(nums.begin(),nums.end(),[](vector<int>& a,vector<int>& b)
    {
        return a[0] < b[0];
    });

    int low = mn,high=mx;
    for(int i=0;i<nums[0].size();++i)
    {
        int c = nums[0][i];

        bool valid = true;
        int left = mn,right=c+1;
        while(left < right)
        {
            int mid = left + (right-left)/2;

            valid = true;
            for(int j=1;j<nums.size();++j)
            {
                if(nums[j].back() < mid)
                {
                    valid = false;
                    break;
                }
            }

            if(valid)
            {
                left = mid+1;
            }
            else
            {
                right = mid;
            } 
        }

        int a = left-1;
        // if(!valid || left == right)
        // {
        //     --a;
        // }

        left=c,right=mx;
        while(left < right)
        {
            int mid= left + (right-left)/2;
            valid = true;
            for(int j=1;j<nums.size();++j)
            {
                auto it = upper_bound(nums[j].begin(),nums[j].end(),mid);
                if(it == nums[j].begin() || (*(it-1)) < a)
                {
                    valid = false;
                    break;
                }
            }

            if(valid)
            {
                right = mid;
            }
            else
            {
                left = mid+1;
            }
        }

        int b = left;

        if(high-low > b-a || (high-low==b-a && a < low))
        {
            low = a;
            high = b;
        }
    }

    return {low,high};

}

vector<int> smallestRange3(vector<vector<int>>& nums)
{
    //思路：要使用二分法，首先需要确定left,超时
    int mn=INT_MAX,mx=INT_MIN;
    int mx2=INT_MAX;
    for(int i=0;i<nums.size();++i)
    {
        mn = min(mn,nums[i].front());
        mx = max(mx,nums[i].back());
        mx2 = min(mx2,nums[i].back());
    }

    int low = mn,high=mx;
    for(int i=mn;i<=mx2;++i)
    {
        int a = i;
        int left=a,right=mx;
        bool valid = true;
        while(left < right)
        {
            int mid= left + (right-left)/2;
            valid = true;
            for(int j=0;j<nums.size();++j)
            {
                auto it = upper_bound(nums[j].begin(),nums[j].end(),mid);
                if(it == nums[j].begin() || (*(it-1)) < a)
                {
                    valid = false;
                    break;
                }
            }

            if(valid)
            {
                right = mid;
            }
            else
            {
                left = mid+1;
            }
        }

        int b = left;
        if(high-low > b-a || (high-low==b-a && a < low))
        {
            low = a;
            high = b;
        }

    }

    return {low,high};
}

vector<int> smallestRange4(vector<vector<int>>& nums) {
    //思路：用优先队列，因为每个数组至少有一个数要被包含在区间中，我们保持优先队列的大小为n
    //每次都把优先队列中最小的数出队，然后再加入新的数，不断更新，直到某个数组遍历完成。。

    int sz = nums.size();
    vector<int> next(sz,0);

    auto cmp = [&](const int& a,const int& b)
    {
        return nums[a][next[a]] > nums[b][next[b]];
    };

    priority_queue<int,vector<int>,decltype(cmp)> pq(cmp);

    int mx = INT_MIN;
    for(int i=0;i<sz;++i)
    {
        pq.push(i);
        mx = max(mx,nums[i][0]);
    }

    int low = nums[pq.top()][next[pq.top()]],high = mx;
    while(true)
    {
        int top = pq.top();
        pq.pop();

        int mn = nums[top][next[top]];
        if(high - low > mx - mn ||
            (high - low == mx - mn && mn < low))
        {
            high = mx;
            low = mn;
        }

        ++next[top];
        if(next[top] >= nums[top].size())
        {
            break;
        }
        mx = max(mx,nums[top][next[top]]);
        pq.push(top);
    }

    return {low,high};
}

//哈希+滑动窗口
vector<int> smallestRange5(vector<vector<int>>& nums) {
    int n = nums.size();
    unordered_map<int, vector<int>> indices;
    int xMin = INT_MAX, xMax = INT_MIN;
    for (int i = 0; i < n; ++i) {
        for (const int& x: nums[i]) {
            indices[x].push_back(i);
            xMin = min(xMin, x);
            xMax = max(xMax, x);
        }
    }

    vector<int> freq(n);
    int inside = 0;
    int left = xMin, right = xMin - 1;
    int bestLeft = xMin, bestRight = xMax;

    while (right < xMax) {
        ++right;
        if (indices.count(right)) {
            for (const int& x: indices[right]) {
                ++freq[x];
                if (freq[x] == 1) {
                    ++inside;
                }
            }
            while (inside == n) {
                if (right - left < bestRight - bestLeft) {
                    bestLeft = left;
                    bestRight = right;
                }
                if (indices.count(left)) {
                    for (const int& x: indices[left]) {
                        --freq[x];
                        if (freq[x] == 0) {
                            --inside;
                        }
                    }
                }
                ++left;
            }
        }
    }

    return {bestLeft, bestRight};
}

int main()
{
    vector<vector<int>> nums = {{4,10,15,24,26}, {0,9,12,20}, {5,18,22,30}}; //{20,24}
    // nums = {{1,2,3},{1,2,3},{1,2,3}}; //{1,1}
    // nums = {{10,10},{11,11}};  //{10,11}
    // nums = {{11,38,83,84,84,85,88,89,89,92},{28,61,89},{52,77,79,80,81},{21,25,26,26,26,27},{9,83,85,90},{84,85,87},{26,68,70,71},{36,40,41,42,45},{-34,21},{-28,-28,-23,1,13,21,28,37,37,38},{-74,1,2,22,33,35,43,45},{54,96,98,98,99},{43,54,60,65,71,75},{43,46},{50,50,58,67,69},{7,14,15},{78,80,89,89,90},{35,47,63,69,77,92,94}}; //[15,84]
    // nums = {{2,18,24,26},{0,10,12,20},{1,3,22,30}}; //{0,2}
    //{13,73}
    nums = {{-89,1,69,89,90,98},{-43,-36,-24,-14,49,61,66,69},{73,94,94,96},{11,13,76,79,90},{-40,-20,1,9,12,12,14},{-91,-31,0,21,25,26,28,29,29,30},{23,88,89},{31,42,42,57},{-2,6,11,12,12,13,15},{-3,25,34,36,39},{-7,3,29,29,31,32,33},{4,11,14,15,15,18,19},{-34,9,12,19,19,19,19,20},{-26,4,47,53,64,64,64,64,64,65},{-51,-25,36,38,50,54},{17,25,38,38,38,38,40},{-30,12,15,19,19,20,22},{-14,-13,-10,68,69,69,72,74,75},{-39,42,70,70,70,71,72,72,73},{-67,-34,6,26,28,28,28,28,29,30,31}};
    auto res = smallestRange4(nums);
    printf("%d %d\n",res[0],res[1]);

    return 0;
}