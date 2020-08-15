//1498. 满足条件的子序列数目

#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

//求组合数,用动归优化

int countCombinations(vector<int>& factorial,int n)
{
    int res = 0;
    for(int i=0;i<=n;++i)
    {
        res += factorial[n]/(factorial[i] * factorial[n-i]);
    }

    return res;
}

long long powerValue(int n, int modValue)
{
    static vector<int> powerValues(10000,0);

    if(powerValues[n] == 0)
    {
        long long t = 1;
        if(n < 15)
        {
            t = (1 << n) % modValue;
        }
        else
        {
            t = (1 << 15) * powerValue(n-15,modValue);  //这里也溢出。。。。
            t %= modValue;
        }
        
        powerValues[n] = t;
    }

    return powerValues[n];
}

int numSubseq(vector<int>& nums, int target) {
    //思路：先排序，这样可以方便的确定最大最小值
    //我们先选取最小值，然后再遍历找寻最大的符合要求的最大值，那么，它的自序列都是符合要求的

    static const int kLimit = 1000000000 + 7;
    sort(nums.begin(),nums.end());

    // int n = nums.size();
    // vector<int> factorial(n+1,-1);   //阶乘溢出了。。。。
    // factorial[0] = 1;
    // for(int i=1;i<=n;++i)
    // {
    //     factorial[i] = factorial[i-1] * i;
    // }

    vector<int> powerValues(nums.size()+1,1);
    for(int i=1;i<powerValues.size();++i)
    {
        long long t = powerValues[i-1] * 2;
        powerValues[i] = t % kLimit;   
    }

    vector<int> combinations(nums.size(),1);
    for(int i=1;i<combinations.size();++i)
    {
        long long t = combinations[i-1] + powerValues[i];
        combinations[i] = t % kLimit;
    }

    long long res = 0;
    for(int i=0;i<nums.size();++i)
    {
        if(nums[i] > target)
        {
            break;
        }

        //二分法找
        int t = target - nums[i];
        int left=i,right=nums.size()-1;
        while(left < right)
        {
            int mid = left + (right-left) / 2;
            if(nums[mid] > t)
            {
                right = mid;
            }
            else
            {
                left = mid+1;
            }
        }

        if(left > i && nums[left] > t)
        {
            --left;
        }


        if(nums[left] <= t)
        {
            //i为起点，且符合要求的子序列，使用组合的方式得出
            res += 1;
            // for(int j=i+1;j<=left;++j) //这个循环有点费时，观察发现，其实没必要
            // {
            //     // res += countCombinations(factorial,j-i-1);   //从阶乘看出来这是一个2的幂次方
            //     // long long tt = pow(2,j-i-1);  //这个地方也溢出。。。。

            //     int len = j-i-1;
            //     // long long tt = 1;
            //     // while(len >= 15) //还需要优化，记录计算过值，避免重复计算
            //     // {
            //     //     tt *= (1 << 15);
            //     //     tt %= kLimit;
            //     //     len -= 15;   
            //     // }
            //     // tt *= (1 << len);
            //     // res += tt;
            //     // res %= kLimit;



            //     // res += powerValue(len,kLimit);
            //     res += powerValues[len];
            //     res %= kLimit;
            // }

            //优化，确定起点和长度后，不用每次都计算，因为和起点没关系，长度是唯一因素
            if(left-i-1>=0)
            {
                res += combinations[left-i-1];
                res %= kLimit;
            }

        }

    }

    return res;
}


int numSubseq2(vector<int>& nums, int target) {
    //思路：先排序，这样可以方便的确定最大最小值
    //我们先选取最小值，然后再遍历找寻最大的符合要求的最大值，那么，它的自序列都是符合要求的
    //vmax+vmin<=target,则vmin<=vmax => vmin <=target-vmin => vmin <= target/2
    static const int kLimit = 1000000000 + 7;
    sort(nums.begin(),nums.end());

    vector<int> powerValues(nums.size()+1,1);
    for(int i=1;i<powerValues.size();++i)
    {
        long long t = powerValues[i-1] * 2;
        powerValues[i] = t % kLimit;   
    }

    //发现combinations的值其实是2^i-1    ........
    // vector<int> combinations(nums.size(),1);
    // for(int i=1;i<combinations.size();++i)
    // {
    //     long long t = combinations[i-1] + powerValues[i];
    //     combinations[i] = t % kLimit;
    // }


    long long res = 0;
    for(int i=0;i<nums.size();++i)
    {
        if(nums[i] > target/2)
        {
            break;
        }

        //二分法找
        int t = target - nums[i];
        int left=i,right=nums.size()-1;
        while(left < right)
        {
            int mid = left + (right-left) / 2;
            if(nums[mid] > t)
            {
                right = mid;
            }
            else
            {
                left = mid+1;
            }
        }

        if(left > i && nums[left] > t)
        {
            --left;
        }

        if(nums[left] <= t)
        {
            if(left-i>=0)
            {
                res += powerValues[left-i];
                res %= kLimit;
            }

        }

    }

    return res;
}


int main()
{
    vector<int> nums = {3,5,6,7};
    int target = 9; //4

    // nums = {3,3,6,8}, target = 10;//6
    nums = {2,3,3,4,6,7}, target = 12;  //61
    // nums = {5,2,4,1,7,6,8}, target = 16;    //127

    nums={6,10,12,3,29,21,12,25,17,19,16,1,2,24,9,17,25,22,12,22,26,24,24,11,3,7,24,5,15,30,23,5,20,10,19,20,9,27,11,4,23,4,4,12,22,27,16,11,26,10,23,26,16,21,24,21,17,13,21,9,16,17,27};
    target = 26;    //963594139

    printf("%d\n",numSubseq2(nums,target));
    return 0;
}