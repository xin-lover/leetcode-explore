//leetcode 966. 元音拼写检查器

#include <cstdio>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>

using namespace std;

struct TrieNode
{
    TrieNode* childs[26];
    bool upper;
    bool all;
    bool end;

    TrieNode():upper(true),end(false),all(true)
    {
        for(int i=0;i<26;++i)
        {
            childs[i] = nullptr;
        }
    }
};

using TrieTree = TrieNode;

void insert(TrieTree* tree, const string& word)
{
    TrieNode* tmp = tree;
    for(int i=0;i<word.size();++i)
    {
        char c = word[i];
        bool isUpper = true;
        if(c > 'Z')
        {
            c -= ('a'-'A');
            isUpper = false;
        }
        int p = c - 'A';
        if(tmp->childs[p] == nullptr)
        {
            TrieNode* node = new TrieNode();
            tmp->childs[p] = node;
            tmp->childs[p]->upper = isUpper;
            tmp->childs[p]->all = false;
        }

        tmp = tmp->childs[p];
        if(!tmp->all && tmp->upper != isUpper)
        {
            tmp->all = true;
        }
    }

    tmp->end = true;
}

bool find(TrieTree* tree,const string& word, int index,vector<bool>& flags,string& resWord)
{
    static vector<char> vowel = {'A','E','I','O','U'};   
    TrieNode* tmp = tree;
    for(int i=index;i<word.size();++i)
    {
        char c = word[i];
        if(c > 'Z')
        {
            c -= ('a' - 'A');
        }

        int p = c - 'A';
        if(tmp->childs[p] != nullptr)
        {
            if(tmp->childs[p]->all)
            {
                resWord.push_back(word[i]);
            }
            else
            {
                resWord.push_back(tmp->childs[p]->upper ? c : c + ('a'-'A'));
            }
            tmp = tmp->childs[p];
        }
        else
        {
            for(int j=0;j<vowel.size();++j)
            {
                // if(tmp->childs[vowel[j]-'A'] != nullptr)
                // {
                //     printf("get:%s %c\n",word.c_str(),vowel[j]);
                // }
                TrieTree* tt = tmp->childs[vowel[j]-'A'];
                if(tt != nullptr)
                {
                    resWord.push_back(tt->upper ? vowel[j] : vowel[j] + 'a'-'A');
                    if(find(tt,word,i+1,flags,resWord))
                    {
                        return true;
                    }
                    resWord.pop_back();
                }
                
            }
            return false;
        }
    }

    if(tmp->end)
    {
        return true;
    }

    return false;
}

vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {
    //思路：大小写匹配很简单，直接都转换为大写或小写即可，对于查找可以使用字典树
    //判断元音字符需要判断5次，比较费时，一个优化是set保存或者直接保存一个数组
    //对于返回第一个匹配的单词，我们可以在插入字典树时只记录第一个单词的大小写状态

    //问题：完全匹配和顺序问题无法解决

    TrieTree* tree = new TrieNode();
    for(int i=0;i<wordlist.size();++i)
    {
        insert(tree,wordlist[i]);
    }

    vector<bool> flags(26,false);
    flags['a'-'a'] = true;
    flags['e'-'a'] = true;
    flags['i'-'a'] = true;
    flags['o'-'a'] = true;
    flags['u'-'a'] = true;

    vector<string> res;
    for(int i=0;i<queries.size();++i)
    {
        string ss;
        if(find(tree,queries[i],0,flags,ss))
        {
            res.push_back(ss);
        }
        else
        {
            res.push_back("2");
        }
    }

    return res;
}

vector<string> spellchecker2(vector<string>& wordlist, vector<string>& queries) {
    //思路：把wordlist中的单词存在一个map中，然后在对每个单词都转换为大写，这样就可能冲突，所以对于每个单词存两个索引
    //第一个表示本身，第二个表示大小写匹配的第一个
    //对于元音字符，我们统一转换为‘a'，在存一个map
    //这样，查找规则就是先看本身有没有，没有在转换为大写，看有没有，某则转换元音字符

    vector<bool> flags(26,false);
    flags['A'-'A'] = true;
    flags['E'-'A'] = true;
    flags['I'-'A'] = true;
    flags['O'-'A'] = true;
    flags['U'-'A'] = true;

    set<string> st;
    for(auto a : wordlist)
    {
        st.insert(a);
    }

    unordered_map<string,int> um;
    unordered_map<string,int> um2;
    for(int i=0;i<wordlist.size();++i)
    {
        string tmp = wordlist[i];
        for(int j=0;j<tmp.size();++j)
        {
            tmp[j] = tmp[j] > 'Z' ? tmp[j]-('a'-'A') : tmp[j];
        }

        if(um.find(tmp) == um.end())
        {
            um[tmp] = i;
        }

        for(int j=0;j<tmp.size();++j)
        {
            if(flags[tmp[j]-'A'])
            {
                tmp[j] = 'A';
            }
        }

        if(um2.find(tmp) == um2.end())
        {
            um2[tmp] = i;
            printf("um2insert:%d %s\n",i,tmp.c_str());
        }
    }

    vector<string> res;
    for(auto a : queries)
    {
        if(st.find(a) != st.end())
        {
            res.push_back(a);
        }
        else
        {
            //转换为大写
            string tmp = a;
            for(int j=0;j<tmp.size();++j)
            {
                tmp[j] = tmp[j] > 'Z' ? tmp[j]-('a'-'A') : tmp[j];
            }
            
            if(um.find(tmp) != um.end())
            {
                res.push_back(wordlist[um[tmp]]);
                continue;
            }

            //转换元音字符
            for(int j=0;j<tmp.size();++j)
            {
                if(flags[tmp[j]-'A'])
                {
                    tmp[j] = 'A';
                }
            }

            if(um2.find(tmp) != um2.end())
            {
                res.push_back(wordlist[um2[tmp]]);
                continue;
            }

            // printf("wy:%s\n",tmp.c_str());
            res.push_back("");
        }
    }

    return res;

}

int main()
{
    //["kite","KiTe","KiTe","Hare","hare","","","KiTe","","KiTe"]
    vector<string> wordlist = {"KiTe","kite","hare","Hare"};
    vector<string> queries = {"kite","Kite","KiTe","Hare","HARE","Hear","hear","keti","keet","keto"};

    vector<string> res = spellchecker2(wordlist,queries);
    for(auto a : res)
    {
        printf("%s ",a.c_str());
    }
    printf("\n");
    return 0;
}