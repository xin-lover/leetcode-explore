//483. 最小好进制

#include <cstdio>
#include <vector> 
#include <string>
#include <cmath>

using namespace std;

long long longPow(long long base,long long ex)
{
    if(ex == 1)
    {
        return base;
    }

    if(ex & 1)
    {
        return longPow(base*base,ex/2) * base;
    }
    else
    {
        return longPow(base*base,ex/2);
    }
    
}

string smallestGoodBase(string n) {
    //思路：先来看看n个1的数字在k进制下的结果
    //k^(n-1)+k^(n-2)……+k^0,由等比数列求和公式得：S=(k^n-1)/(k-1)
    //这个很明显，可用二分法来求，但k的n次方会溢出，但10^18次方用long long 好像可以
    //但枚举的性能base的性能很低，也就是每个k都要试试
    //反一下了？枚举n？

    long long in = stoll(n);

    for(int ex=64;ex>0;--ex)
    {
        long long left=2,right=in;
        while(left < right)
        {
            long long mid = left + (right - left) / 2;
            long long tmp = in;
            int e = 0;
            while(tmp >= mid)
            {
                tmp /= mid;
                ++e;
            }

            if(e > ex)
            {
                left = mid+1;
            }
            else if(e < ex)
            {
                right = mid;
            }
            else
            {
                long long t = 1;// (longPow(mid,ex)-1)/(mid-1);
                long long tm = 1;
                for(int i=0;i<ex;++i)
                {
                    tm *= mid;
                    t += tm;
                }

                if(t == in)
                {
                    return to_string(mid);
                }
                else if(t < in)
                {
                    left = mid+1;
                }
                else
                {
                    right = mid;
                }
                
            }
        }
    }

    return "";
}

//这个思路漂亮啊，(n-1)进制的“11”的值为n，所以肯定存在一个保底的结果n-1,
//直接求k次方根,同时由k^m < n < (k+1)^m，得k < n^(1/s) < k+1,这样当s>=2时，n^(1/s)次方的整数部分肯定是k，这个不等式也就是决定了k肯定是唯一的
string smallestGoodBase2(string n) {
    long long N = stoll(n);
    for (int m = 59; m > 1; m--) {
        long k = (long long)pow(N, 1.0 / m);
        //不存在1进制，如果k<=1，直接下一次
        if (k <= 1)
            continue;
        long s = 0;
        for (int i = 0; i <= m; i++) 
            s = s * k + 1;
        if (s == N) 
            return to_string(k);
    }

    return to_string(N - 1);
}

//另一种二分，更简洁,确定m的范围位1<=m<=log2N
//有等比求和公式可确定k的最大范围，二分查找。。。。
string smallestGoodBase3(string n) {
long long int num = atoll(n.c_str());
for (int m = log2(num); m >= 1; m--) {
    long long l = 2, r = powl(num, 1.0 / m) + 1, mid, sum;
    while (l < r) {
    mid = (l + r) / 2;
    sum = 1;
    for (int j = 0; j < m; ++j) {
        sum = sum * mid + 1;
    }
    if (sum == num) {
        return string(to_string(mid));
    }
    else if (sum < num) {
        l = mid + 1;
    }
    else {
        r = mid;
    }
    }
}
return "";
}

int main()
{
    // printf("%s\n",smallestGoodBase("13").c_str()); //3
    // printf("%s\n",smallestGoodBase("4681").c_str()); //8
    printf("%s\n",smallestGoodBase2("1000000000000000000").c_str()); //999999999999999999
    return 0;
}