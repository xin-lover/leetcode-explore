//1362. 最接近的因数

#include <cstdio>
#include <vector>

using namespace std;

vector<int> closestDivisors(int num) {
    //思路：二分法，确定一个数之后，另一个数也就随之确定
    //因为两个数其实相对对等，也就是a=3,b=5和a=5,b=3是一样的，我们只要其中一种情况即可
    //两个数肯定都小于num，那么a=b=num/2时，积最大，差最小
    //用二分法需要单调性，但a=1,b=num+2时，差最大，a最大可去(num+1)或(num+2)的平方根
    //根据抛物线在这个区间中a，b的积和差都有单调性
    //(n/2 * n/2)>=n，求得n>=4,也就是num+2>=4推出num>=2
    //所以在本题中，num>=2时，我们只需要考察[1,(num+2)/2]的区间即可

    //问题，会漏掉一些数对

    int left = 1,right=(num+2)/2;
    vector<int> res = {left,right};
    while(left < right)
    {
        int mid = left + (right-left) / 2;

        if((num+1) % mid == 0)
        {
            int a = mid,b=(num+1)/mid;
            if(abs(a-b) < abs(res[0]-res[1]))
            {
                res = {a,b};
            }
        }

        if((num+2) % mid == 0)
        {
            int a = mid,b=(num+2)/mid;
            if(abs(a-b) < abs(res[0]-res[1]))
            {
                res = {a,b};
            }
        }

        int product = mid * mid;
        if(product > num+2)
        {
            right = mid;
        }
        else if(product < num+1)
        {
            left = mid+1;
        }
        else
        {
            return {mid,mid};
        }
    }

    return res;
}

vector<int> closestDivisors2(int num) {
    //思路：二分法可能会漏掉一些符合要求的数对

    vector<int> res = {1,num+1};
    for(int i=1;i*i<=num+2;++i)
    {
        if((num+1) % i == 0)
        {
            int a = i,b=(num+1)/i;
            if(abs(a-b) < abs(res[0]-res[1]))
            {
                res = {a,b};
            }
        }

        if((num+2) % i == 0)
        {
            int a = i,b=(num+2)/i;
            if(abs(a-b) < abs(res[0]-res[1]))
            {
                res = {a,b};
            }
        }
    }

    return res;
}

int main()
{
    int num = 8; //[3,3];
    num = 123; //[5,25]
    num = 999;   //[40,25]
    num = 2; //[2,2]
    for(auto a : closestDivisors2(num))
    {
        printf("%d ",a);
    }
    printf("\n");

    return 0;
}