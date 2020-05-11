//1291. 顺次数

#include <cstdio>
#include <vector>

using namespace std;

vector<int> sequentialDigits(int low, int high) {
    //思路：因为顺次数肯定不多，一个思路就是找到所有的顺次数
    //然后用二分法

    vector<int> nums;
    for(int j=2;j<10;++j)
    {
        for(int i=1;i+j-1<10;++i)
        {
            int k = i;
            int t = i;
            int p = 1;
            while(p++ < j)
            {
                t *= 10;
                ++k;
                t += k;
            }
            nums.push_back(t);
        }
    }

    for(auto a : nums)
    {
        printf("%d ",a);
    }
    printf("\n");

    int lowPos=0,highPos = 0;
    int left=0,right=nums.size();
    while(left < right)
    {
        int mid = left + (right - left) / 2;
        if(nums[mid] >= low)
        {
            right = mid;
        }
        else
        {
            left = mid+1;
        }
    }
    lowPos = left;

    left=0,right=nums.size();
    while(left < right)
    {
        int mid = left + (right - left) / 2;
        if(nums[mid] > high)
        {
            right = mid;
        }
        else
        {
            left = mid+1;
        }
    }
    highPos = right;

    vector<int> res(highPos-lowPos);
    std::copy(nums.begin()+lowPos, nums.begin()+highPos, res.begin());
    return res;
}

int main()
{
    int low = 100, high = 300;  //[123,234]
    low = 1000, high = 13000;   //[1234,2345,3456,4567,5678,6789,12345]
    low = 10, high = 1000000000;    //[12,23,34,45,56,67,78,89,123,234,345,456,567,678,789,1234,2345,3456,4567,5678,6789,12345,23456,34567,45678,56789,123456,234567,345678,456789,1234567,2345678,3456789,12345678,23456789,123456789]
    auto res = sequentialDigits(low,high);
    for(auto a :res)
    {
        printf("%d ",a);
    }
    printf("\n");
    return 0;
}