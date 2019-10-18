//leetcode 932. 漂亮数组

#include <cstdio>
#include <vector>

using namespace std;

void beautifulArray(int N,int base,vector<int>& nums) {
    if(N == 1)
    {
        nums[0] = base;
        return;
    }

    int mid = N / 2;
    for(int i=0;i<N-mid;++i)
    {
        nums[mid+i] = (2*i+1) * base;
    }

    return beautifulArray(N/2,base*2,nums);
}

vector<int> beautifulArray(int N) {
    //思路：A[k] * 2 = A[i] + A[j]
    //按奇偶来排，比如先放偶数，再放奇数，那么奇数部分肯定符合要求
    //偶数部分我们除2，又变成一个新的数组，也就是n变为n/2，问题又回来了，那么我们迭代的处理即可

    vector<int> res(N);
    beautifulArray(N,1,res);
    return res;
}

int main()
{
    vector<int> res = beautifulArray(2);
    for(auto a : res)
    {
        printf("%d ",a);
    }
    printf("\n");
    return 0;
}