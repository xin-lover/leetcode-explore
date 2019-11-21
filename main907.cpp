//leetcode 907. 子数组的最小值之和

#include <cstdio>
#include <vector>
#include <cmath>
#include <map>
#include <queue>
#include <stack>

using namespace std;

int sumSubarrayMins(vector<int>& A) {
    //思路：相当于如何快速的求最小值，先用最简单的做法

    const int uplimit=pow(10,9) + 7;
    int n = A.size();

    int res = 0;
    for(int i=0;i<n;++i)
    {
        int mn = A[i];
        for(int j=i;j<n;++j)
        {
            mn = min(mn,A[j]);
            res+=mn;
            if(res > uplimit)
            {
                res-=uplimit;
            }
        }
    }

    return res;
}

int help2(vector<int>& A,int start,int end)
{
    //求以end结尾的数列的结果
    printf("start:%d end:%d\n",start,end);
    const int uplimit=pow(10,9) + 7;
    int res = 0;
    int mn_index =end;
    for(int i=start;i<=end;++i)
    {
        if(A[i] <= A[mn_index])
        {
            res += (i-start+1) * A[i];
            mn_index = i;
        }
        else
        {
            res += (mn_index-start+1) * A[mn_index];
            res += help2(A,mn_index+1,end); //重复计算了，不行
            
        }
        
        if(res > uplimit)
        {
            res -= uplimit;
        }
    }

    

    return res;
}

int sumSubarrayMins2(vector<int>& A) {
    //思路：O(n^2)的复杂度不行，所以必须降低复杂度
    //sub(i,j)表示一个子序列，如果A[k]是sub(i,j)的最小值，则包含A[k]的子序列的最小值就确定了
    //sub(0,0),A[0]最小，
    //sub(0,i),新的可能的子序列都是以A[i]结尾，如果A[i]是最小的，直接使用最小值*新的子序列数量求解
    //而如果A[i]不是最小的，假设最小值是A[j],则有A[i]和A[j]的数列可直接求解，
    //问题就变成了如何求解j+1到i之间的如何求解?
    //使用一个数组记录当前最小值到当前位置的最小值，即假设0到i的最小值在k位置，则dp[i]表示sub(k,i)的最小值
    
    //思考2:假设sum(i)表示以i结尾的子数列的最小值的和，如果A[i+1]>=A[i]]则sum(i+1)=sum(i)+A[i+1]
    //如果A[i+1]<A[i],则往回找A[j],A[j]<=A[i+1]，而找到之前A[j]都是最小的，所以结果就出来了

    const int uplimit=pow(10,9) + 7;
    int res = A[0];
    vector<int> dp(A.size(),0);
    dp[0] = A[0];
    for(int i=1;i<A.size();++i)
    {
        long long sum = 0;
        if(A[i] >= A[i-1])
        {
            sum = dp[i-1] + A[i];
        }
        else
        {
            //这里需要优化,因为如果是递减，则比较次数一个都没少
            int j;
            for(j=i-1;j>=0;--j)
            {
                if(A[i] >= A[j])
                {
                    break;
                }
            }

            if(j < 0)
            {
                sum = A[i] * (i+1);
            }
            else
            {
                sum = dp[j] + A[i]*(i-j);
            }
        }

        sum %= uplimit;
        dp[i] = sum;
        res+=sum;
        res %= uplimit;
    }

    return res;
}

int sumSubarrayMins3(vector<int>& A) {
    //思路：计算出所有以A[i]为最小元素的子序列也就是存在j<=i<=k,
    //A[j],A[j+1] ……>=A[i];
    //A[i+1],A[i+2]……A[k]>=A[i]
    //那么包含A[i]的子序列个数就是(i-j+1) * (k-i+1)

    const int uplimit=pow(10,9) + 7;
    stack<int> sk;
    vector<int> prev(A.size());
    for(int i =0;i<A.size();++i)
    {
        while(!sk.empty() && A[i] <= A[sk.top()])
        {
            sk.pop();
        }

        prev[i] = sk.empty() ? -1 : sk.top();
        sk.push(i);
    }

    vector<int> next(A.size());
    stack<int> skk;
    for(int i=A.size()-1;i>=0;--i)
    {
        while(!skk.empty() && A[i] < A[skk.top()])
        {
            skk.pop();
        }

        next[i] = skk.empty() ? A.size() : skk.top();
        skk.push(i);
    }

    long long t = 0;
    for(int i=0;i<A.size();++i)
    {
        t += ((i-prev[i]) * (next[i] - i) * A[i]);
        t %= uplimit;
    }

    return t;
}

int sumSubarrayMins4(vector<int>& A) {
    //思路：最小栈
    const int uplimit=pow(10,9) + 7;

    stack<pair<int,int>> sk;

    
    int dot = 0;
    int res = 0;
    for(int i=0;i<A.size();++i){
        int count=1;
        while(!sk.empty() && sk.top().first >= A[i])
        {
            auto a = sk.top();
            sk.pop();
            count += a.second;
            dot -= a.first * a.second;
        }

        sk.push({A[i],count});
        dot += A[i]*count;
        res += dot;
        res %= uplimit;

    }

    return res;
}


int main()
{
    vector<int> v = {3,1,2,4};
    // v = {71,55,82,55};
    v = {59,91};
    printf("%d\n",sumSubarrayMins4(v));
    return 0;
}