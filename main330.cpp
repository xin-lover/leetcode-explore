//330. 按要求补齐数组

#include <cstdio>
#include <vector>
#include <unordered_map>

using namespace std;

int minPatches(vector<int>& nums, int n) {
    //思路：假设combine(nums)表示nums中的组合数，新加一个数字，会新加combine(nums)+1中可能，暴力求解将是指数级的
    //考虑二进制表示，所以整数最多31个数字就可以了，1,2,4,8,16,32……
    //其它的数字会有影响吗？比如3会影响4的选用吗？1和3可以代替4，但如果另一个数字同时还使用到1和3时，就不行
    //同时nums还可能有重复数字,比如1,2,2 可以最大到5，而且都可以到，主要是处理这个情况
    //nums有序，那么相同字符很容易找到，如果重复数字是n，如果在n之前所有的数字{1,2,……,n-1}都可得，那么m*n+n-1之前都可得
    //综上，2的幂作为关键数字，除了2的幂之外（重复时只取一个），其它数字可以累加，这个累加的和加上2的幂可达的最大值的和就是能到达的最大和
    //这个思路还是有问题，2的mi可以由其它数字代替，比如32，可以由1和31代替，也就是说如果额外由1和31，那么是可以不需要32这个数的
    //所以问题可以这么定义，如果到nums[i-1]时最大可达k，那么对于nums[i],可达nums[i]+k;
    //也就是说不用考虑2的幂，其实2的幂也是可以这样推出来

    int res = 0;
    long long arrive = 0;
    for(int i=0;i<nums.size() && arrive <n;++i)
    {
        int need = 0;
        while(arrive < nums[i] && arrive < n)
        {
            need = arrive+1;
            arrive += need;
            ++res;
        }

        if(nums[i] == need)
        {
            --res;
        }
        else
        {
            arrive += nums[i];
        }
    }

    while(arrive < n) //最终还是比n小
    {
        arrive += arrive + 1;
        ++res;
    }

    return res;
}

int main()
{
    vector<int> nums = {1,2,2};
    int n=5; //0

    // nums = {1,3};
    // n = 6; //1

    // nums = {1,5,10};
    // n=20;   //2
    
    // nums={};
    // n = 7; //3

    nums = {1,2,31,33};
    n = 2147483647; //28

    nums = {1,2,2,6,34,38,41,44,47,47,56,59,62,73,77,83,87,89,94};
    n = 20;//1
    printf("%d\n",minPatches(nums,n));
    return 0;
}