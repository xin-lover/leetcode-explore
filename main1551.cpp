//1551. 使数组中所有元素相等的最小操作数

#include <cstdio>
#include <vector>

using namespace std;

int minOperations(int n) {
    //思路：数组是对称的，操作也是对称的，想要让所有元素相等，很明显，
    //最后的元素可以确认，那么操作数也就可以确认

    //分奇偶
    // if(n & 1)
    // {
    //     return (1+(n-1)/2) * ((n-1)/2);
    // }
    // else
    // {
    //     return (1+(n-1)/2) * ((n-1)/2) + n/2;
    // }
    

    return n*n/4;
    
}

int main()
{
    int n = 3; //2
    // n=6; //9
    printf("%d\n",minOperations(n));

    return 0;
}