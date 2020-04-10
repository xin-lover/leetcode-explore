//1209. 删除字符串中的所有相邻重复项 II

#include <cstdio>
#include <vector>
#include <string>
#include <stack>

using namespace std;

string removeDuplicates(string s, int k) {
    //思路：最简单的就是按步骤重复扫描，但这样扫描和合并的操作会很多
    //同时k可能很大，这样一个一个字符扫描，效率低
    //可以统计连续相同的字符的个数，组成一个序列，这样子合并比较好
    //合并时借助栈

    if(s.empty())
    {
        return "";
    }

    char cur = s[0];
    int count = 1;
    stack<pair<char,int>> sk;
    int len = 0; //记录最后字符串需要的长度，避免合并时额外的空间申请
    for(int i=1;i<=s.size();++i)
    {
        if(s[i] == cur)
        {
            ++count;
        }
        else
        {
            while(!sk.empty() && sk.top().first == cur)
            {
                auto p = sk.top();
                sk.pop();

                count += p.second;
                len -= p.second;
            }

            count %= k;
            if(count > 0)
            {
                sk.push({cur,count});
                len += count;
            }

            cur = s[i];
            count = 1;
        }
    }

    string res(len,'0');
    int i = len-1;
    while(!sk.empty())
    {
        auto p = sk.top();
        sk.pop();
        int t = p.second;
        while(t-- > 0)
        {
            res[i--] = p.first;
        }
    }

    return res;
}

int main()
{
    string s = "deeedbbcccbdaa";
    int k = 3; //aa
    
    // s = "pbbcggttciiippooaais";
    // k =2;   //ps
    printf("%s\n",removeDuplicates(s,k).c_str());

    return 0;
}