//1015. 可被 K 整除的最小整数

#include <cstdio>
#include <vector>
#include <set>

using namespace std;

int smallestRepunitDivByK(int K) {
    //思路：由1组成的数，首先K为偶数肯定不行
    //不断枚举即可
    //思路错了，多少个1，没有说是int，只是1组成的整数

    if((K & 1) == 0)
    {
        return -1;
    }

    int res = 1;
    const int uplimit = 2 * 1e9;
    int tmp = 1;
    while(tmp < K || tmp % K != 0)
    {
        tmp*=10;
        tmp+=1;
        if(tmp > uplimit)
        {
            break;
        }

        ++res;
    }

    return tmp > uplimit ? -1 : res;
}

int smallestRepunitDivByK2(int K) {
    //思路：首先偶数肯定不行
    //假设M=x*K+N，那么给M后面加一个1就是10*M+1
    //(10*M+1)=(10*x*K+10*N+1),求余K得(10*N+1)%K
    //也就是说对于K，M==N，
    //那么一个思路就是使用set存储每个N，如果遇到重复的N就返回-1
    //因为set存储的肯定是小于K的数，不会出现无限不循环的情况
    if((K & 1) == 0 || K%5==0)
    {
        return -1;
    }

    set<int> st;
    int m = 1;
    int count = 1;
    while((m%=K) != 0)
    {
        if(st.find(m) != st.end())
        {
            return -1;
        }

        st.insert(m);
        while(m < K)
        {
            ++count;
            m=m*10+1;
        }
    }

    return count;
}

int smallestRepunitDivByK3(int K) {
    //思路：去除使用set存储判断是否循环，我们使用set的原因就是怕出现循环的情况，我们可以证明这种情况已经被我们排除
    //证明：假设我们的余数序列是S1，S2……Si……Sj……,其中Si==Sj，也就是出现了循环
    //设m=i-1,n=j-1, 那么也就是(10*Sm+1)%K=(10*Sn+1)%K
    //可以得到:10*Sm+1 = 10*Sn+1+a*K,a为任意不等于0的整数（在这里a大于0）
    //也就是10*(Sm-Sn) = a*K,而Sm,Sn都小于K，所以0<a<10,
    //转换得：Sm-Sn=a*K/10,Sm-Sn是一个整数，所以a*K/10如果要为整数，只能把10消为一个小于10的数，这样a才可能整除它
    //10只能分解为2*5,所以K必须能被2或5整除，而这两种情况刚好都是被排除的
    if((K & 1) == 0 || K%5==0)
    {
        return -1;
    }

    int m = 1;
    int count = 1;
    while((m%=K) != 0)
    {
        while(m < K)
        {
            ++count;
            m=m*10+1;
        }
    }

    return count;
}


int main()
{
    printf("%d\n",smallestRepunitDivByK2(1)); //1
    printf("%d\n",smallestRepunitDivByK2(2)); //-1
    printf("%d\n",smallestRepunitDivByK2(3));//3
    printf("%d\n",smallestRepunitDivByK2(63));//18
    printf("%d\n",smallestRepunitDivByK2(97));//96
    return 0;
}
