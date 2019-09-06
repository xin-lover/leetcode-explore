//leetcode 求出大于或等于 N 的最小回文素数。

#include <cstdio>
#include <vector>
#include <string>
#include <cmath>

using namespace std;


int isPrime(int N)
{
    if(N % 2 == 0)
    {
        return false;
    }

    for(int i=3;i*i<=N;i+=2)
    {
        if(N % i == 0)
        {
            return false;
        }
    }

    return true;
}

int nextPrime(int N)
{
    if(N % 2 == 0)
    {
        ++N;
    }

    for(;;N+=2)
    {
        bool isPrime = true;
        for(int i=3;i*i<=N;i+=2)
        {
            if(N % i == 0)
            {
                isPrime = false;
                break;
            }
        }

        if(isPrime)
        {
            return N;
        }
    }
   
    return 2;
}

int isPalindrome(int N)
{
    vector<int> v;
    while(N > 0)
    {
        v.push_back(N%10);
        N/=10;
    }

    int sz = v.size();
    for(int i=0;i<sz/2;++i)
    {
        if(v[i] != v[sz-i-1])
        {
            return false;
        }
    }

    return true;
}

int nextPalindrome(int N)
{
    vector<int> v;
    int t = N;
    while(t > 0)
    {
        v.push_back(t%10);
        t/=10;
    }

    if(v.size() == 1)
    {
        return N;
    }

    reverse(v.begin(),v.end());
    int sz = v.size();
    int i = sz/2-1;
    while(i >= 0 && v[i] == v[sz-i-1])
    {
        --i;
    }

    if(i < 0)
    {
        return N;   
    }

    if(v[i] > v[sz-i-1])
    {
        for(int j=i;j>=0;--j)
        {
            v[sz-j-1] = v[j];
        }
    }
    else
    {
        //v[i]肯定不为9
        int k= (sz&1)==1 ? sz/2 : sz/2-1;
        while(k>i && v[k] == 9)
        {
            v[k]=0;
            --k;
        }

        v[k] += 1;
        for(int j=0;j<sz/2;++j)
        {
            v[sz-1-j] = v[j];
        }
    }

    int sum = 0;
    for(int i=0;i<sz;++i)
    {
        sum *=10;
        sum+=v[i];
    }

    return sum;
}

int primePalindrome(int N) {
    //思路：回文数和素数
    //一种思路是求出所有的素数，然后找大于等于N的回文数
    //一种思路是求出说有的回文数，然后找大于等于N的素数
    //然后缓存这些数，使用二分查找，这个适合多次调用
    //还有一种思路就是从N开始，依次查找，思路也是上面的两个
    //先验证回文的话，可以先把N分解为一个数组，然后排列数组

    if(N == 1)
    {
        return 2;
    }
    if(N > 3 && N % 2 == 0)
    {
        N+=1;
    }

    do
    {
        N = nextPrime(N);   //超时，素数还是很多的
    } while(!isPalindrome(N) && ++N);

    return N;
}

int primePalindrome2(int N) 
{
    //思路：找到大于等于N的回文数，再找大于等于这个数的素数，如果相等则找到了，否则继续找 

    int p = nextPalindrome(N);
    int pd = nextPrime(p);

    while(p != pd)
    {
        p = nextPalindrome(pd);
        pd = nextPrime(p);
    }

    return p;
}

int primePalindrome3(int N)
{
    if (N<=2)         return 2;
    else if (N <= 3)  return 3;
    else if (N <= 5)  return 5;
    else if (N <= 7)  return 7;
    else if (N <= 11) return 11;
    int tmp = 1;
    for(int i = N; i < INT_MAX / 10; i += tmp) 
    {
        string s = to_string(i);
        int len = s.size();
        //除11外的偶数位回文数，都能被11整除
        if (len % 2 == 0)
        {
            i = pow(10, len);
            s = to_string(i);
            len++;
        }
        tmp = pow(10, len / 2); //这样相当于先变换中间的数
        string s1 = s.substr(0, len / 2);
        reverse(s1.begin(), s1.end());
        s = s.substr(0, len / 2 + 1) + s1;
        i = stoi(s);
        if (i < N)
            continue;
        else
            if (isPrime(i))
                return i;
    }
    return -1;
}

//思路：假设有一个回文串 XX，下一个回文串是什么？
//每个 dd 长度的回文串都有一个 回文根，回文根为前 k= d+1)/2个数字。下一个回文串一定是由下一个回文根组成的。
//举个例子，如果 123123 是 1232112321 的回文根，那么下一个回文串 1242112421 的回文根就是 124124。
// 需要注意一个回文根可能对应两个回文串，例如 123321123321，1232112321 的回文根就都是 123123。

//这里一个关键的优化是偶数位的回文数都能被11整除把这些数去掉会是一个很大的提升

int main()
{
    // printf("%d\n",primePalindrome(9989900));
    // printf("%d\n",nextPrime(9989900));
    // printf("%d\n",nextPalindrome(101));
    // printf("%d\n",primePalindrome3(9989900));
    printf("%d\n",primePalindrome3(103));
    return 0;
}