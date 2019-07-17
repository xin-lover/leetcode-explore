#include <cstdio>

using namespace std;

int lastRemaining(int n)
{
    //思路：观察规律，如果n为偶数，则n和n+1的结果是一样的，因为第一步剔除的是奇数
    //可以考虑逼近法，数列是有首尾元素和步长定义的，即原始的序列是1开始，n结束，步长为1的序列
    //我们不断改变这个序列直到首尾元素相等

    int start = 1;
    int end = n;
    int step = 1;
    bool lefttoright = true;
    while(start < end)
    {
        int count = ((end-start) / step + 1);
        if(lefttoright)
        {
            start += step;
            end -= step * (count % 2);
        }
        else
        {
            start += step * (count % 2);
            end = end - step;
        }

        step *= 2;
        lefttoright = !lefttoright;
        printf("start:%d end:%d\n",start,end);
    }

    return start;
}

int main()
{
    printf("1:%d\n",lastRemaining(1));
    printf("2:%d\n",lastRemaining(2));
    printf("3:%d\n",lastRemaining(3));
    printf("4:%d\n",lastRemaining(4));
    printf("9:%d\n",lastRemaining(9));
    printf("10:%d\n",lastRemaining(10));
    return 0;
}