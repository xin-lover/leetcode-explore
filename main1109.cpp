//1109. 航班预订统计

#include <cstdio>
#include <vector>

using namespace std;

vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
    //思路：直接累加？

    //结果超时
    vector<int> res(n,0);
    for(int i=0;i<bookings.size();++i)
    {
        for(int j=bookings[i][0];j<=bookings[i][1];++j)
        {
            res[j-1]+=bookings[i][2];
        }
    }   

    return res;
}

vector<int> corpFlightBookings2(vector<vector<int>>& bookings, int n) {
    //思路：在每条记录看成上和下，上是正数，下是负数，那么我们只需要顺序遍历计算即可

    vector<int> tmp(n+1,0);
    for(int i=0;i<bookings.size();++i)
    {
        tmp[bookings[i][0]-1]+=bookings[i][2];
        tmp[bookings[i][1]]-=bookings[i][2];
    }   

    vector<int> res(n);
    int sum = 0;
    for(int i=0;i<n;++i)
    {
        sum += tmp[i];
        res[i] = sum;
    }
    
    return res;
}

int main()
{
    vector<vector<int>> bookings = {{1,2,10},{2,3,20},{2,5,25}};
    int n = 5;
    vector<int> res = corpFlightBookings2(bookings,n);//10 55 45 25 25 
    for(auto a : res)
    {
        printf("%d ",a);
    }
    printf("\n");
    return 0;
}