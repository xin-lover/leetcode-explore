//327. 区间和的个数

#include <cstdio>
#include <vector>
#include <set>

using namespace std;

int countRangeSum(vector<int>& nums,int left,int right, int lower, int upper) {

    if(left > right)
    {
        return 0;
    }
    if(left == right)
    {
        return (nums[left]>=lower && nums[left]<=upper) ? 1 : 0;
    }

    int center = left + (right-left)/2;
    int lcount = countRangeSum(nums,left,center,lower,upper);
    int rcount = countRangeSum(nums,center+1,right,lower,upper);

    int res = lcount + rcount;
    long long t = 0;
    for(int i=center;i>=left;--i) //复杂度并未下降
    {
        t += static_cast<long long>(nums[i]);
        long long r = t;
        for(int j=center+1;j<=right;++j)
        {
            r+=static_cast<long long>(nums[j]);
            res += (r>=lower && r<=upper ? 1 : 0);
        }
    }

    return res;
}

int countRangeSum(vector<int>& nums, int lower, int upper) {
    //思路：有负数，不然就是前缀和+二分
    //考虑分治，把区间分开两边，那么符合要求的区间就是两侧符合要求的区间和包含中间相邻两个数的区间
    //利用二叉树数据结构，其实还是二分

    multiset<long long> st;

    int res = 0;
    long long t = 0;
    for(int i=0;i<nums.size();++i)
    {
        t+= nums[i];

        if(t >= lower && t <= upper)
        {
            ++res;
        }

        if(!st.empty())
        {
            auto it1 = st.lower_bound(t - upper);
            auto it2 = st.upper_bound(t - lower);

            res += std::distance(it1,it2);
        }

        st.insert(t);
    }

    return res;

    
}

int lowbit(int x)
{
    return x & (-x);
}

void add(vector<int>& tree,int index,int val)
{
    int n = tree.size();
    for(int x = index;x < n;x += lowbit(x))
    {
        tree[x] += val;
    }
}

int find(vector<int>& tree,int x)
{
    int res = 0;
    for(;x>0;x-=lowbit(x))
    {
        res += tree[x];
    }

    return res;
}

//找最后一个小于等于target的索引,注意nums是去重了的，否则是不对的。。。 
int binary_search1(vector<long long>& nums,long long target)
{
    int left = 0,right=nums.size()-1;
    while(left < right)
    {
        int mid = left + (right-left) / 2;
        if(nums[mid] <= target)
        {
            left = mid+1;
        }
        else
        {
            right = mid;
        }
    }

    if(nums[left] > target)
    {
        return left-1;
    }

    return nums.size()-1;
}

//找小于target的最后一个索引
int binary_search2(vector<long long>& nums,long long target)
{
    int left = 0,right=nums.size()-1;
    while(left < right)
    {
        int mid = left + (right-left) / 2;
        if(nums[mid] < target)
        {
            left = mid+1;
        }
        else
        {
            right = mid;
        }
    }

    if(nums[left] >= target)
    {
        return left-1;
    }
    else
    {
        return left;
    }
}



