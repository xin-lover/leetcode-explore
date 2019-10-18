//leetcode 923. 三数之和的多种可能

#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;


//求两数之和的双指针法

int towSum(vector<int>& A, int target)
{
    int i=0,j=A.size()-1;
    int res = 0;
    while(i < j)
    {
        if(A[i] + A[j] < target)
        {
            ++i;
        }
        else if(A[i] + A[j] > target)
        {
            --j;
        }
        else
        {
            ++res;
            ++i;
            --j;
        }
    }

    return res;
}

//三数之和可以用三指针法，先排序，然后固定i，则新的target=target-A[i],就退化为两数之和了,因为有重复元素的情况
//特殊处理即可

int threeSumMulti(vector<int>& A, int target) {
    //思路：查看示例，发现有很多的重复数字，所以重复数字我们需要改变一下，记录其次数
    //先确定第一第二个数，然后找第三个数

    const int uplimit = pow(10,9) + 7;
    vector<int> nums(101,0);
    for(int i=0;i<A.size();++i)
    {
        ++nums[A[i]];
    }

    long long res =0;
    vector<bool> iflags(nums.size(),true);  //其实可以不用标记，我们这里保证i < j < k即可，因为j>i,所以只需要保证t > j即可,但要处理t==i和t==j的情况
    for(int i=0;i<nums.size();++i)
    {
        if(nums[i] == 0)
        {
            continue;
        }
        //三个数相同
        if(i + i + i == target && nums[i] > 2)
        {
            res += (static_cast<long long>(nums[i]) * (nums[i]-1) * (nums[i]-2) / 6);
        }
        vector<bool> flags(nums.size(),true);
        for(int j=i+1;j<nums.size();++j)
        {
            if(nums[j] == 0 || !flags[j])
            {
                continue;
            }

            flags[j] = false;
            int t = target - i - j;
            if(t < 0 || t >= nums.size() || nums[t] == 0 || !iflags[t])
            {
                continue;
            }

            printf("i:%d j:%d t:%d\n",i,j,t);
            flags[t] = false;
            if(t == i)
            {
                res += (nums[i] * (nums[i]-1) / 2 * nums[j]);
            }
            else if(t == j)
            {
                res += (nums[j] * (nums[j]-1) / 2 * nums[i]);
            }
            else
            {
                res += nums[i] * nums[j] * nums[t];
            }
        }

        iflags[i] = false;
    }

    return res % uplimit;
}

int main()
{
    vector<int> v = {1,1,2,2,2,2};
    // printf("%d\n",threeSumMulti(v,5));//12
    // v = {1,1,2,2,3,3,4,4,5,5};
    // printf("%d\n",threeSumMulti(v,8));//20
    // v = {16,51,36,29,84,80,46,97,84,16};
    // printf("%d\n",threeSumMulti(v,171));//2
    v = {0,0,0};
    printf("%d\n",threeSumMulti(v,0));//1


    return 0;
}