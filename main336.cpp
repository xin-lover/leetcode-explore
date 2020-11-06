//336. 回文对

#include <cstdio>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

vector<vector<int>> palindromePairs(vector<string>& words) {
    //思路：最直观的解法，就是O(n^2)

    vector<vector<int>> res;
    for(int i=0;i<words.size();++i)
    {
        for(int j=0;j<words.size();++j)
        {
            if(i == j)
            {
                continue;
            }

            int x=0,y=words[j].size()-1;
            int len = words[i].size() + words[j].size();
            int halfLen = len / 2;
            bool isPalindrome = true;
            while(x < halfLen)
            {
                int lc = x >= words[i].size() ? words[j][x-words[i].size()] : words[i][x];
                int rc = y < 0 ? words[i][words[i].size()+y] : words[j][y];
                if(lc != rc)
                {
                    isPalindrome = false;
                    break;
                }

                ++x;
                --y;
            }

            if(isPalindrome)
            {
                res.push_back({i,j});
            }
        }
    }

    return res;
}

vector<vector<int>> palindromePairs2(vector<string>& words) {
    //思路：如果有一种快速的算法能判断字符串是否是回文，那么找出words[i]所有可能的回文字符串，是否简单点？

    unordered_map<string,int> um;
    for(int i=0;i<words.size();++i)
    {
        um[words[i]] = i;
    }

    vector<vector<int>> res;
    for(int i=0;i<words.size();++i)
    {
        for(int j=0;j<=words[i].size();++j)
        {
            int x=j,y=words[i].size()-1;
            bool isPalind = true;
            while(x < y)
            {
                if(words[i][x] != words[i][y])
                {
                    isPalind = false;
                    break;
                }
                ++x;
                --y;
            }

            if(isPalind)
            {
                string pre = words[i].substr(0,j);
                reverse(pre.begin(),pre.end());
                if(um.find(pre) != um.end() && i != um[pre])
                {
                    res.push_back({i,um[pre]});
                }                
            }

            if(j == 0)
            {
                continue;
            }

            isPalind = true;
            x=0,y=j-1;
            while(x < y)
            {
                if(words[i][x] != words[i][y])
                {
                    isPalind = false;
                    break;
                }
                ++x;
                --y;
            }

            if(isPalind)
            {
                string pre = words[i].substr(j,words[i].length() - j);
                reverse(pre.begin(),pre.end());
                if(um.find(pre) != um.end() && i != um[pre])
                {
                    res.push_back({um[pre],i});
                }                
            }
        }
    }

    return res;
}


int main()
{
    vector<string> words = {"abcd","dcba","lls","s","sssll"}; //[[0,1],[1,0],[3,2],[2,4]] 
    words = {"bat","tab","cat"};    //[[0,1],[1,0]] ]
    words = {"a","abc","aba",""}; //[[0,3],[3,0],[2,3],[3,2]]

    for(auto a : palindromePairs2(words))
    {
        for(auto b : a)
        {
            printf("%d ",b);
        }
        printf("\n");
    }

    return 0;
}