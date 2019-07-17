//leetcoe 650. 只有两个键的键盘

#include <cstdio>

using namespace std;

int minSteps(int n) {
    //思路：如果使用copyall，则每次copy的数量指数递增，我们要想用最少的次数，则能使用copyall的时候就使用copyall
    //但例外可能出现在前期可以凑出n的一半，则最后可以只copy和past一次即可，
    //所以我们可以不断除2递归，即求n/2的次数，
    //但对于n为奇数的情况，一种是质数，比如说7，则只能第一次copyall然后past6次
    //这样其实就有点像因式分解，7只有1和7，所以需要7个1，而9可以分解为3x3，所以所以可以copyall一次past两次，在copyall，然后past2次
    //所以现在的问题就是如何对n进行分解，因为我们只需要分解一次，而且只需要找因子相差最大的即可，

    if(n < 2)
    {
        return 0;
    }
    if(n % 2 == 0)
    {
        return 2 + minSteps(n/2);
    }

    //找因子

    int f = 1;
    for(int i=3;i<n/2;i+=2)
    {
        if(n % i == 0)
        {
            f = i;
            break;
        }
    }
    printf("f:%d\n",f);

    if(f == 1)
    {
        return n;
    }

    return f + minSteps(n/f);
}

int main()
{
    printf("res:%d\n",minSteps(9));
    return 0;
}