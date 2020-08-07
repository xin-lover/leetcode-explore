//1477. 找两个和为目标值且不重叠的子数组

#include <cstdio>
#include <vector>

using namespace std;

int minSumOfLengths(vector<int>& arr, int target) {
    //思路：可以用浮动窗口法找到所有符合要求的子数组，然后找最小和

    vector<vector<int>> areas;
    int sum = 0;
    int left = 0;
    for(int i=0;i<arr.size();++i)
    {
        sum += arr[i];
        if(sum == target)
        {
            areas.push_back({left,i});
            printf("push:%d %d\n",left,i);
            sum -= arr[left];
            left++;
        }
        else if(sum > target)
        {
            while(sum > target)
            {
                sum -= arr[left];
                left++;
                if(sum == target)
                {
                    areas.push_back({left,i});
                }
            }

        }
    }

    if(sum == target)
    {
        areas.push_back({left,(int)arr.size()-1});
    }

    if(areas.size() < 2)
    {
        return -1;
    }

    //这个地方复杂度有点高，可以用动归的方式优化一下，记录每一个位置之前之后符合要求的最短子数组
    int res = INT_MAX;
    // for(int i=0;i<areas.size();++i)
    // {
    //     for(int j=i+1;j<areas.size();++j)
    //     {
    //         if(areas[i][1] < areas[j][0])
    //         {
    //             res = min(res,areas[i][1]-areas[i][0] + areas[j][1]-areas[j][0] + 2);
    //         }
    //     }
    // }

    //这个空间复杂度高一些，想减少的化可以配合二分
    vector<int> dp1(arr.size());
    int mn = INT_MAX;
    int j = 0;
    for(int i=0;i<arr.size();++i)
    {
        while(j < areas.size() && i >= areas[j][1])
        {
            mn = min(mn,areas[j][1]-areas[j][0]+1);
            ++j;
        }

        dp1[i] = mn;
    }

    vector<int> dp2(arr.size());
    mn = INT_MAX;
    j=areas.size()-1;
    for(int i=arr.size()-1;i>=0;--i)
    {
        while(j>=0 && i < areas[j][0])
        {
            mn = min(mn,areas[j][1]-areas[j][0]+1);
            --j;
        }

        dp2[i] = mn;
    }

    for(int i=0;i<arr.size();++i)
    {
        if(dp1[i] == INT_MAX || dp2[i] == INT_MAX)
        {
            continue;
        }
        res = min(res,dp1[i] + dp2[i]);
    }

    return res==INT_MAX ? -1 : res;
}

//动归的简单写法
int minSumOfLengths2(vector<int>& arr, int target) {
    //假设dp[i]是以第i个元素结尾的符合要求的最短子数组长度
    //那么dp[i]= dp[j] + i-j+1;其中sum[i,j]==target

    vector<int> dp(arr.size()+1,-1);
    int sum = 0;
    int left = 0;
    int res = INT_MAX;
    for(int i=1;i<=arr.size();++i)
    {
        sum += arr[i-1];
        while(sum > target && left <i)
        {
            sum -= arr[left];
            ++left;
        }

        if(sum == target)
        {
            if(dp[left]> -1)
            {
                res = min(res,dp[left] + i-left);
            }
            dp[i] = i-left;
            if(dp[i-1] > -1)
            {
                dp[i] = min(dp[i-1],dp[i]);
            }
        }
        else
        {
            dp[i] = dp[i-1];
        }
    }

    return res==INT_MAX ? -1 : res;
} 

int main()
{
    vector<int> arr = {3,2,2,4,3};
    int target = 3; //2

    arr = {7,3,4,7}, target = 7;    //2
    arr = {4,3,2,6,2,3,4}, target = 6;  //-1

    arr = {1,2,2,3,2,6,7,2,1,4,8},target = 5;   //4

    arr = {1,6,1},target = 7;   //-1
    printf("%d\n",minSumOfLengths2(arr,target));

    return 0;
}