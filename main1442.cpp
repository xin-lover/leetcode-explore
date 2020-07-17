//1442. 形成两个异或相等数组的三元组数目

#include <cstdio>
#include <vector>
#include <unordered_map>

using namespace std;

int countTriplets(vector<int>& arr) {
    //思路：异或运算的一个规律，两个相同的值异或为0，而与0异或不变
    //第一个方案就是O(n^3)的复杂度

    int n = arr.size();
    int res = 0;
    for(int i=0;i<n;++i)
    {
        int t = arr[i];
        for(int j=i+1;j<n;++j)
        {
            t ^= arr[j];

            int left=arr[i],right=t^arr[i];
            if(left == right)
            {
                ++res;
            }
            for(int k=i+1;k<j;++k)
            {
                left ^= arr[k];
                right ^=arr[k];
                if(left == right)
                {
                    ++res;
                }
            }
        }
    }

    return res;
}

int countTriplets2(vector<int>& arr) {
    //思路：考查异或运算，left == right => left ^ right==0
    //(left ^ a) ^ (right ^a) = (left ^ right) ^ (a ^ a) = (left ^ right) ^ 0 = (left ^ right)
    //所以上面最内层的循环可以优化掉，复杂度为O(n^2)

    int n = arr.size();
    int res = 0;
    for(int i=0;i<n;++i)
    {
        int t = arr[i]; 
        for(int j=i+1;j<n;++j)
        {
            t ^= arr[j];

            int left=arr[i],right=t^arr[i];
            if(left == right)
            {
                res += (j-i);
            }
        }
    }

    return res;
}

int countTriplets3(vector<int>& arr) {
    //思路：O(n)的思路，上面计算t的过程可以利用前缀和的思路，这样，求某个区间的异或就是xor[i]^xor[i+k]
    //而我们在内层循环只要判断初始的情况是否相等即可，这就有点像是两数之和的问题，使用map记录异或值，遇到相同值时计算即可
    //因为可能出现多个位置异或值相同，我们第一个方案就是在map中用vector存储各自位置，这样复杂度最坏的情况还是O(n^2)，即所有异或值都相同
    //但对于求和这过程，我们可以简化
    //假设当前位置i出现了重复的异或值，之前异或值的位置列表是list
    //之前是sum(i-list[j]),同类项合并得i*list.size() - sum(list[j])
    //而sum(list[j])用动归的思路可以简化为O(1),所以我们map的value存储出现的次数和出现的位置下标的和

    unordered_map<int,vector<int>> um;
    um[0] = {1,0};  //注意0，这个是初始情况，应对的是类似[1,1]的情况
    int t = 0;
    int res = 0;
    for(int i=0;i<arr.size();++i)
    {
        t ^= arr[i];
        if(um.find(t) != um.end())
        {
            res += um[t][0] * i - um[t][1];
            ++um[t][0];
            um[t][1] += i+1;
        }
        else
        {
            um[t] = {1,i+1};
        }
    }

    return res;
}

int main()
{
    vector<int> arr = {2,3,1,6,7};  //4
    arr = {1,1,1,1,1};  //10
    printf("%d\n",countTriplets3(arr));

    return 0;
}