//664. 奇怪的打印机

#include <cstdio>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>

using namespace std;

int strangePrinter(const string& s, int start,int end,vector<vector<int>>& states)
{
    if(start > end)
    {
        return 0;
    }
    if(states[start][end] == 0)
    {
        states[start][end] = 1 + strangePrinter(s,start+1,end,states);
        for(int i=start+1;i<=end;++i)
        {
            if(s[i] == s[start])
            {
                states[start][end] = min(states[start][end],strangePrinter(s,start,i-1,states)+strangePrinter(s,i+1,end,states));
            }
        }
    }

    return states[start][end];
}
int strangePrinter(string s) {
    //思路：给定s，最少的打印次数是多少？s中有多少种字符
    //如何才能达到这种打印次数？那就是嵌套型的字符串，比如“aabbaa",也就是字符串的两侧是相同的
    //先用迭代吧，假设f(i,j)表示s的{i,j}区间的最少打印步数，那么对于f(i,j) = min{f(i,k)+f(k+1,j) | i<=k<=j}
    //就是我想的思路，为什么不坚持？其实这个思路和图的问题中求最短路径的差不多。。。
    
    if(s.empty())
    {
        return 0;
    }

    int n = s.size();
    vector<vector<int>> f(n,vector<int>(n,0));
    strangePrinter(s,0,n-1,f);

    return f[0][n-1];
}

int main()
{
    string s = "aaabbb"; //2
    // s = "aba"; //2
    s = "abdnbd";    //5
    // s= "ababc"; //4
    
    printf("%d\n",strangePrinter(s));

    return 0;
}