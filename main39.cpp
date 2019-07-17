#include <vector>
#include <cstdio>

using namespace std;

int hammingDistance(int a,int b)
{
    int t = a^b;
    int res = 0;
    for(int i=0;i<32;++i)
    {
        if((t >> i) & 1)
        {
            ++res;
        }
    }

    return res;
}

int totalHammingDistance(vector<int>& nums) {
    //思路：暴力破解，直接异或然后求1的数量

    // int res = 0;
    // for(int i=0;i<nums.size();++i)
    // {
    //     for(int j=i+1;j<nums.size();++j)
    //     {
    //         res += hammingDistance(nums[i],nums[j]);
    //     }
    // }

    // return res;

    //思路：记录每一位上的1和0的数量m，n，不同的组合就是m*n，把所有的相加就是总和
    int n = nums.size();
    vector<int> cv(32,0);
    for(int i=0;i<nums.size();++i)
    {
        for(int j=0;j<32;++j)
        {
            if((nums[i] >> j) & 1)
            {
                cv[j] += 1;
            }
        }
    }

    int res = 0;
    for(int i=0;i<32;++i)
    {
        printf("i:%d cv:%d\n",i,cv[i]);
        res += cv[i] * (n-cv[i]);
    }

    return res;
}


int main()
{
    vector<int> v = {4, 14, 2};
    printf("%d\n",totalHammingDistance(v));
    return 0;
}