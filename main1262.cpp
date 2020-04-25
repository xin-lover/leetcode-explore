//1262. 可被三整除的最大和

#include <cstdio>
#include <vector>

using namespace std;

int maxSumDivThree(vector<int>& nums) {
    //思路：使用回溯法复杂度太高
    //我们可以考虑分集合，除3有3中结果，余数分别为0，1，2
    //我们可以拿这些集合中的数来组合，分别有1+2，1*3，2*3
    //现在的问题是如何确定选择？
    //1.假设1集合的数量多于2集合的，优先1+2的情况，则剩余(c1-c2)%3个1集合中的数；如果优先3个1集合的元素组合，那么剩余c2-(c1%3)个2集合中元素
    //也就是最后只会剩余其中一种元素，我们只需要判断一下就可以了
    //2.如果优先3个集合元素组合的话，那么两个集合最后都少于3个元素，而且根据1，我们只会剩余1种，所以我们对集合排序，然后判断留1还是留2集合的元素,这种方式简单一些

    vector<int> set1;
    vector<int> set2;

    int sum = 0;
    for(int i=0;i<nums.size();++i)
    {
        sum += nums[i];
        int p = nums[i] % 3;
        if(p == 1)
        {
            set1.push_back(nums[i]);
        }
        else if(p == 2)
        {
            set2.push_back(nums[i]);
        }
    }

    if(sum % 3== 0)
    {
        return sum;
    }

    int res = 0;
    int tmp = sum;
    //留1
    sort(set1.begin(),set1.end());
    for(int i=0;i<3 && i<set1.size();++i)
    {
        tmp -= set1[i];
        if(tmp % 3 == 0)
        {
            res = max(res,tmp);
            break;
        }
    }

    //留2
    tmp = sum;
    sort(set2.begin(),set2.end());
    for(int i=0;i<3 && i<set2.size();++i)
    {
        tmp-=set2[i];
        if(tmp % 3 == 0)
        {
            res = max(res,tmp);
            break;
        }
    }

    return res;
    
}

//第二种思路：dp，记录和除3后余数的情况，对此也就变成了求dp[0]最大的情况
//对于每一个数字,dp[0] = max(dp[0],nums[i]%3 + dp[nums[i]%3])
//这里唯一的疑问就是选取数字可能的先后情况，也就是说同样余1，我们可能选择后面大的数，你一开始就选择小的数，会把后面的大的数排除了
//但因为这里还会记录dp[1],dp[2]当前最大的值，所以dp[0]会更新会最大的情况
int maxSumDivThree2(vector<int>& nums) {
    int dp[3] = {0, 0, 0};
    
    for (int i = 0; i < nums.size(); ++i) {
        int mod = nums[i] % 3;

        int a = dp[(3 + 0 - mod) % 3];
        int b = dp[(3 + 1 - mod) % 3];
        int c = dp[(3 + 2 - mod) % 3];
        
        if (a || mod == 0) dp[0] = std::max(dp[0], a + nums[i]);
        if (b || mod == 1) dp[1] = std::max(dp[1], b + nums[i]);
        if (c || mod == 2) dp[2] = std::max(dp[2], c + nums[i]);
    }
    return dp[0];
}

int main()
{
    vector<int> v = {1,2,3,4,4};//12
    // v = {4};//0
    v = {3,6,5,1,8};//18
    // v = {2,6,2,2,7};//15
    printf("%d\n",maxSumDivThree2(v));
    return 0;
}