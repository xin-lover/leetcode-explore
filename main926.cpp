//leetcode 926. 将字符串翻转到单调递增

#include <cstdio>
#include <string>
#include <vector>

using namespace std;

int minFlipsMonoIncr(string S) {
    //思路：考虑动归，dp1[i]表示第i个时为0且递增需要翻转的次数，dp2[i]表示第i个为1且递增需要翻转的次数

    if(S.empty())
    {
        return 0;
    }
    vector<int> dp0(S.size());
    vector<int> dp1(S.size());

    dp0[0] = S[0]=='0' ? 0 : 1;
    dp1[0] = S[0]=='0' ? 1 : 0;

    for(int i=1;i<S.size();++i)
    {
        if(S[i] == '0')
        {
            dp0[i] = dp0[i-1];
            dp1[i] = dp1[i-1] + 1;
        }
        else
        {
            dp0[i] = dp0[i-1] + 1;
            dp1[i] = min(dp0[i-1],dp1[i-1]);
        }
    }

    return min(dp0.back(),dp1.back());
}

int minFlipsMonoIncr(string S,int start,int ones) {
    int count = 0;
    int n = S.size();
    for(int i=start;i<S.size();++i)
    {
        if(S[i] == '1')
        {
            ++count;
        }
        else if(i > 0 && S[i-1] == '1')
        {
            return min(count+minFlipsMonoIncr(S,i+1,ones-count),1 + (n-i-1 - (ones - count)));
        }
    }

    return 0;
}

int minFlipsMonoIncr2(string S) {
    //思路：找逆序，也就是’10‘的情况，对于这种情况有两种处理，即1变0或0变1
    //如果0变1，那么后面的0都要变为1，
    //如果1变0，那么后续的结果需要迭代

    int ones = 0;
    for(auto a : S)
    {
        if(a == '1')
        {
            ++ones;
        }
    }

    return minFlipsMonoIncr(S,0,ones);
}

int minFlipsMonoIncr3(string S) {
    //前缀和：其实最终答案就是m个0和n个1的顺序排列，那么我们只需要选出一个位置，让它之前都是0，之后都是1即可
    //所以方案就是使用p[i]记录第i个位置前有多少个1，然后计算以这个位置为分割，需要的翻转次数，选最小值即可

    int n = S.size();
    int res = n;
    vector<int> p(n+1,0);
    for(int i=0;i<n;++i)
    {
        if(S[i] == '1')
        {
            p[i+1] = p[i]+1;
        }
        else
        {
            p[i+1] = p[i];
        }
    }

    for(int i=0;i<=n;++i)
    {
        res = min(res,p[i] + (n-i-(p[n]-p[i])));
    }

    return res;
}

int main()
{
    printf("%d\n",minFlipsMonoIncr3("00110"));   //1
    printf("%d\n",minFlipsMonoIncr3("010110"));   //2
    printf("%d\n",minFlipsMonoIncr3("00011000"));   //2
    printf("%d\n",minFlipsMonoIncr3("11011"));   //1
    return 0;
}