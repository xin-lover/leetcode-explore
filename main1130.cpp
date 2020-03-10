//1130. 叶值的最小代价生成树

#include<cstdio>
#include<vector>
#include<stack>

using namespace std;

int mctFromLeafValues(vector<int>& arr,int left,int right,int& res,vector<vector<pair<int,int>>>& dp)
{
    if(dp[left][right].first != -1)
    {
        res = dp[left][right].second;
        return dp[left][right].first;
    }
    if(left == right)
    {
        dp[left][right] = {arr[left],0};
        return arr[left];
    }

    int max_v = 0,min_res = INT_MAX;
    for(int i=left;i<right;++i)
    {
        int left_res=0,right_res=0;
        int left_max = mctFromLeafValues(arr,left,i,left_res,dp);
        int right_max = mctFromLeafValues(arr,i+1,right,right_res,dp);

        if(left_max * right_max + left_res + right_res < min_res)
        {
            min_res = left_max*right_max + left_res + right_res;
            max_v = max(left_max,right_max);
        }
    }

    res = min_res;
    dp[left][right] = {max_v,res};

    return max_v;
}

int mctFromLeafValues(vector<int>& arr) {
    //思路：树的问题我们可以递归，对于这道题我们可以回溯
    //因为只有2个和0个孩子节点，所以对于每个数组我们都可以分为两个数组，这两个数组的最大值的乘积是两个数组代表的子树的父节点的值
    //所以问题是如何划分，使用穷举法，但重复计算会很多，用动归的思想，存储中间结果

    int n = arr.size();

    vector<vector<pair<int,int>>> dp(n,vector<pair<int,int>>(n,{-1,-1}));
    int res = 0;
    mctFromLeafValues(arr,0,arr.size()-1,res,dp);

    return res;
}

int mctFromLeafValues2(vector<int>& arr) {
    //思路：

    int n = arr.size();

    vector<vector<pair<int,int>>> dp(n,vector<pair<int,int>>(n,{-1,-1}));
    int res = 0;
    mctFromLeafValues(arr,0,arr.size()-1,res,dp);

    return res;
}

int mctFromLeafValues3(vector<int>& arr) {
    //单调栈：可以把这个题看成把相邻的两个元素a和b，去掉小的那个，花费的代价是a*b,求最后只剩一个元素要花费的代价
    //这样可以使用一个单调栈
    // 单调栈的方法有点讨巧。
    // 以上是我的个人理解
    // 我们维护一个单调递减栈，单调递减栈有一个特性。
    // 如果我们遇到一个比栈顶元素大元素，于是乎就有了两种情况。
    // 我们就看前面3个。
    // 第一种情况：大 小 中，这样只会将小出栈。
    // 我们来算一下：
    // 大小放一块：大 * 小 + 大 * 中
    // 小中放一块：小 * 中 + 大 * 中
    // 所以把小和中放在一起得到的值更小。
    // 第二种情况： 中 小 大， 小 中 都会出栈
    // 中小放在一块：中 * 小 + 中 * 大
    // 小大放在一块：小 * 大 + 中 * 大
    // 因此把中小放在一起得到的值更小。
    // 由此得出结论如果遇到出栈情况，我们将小的那个(也就是栈顶元素)和它左边或右边较小的那个放在一起得到的答案是最优。
    // 同时，小的那个元素就不再需要了，我们只看大的那个元素可能还会和别的值相乘。
    // 最后将值放入栈后，栈内元素单调递减，于是就有了大 中 小,这个可以自己去证。会发现还是把中小放在一起最优。

    stack<int> sk;
    sk.push(INT_MAX);
    int ans = 0;
    for (int n : arr) {
        while (sk.top() < n)
        {
            int t = sk.top();
            sk.pop();
            printf("t:%d top:%d\n",t,sk.top());
            ans += t * min(sk.top(), n);
        } 
        sk.push(n);
    }
    while (sk.size() > 2)
    {
        int t = sk.top();
        sk.pop();
        ans += t * sk.top();
    } 
    return ans;
}

int main()
{
    vector<int> arr = {6,2,4};
    arr = {10,2,15,9,1,3,8,5,13,6,11,3,8,6,5,13,13,7};
    arr = {7,12,8,10};
    printf("%d\n",mctFromLeafValues3(arr));
    return 0;
}

    96           84
 84               96
7 12  8      7   12 8