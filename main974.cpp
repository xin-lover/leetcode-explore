//leetcode 974. 和可被 K 整除的子数组

#include <cstdio>
#include <vector>
#include <unordered_map>

using namespace std;

int subarraysDivByK(vector<int>& A, int K) {
    //思路：连续，非空的子数组，枚举法是n的平方复杂度
    //令P[i]为0到i的子数组的和，那么子数组i到j的和能整除K，即(P[j]-P[i])%K==0表示(P[i]%K)==(P[j]%K)
    //也就是P[i]和P[j]同余

    int sum = 0;
    unordered_map<int,int> um;  //可以不用hash，使用一个K长度的数组即可
    for(int i=0;i<A.size();++i)
    {
        sum += A[i];
        int m = sum % K;
        if(m < 0)
        {
            m+=K;
        }
        ++um[m];
    }

    int res = 0;
    for(auto it=um.begin();it!=um.end();++it)
    {
        printf("%d %d\n",it->first,it->second);
        res += (it->second)*(it->second - 1) / 2;
    }

    res += um[0];

    return res;
}

int main()
{
    vector<int> v = {4,5,0,-2,-3,1};
    int K = 5; //7
    // v = {8,9,7,8,9};
    // K = 8; //7
    printf("%d\n",subarraysDivByK(v,K));
    return 0;
}