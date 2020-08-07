//1482. 制作 m 束花所需的最少天数

#include <cstdio>
#include <vector>

using namespace std;

bool check(vector<int>& bloomDay,int day,int m,int k)
{
    int start = -1;
    int r = 0;
    for(int i=0;i<bloomDay.size();++i)
    {
        if(bloomDay[i] <= day)
        {
            if(start == -1)
            {
                start = i;
            }

            if(i-start+1 >= k)
            {
                ++r;
                start = -1;
            }
        }
        else
        {
            start = -1;
        }
    }

    return r >= m;
}

int minDays(vector<int>& bloomDay, int m, int k) {
    //思路：哎，二分，哈哈哈
    //第i天符合要求，则第i+1天也符合

    if(m*k> bloomDay.size())
    {
        return -1;
    }

    int left = 0,right=1000000000;
    while(left < right)
    {
        int mid = left + (right-left)/2;
        if(check(bloomDay,mid,m,k))
        {
            right = mid;
        }
        else
        {
            left = mid+1;
        }
    }

    return left;
}

int main()
{
    vector<int> bloomDay = {1,10,3,10,2};
    int m = 3, k = 1; //3

    bloomDay = {1,10,3,10,2}, m = 3, k = 2; //-1

    bloomDay = {7,7,7,7,12,7,7}, m = 2, k = 3;//12

    bloomDay = {1,10,2,9,3,8,4,7,5,6}, m = 4, k = 2;//9

    bloomDay = {1000000000,1000000000}, m = 1, k = 1;//1000000000

    printf("%d\n",minDays(bloomDay,m,k));

    return 0;
}