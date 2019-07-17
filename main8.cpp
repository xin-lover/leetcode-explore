#include <vector>
#include <string>
#include <cstdio>

using namespace std;

class Solution {
public:
    int findLUSlength(vector<string>& strs) {
        
        if(strs.empty())
        {
            return 0;
        }
        
        if(strs.size() == 1)
        {
            return strs[0].size();
        }
        
        int res = -1;
        vector<string> v;
        for(int i=0;i+1<strs.size();i+=2)
        {
            string t;
            findLUSLength(strs[i],strs[i+1],t,res);
            v.push_back(t);
        }
        
        if(strs.size() % 2 == 1)
        {
            v.push_back(strs.back());
        }
        
        return max(res,findLUSlength(v));
    }
    
    int findLUSLength(string a, string b, string& longstr, int& res)
    {
        int m = a.size();
        int n = b.size();
        int p = -1;
        if(m < n)
        {
            longstr = b;
            p = longstr.size();
        }
        else if(m > n)
        {
            longstr = a;
            p = longstr.size();
        }
        else
        {
            for(int i=a.size() -1;i>=0;--i)
            {
                if(a[i] != b[i])
                {
                    p = i + 1;
                }
            }
            
            longstr = a;
        }
        
        res = max(res,p);
        return p;
        printf("%s %s %d\n",a.c_str(),b.c_str(),res);
    }
};

int main()
{
    Solution s;
    vector<string> strs = {"aaa","aaa","aa"};
    printf("%d\n",s.findLUSlength(strs));
    return 0;
}