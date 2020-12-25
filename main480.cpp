//480. 滑动窗口中位数

#include <cstdio>
#include <vector>
#include <set>
#include <unordered_map>
#include <queue>

using namespace std;

vector<double> medianSlidingWindow(vector<int>& nums, int k) {
    //思路：有序序列的中位数，所以直观的解法是给窗口的序列排序，然后选择中位数
    //k确定，所以问题就变成了排序的问题了，每一次都排，这个性能肯定不能接受
    //那么我们看如果前k个已经排序，那么问题就变成了窗口右移后，如何快速确定顺序
    //本质上是插入和删除两个操作，通过二分能快速确定插入删除的位置，但需要考虑避免移动
    //用链表，删除O(1),但插入和查找是O(k)
    //用map，value存key有序序号，那么更新序号是O(k)，都是O(n*k)，没变

    if(k > nums.size())
    {
        return {};
    }

    vector<int> kNums(k,0);
    for(int i=0;i<k;++i)
    {
        kNums[i] = nums[i];
    }

    sort(kNums.begin(),kNums.end());
    vector<double> res;
    if(k & 1)
    {
        res.push_back(kNums[k/2]);
    }
    else
    {
        res.push_back(kNums[k/2] * 0.5 + kNums[k/2-1] * 0.5);
    }

    for(int i=k;i<nums.size();++i)
    {
        int left = i-k;
        for(int j=0;j<k;++j)
        {
            if(kNums[j] > nums[left])
            {
                kNums[j-1] = kNums[j];
            }
        }

        int j = k-2;
        for(;j>=0 && kNums[j] > nums[i];--j)
        {
            kNums[j+1] = kNums[j];
        }
        kNums[j+1] = nums[i];

        if(k & 1)
        {
            res.push_back(kNums[k/2]);
        }
        else
        {
            res.push_back(kNums[k/2] * 0.5 + kNums[k/2-1] * 0.5);
        }
        
    }

    return res;
}

vector<double> medianSlidingWindow2(vector<int>& nums, int k) {
    //思路：假设前k个数排序了，中位数也找到了，窗口左侧出去一个数，右侧进来一个数
    //可分为几种情况：
    //1.都小于当前中位数，那么中位数不变；
    //2.都大于当前中位数，中位数也不变；
    //3.左侧去掉的小于中位数，右侧加入的大于中位数，那么情况复杂了，假设右侧加入的数比较大（与中位数不相邻），那么新的中位数是之前的下一位，否则它就是中位数
    //4.左侧去掉的大于中位数，右侧加入的比较小，那么中位数变成上一位，否则它就是中位数
    //5.看看k的情况，1，2是最简单的情况，容易得出结果，如果k=3，中位数在3，4情况中会向前向后移动，这意味着窗口中的元素需要知道其前一个数和后一个数的，但如果要维护这个链表，那么负责度又回去了。。。
    
    //堆的思路，维护一个k个数的堆，每次删除新增，找中位数即可，比如set。。。
    //优化：我们维护多重集合 window 的迭代器 mid；
    // 首先我们在 window 中加入前 k 个元素，并让 mid 指向 window 中的第 \lfloor k/2 \rfloor⌊k/2⌋ 个元素（从 0 开始计数）；
    // 当我们在 window 中加入数 num 时：
    // 如果 num < *mid，那么我们需要将 mid 往前移；
    // 如果 num >= mid，我们不需要对 mid 进行任何操作。
    // 当我们在 windows 中删除数 num 时：
    // 如果 num < *mid，我们需要将 mid 先往后移，再删除 num；
    // 如果 num > *mid，我们不需要对 mid 进行任何操作；
    // 如果 num == *mid，我们需要找到 num 第一次出现的位置对应的迭代器（使用 lower_bound()）并删除，而不是删除 mid 对应的数。随后和 num < *mid 的处理方式相同。

    //     vector<double> medians;
    // multiset<int> window(nums.begin(), nums.begin() + k);

    // auto mid = next(window.begin(), k / 2);

    // for (int i = k;; i++) {

    //     // Push the current median
    //     medians.push_back(((double)(*mid) + *next(mid, k % 2 - 1)) * 0.5);

    //     // If all done, break
    //     if (i == nums.size())
    //         break;

    //     // Insert incoming element
    //     window.insert(nums[i]);
    //     if (nums[i] < *mid)
    //         mid--;                  // same as mid = prev(mid)

    //     // Remove outgoing element
    //     if (nums[i - k] <= *mid)
    //         mid++;                  // same as mid = next(mid)

    //     window.erase(window.lower_bound(nums[i - k]));
    // }

    // return medians;



    if(k <= 0)
    {
        return {};
    }

    multiset<int> st;
    for(int i=0;i<k;++i)
    {
        st.insert(nums[i]);
    }


    vector<double> res;
    if(k&1)
    {
        auto it = st.begin();
        for(int j=0;j<k/2;++j)
        {
            ++it;
        }
        res.push_back(*it);
        for(int i=k;i<nums.size();++i)
        {
            int left = i-k;
            auto pp = st.find(nums[left]);
            st.erase(pp);
            st.insert(nums[i]);
            it = st.begin();
            for(int j=0;j<k/2;++j)
            {
                ++it;
            }
            res.push_back(*it);
        }
    }
    else
    {
        auto it = st.begin();
        for(int j=0;j<(k/2-1);++j)
        {
            ++it;
        }
        auto it2 = it;
        it2++;
        res.push_back(*it * 0.5 + *it2 * 0.5);

        for(int i=k;i<nums.size();++i)
        {
            int left = i-k;
            auto pp = st.find(nums[left]);
            st.erase(pp);
            st.insert(nums[i]);
            it = st.begin();
            for(int j=0;j<k/2-1;++j)
            {
                ++it;
            }
            it2 = it;
            it2++;
            res.push_back(*it * 0.5 + *it2 * 0.5);
        }
    }

    return res;
}

