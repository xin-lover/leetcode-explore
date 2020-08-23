//1508. 子数组和排序后的区间和

#include <cstdio>
#include <vector>
#include <set>

using namespace std;

int rangeSum(vector<int>& nums, int n, int left, int right) {
    //思路：非空连续子数组,使用multiset试试

    static const int kLimit=1000000007;
    multiset<int> st;
    for(int i=0;i<nums.size();++i)
    {
        int sum = 0;
        for(int j=i;j<nums.size();++j)
        {
            sum += nums[j];
            st.insert(sum);
        }
    }

    int sum = 0;
    multiset<int>::iterator start = st.begin();
    auto end = start;
    for(int i=0;i<left-1;++i)
    {
        start++;
    }
    for(int i=0;i<right;++i)
    {
        end++;
    }
    
    for(auto it = start;it!=end;++it)
    {
        sum += *it;
        if(sum >= kLimit)
        {
            sum -= kLimit;
        }
    }

    return sum;
}

//前缀和思路,这个思路很巧妙，特别在二分查找的时候和找小于某个和的子数组和。。。高明
// 方法一中，首先计算每个连续子数组的和，然后计算区间和。其实，并不需要计算每个连续子数组的和，而是可以将问题转化成求所有的子数组的和当中的最小的 kk 个元素之和，对于这道题，分别计算 k=\textit{right}k=right 和 k=\textit{left}-1k=left−1 的结果，然后计算两者之差，即可得到区间和。
// 构造两个数组，第一个数组 \textit{prefixSums}prefixSums 存储原始数组的前缀和，第二个数组 \textit{prefixPrefixSums}prefixPrefixSums 存储第一个数组的前缀和。
// 要求出所有的子数组的和当中的最小的 kk 个元素之和，首先需要得到第 kk 小的元素，即第 kk 小的子数组的和。可以通过对第一个数组使用二分查找 + 双指针的方法得到第 kk 小的子数组的和，其思想与「378. 有序矩阵中第K小的元素」类似。
// 「有序矩阵中第K小的元素」使用双指针在每行和每列元素均按升序排序的二维矩阵中寻找不超过目标值的元素个数，这道题则是使用双指针借助第一个数组寻找有多少个子数组的和不超过目标值。具体做法是，对于从 00 到 n-1n−1 的每个下标 ii，找到最大的下标 jj 使得原始数组从下标 ii 到下标 j-1j−1 范围的子数组的元素之和不超过目标值（子数组的元素之和可以通过第一个数组在 O(1)O(1) 的时间内计算得到结果），由于原始数组的元素都是正整数，因此对于任意从下标 ii 开始且长度不超过 j-ij−i 的子数组，其元素之和都不超过目标值，这样就能得到 j-ij−i 个和不超过目标值的子数组。遍历完 ii 的所有可能取值之后，即可知道有多少个子数组的和不超过目标值。目标值的选取则使用二分查找的方式，目标值的最终取值即为第 kk 小的子数组的和。
// 得到第 kk 小的子数组的和之后，即可求所有的子数组的和当中的最小的 kk 个值之和。令第 kk 小的子数组的和是 \textit{num}num，考虑到可能有多个子数组的和都等于第 kk 小的子数组的和，因此分成两步计算。
// 第一步计算所有严格小于 \textit{num}num 的子数组的和的个数以及它们的和，假设有 \textit{count}count 个严格小于 \textit{num}num 的子数组的和，它们的和是 \textit{sum}sum，可以借助构造的两个数组，使用双指针计算得到 \textit{count}count 和 \textit{sum}sum 的值。具体做法是，对于从 00 到 n-1n−1 的每个下标 ii，找到最大的下标 jj 使得原始数组从下标 ii 到下标 j-1j−1 范围的子数组的元素之和不超过 \textit{num}num（子数组的元素之和可以通过第一个数组在 O(1)O(1) 的时间内计算得到结果），由于原始数组的元素都是正整数，因此对于任意从下标 ii 开始且长度不超过 j-ij−i 的子数组，其元素之和都不超过目标值，这样就能得到 j-ij−i 个和不超过目标值的子数组，这些子数组的和之和计算如下：
// \textit{prefixPrefixSums}[j] - \textit{prefixPrefixSums}[i] - \textit{prefixSums}[i] * (j - i)
// prefixPrefixSums[j]−prefixPrefixSums[i]−prefixSums[i]∗(j−i)
// 其中，\textit{prefixPrefixSums}[j] - \textit{prefixPrefixSums}[i]prefixPrefixSums[j]−prefixPrefixSums[i] 的结果等价于 \textit{prefixSums}prefixSums 从下标 i+1i+1 到下标 jj 范围内的所有元素之和，对于 i+1 \le m \le ji+1≤m≤j，\textit{prefixSums}[m]prefixSums[m] 表示原始数组从下标 00 到下标 m-1m−1 范围内的所有元素之和，因此，\textit{prefixPrefixSums}[j] - \textit{prefixPrefixSums}[i]prefixPrefixSums[j]−prefixPrefixSums[i] 的结果为原始数组的 j-ij−i 个前缀之和，每个前缀的结束下标依次从 ii 到 j-1j−1。由于只需要计算原始数组的从下标 ii 开始且长度不超过 j-ij−i 的子数组，因此还需要对这 j-1j−1 个前缀中的每一项减去原始数组从下标 00 到下标 i-1i−1 范围内的所有元素之和才能得到对应的子数组之和，原始数组从下标 00 到下标 i-1i−1 范围内的所有元素之和为 \textit{prefixSums}[i]prefixSums[i]，因此要减去 \textit{prefixSums}[i] * (j - i)prefixSums[i]∗(j−i)，才能得到 j-ij−i 个和不超过目标值的子数组的和之和。
// 遍历完 ii 的所有可能取值之后，即可得到所有严格小于 \textit{num}num 的子数组的和的个数以及它们的和。
// 第二步考虑最小的 kk 个子数组的和当中剩下的等于 \textit{num}num 的子数组的和，这些子数组的和之和等于 \textit{num}*(k-\textit{count})num∗(k−count)。在第一步计算得到的 \textit{sum}sum 的基础上令 \textit{sum}=\textit{sum}+\textit{num}*(k-\textit{count})sum=sum+num∗(k−count)，则 \textit{sum}sum 的值即为所有的子数组的和当中的最小的 kk 个元素之和。
class Solution {
public:
    static constexpr int MODULO = 1000000007;

