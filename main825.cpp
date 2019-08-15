//leetcode 825. 适龄的朋友

#include <cstdio>
#include <vector>

using namespace std;

int numFriendRequests(vector<int>& ages) {
    //思路：
    // age[B] <= 0.5 * age[A] + 7
    // age[B] > age[A]
    // age[B] > 100 && age[A] < 100
    //总的来说，A>=B,但A和B不能相差太大
    //策略就是：暴力遍历,但剪枝，也就是对ages排序

    //结果超时
    sort(ages.begin(),ages.end());
    int res = 0;
    for(int i=0;i<ages.size();++i)
    {
        for(int j=i+1;j<ages.size();++j)
        {
            if(ages[j] < 100 && ages[i] > 100)
            {
                break;
            }
            if(ages[i] <= 0.5 * ages[j] + 7)
            {
                break;
            }

            printf("%d %d\n",ages[j],ages[i]);
            if(ages[i] == ages[j])
            {
                res += 2;
            }
            else
            {
                ++res;
            }
            
        }
    }

    return res;
}

int numFriendRequests2(vector<int>& ages) {
    //思路：由条件可知每个年龄可发邀请的年龄段，所以使用二分法

    //优化
    //临界值,
    //1.小于15岁是不能发的请求的

    int res = 0;
    sort(ages.begin(),ages.end());

    int same = 0;
    for(int i=1;i<ages.size();++i)
    {
        if(ages[i] == ages[i-1])
        {
            ++same;
        }
        else
        {
            same = 0;
        }
        
        //只能大的给小的发
        int mn = ages[i] * 0.5 + 7;

        int left = 0,right = i;
        while(left < right)
        {
            int mid = left + (right - left) / 2;
            if(ages[mid] <= mn)
            {
                left = mid+1;
            }
            else
            {
                right = mid;
            }
        }

        res += i-left+(i-left>0 ? same : 0);
    }

    return res;
}

int numFriendRequests3(vector<int>& ages) {
    //优化：滑动窗口

    sort(ages.begin(),ages.end());
    int left =0;
    int res = 0;
    for(int i=1;i<ages.size();++i)
    {
        int mn = ages[i] * 0.5 + 7;
        while(left < i && ages[left]<=mn)
        {
            ++left;
        }

        printf("left:%d\n",left);
        res += i- left;
        if(i-left > 0)
        {
            int j =0;
            while(i-j-1>=0 && ages[i]== ages[i-j-1])
            {
                ++j;
            }
            res += j;
        }

    }

    return res;

}

int numFriendRequests4(vector<int>& ages) {
    //没看题目额外条件，最大年龄120岁
    //策略：统计各年龄的人数，然后计算满足条件的人数即可

    vector<int> counts(121,0);
    for(int i=0;i<ages.size();++i)
    {
        ++counts[ages[i]];
    }

    vector<int> dp(121,0);
    for(int i=1;i<121;++i)
    {
        dp[i] = dp[i-1] + counts[i];
    }
    int res = 0;
    for(int i=1;i<121;++i)
    {
        if(i < 15 || counts[i] <= 0)
        {
            continue;
        }

        res += counts[i] * (counts[i]-1);   //组内自发，每个人都可以给组内其它人发
        int t = i/2+7;
        if(i > t)
        {
            res += counts[i] * (dp[i-1]-dp[t]);//给其它组的人发
        }        
    }

    return res;
}

int numFriendRequests5(vector<int>& ages) {

    vector<int> counts(121,0);
    for(int i=0;i<ages.size();++i)
    {
        ++counts[ages[i]];
    }

    for(int i=1;i<121;++i)
    {
        counts[i]+=counts[i-1];
    }

    int res =0;
    for(int i=0;i<ages.size();++i)
    {
        int low = ages[i]/2 + 7;
        if(low >= ages[i])
        {
            continue;
        }
        if(ages[i] > low)
        {
            --res;
        }

        res += counts[ages[i]]-counts[low];
    }

    return res;
}


int main()
{
    vector<int> ages = {16,16};
    // ages = {16,16,16};
    // ages = {16,17,18};
    // // ages = {20,30,100,110,120};
    ages = {101,56,69,48,30};
    // // ages={6,6,112};
    // ages = {118,14,7,63,103};
    // ages = {14,7};
    // ages = {6,6};
    printf("%d\n",numFriendRequests5(ages));
    return 0;
}