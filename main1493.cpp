//1493. 删掉一个元素以后全为 1 的最长子数组

#include <cstdio>
#include <vector>

using namespace std;

int longestSubarray(vector<int>& nums) {
    //思路：可以考虑滑动窗口，第一次遇到0时，不处理
    //直到第二次遇到0，然后我们开始缩小窗口直到之前的0

    int lastZero = -1;
    // int secondZero = -1;
    int left = 0;
    int res = 0;
    for(int i=0;i<nums.size();++i)
    {
        if(nums[i] == 0)
        {
            if(lastZero != -1)
            {
                res = max(res,i-left);
                left = lastZero+1;
            }
            
            lastZero = i;
        }
    }

    res = max(res,(int)nums.size() - left);

    return res-1;
}

//动归思路：假设nums[i]==0,那么包含索引i的子数组长度是以i-1结尾的全1子数组和以i+1开头的全1子数组的长度和
//所以分别从左往右和从右往左遍历求出对应值即可
//上面的思路需要遍历3次，用两个额外的数组，可以优化：
//记p(i)是以索引i结尾的全1最长子数组长度，q(i)为以索引i结尾且删除一个0时的最长全1子数组长度
//递推公式：nums[i]==0,则q(i)=p(i-1),否则q(i)=q(i-1)+1
int longestSubarray2(vector<int>& nums) {

    int res = 0;
    int p=0,q=0;
    for(int n : nums)
    {
        if(n == 0)
        {
            q = p;  //注意多出的0是要被删除的,所以不是p+1
            p=0;
        }
        else
        {
            ++p;
            ++q;
        }

        res = max(res,q);
    }

    if(res == nums.size())
    {
        return res-1;
    }
    
    return res;
}

int main()
{
    vector<int> nums = {1,1,0,1}; //3
    nums = {0,1,1,1,0,1,1,0,1}; //5
    nums = {1,1,1}; //2
    nums = {1,1,0,0,1,1,1,0,1}; //4
    // nums = {0,0,0}; //0

    printf("%d\n",longestSubarray2(nums));

    return 0;
}