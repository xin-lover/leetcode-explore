//leetcode 967. 连续差相同的数字

#include <cstdio>
#include <vector>

using namespace std;

void numsSameConsecDiff(int N,int K, int index, int current, int last,vector<int>& res)
{
    if(index >= N)
    {
        res.push_back(current);
        return;
    }

    if(last + K <= 9)
    {
        numsSameConsecDiff(N,K,index+1,current*10 + last + K,last+K,res);
    }

    if(K != 0 && last - K >= 0) //去重
    {
        numsSameConsecDiff(N,K,index+1,current*10 + last - K,last-K,res);
    }
}

vector<int> numsSameConsecDiff(int N, int K) {
    //思路：先不考虑前导0，那么前面一位的数字能确定后面可能的数字，所以使用回溯法即可

    if(N < 1)
    {
        return {};
    }

    if(N == 1)
    {
        return {0,1,2,3,4,5,6,7,8,9};
    }

    vector<int> res;
    for(int i=1;i<=9;++i)
    {
        numsSameConsecDiff(N,K,1,i,i,res);
    }

    return res;
}

int main()
{
    vector<int> res = numsSameConsecDiff(3,7);//[181,292,707,818,929]
    res = numsSameConsecDiff(2,1);//[10,12,21,23,32,34,43,45,54,56,65,67,76,78,87,89,98]
    for(auto a : res)
    {
        printf("%d ",a);
    }
    printf("\n");
    return 0;
}

