//leetcode 962. 最大宽度坡

#include <cstdio>
#include <vector>
#include <stack>
using namespace std;

int maxWidthRamp(vector<int>& A) {
    //思路：直接做法是N的平方复杂度
    //单调栈可以考虑,先排序

    if(A.empty())
    {
        return 0;
    }

    vector<int> v(A.size());
    for(int i=0;i<A.size();++i)
    {
        v[i] = i;
    }
    sort(v.begin(),v.end(),[&](int a,int b){
       return A[a] < A[b] || (A[a] == A[b] && a < b); 
    });

    // for(auto a : v)
    // {
    //     printf("%d ",a);
    // }
    // printf("\n");
    int res = 0;
    int mxp = v[0];
    for(int i=1;i<A.size();++i)
    {
        if(v[i] < mxp)
        {
            mxp = v[i];
        }
        else
        {
            res = max(res,v[i] - mxp);
        }
        
    }

    return res;
}

//这个思路很巧妙，从右往左
int maxWidthRamp2(vector<int>& A) {
    //思路：单调递减栈
    stack<int> sk;
    sk.push(0);
    for(int i=1;i<A.size();++i)
    {
        if(A[i] <= A[sk.top()])
        {
            sk.push(i);
        }
    }

    int res = 0;
    for(int i=A.size()-1;i>=0;--i)
    {
        while(!sk.empty() && A[i] >= A[sk.top()])
        {
            res = max(res,i - sk.top());
            sk.pop();
        }
    }

    return res;
}

int maxWidthRamp3(vector<int>& A) {
    //动归：dp[i]
}

int main()
{
    vector<int> A ={6,0,8,2,1,5}; //4
    A = {9,8,1,0,1,9,4,0,4,1};  //7
    A = {3,28,15,1,4,12,6,19,8,15,3,9,6,4,13,12,6,12,10,1,2,1,4,1,4,0,0,1,1,0};
    printf("%d\n",maxWidthRamp2(A));
    return 0;
}