int countRangeSum2(vector<int>& nums, int lower, int upper) {
    //思路：前缀和+离散化+树状数组
    //lower<=presums[i] - presums[j]<=upper
    //对于所以i来说要找满足 presums[i]-upper <= presums[j] <= presums[i]-lower
    //这里面其实没那么复杂，但把离散化什么的搞进来，复杂的很
    //步骤：
    //1.求从索引0开始的所有前缀和；
    //2.对这些前缀和排序，去重；
    //3.这里面就开始了离散化这个不接地气概念了，其实是开始创建和更新树状数组，这个树状数组存储的不是前缀和，而是符合要求的区间的个数
    //问题是如何更新树状数组？这就是应用上面那个表达式的时候了，对于索引i，可知其前缀和，用presums[i]-upper和presums[i]-lower
    //通过二分法在第2步得出的数组中查找这两个值的位置，两个位置的差即符合要求区间的个数
    //这里有意思的点就是树状数组的更新，注意树状数组存的是前缀和的数量（与第2步的前缀和数组对应），所以更新的值是加1

    vector<long long> preSums(nums.size()+1,0);
    long long t = 0;
    for(int i=0;i<nums.size();++i)
    {
        t += nums[i];
        preSums[i] = t;
    }

    sort(preSums.begin(),preSums.end());
    preSums.erase(unique(preSums.begin(),preSums.end()),preSums.end());

    for(auto a : preSums)
    {
        printf("%lld ",a);
    }
    printf("\n");

    vector<int> tree(preSums.size()+1,0);
    add(tree,binary_search1(preSums,0)+1,1);

    int res = 0;
    t = 0;
    for(int i=0;i<nums.size();++i)
    {
        t += nums[i];
        int idx1 = binary_search2(preSums,t-upper)+1;
        int idx2 = binary_search1(preSums,t-lower)+1;
        printf("t:%d\n",t);
        printf("ww:%d %d\n",idx1,idx2);

        if(idx2!=0)
        {
            if(idx1 == 0)
            {
                res += find(tree,idx2);
            }
            else
            {
                res += find(tree,idx2) - find(tree,idx1);
            }
            
        }

        int idxx = binary_search1(preSums,t)+1;
        add(tree,idxx,1);
    }

    return res;
}

// typedef long long LL;
// class Solution {
// public:
    
//     vector<LL> data;
//     vector<int> tr;
    
//     // 查找小于等于x的第一个数的下标，找不到返回0
//     int binary_search1(LL x) {
        
//         int l = 0, r = data.size() - 1;
//         while (l < r) {
//             int mid = l + r + 1 >> 1;
//             if (data[mid] <= x) l = mid;
//             else r = mid - 1;
//         }
//         if (l == 0 && data[0] > x) return 0;
//         else return l + 1;
//     }
    
//     // 查找小于x的第一个数的下标，找不到返回0
//     int binary_search2(LL x) {
//         int l = 0, r = data.size() - 1;
//         while (l < r) {
//             int mid = l + r + 1 >> 1;
//             if (data[mid] < x) l = mid;
//             else r = mid - 1;
//         }
//         if (l == 0 && data[0] >= x) return 0;
//         else return l + 1;
//     }
    
//     int lowbit(int x) {
//         return x & -x;
//     }
    
//     int find(int x) {
//         int ans = 0;
//         for (int i = x; i; i -= lowbit(i)) ans += tr[i];
//         return ans;
//     }
    
//     void add(int x, int c) {
//         int n = tr.size() - 1;
//         for (int i = x; i <= n; i += lowbit(i)) tr[i] += c;
//     }
    
//     int countRangeSum(vector<int>& nums, int lower, int upper) {
//         int n = nums.size();
//         LL sum = 0;
//         vector<LL> s(n);
//         for (int i = 0; i < n; i ++) {
//             sum += nums[i];
//             s[i] = sum;
//         }
//         data = s;
//         data.push_back(0);
//         sort(data.begin(), data.end());
//         data.erase(unique(data.begin(), data.end()), data.end());
//         tr = vector<int>(data.size() + 1);
        
// //         for (int i = 0; i < data.size(); i ++) cout << data[i] << " ";
// //         cout << endl;
//         int ans = 0;
//         int idx_zero = binary_search1(0);
//         add(idx_zero, 1);
//         for (auto x : s) {
//             LL a = x - upper, b = x - lower;
//             int idxa = binary_search2(a), idxb = binary_search1(b);
//             int idxx = binary_search1(x);
//             // cout << idxa << " " << idxb << " " << idxx << endl;
//             if (idxb != 0) {
//                 if (idxa == 0) ans += find(idxb);
//                 else ans += find(idxb) - find(idxa);
//             }
//             add(idxx, 1);   
//             // cout << ans << endl;
//         }
//         return ans;
//     }
// };

int main()
{
    vector<int> nums = {-2,5,-1}; 
    int lower = -2, upper = 2;    //3

    // nums = {};
    // lower = 0,upper = 0;

    nums = {2147483647,-2147483648,-1,0};
    lower = -1,upper = 0; //4

    // nums = {-1,1};
    // lower = 0,upper = 0; //1

    // Solution s;
    printf("%d\n",countRangeSum2(nums,lower,upper));
    return 0;
}