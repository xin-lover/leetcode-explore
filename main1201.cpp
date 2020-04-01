//1201. 丑数 III

#include <cstdio>
#include <vector>

using namespace std;

int gcd2(int x,int y)
{
    if(x == y)
    {
        return x;
    }
    while(x != 0 && y != 0)
    {
        if(x>y)
        {
            x %= y;
        }
        else if(x < y)
        {
            y %= x;
        }
    }

    return x > y ? x : y;
}

int nthUglyNumber(int n, int a, int b, int c) {
    //思路： 3指针法

    //超时

    int ai=1,bi=1,ci=1;

    int res = 0;
    int count = 0;
    while(count++ < n)
    {
        int t1 = a * ai,t2 = b*bi,t3=c*ci;
        if(t1 <= t2 && t1 <= t3)
        {
            ++ai;
            res = t1;
            if(t2 == t1)
            {
                ++bi;
            }
            if(t3 == t1)
            {
                ++ci;
            }
        }
        else if(t2 <= t1 && t2 <= t3)
        {
            ++bi;
            res = t2;
            if(t1 == t2)
            {
                ++ai;
            }
            if(t3 == t2)
            {
                ++ci;
            }
        }
        else
        {
            ++ci;
            res = t3;
            if(t1 == t3)
            {
                ++ai;
            }
            if(t2 == t3)
            {
                ++bi;
            }
        }
    }

    return res;
}

int nthUglyNumber2(int n, int a, int b, int c) {
    //思路：不用3个指针，但我们知道这个丑数序列可以分为3个部分，整除a，b，c
    //可以计数，同时能同时整除a，b的总数要-1，同理b，c和a，c，但同时整除a，b，c的需要+1
    //使用二分法，

    //处理a,b ,c之间的整除情况,还有a,b,c有公约数的情况

    vector<int> tmp = {a,b,c};
    sort(tmp.begin(),tmp.end());
    a = tmp[0];
    b = tmp[1];
    c = tmp[2];
    if(b % a == 0)
    {
        b = INT_MAX;
    }
    if(c % a == 0)
    {
        c = INT_MAX;
    }
    if(c % b == 0)
    {
        c = INT_MAX;
    }
    


    long long ab = static_cast<long long>(a) * b / gcd2(a,b);
    long long ac = static_cast<long long>(a)*c / gcd2(a,c);
    long long bc = static_cast<long long>(b) * c / gcd2(b,c);
    long long abc = static_cast<long long>(a) * b * c / gcd2(gcd2(a,b),c);
    int left=0,right=INT_MAX;
    while(left<right)
    {
        int mid = left + (right-left) / 2;
        int an = mid / a;
        int bn = mid / b;
        int cn = mid / c;
        int abn = mid / ab;
        int bcn = mid / bc;
        int acn = mid / ac;
        int abcn = mid / abc;
        // printf("mid:%d\n",mid);

        int t = an + bn + cn - abn - bcn - acn + abcn;
        printf("left:%d right:%d mid:%d t:%d\n",left,right,mid,t);
        if(t < n)
        {
            left = mid+1;
        }
        else
        {
            right = mid;
        }
        
    }

    return right;
}


int main()
{
    // printf("%d\n",nthUglyNumber2(3,2,3,5)); // 4
    // printf("%d\n",nthUglyNumber2(1000000000,2,217983653,336916467)); //1999999984
    // printf("%d\n",nthUglyNumber2(4,2,3,4)); //
    // printf("%d\n",nthUglyNumber2(10,7,6,8)); //
    printf("%d\n",nthUglyNumber2(6,2,1,3)); //
    // int a = 1999999982;
    // printf("%d\n",a / 2 + a / 217983653 + a / 336916467 - a / (2 * 217983653)
    // -a/(2*336916467) - a / (217983653 * 336916467) + a / (217983653 * 336916467 * 2));

    return 0;
}