    int rangeSum(vector<int>& nums, int n, int left, int right) {
        vector<int> prefixSums = vector<int>(n + 1);
        prefixSums[0] = 0;
        for (int i = 0; i < n; i++) {
            prefixSums[i + 1] = prefixSums[i] + nums[i];
        }
        vector<int> prefixPrefixSums = vector<int>(n + 1);
        prefixPrefixSums[0] = 0;
        for (int i = 0; i < n; i++) {
            prefixPrefixSums[i + 1] = prefixPrefixSums[i] + prefixSums[i + 1];
        }
        return (getSum(prefixSums, prefixPrefixSums, n, right) - getSum(prefixSums, prefixPrefixSums, n, left - 1)) % MODULO;
    }

    int getSum(vector<int>& prefixSums, vector<int>& prefixPrefixSums, int n, int k) {
        int num = getKth(prefixSums, n, k);
        int sum = 0;
        int count = 0;
        for (int i = 0, j = 1; i < n; i++) {
            while (j <= n && prefixSums[j] - prefixSums[i] < num) {
                j++;
            }
            j--;
            sum += prefixPrefixSums[j] - prefixPrefixSums[i] - prefixSums[i] * (j - i);
            sum %= MODULO;
            count += j - i;
        }
        sum += num * (k - count);
        return sum;
    }

    int getKth(vector<int>& prefixSums, int n, int k) {
        int low = 0, high = prefixSums[n];
        while (low < high) {
            int mid = (high - low) / 2 + low;
            int count = getCount(prefixSums, n, mid);
            if (count < k) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        return low;
    }

    int getCount(vector<int>& prefixSums, int n, int x) {
        int count = 0;
        for (int i = 0, j = 1; i < n; i++) {
            while (j <= n && prefixSums[j] - prefixSums[i] <= x) {
                j++;
            }
            j--;
            count += j - i;
        }
        return count;
    }
};

//优先队列也会一个思路，也就是n路子数组，分别是以所以0，1，2，……n-1开头的
//每次更新最小的那一路，比如nums={1,2,3};
//一开始分别是1,2,3，然后优先更新1开头这一路，变为1+2，队列中删除1，加入1+2；
//再更新，发现2是最小的，同理，删除2，添加2+3
//再更新，发现两个3，随意，比如选择第1路的3，则删除3，添加1+2+3
//所以优先队列中存储的是每一路的当前子数组和及其下标
// class Solution {
//     public int rangeSum(int[] nums, int n, int left, int right) {
//         int MOD = 1_000_000_007;
//         PriorityQueue<int[]> pq = new PriorityQueue<>(n, (a, b) -> Integer.compare(a[0], b[0]));
//         for (int i = 0; i < nums.length; i++) {
//             pq.offer(new int[] {nums[i], i});
//         }
//         int ans = 0;
//         int count = 0;
//         while (++count <= right && !pq.isEmpty()) {
//             int[] cur = pq.poll();
//             if (count >= left) {
//                 ans += cur[0] % MOD;
//             }
//             if (cur[1] < n - 1) {
//                 pq.offer(new int[]{cur[0] + nums[cur[1] + 1], cur[1] + 1});
//             }
//         }
//         return ans;
//     }
// }

int main()
{
    vector<int> nums = {1,2,3,4};
    printf("%d\n",rangeSum(nums,4,1,5));    //13
    printf("%d\n",rangeSum(nums,4,3,4));    //6
    printf("%d\n",rangeSum(nums,4,1,10));    //50
    return 0;
}