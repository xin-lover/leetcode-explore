//1155. 掷骰子的N种方法

#include <cstdio>
#include <vector>
#include <set>
#include <string>
#include <math.h>

using namespace std;

int fractorial(int n)
{
    int s = 1;
    int t = 1;
    while(t <= n)
    {
        s *= t;
        ++t;
    }

    return s;
}

void dfs(vector<int>& flags,int index,int d,int sum,int target,set<string>& arrangedGroups,long long& res)
{
    static int kmode=pow(10,9)+7;

    if(index >= d)
    {
        if(sum == target)
        {
            string s(flags.size(),'0');
            for(int i=0;i<flags.size();++i)
            {
                s[i] = flags[i]+'0';
            }

            //计算排列组合
            if(arrangedGroups.find(s) == arrangedGroups.end())
            {
                // printf("%s\n",s.c_str());
                arrangedGroups.insert(s);
                // int cc = 0;
                int denom = 1;
                for(int i=0;i<flags.size();++i)
                {
                    // cc += flags[i];//这里cc最终就是d，不用计算
                    denom *= fractorial(flags[i]);
                }
                res += fractorial(d) / denom; //去重
                res %= kmode;
            }

        }   

        return;
    }
    for(int i=1;i<=flags.size();++i)
    {
        ++flags[i-1];
        dfs(flags,index+1,d,sum+i,target,arrangedGroups,res);
        --flags[i-1];
    }
}

int numRollsToTarget(int d, int f, int target) {
    //思路：排列组合，把target分成d分，每一份不超过f
    //首先我们来看，target = d时，只有1种方式；
    //target=d+1时，多出来的1可以放到其它骰子上，所以时d种
    //target=d+2时，2有两种分配方式，可得d+d*(d-1)/2!
    //target=d+3时，3种分配方式，可得d+d*(d-1)/2! + d*(d-1)*(d-2)/3!
    //所以也就是说对于t=targe-d，先确定分堆，然后排列
    //对于分堆，我们使用回溯法

    //结果，超时,分堆的可能性太多
    vector<int> flags(f,0);
    set<string> arrangedGroups;
    
    long long res = 0;
    dfs(flags,0,d,0,target,arrangedGroups,res);
    return res;
}

int numRollsToTarget2(int d, int f, int target) {
    //思路：如果1个骰子，这个最简单，一种可能
    //1.2个骰子，可取(1,2……,target-1),也就是target-1种；
    //2.3个骰子，我们可以分成两部分，1个骰子和两个骰子，这样可以有target-1种分法，每一种分法在两个骰子那又会不同，
    //也就是总数为(1,target-2)+(2,target-3) + …… + (n,target-n-1)-n
    //这样可用动归
    //dp[i][j]表示i个骰子，得到target的组合数，那么dp[i][j] = sum(dp[i-1][target-n])n->1,j/2

    if(target > d*f)
    {
        return 0;
    }
    vector<vector<int>> dp(d+1,vector<int>(d*f+1,0));
    for(int i=1;i<=f;++i)
    {
        dp[1][i] = 1;
    }

    for(int i=2;i<=d;++i)
    {
        for(int j=d;j<=i*f;++j)
        {
            for(int k=1;k<=f;++k)
            {
                dp[i][j] += dp[i-1][j-k];
            }
        }
    }

    return dp[d][target];

}

int main()
{
    // printf("%d\n",numRollsToTarget2(1,6,3));//1
    // printf("%d\n",numRollsToTarget2(2,6,7));//6
    // printf("%d\n",numRollsToTarget2(2,5,10));//1
    // printf("%d\n",numRollsToTarget2(1,2,3));//0
    printf("%d\n",numRollsToTarget2(2,6,7));//
    return 0;
}