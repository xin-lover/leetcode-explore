//1535. 找出数组游戏的赢家

#include <cstdio>
#include <vector>

using namespace std;

int getWinner(vector<int>& arr, int k) {
    //思路：可以模拟这个过程，如果一个数比后面的数都要大，那么它就是胜利者
    //否则，除非某个数能提前胜利，不然都会到达这样一个数
    //模拟的问题是如何处理数组需要移动的情况
    //考虑这些情况：
    //1.假设当前在i位置，如果j < k,arr[i] > arr[j]，那么我们更新位置到k继续
    //也就是k之前的数都小于k，当然，这个时候这些数都被排到k的后面去了
    //所以我们要找的数其实就是i之后有k或k-1个（视前面的数而定）数小于它
    //如果遍历到最后都不够，那么就返回它

    int first=0,second=1;
    int wins = 0;
    while(second<arr.size())
    {
        if(arr[first] >= arr[second])
        {
            ++second;
            ++wins;
        }
        else
        {
            wins = 1;
            first = second;
            second = first+1;
        }

        if(wins == k)
        {
            return arr[first];
        }
    }

    return arr[first];
}

int main()
{
    vector<int> arr = {2,1,3,5,4,6,7};
    int k = 2;  //5

    arr = {3,2,1}, k = 10; //3

    arr = {1,9,8,2,3,7,6,4,5}, k = 7;   //9

    printf("%d\n",getWinner(arr,k)); 

    return 0;
}