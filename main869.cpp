//leetcode 869. 重新排序得到 2 的幂

#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;


bool reorderedPowerOf2(int N) {
    //思路：一种就是暴力破解，求出每一位，然后排列，这个复杂度较高
    //另一种思路就是，2的幂是固定的，可以把2的幂的数字组合求出，然后与N的比对，符合即可

    vector<int> flags(10,0);
    int t = N;
    int len = 0;
    while(t > 0)
    {
        ++flags[t%10];
        t /= 10;
        ++len;
    }

    int mn = pow(10,len-1);
    int mx = pow(10,len)-1;

    int tmp = 1;
    while(tmp < mn)
    {
        tmp =(tmp << 1);
    }

    // printf("mn:%d mx:%d tmp:%d\n",mn,mx,tmp);
    while(tmp < mx)
    {
        vector<int> nums(10,0);
        t = tmp;
        while(t > 0)
        {
            ++nums[t%10];
            t/=10;
        }

        bool same = true;
        for(int i=0;i<nums.size();++i)
        {
            if(nums[i] != flags[i])
            {
                same = false;
            }
        }

        if(same)
        {
            return true;
        }

        tmp *= 2;
    }

    return false;
}

int main()
{
    // printf(reorderedPowerOf2(1) ? "true\n" : "false\n");
    // printf(reorderedPowerOf2(10) ? "true\n" : "false\n");
    // printf(reorderedPowerOf2(16) ? "true\n" : "false\n");
    // printf(reorderedPowerOf2(24) ? "true\n" : "false\n");
    // printf(reorderedPowerOf2(46) ? "true\n" : "false\n");
    printf(reorderedPowerOf2(218) ? "true\n" : "false\n");
    return 0;
}