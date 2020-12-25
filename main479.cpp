//479. 最大回文数乘积

#include <cstdio>
#include <string>
#include <vector>

using namespace std;

bool isPalindrome(long long n)
{
    vector<int> tmp;
    while(n > 0)
    {
        tmp.push_back(n % 10);
        n = n /10;
    }

    int left=0,right=tmp.size()-1;
    while(left < right)
    {
        // printf("%d %d\n",tmp[left],tm)
        if(tmp[left] != tmp[right])
        {
            return false;
        }

        ++left;
        --right;
    }

    return true;
}

int largestPalindrome(int n) {
    //思路：如何判断一个数字是回文数？朴素的求，求出各位数比较即可
    //n不超过9，所以还是n为数还是很多的，暴力求解有点慢
    //考虑回文数是不是少数？长度为n的回文数有多少个？如何求？
    //用迭代的方式构建很简单，如果知道n-1的回文数，在数两侧加数字即可，不如n-2位的回文数有x个，那么n位的回文数应该是9*x，两侧9种选择。。
    //但注意中间连续0存在的情况，也就是额外加9种，即9*x+9，这样n位的回文数大概在10^(n/2)这个数量级
    //两个n位数相乘，最小是10^(n+n-2),最大是(10^n-1)*(10^-1)，粗略估计是10^2n，大概是差两位数，取n=8，初始x=10，那么回文数大概就是10^8数量级，这个有点多
    //来那个n位数相乘，粗略点算有10^2n种可能，所以相对来说少很多，但如果确定回文数，再来分解，n位数的可能性又在10^n左右，这样复杂度没变

    long long mn = pow(10,n-1);
    long long mx = pow(10,n)-1;

    long long res = 0;
    for(long long i=mx;i>=mn;--i)
    {
        for(long long j=i;j>=mn;--j)
        {
            if(isPalindrome(i*j))
            {
                // printf("i:%lld j:%lld ddd:%lld\n",i,j,i*j);
                res = max(res,i*j);
                // return (i*j) % 1337;
            }
        }
    }

    return res % 1337;
}


//数学解法和非数学解法
// Non-math solution:
// maximum assumed palindrom: iterate by the first half of maxNumber
// a palindrome with an even number of digits is a multiple of 11

// class Solution:
//     def largestPalindrome(self, n: int) -> int:
//         if n == 1: return 9
//         hi = 10**n - 1
//         lo = 10**(n-1)
//         maxNum = hi*hi
//         firstHalf = maxNum // (10**n)
//         for first in range(firstHalf, lo-1, -1):
//             second = str(first)[::-1]
//             num = int(str(first) + second)
//             y_hi = hi//11*11
//             for y in range(y_hi, lo-1, -11):
//                 if num % y == 0 and lo <= num // y <= hi:
//                     return num % 1337
//                 if num // y > hi:
//                     break
// Math solution:
// Let Palindrome = X * Y, both have n digits, and assume they are very close to 10^n
// Denote X = 10^n - i, Y = 10^n - j, with assumption: i*j < 10^n
// Palindrome = upper*10^n + lower = (10^n - i)*(10^n - j) = (10^n-i-j)*10^n + i*j
// therefore: upper = 10^n-i-j, lower = i*j
// Let a = i + j, then lower = i*(a-i), upper = 10^n-a
// Algorithm: we iterate a and search for an integer i
// i^2 - a*i + lower = 0 => (i-a/2)^2 = 0.25*a^2 - lower
// Given a start from 2, check if sqrt(a^2 - lower*4) is an integer, then return upper*10^n + lower

// class Solution:
//     def largestPalindrome(self, n: int) -> int:
//         if n == 1: return 9
//         a = 2
//         while a < 10**n:
//             upper = 10**n-a
//             lower = int(str(upper)[::-1])
//             if a**2-lower*4 >= 0 and (a**2-lower*4)**0.5 == int((a**2-lower*4)**0.5):
//                 return (upper*10**n+lower) % 1337
//             a += 1

int largestPalindrome2(int n) {
    if(n==1)
    {
        return 9;
    }

    long long hi = pow(10,n) - 1;
    long long lo = pow(10,n-1);
    long long maxNum = hi*hi;
    long long firstHalf = maxNum / (pow(10,n));
    // for first in range(firstHalf, lo-1, -1):
    for(long long first = firstHalf;first >= lo; --first)
    {
        // second = str(first)[::-1]
        string firstStr = to_string(first);
        string secondStr = firstStr;
        reverse(secondStr.begin(),secondStr.end());
        long long num = stoll(firstStr + secondStr);
        long long y_hi = (hi/11)*11;
        for(int y=y_hi;y>=lo;y-=11)
        {
            // if num % y == 0 and lo <= num // y <= hi:
            if(num % y == 0 && lo <= (num / y) && (num/y) <= hi)
            {
                return num % 1337;
            }
            if(num/y > hi)
            {
                break ;
            } 
        }

    }

    return 0;
}

int largestPalindrome3(int n) {

    if(n == 1)
    {
        return 9;
    }
    int a = 2;
    while(a < pow(10,n))
    {
        int upper = pow(10,n)-a;
        string tmp = to_string(upper);
        reverse(tmp.begin(),tmp.end());
        int lower = stoi(tmp);
        if(a*a-lower*4 >= 0 && sqrt(a*a-lower*4) == int(sqrt(a*a-lower*4)))
        {
            long long b = pow(10,n);
            return (upper*b+lower) % 1337;
        }
        ++a;
    }

    return 0;
}

int main()
{
    printf("%d\n",largestPalindrome3(2)); //987
    printf("%d\n",largestPalindrome3(3)); //123
    return 0;
}