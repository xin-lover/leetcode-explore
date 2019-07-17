//leetcode 611. 有效三角形的个数

#include <cstdio>
#include <vector>

using namespace std;

int triangleNumber(vector<int>& nums) {
    
    //思路：组成三角形的条件:a+b>c,a+c>b,b+c>a
    //暴力破解，没问题，但会超时，其中有很多计算是重复的
    //优化：首先排序，先选取两个元素，a，b，其中a<b,则由上述公式推导出：b-a < c < a + b

    sort(nums.begin(),nums.end());

    int res = 0;
    int lastCount = 0;
    for(int i=0;i<nums.size();++i)
    {
        if(nums[i] == 0)
        {
            lastCount = 0;
            continue;
        }
        for(int j=i+1;j<nums.size();++j)
        {
            if(!(j-i > 1 && j < nums.size() - 1 && nums[j] == nums[j-1]))
            {
                lastCount = 0;
                for(int k=j+1;k<nums.size();++k)
                {
                    if(nums[k] < nums[i] + nums[j])
                    {
                        ++lastCount;
                    }
                    else
                    {
                        break;
                    }
                }   
            }
            
            printf("lastcount:%d\n",lastCount);
            res += lastCount;
        }
    }

    return res;
}

int main()
{
    vector<int> v = {2,2,2,3};

    printf("%d\n",triangleNumber(v));
    return 0;
}