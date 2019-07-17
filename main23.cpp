#include <cstdio>
#include <string>
#include <vector>

using namespace std;

bool isSubsequence(string s, string t) {
    
    //思路：主要的问题在于t会非常大，如何快速求解是这个问题的关键
    //先用普通遍历法求解

    // if(s.empty())
    // {
    //     return true;
    // }
    // if(s.size() > t.size())
    // {
    //     return false;
    // }

    // int cur = 0;
    // for(int i=0;i<t.size();++i)
    // {
    //     if(t[i] == s[cur])
    //     {
    //         ++cur;
    //         if(cur >= s.size())
    //         {
    //             return true;
    //         }
    //     }
    // }

    // return false;

    //思考大量调用情况下，如何优化
    //也就是说如何使用已有结果
    //网络思路：存储每个字母出现的位置集合，对于s的每个字母使用二分法查找是否存在递增的位置

    vector<vector<int>> ay(26,vector<int>());
    for(int i=0;i<t.size();++i)
    {
        ay[t[i]-'a'].push_back(i);
    }

    int next = -1;
    for(int i=0;i<s.size();++i)
    {
        vector<int> &st = ay[s[i]-'a'];
        if(st.empty())
        {
            return false;
        }
        int left=0,right=st.size()-1;
        while(left < right)
        {
            int mid = left + (right-left) / 2;
            if(st[mid] <= next)
            {
                left = mid+1;
            }
            else
            {
                right = mid;
            }
            
        }

        if(st[left] <= next)
        {
            return false;   
        }

        next = st[left];
    }

    return true;

}

int main()
{
    printf(isSubsequence("aac","addshc") ? "true" : "false");
    printf("\n");
    return 0;
}