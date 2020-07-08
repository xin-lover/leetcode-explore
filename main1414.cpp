//1414. 和为 K 的最少斐波那契数字数目

#include <cstdio>
#include <vector>

using namespace std;

int findMinFibonacciNumbers(int k) {
    //思路：f(n) = f(n-1) + f(n-2)
    //如果k是斐波那契数列中的数，那么需要的数字数量就是1个
    //而斐波那契数列需要计算，所以使用贪心试试

    if(k == 0)
    {
        return 0;
    }

    int t1=1,t2=1;
    while(t2 <= k)
    {
        int t = t2;
        t2 = t1 + t2;
        t1 = t;
    }

    return 1 + findMinFibonacciNumbers(k-t1);

}

int main()
{
    printf("%d\n",findMinFibonacciNumbers(7));//2
    printf("%d\n",findMinFibonacciNumbers(10));//2
    printf("%d\n",findMinFibonacciNumbers(19));//3

    return 0;
}