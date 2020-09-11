//1545. 找出第 N 个二进制字符串中的第 K 位

#include <cstdio>
#include <vector>

using namespace std;

char findKthBit(int n, int k) {
    //思路：不能直接模拟，性能低
    //把k不断的往前定位，因为后半部分是前半部分反转+翻转

    int len = (1 << (n-1)) - 1;

    bool flip = false;
    //确定了p，也就是前半段的长度，然后开始往前定位
    while(len >= 1)
    {
        if(len+1 == k)
        {
            flip = !flip;
            break;
        }
        else if (len >= k)
        {
            // k=k-len;
            len = (len-1)/2;
        }
        else
        {
            k = k - len - 1;
            k = len + 1 - k;
            len = (len-1)/2;
            //翻转+反转的逆操作
            flip = !flip;
        }
    }

    return flip ? '1' : '0';
}

//递归写法更简单
char findKthBit2(int n, int k) {
    if (k == 1) {
        return '0';
    }
    int mid = 1 << (n - 1);
    if (k == mid) {
        return '1';
    } else if (k < mid) {
        return findKthBit(n - 1, k);
    } else {
        k = mid * 2 - k;
        return invert(findKthBit(n - 1, k));
    }
}

char invert(char bit) {
    return (char) ('0' + '1' - bit);
}

int main()
{
    int n = 3, k = 1; //0
    n = 4, k = 11;  //1
    // n = 1, k = 1;   //0
    // n = 2, k = 3;   //1
    n=3,k=2;    //1
    n=3,k=5;    //0
    // n=4,k=12;   //0

    printf("%c\n",findKthBit(n,k));

    return 0;
}