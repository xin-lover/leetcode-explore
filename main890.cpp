//leetcode 890. 查找和替换模式

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

bool isvalid(const string& word, const string& pattern)
{
    if(word.size() != pattern.size())
    {
        return false;
    }

    vector<int> w2p(26,-1);
    vector<int> p2w(26,-1);
    for(int i=0;i<word.size();++i)
    {
        int inx1 = word[i]-'a';
        int inx2 = pattern[i]-'a';
        if(w2p[inx1] == -1)
        {
            if(p2w[inx2] == -1)
            {
                w2p[inx1] = pattern[i];
                p2w[inx2] = word[i];
            }
            else
            {
                if(p2w[inx2] != word[i])    //多个word中的字符映射为同一个字符
                {
                    return false;
                }
            }
            
        }
        else
        {
            if(w2p[inx1] != pattern[i])
            {
                return false;
            }
        }
    }

    return true;
}

bool isvalid2(const string& word, const vector<int> &pattern)
{
    vector<int> cc(50,0);
    vector<int> counts(26,0);
    for(auto a : word)
    {
        ++counts[a-'a'];
    }

    for(auto c : counts)
    {
        ++cc[c];
    }

    for(int i=0;i<50;++i)
    {
        if(cc[i] != pattern[i])
        {
            return false;
        }
    }

    return true;
}

bool isvalid3(const string& word, const string &pattern)
{
    //上面是两个映射表，可以优化为一个映射表，即先遍历一边做好映射关系，然后统计映射表各字符的出现次数，多余一次即不行
    if(word.size() != pattern.size())
    {
        return false;
    }
    vector<int> states(26,-1);
    for(int i=0;i<word.size();++i)
    {
        if(states[word[i]-'a'] != -1 && states[word[i]-'a'] != pattern[i])
        {
            return false;
        }

        states[word[i]-'a'] = pattern[i];
    }

    vector<bool> counts(26,false);
    for(auto c : states)
    {
        if(c == -1)
        {
            continue;
        }
        if(counts[c-'a'])
        {
            return false;
        }

        counts[c-'a'] = true;
    }

    return true;
}




vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
    //思路：主要是考察映射，如何构建映射关系
    //1.长度不一致，肯定不符合
    //2.使用一个数组来记录映射关系，如果新的映射与老的不一样，则不匹配
    //3.或者记录每个字符的出现次数，然后比较次数是否相等
    //ao和ya是合法的映射，即a->y,o->a，所以不是一个双向映射

    vector<string> res;
    for(int i=0;i<words.size();++i)
    {
        if(isvalid3(words[i],pattern))
        {
            res.push_back(words[i]);
        }
    }

    return res;

    //统计次数不行，忽略了排列顺序
//     vector<string> res;
//     vector<int> pc(50,0);
//     vector<int> counts(26,0);
//     for(auto a:pattern)
//     {
//         ++counts[a-'a'];
//     }
//     for(auto c : counts)
//     {
//         ++pc[c];
//     }
//     for(int i=0;i<words.size();++i)
//     {
//         if(isvalid2(words[i],pc))
//         {
//             res.push_back(words[i]);
//         }
//     }

//     return res;
}

int main()
{
    vector<string> words = {"abc","deq","mee","aqq","dkd","ccc"};
    string pattern = "abb"; //输出：["mee","aqq"]

    // words = {"ao"};
    // pattern = "ya";
    vector<string> res = findAndReplacePattern(words,pattern);
    for(auto a : res)
    {
        printf("%s ",a.c_str());
    }
    printf("\n");
    return 0;
}