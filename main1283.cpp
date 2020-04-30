//1283. 使结果不超过阈值的最小除数

#include <cstdio>
#include <vector>

using namespace std;

int smallestDivisor(vector<int>& nums, int threshold) {
    //思路：考虑二分法，但二分法要验证a<b,sum{nums[i]/a} > sum{nums[i]/b}
    //对于c,我们来看v1=c/a+(c%a>0)?1:0,v2=c/b+(c%b=0)?1:0;
    //那么我们令c=a*x+d=b*y+e,则v1=x+d==0?0:1;v2=y+e==0?0:1
    //a<b,那么x>y;
    //假设x==y,那么d<e,d==0 => v1<v2,d>0=>v1==v2；综合v1>=v2
    //假设x>y,那么d<e,x,y最接近时是d=0,e>d,也就是v1=x,v2=y+1,=>v1>=v2
    //可以看出整体上是递减的,符合二分查找

    int left=1,right=INT_MAX;
    while(left<right)
    {
        int mid = left + (right-left)/2;

        int sum =0;
        for(int i=0;i<nums.size();++i)
        {
            // sum += nums[i]/mid + (nums[i]%mid == 0 ? 0 : 1); //这个是可优化点
            sum += (nums[i] - 1) / mid + 1;;
        }

        if(sum <= threshold)
        {
            right = mid;
        }
        else
        {
            left = mid+1;
        }
        
    }

    return left;
}

int main()
{
    vector<int> nums = {1,2,5,9};
    int threshold = 6; //5

    nums = {2,3,5,7,11};
    threshold = 11;
    printf("%d\n",smallestDivisor(nums,threshold));
    return 0;
}