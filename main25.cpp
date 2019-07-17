#include <cstdio>
#include <climits>
#include <algorithm>

using namespace std;

void backtrace(int n,int count,int& res)
{
    printf("n:%d\n",n);
    if(n == 1)
    {
        res = min(count,res);
        return;
    }
    if((n&1) == 1)
    {
        backtrace(n+1,count+1,res);
        backtrace(n-1,count+1,res);
    }
    else
    {
        backtrace(n/2,count+1,res);
    }
    
}

int aa(long long n)
{
    if(n==1)
    {
        return 0;
    }
    if((n&1) == 1)
    {
        return min(1+aa(n+1),1+aa(n-1));
    }
    else
    {
        return 1+aa(n/2);
    }
}
int integerReplacement(int n)
{
    //思路使用回溯法
    // int res = INT_MAX;
    // backtrace(n,0,res);

    // return res;

    //递归
    // if(n==1)
    // {
    //     return 0;
    // }
    // if((n&1) == 1)
    // {
    //     return min(1+integerReplacement(n+1),1+integerReplacement(n-1));
    // }
    // else
    // {
    //     return 1+integerReplacement(n/2);
    // }

    return aa(n);

}

int main()
{
    printf("res:%d\n",integerReplacement(2147483647));
    return 0;
}