//两个堆，一个最小堆，一个最大堆，分别存放窗口前半部分和后半部分
//同时利用map延迟删除。。。
vector<double> medianSlidingWindow(vector<int>& nums, int k)
{
    vector<double> medians;
    unordered_map<int, int> hash_table;
    priority_queue<int> lo;                                 // max heap
    priority_queue<int, vector<int>, greater<int> > hi;     // min heap

    int i = 0;      // index of current incoming element being processed

    // initialize the heaps
    while (i < k)
        lo.push(nums[i++]);
    for (int j = 0; j < k / 2; j++) {
        hi.push(lo.top());
        lo.pop();
    }

    while (true) {
        // get median of current window
        medians.push_back(k & 1 ? lo.top() : ((double)lo.top() + (double)hi.top()) * 0.5);

        if (i >= nums.size())
            break;                          // break if all elements processed

        int out_num = nums[i - k],          // outgoing element
            in_num = nums[i++],             // incoming element
            balance = 0;                    // balance factor

        // number `out_num` exits window
        balance += (out_num <= lo.top() ? -1 : 1);
        hash_table[out_num]++;

        // number `in_num` enters window
        if (!lo.empty() && in_num <= lo.top()) {
            balance++;
            lo.push(in_num);
        }
        else {
            balance--;
            hi.push(in_num);
        }

        // re-balance heaps
        if (balance < 0) {                  // `lo` needs more valid elements
            lo.push(hi.top());
            hi.pop();
            balance++;
        }
        if (balance > 0) {                  // `hi` needs more valid elements
            hi.push(lo.top());
            lo.pop();
            balance--;
        }

        // remove invalid numbers that should be discarded from heap tops
        while (hash_table[lo.top()]) {
            hash_table[lo.top()]--;
            lo.pop();
        }
        while (!hi.empty() && hash_table[hi.top()]) {
            hash_table[hi.top()]--;
            hi.pop();
        }
    }

    return medians;
}

int main()
{
    vector<int> nums = {1,3,-1,-3,5,3,6,7}; //[1.00000,-1.00000,-1.00000,3.00000,5.00000,6.00000]
    int k =3;

    // nums = {1,4,2,3};
    // k = 4;

    nums = {5,5,8,1,4,7,1,3,8,4};
    k = 8;

    // nums = {2147483647,2147483647};
    // k=2;
    for(auto a : medianSlidingWindow2(nums,k))
    {
        printf("%f ",a);
    }
    printf("\n");

    return 0;
}