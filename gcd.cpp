#include <cstdio>

using namespace std;

//最大公约数

//更相减损法：假设x=y,则x就是最大公约数,否则假设最大公约数D，x>y,则x=a*D,y=b*D,则x-y=(a-b)*D，很明显y和x-y的最大公约素也是D，
int gcd1(int x,int y)
{
    if(x == 0 || y == 0)
    {
        return 0;
    }
    while(true)
    {
        if(x>y)
        {
            x-=y;
        }
        else if(x<y)
        {
            y-=x;
        }
        else
        {
            return x;
        }
    }
}

//辗转相除法，与上述推理同理
int gcd2(int x,int y)
{
    while(x*y)
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

//这种方法其实是更相减损法的优化
int gcd3(int x,int y)
{
    if(x == 0 || y == 0)
    {
        return 0;
    }
    if(x == y)
    {
        return x;
    }

    if(x < y)
    {
        return gcd3(y,x);
    }
    else
    {
        if(!(x&1) && !(y&1))
        {
            return gcd3(x>>1,y>>1) << 1;
        }
        else if(!(x&1) && (y&1))
        {
            return gcd3(x>>1,y);
        }
        else if((x&1) && !(y&1))
        {
            return gcd3(x,y>>1);
        }
        else
        {
            return gcd3(y,x-y);
        }
        
    }
}

int main()
{
    printf("gcd1:%d\n",gcd1(0,3));
    printf("gcd1:%d\n",gcd1(9,3));
    printf("gcd2:%d\n",gcd2(9,3));
    printf("gcd3:%d\n",gcd3(9,3));
    return 0;
}