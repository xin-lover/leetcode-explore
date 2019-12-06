//1006. 笨阶乘

#include <cstdio>

using namespace std;

int clumsy(int N) {
    //思路：乘除加减，因为没有括号，所以乘除两个符号3个数为一组参与加减运算
    //所以整个表达式最终是加减加减这样一个顺序
    //乘除表达式为 n*(n-1)/(n-2）,简化后为 n+1+ 2/(n-2);
    //当n>4时，因为地板除法，所以就变为n+1
    //n==2时，n*(n-1)=2
    //n==1时，1
    //对于n>4,加号对应的是n-3,除了第一组，都是-(n+1)+n-3,也就是-4
    //那么这个就简单了

    int res = 0;
    int dir = 1;
    if(N > 4)
    {
        res = N+1+N-3;
        N-=4;
        dir = -1;
    }
    while(N > 4)//使用除法也可以，但会有求余，对于计算机来说不一定更快
    {
        res -= 4;
        N-=4;
    }
    
    if(N > 2)
    {
        res += dir*((N+1) + 2 /(N-2));
        res += N-3;
    }
    else
    {
        res += dir*N;
    }

    return res;
}

int clumsy2(int N) {
    //思路：常数时间优化

    int res = 0;
    int dir = 1;
    if(N > 4)
    {
        res = N+1+N-3;
        N-=4;
        dir = -1;
    }

    if(N > 4)
    {
        int group = N / 4;
        N %= 4;
        if(N == 0)
        {
            group-=1;
            N=4;
        }
        res -= 4 * group;
    }

    if(N > 2)
    {
        res += dir*((N+1) + 2 /(N-2));
        res += N-3;
    }
    else
    {
        res += dir*N;
    }

    return res;
}

int clumsy3(int N) {
    //思路：再次组合结果，2*n-2-(-4*(n-4)/4)+x=n+2+x
    //这个x也就是根据(N-4）% 4来决定的
    //如果余数为0，因为我们在n>4的时候省略了2/(n-2)这一项，也就是最后一组少-1，所以x就是-1
    //余数为1时，也就是最后一组是-1，但我们观察(-4*(n-4)/4)这一项，我们的原意是先计算（n-4)/4，而且是整除运算
    //那么记过应该是0，但消去分母之后，得到的是-1,也就是说如果n-4不能整除4时，那么最终结果就差(n-4)%4
    //所以（n-4）%4需要被加回来，所以对于5要加1，最后一组是-1，所以x是1-1
    //同理n==6,x=2-2
    //n==7时,x=3-6
    

    static int mm[] = {1,2,2,-1};

    if(N > 4)
    {
        return N + mm[N%4];
    }
    else if(N > 2)
    {
        return (N+1) + 2 /(N-2) + N - 3;
    }
    else
    {
        return N;
    }
    
}

int main()
{
    // printf("%d\n",clumsy2(4));//7
    // printf("%d\n",clumsy2(10));//12
    // printf("%d\n",clumsy(2));//2
    // printf("%d\n",clumsy(1));//1
    // printf("%d\n",clumsy2(7));//6
    // printf("%d\n",clumsy2(12));//13
    printf("%d\n",clumsy3(5));
    return 0;
}