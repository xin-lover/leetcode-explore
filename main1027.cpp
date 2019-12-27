//给定一个整数数组 A，返回 A 中最长等差子序列的长度。

#include <cstdio>
#include <vector>
#include <unordered_map>

using namespace std;

int longestArithSeqLength(vector<int>& A) {
    //思路：假设所有元素都不相同，那么我们直接记录每个元素的差即可
    //但问题是，这记录的是所有差值相同的数对，也就是多个等差数列的集合
    //这是不行的，而且重复元素需要额外处理

    sort(A.begin(),A.end());

    unordered_map<int,int> um;
    for(int i=0;i<A.size();++i)
    {
        for(int j=i+1;j<A.size();++j)
        {
            int t = A[j] - A[i];
            ++um[t];
        }
    }

    int res =0;
    for(auto it = um.begin();it!=um.end();++it)
    {
        printf("t:%d %d ",it->first,it->second);
        res = max(it->second,res);
    }
    printf("\n");

    return res+1;
}

int longestArithSeqLength2(vector<int>& A) {
    //思路：子序列是可以不连续但要保持序列的顺序
    //采用动归的思想，使用map，map存储的是以包含当前节点，但差值为key的元素数量信息

    vector<unordered_map<int,int>> dp(A.size());

    for(int i=1;i<A.size();++i)
    {
        for(int j=0;j<i;++j)
        {
            int d = A[i]-A[j];
            dp[i][d] = dp[j][d]+1;
        }
    }

    int res =0;
    for(int i=0;i<dp.size();++i)
    {
        for(auto it = dp[i].begin();it !=dp[i].end();++it)
        {
            res = max(res,it->second);
        }
    }

    return res+1;
}

int longestArithSeqLength3(vector<int>& A) 
    //思路：使用map存储A的元素，然后确定前两项元素，构建等差数列
    //这里要注意相同元素的存在,这样其实写起来也不简单，需要map嵌套一个vector

    // unordered_map<int,int> um;
    // for(int i=0;i<A.size();++i)
    // {
    //     um[A[i]]=i;
    // }
}

int main()
{
    vector<int> v= {3,6,9,12};//4
    v = {9,4,7,2,10};//3
    // v = {20,1,15,3,10,5,8}; //4
    printf("%d\n",longestArithSeqLength2(v));
    return 0;
}