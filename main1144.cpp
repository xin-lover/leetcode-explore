//

#include <cstdio>
#include <vector>

using namespace std;

int movesToMakeZigzag(vector<int>& nums) {
    //思路：因为每一个数字的变化都会影响其前后数字变化的情况，所有用回溯或dfs负复杂度会很高
    //考虑动归，如果数组只有两个数字，那么只要他们不相同，则符合要求
    //对于3个数字，因为只有递减操作，如果我们遇到递减序列的时候，我们有两个选择，缩减第一个或第二数字
    //如果是递增序列，也是两个，缩减第二个或第三个
    //如果先确定前面，那么对于递减序列缩减第1个数字的情况可能会再造一个递减序列，所以前面也无法确定了
    //但再细想，递减序列，缩减第二个和缩减第一个的成本，我们发现肯定第第一个的大，所以我们不可能缩减第一个，而且第一个可能引发新的递减序列
    //而对于递增序列，缩减第二个的成本小，但会造成新的递减序列，也就是说每个数字的位置都可能造成递增递减的可能，太乱了
    //换一种思路，我们发现只有两种情况，也就是前两个元素递增递减的情况，只要确定他们两个，后面操作就很清楚了
    //比如碰到递减序列，我们只能把前面的整体缩减，某则就是另一种情况了

    //第一种情况，递增
    vector<int> tmp = nums;
    int res1 = 0;
    for(int i=1;i<tmp.size();++i)
    {
        if(i & 1)
        {
            if(tmp[i] <= tmp[i-1])
            {
                //递减前面的
                for(int j=i-1;j>=0;--j)
                {
                    if(j & 1)
                    {
                        if(tmp[j] > tmp[j+1])
                        {
                            break;
                        }
                        res1 += tmp[j+1]-tmp[j]+1;
                        tmp[j] = tmp[j+1]+1;
                    }
                    else 
                    {
                        if(tmp[j] < tmp[j+1])
                        {
                            break;
                        }
                        res1 += tmp[j] -tmp[j+1]+1;
                        tmp[j] = tmp[j+1]-1;
                    }
                }

            }
        }
        else 
        {
            if(tmp[i] >= tmp[i-1])
            {
                res1 += tmp[i]-tmp[i-1]+1;
                tmp[i] = tmp[i-1]-1;
            }
        }
    }

    for(auto a :tmp)
    {
        printf("%d ",a);
    }
    printf("\n");
    //递减
    tmp = nums;
    int res2 = 0;
    for(int i=1;i<tmp.size();++i)
    {
        if(i & 1)
        {
            if(tmp[i] >= tmp[i-1])
            {
                res2 += tmp[i]-tmp[i-1]+1;
                tmp[i] = tmp[i-1]-1;
            }
        }
        else 
        {
            if(tmp[i] <= tmp[i-1])
            {
                //递减前面的
                for(int j=i-1;j>=0;--j)
                {
                    if(j & 1)
                    {
                        if(tmp[j] < tmp[j+1])
                        {
                            break;
                        }
                        res2 += tmp[j]-tmp[j+1]+1;
                        tmp[j] = tmp[j+1]-1;
                    }
                    else 
                    {
                        if(tmp[j] > tmp[j+1])
                        {
                            break;
                        }
                        res2 += tmp[j+1] -tmp[j]+1;
                        tmp[j] = tmp[j+1]+1;
                    }
                }

            }
        }
    }

    for(auto a :tmp)
    {
        printf("%d ",a);
    }
    printf("\n");
    printf("%d %d\n",res1,res2);
    return min(res1,res2);
}

//这个思路更清新，因为只能缩减，所以分为只变动奇数位置或只变动偶数位置的数
// int movesToMakeZigzag(vector<int>& nums) {
//     int ans1 = 0;
//     int ans2 = 0;
//     for(int i = 1;i < nums.size(); i += 2){
//         int raise = 0;
//         if(nums[i] >= nums[i-1]){
//             raise = abs(nums[i]-nums[i-1]) + 1;
//         }
//         if(i+1 < nums.size()&& nums[i] >= nums[i+1]){
//             raise = max(raise,abs(nums[i]-nums[i+1])+1);
//         }
//         ans1 += raise;
//     }
    
//     for(int i = 0;i < nums.size(); i += 2){
//         int raise = 0;
//         if(i > 0 && nums[i] >= nums[i-1]){
//             raise = abs(nums[i]-nums[i-1]) + 1;
//         }
//         if(i+1 < nums.size()&& nums[i] >= nums[i+1]){
//             raise = max(raise,abs(nums[i]-nums[i+1])+1);
//         }
//         ans2 += raise;
//     }
    
//     return min(ans1,ans2);
// }

int main()
{
    vector<int> nums = {1,2,3};
    nums = {9,6,1,6,2};
    nums = {10,4,4,10,10,6,2,3};
    printf("%d\n",movesToMakeZigzag(nums));
    return 0;
}