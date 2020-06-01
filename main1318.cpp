//1318. 或运算的最小翻转次数

#include <cstdio>
#include <vector>

using namespace std;

int minFlips(int a, int b, int c) {
    //思路：最多32次，我们可以一位一位的进行

    int res = 0;
    for(int i=0;i<32;++i)
    {
        int ai = (a >> i) & 1;
        int bi = (b >> i) & 1;
        int ci = (c >> i) & 1;

        if(ci == 0)
        {
            res += ai + bi;
        }
        
        if(ci == 1 && ai + bi == 0)
        {
            ++res;
        }
    }

    return res;
}

int main()
{
    printf("%d\n",minFlips(2,6,5));//1
    printf("%d\n",minFlips(4,2,7));//1
    printf("%d\n",minFlips(1,2,3));//0

    return 0;
}