#include <cstdio>
#include <map>
#include <vector>
#include <map>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        
        unordered_map<char,int> um;
        for(auto c : s1)
        {
            if(um.find(c) != um.end())
            {
                ++um[c];
            }
            else
            {
                um[c] = 1;
            }
        }
        
        int len1 = s1.size();
        for(int i=0;i<len1;++i)
        {
            char c = s2[i];
            if(um.find(c) != um.end())
            {
                --um[c];
            }
        }
        
        bool contain = true;
        for(auto it = um.begin();it!=um.end();++it)
        {
            if(it->second != 0)
            {
                contain = false;
                break;
            }
        }
        
        if(contain)
        {
            return true;
        }

        int end = s2.size() - len1 + 1;
        for(int i=1;i< end;++i)
        {
            char pc = s2[i-1];
            char ec = s2[i + len1 - 1];
            if(pc == ec)
            {
                continue;
            }
            
            printf("vvvvv: %d\n",i);
            if(um.find(pc) != um.end())
            {
                ++um[pc];
            }
            
            if(um.find(ec) != um.end())
            {
                --um[ec];
            }
            
            bool contain = true;
            for(auto it = um.begin();it!=um.end();++it)
            {
                if(it->second != 0)
                {
                    contain = false;
                    break;
                }
            }

            if(contain)
            {
                printf("wh %d\n",um.size());
                return true;
            }
                
        }
        
        return false;
    }
};

int hh()
{
    int a = 0;
    return a=1;
}

int main()
{
	// Solution s;
    // bool res = s.checkInclusion("abcdxabcde","abcdeabcdx");
	// printf(res ? "true\n":"false\n");

    // string a = "abc";
    // if(a[3] == '\0')
    // {
    //     printf("yes\n");
    // }
    printf("%d\n",hh());
    return 0;

}
