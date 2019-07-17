//leetcode 738. 单调递增的数字

#include <cstdio>
#include <vector>

using namespace std;

int monotoneIncreasingDigits(int N) {
    
    //如果N是递增的，则返回N，如果不是，找到第一个非递增的数，假设为k,其前面一位为j，则j>k
    //尝试把j减1，如果前面还是递增，则后面填9即可，否则重复这个结果

    vector<int> v;
    int t = N;
    while(t > 0)
    {
        v.push_back(t % 10);
        t /= 10;
    }

    //现在v存储的数字顺序是反的
    int k=-1;
    for(int i=v.size()-1;i>=1;--i)
    {
        if(v[i] > v[i-1])
        {
            k=i;
            break;
        }
    }

    printf("k:%d\n",k);
    if(k == -1)
    {
        return N;
    }

    while(k+1 < v.size() && v[k]-1 < v[k+1])
    {
        ++k;
    }

    v[k]-=1;
    for(int i=0;i<k;++i)
    {
        v[i] =9;
    }

    int res = 0;
    for(int i=v.size()-1;i>=0;--i)
    {
        res *=10;
        res += v[i];
    }

    return res;
}

int main()
{
    printf("%d\n",monotoneIncreasingDigits(10));
    printf("%d\n",monotoneIncreasingDigits(1234));
    printf("%d\n",monotoneIncreasingDigits(332));
    return 0;
}