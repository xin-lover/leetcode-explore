//leetcode 667. 优美的排列 II

#include <cstdio>
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;

bool backtrace(vector<int>& nums,set<int> difference,int step,int lastestNum,int k)
{
    if(step == nums.size())
    {
        return difference.size()  == k;
    }
    else
    {
        if(difference.size() > k)
        {
            return false;
        }
    }
    
    for(int i=0;i<nums.size();++i)
    {
        if(nums[i] == -1)
        {
            int dif = abs(i-lastestNum);
            nums[i] = step;
            if(difference.find(dif) == difference.end())
            {
                difference.insert(dif);
                if(backtrace(nums,difference,step+1,i,k))
                {
                    return true;
                }
                difference.erase(dif);
            }
            else
            {
                if(backtrace(nums,difference,step+1,i,k))
                {
                    return true;
                }
            }
            
            nums[i] = -1;
        }
    }

    return false;
}

vector<int> constructArray(int n, int k) {
    //思路：使用回溯法
    //优化空间使用，使用一个数组存储数字的位置，默认值为-1
    //超时
    // if(k > n-1)
    // {
    //     return vector<int>();
    // }

    // vector<int> nums(n,-1);
    // set<int> difference;
    // for(int i=0;i<n;++i)
    // {
    //     nums[i] = 0;
    //     if(backtrace(nums,difference,1,i,k))
    //     {
    //         vector<int> res(n);
    //         for(int j=0;j<n;++j)
    //         {
    //             int pos = nums[j];
    //             res[pos] = j+1;
    //         }
    //         return res;
    //     }
    //     nums[i]=-1;
    // }
    // return vector<int>();

    //思路：差值可能是1～n-1，n-1的情况只有一种，n-2的情况两种，依此类推，1的情况由n-1种，当然因为是绝对值，所以这些情况总数应该乘2
    //考虑k=1的情况，只有两种情况（逆序排列也符合要求）
    //k=2时，只需要在上述的情况下任意交换其中两个数字即可
    //k=3时，我们考虑n=4，这个时候我们知道差值的最大数量就是3，而差值为3的情况只有2种，即[1,4][4,1]，它们是等价的，所以我们只考虑一种[1,4]
    //然后我们考虑差值2，有4-2种情况，即[3,1][4,2]，两种也是等价的，选择其中一种,[3,1,4]，那这个时候就只剩下2了，也只能放在3前，结果就出来了[2,3,1,4]
    //我们回过去，考虑n=4,k=2的情况，那么我们任意交换[2,3,1,4]的两个数就符合要求，[3,2,1,4]
    //可以总结出来：不考虑等价情况，比如[1,4][4,1]，对每一个k由n-k种情况满足要求
    //构建数组时，我们可以采用交换两个数的方法，同时选择交换数的策略是使我们接下来能有更多组合的策略，不然我们就需要改变之前的选择
    //即如果我们把3和2分别放到1的旁边，就不能得到差值为3的情况
    //所以情况就变为
    //n=4,k=1 [1,2,3,4]
    //n=4,k=2 [1,4,3,2]
    //n=4,k=3 [1,4,2,3]
    //即初始情况为顺序排列，每次确定一个数，把剩余的数逆序

    // vector<int> res(n);
    // for(int i=0;i<n;++i)
    // {
    //     res[i] = i+1;
    // }

    // for(int i=1;i<k;++i)
    // {
    //     int len = n-i;
    //     for(int j=0;j<len/2;++j)
    //     {
    //         swap(res[i+j],res[i+len -1-j]);
    //     }
    // }

    // return res;

    //优化，上述的交换过程浪费太长时间，总结规律可以发现，前面数字都是剩余数字的最大或最小值，然后剩余数字顺序或逆序排列

    // int left = 1,right=n;
    // vector<int> res(n);
    // bool order = true;
    // for(int i=1;i<=k;++i)
    // {
    //     res[i-1] = order ? left++ : right--;
    //     order = !order;
    // }

    // if(order)
    // {
    //     for(int i=right;i>=left;--i)
    //     {
    //         res[k+right-i] = i;
    //     }
    // }
    // else
    // {
    //    for(int i=left;i<=right;++i)
    //     {
    //         res[k+i-left] = i;
    //     }
    // }
    // return res;

    // vector<int> resVec(n, 0);
    // int numK = k + 1, numTemp = 1;
    // //下标段[0, k]中，偶数下标填充[1,2,3..]
    // for (int i = 0; i <= k; i += 2){
    //     resVec[i] = numTemp++;
    // }
    // //下标段[0, k]中，奇数下标填充[k + 1, k, k - 1...]
    // for (int i = 1; i <= k; i += 2){
    //     resVec[i] = numK--;
    // }
    // //下标段[k + 1, n - 1]都是顺序填充
    // for (int i = k + 1; i < n; ++i) {
    //     resVec[i] = i + 1;
    // }
    // return resVec;

    vector<int> res;
    int i=1,j=n;
    while(i<=j){
        res.push_back(k>1?(k--%2?i++:j--):i++);
    }
    return res;
    
}

int main()
{
    vector<int> res = constructArray(4,3);
    for(auto a : res)
    {
        printf("%d ",a);
    }
    printf("\n");
    return 0;
}