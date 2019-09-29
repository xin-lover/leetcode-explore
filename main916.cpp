//leetcode 916. 单词子集

#include <cstdio>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>

using namespace std;

vector<string> wordSubsets(vector<string>& A, vector<string>& B) {
    //思路：一种思路是使用计数，记录每一个字母出现的次数，然后比对

    //优化，A中可能出现重复字符串,使用map
    unordered_map<string,bool> um;

    //长度上也做限制
    int b_max_len = 0;
    
    //结果也去重

    vector<string> res;
    set<vector<int>> bcounts;
    for(int i=0;i<B.size();++i)
    {
       
        vector<int> tmp(26,0);
        for(int j=0;j<B[i].size();++j)
        {
            ++tmp[B[i][j]-'a'];
        }

        bcounts.insert(tmp);

        if(b_max_len < B[i].size())
        {
            b_max_len = B[i].size();
        }
    }

    for(int i=0;i<A.size();++i)
    {
        if(A[i].size() < b_max_len)
        {
            continue;
        }
        if(um.find(A[i]) != um.end())
        {
            if(um[A[i]])
            {
                res.push_back(A[i]);
            }
            continue;
        }
        vector<int> acount(26,0);
        for(int j=0;j<A[i].size();++j)
        {
            ++acount[A[i][j]-'a']; 
        }

        bool valid = true;
        for(auto it = bcounts.begin();it!=bcounts.end();++it)
        {
            for(int k=0;k<it->size();++k)
            {
                if(acount[k] < (*it)[k])
                {
                    valid = false;
                    break;
                }
            }
        }

        um[A[i]] = valid;
        if(valid)
        {
            res.push_back(A[i]);
        }
    }

    return res;
}

vector<string> wordSubsets2(vector<string>& A, vector<string>& B) {

    //思路：把B合成一个单词。。。。。。

    vector<string> res;
    vector<int> bcount(26,0);
    for(int i=0;i<B.size();++i)
    {
        vector<int> tmp(26,0);
        for(int j=0;j<B[i].size();++j)
        {
            ++tmp[B[i][j]-'a'];
        }

        for(int j=0;j<26;++j)
        {
            if(tmp[j]>bcount[j])
            {
                bcount[j] = tmp[j];
            }
        }
    }

    int len = 0;
    for(int i=0;i<bcount.size();++i)
    {
        len += bcount[i];
    }
    for(int i=0;i<A.size();++i)
    {
        bool valid = true;
        if(A[i].size() < len)
        {
            valid = false;
        }
        else
        {
            vector<int> tmp(26,0);
            for(int j=0;j<A[i].size();++j)
            {
                ++tmp[A[i][j]-'a'];
            }

            for(int j=0;j<26;++j)
            {
                if(tmp[j] < bcount[j])
                {
                    valid = false;
                    break;
                }
            }
        }

        if(valid)
        {
            res.push_back(A[i]);
        }
    }

    return res;
}

int main()
{
    vector<string> A = {"amazon","apple","facebook","google","leetcode"};
    vector<string> B = {"e","o"};

    A = {"amazon","apple","facebook","google","leetcode"};
    B = {"lo","eo"};

    A = {"amazon","apple","facebook","google","leetcode"};
    B = {"e","o"};

    vector<string> res = wordSubsets2(A,B);
    for(auto a : res)
    {
        printf("%s,",a.c_str());
    }
    printf("\n");
    return 0;
}