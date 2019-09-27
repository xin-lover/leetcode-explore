//leetcode 904. 水果成篮

#include <cstdio>
#include <vector>
#include <unordered_map>

using namespace std;

int totalFruit(vector<int>& tree) {
    //思路：有点像最长连续子序列，但连续指就两个数
    //因为不循环，最简单的就是暴力破解

    if(tree.size() < 3)
    {
        return tree.size();
    }
    int res = 0;
    int t1=-1,t2=-1;
    for(int i=1;i<tree.size();++i)
    {
        t1 = tree[i-1];
        t2 = tree[i];

        int c = 2;
        for(int j=i+1;j<tree.size();++j)
        {
            if(tree[j] == t1 || tree[j] == t2)
            {
                ++c;
            }
            else
            {
                break;
            }
        }

        res = max(res,c);
    }

    return res;
}

int totalFruit2(vector<int>& tree) {
    //思路：考虑动归，dp[i]表示把tree[i]放入篮子时的结果
    //那tree[i]==tree[i+1]时，dp[i] = dp[i+1]+1;
    //问题是有两个类型，另一个类型如何判断？直接遍历找没问题，
    //还可以对tree做处理，把重复的数字归拢一下

    int n = tree.size();
    if(n < 3)
    {
        return n;
    }

    vector<pair<int,int>> newtree;
    int start = 0;
    int count = 1;
    for(int i=1;i<n;++i)
    {
        if(tree[i] == tree[start])
        {
            ++count;
        }
        else
        {
            newtree.push_back({tree[start],count});
            start = i;
            count = 1;
        }
    }

    newtree.push_back({tree[start],count});

    n = newtree.size();
    if(n<3)
    {
        return tree.size();
    }
    vector<int> dp(n,0);
    dp[0] = newtree[0].second;
    dp[1] = dp[0] + newtree[1].second;
    int res = dp[1];
    for(int i=2;i<n;++i)
    {
        if(newtree[i].first == newtree[i-2].first)
        {
            dp[i] = dp[i-1] + newtree[i].second;
        }
        else
        {
            dp[i] = newtree[i-1].second + newtree[i].second;
        }

        res = max(res,dp[i]);
    }

    return res;
}


int totalFruit3(vector<int>& tree) {
    //滑动窗口
    //记录开始下表i，使用map记录当前类型的个数，一旦超过两个，则从i开始，把遇到的类型-1，知道类型数回到2
    //也就是保证窗口内的类型只有两个，窗口右边先往右扩张，类型数大于3后，窗口左边向右缩小
    //虽然也是O(n),但与上面的相比，运算量还是大一些

    int res = 0;
    int left = 0;

    unordered_map<int,int> um;
    for(int i=0;i<tree.size();++i)
    {
        ++um[tree[i]];
        while(um.size() >= 3)
        {
            --um[tree[left]];
            if(um[tree[left]] == 0)
            {
                um.erase(tree[left]);
            }

            ++left;
        }

        res = max(res,i-left+1);
    }

    return res;
}

int main()
{
    vector<int> v = {1,2,1};
    v = {0,1,2,2};
    // v = {0};
    v = {3,3,3,1,2,1,1,2,3,3,4};
    // v = {3,3,3,1,4};
    printf("%d\n",totalFruit3(v));
    return 0;
}