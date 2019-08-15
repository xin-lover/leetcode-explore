//leetcode 823. 带因子的二叉树

#include <cstdio>
#include <vector>
#include<unordered_map>

using namespace std;

int numFactoredBinaryTrees(vector<int>& A, int root,unordered_map<int,int>& dp)
{
    if(dp.find(root) == dp.end())
    {
        return 0;
    }
    else
    {
        if(dp[root] != -1)
        {
            return dp[root];
        }
    }
    
    //优化
    // if(find(A.begin(),A.end(),root) == A.end())
    // {
    //     return 0;
    // }
    
    long long res = 1;
    for(int i=0;A[i]<root;++i)
    {
        // if(A[i] >= root)//可以考虑对A排序，则大于root就可以break
        // {
        //     continue;
        // }

        int r = root % A[i];
        if(r == 0)
        {
            long long left = numFactoredBinaryTrees(A,A[i],dp);
            long long right = numFactoredBinaryTrees(A,root / A[i],dp);
            res +=  left * right ;
        }
    }

    static int mx = 1000000007;
    res %= mx;
    dp[root] = res;
    return res;
}

int numFactoredBinaryTrees(vector<int>& A) {
    //思路：左右孩子互换一下也是一种
    //所以一个树类型数量是左孩子的类型数量*右孩子的类型数量*2
    //最终的策略就变为：确定root，然后分解为两个数，递归进行
    //同时记录root节点的结果，避免重复计算（动归思想）

    sort(A.begin(),A.end());
    unordered_map<int,int> dp;
    for(int i=0;i<A.size();++i)
    {
        dp[A[i]] = -1;
    }
    int res = 0;
    for(int i=0;i<A.size();++i)
    {
        res += numFactoredBinaryTrees(A,A[i],dp);
    }
    return res;

}

int numFactoredBinaryTrees2(vector<int>& A) {
    //思路：动归，首先对A进行排序，每一个数都只能分解为更小的数，而且A中的数都大于1，所以只需要遍历其中的一半元素
    //递归公式还是那个：假设root=left*right,则dp[root] = dp[left]*dp[right]*2;

    if(A.empty())
    {
        return 0;
    }
    sort(A.begin(),A.end());

    unordered_map<int,int> dp;
    dp[A[0]] = 1;

    int res = 1;
    for(int i=1;i<A.size();++i)
    {
        long long t = 1;
        for(int j=0;j<i;++j)
        {
            int q = A[i] / A[j];
            int r = A[i] - q * A[j];
            if(r == 0)
            {
                printf("q:%d dp[q]:%d\n",q,dp[q]);
                t += static_cast<long long>(dp[A[j]]) * dp[q];
                while(t > 1000000007)
                {
                    t -= 1000000007;
                }
            }
        }

        printf("A[i]:%d dp[A[i]]:%d\n",A[i],dp[A[i]]);
        dp[A[i]] = t;
        res += t;
        while(res > 1000000007)
        {
            res -= 1000000007;
        }
    }

    return res;
}

int main()
{
    vector<int> A = {2,4};
    A = {2,4,5,10};
    // A = {18,3,6,2};
    printf("%d\n",numFactoredBinaryTrees2(A));
    return 0;
}