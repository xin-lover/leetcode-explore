#include <cstdio>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        
        if(s.size() < 11)
        {
            return {};
        }
        //思路：简单的十个遍历
        int n = s.size();
        vector<string> res;
        for(int i=0;i<=n-10;++i)
        {
            for(int j=i+1;j<=n-10;++j)
            {
                bool have = true;
                for(int k=0;k<10;++k)
                {
                    if(s[i+k] != s[j+k])
                    {
                        have = false;
                        break;
                    }
                }
                
                if(have)
                {
                    printf("%d %d %d\n",i,j,n);
                    res.push_back(s.substr(i,10));
                    break;
                }
            }
        }
        
        return res;
    }
};

int main()
{
    Solution s;
    auto res = s.findRepeatedDnaSequences("aaaaaaaaaaa");
    for(auto a : res)
    {
        printf("%s\n",a.c_str());
    }
    return 0;
}