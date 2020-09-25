//30. 串联所有单词的子串

#include <cstdio>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Trie{
public:
    Trie* childs[26];
    bool end;

    Trie():end(false)
    {
        for(int i=0;i<26;++i)
        {
            childs[i] = nullptr;
        }
    }
};

void insertTrie(Trie* trie,const string& word)
{
    Trie* tmp = trie;
    for(int i=0;i<word.size();++i)
    {
        int pos = word[i] - 'a';
        if(!tmp->childs[pos])
        {
            tmp->childs[pos] = new Trie();
        }

        tmp = tmp->childs[pos];
    }

    tmp->end = true;
}

bool findInTrie(Trie* trie,const string& word)
{
    Trie* tmp = trie;
    for(int i=0;i<word.size();++i)
    {
        int pos = word[i] - 'a';
        if(tmp->childs[pos])
        {
            tmp = tmp->childs[pos];
        }
        else
        {
            return false;
        }        
    }

    return tmp->end;
}

bool findInTrie(Trie* trie,const string& s, int start,unordered_map<string,int>& um,int wordsCount)
{
    int t = 0;
    int mark = start;
    Trie* tmp = trie;
    unordered_map<string,int> curUm;
    for(int i = start;i<s.size();++i)
    {
        int pos = s[i]-'a';
        if(tmp->childs[pos] == nullptr)
        {
            return false;
        }

        tmp = tmp->childs[pos];
        if(tmp->end)
        {
            string ss = s.substr(mark,i-mark+1);
            if(curUm[ss] >= um[ss])
            {
                continue;
            }
            ++curUm[ss];
            ++t;
            mark = i+1;
            tmp = trie;
            
            if(t == wordsCount)
            {
                return true;
            }
        }
    }

    return false;
}

vector<int> findSubstring(string s, vector<string>& words) {
    //思路：因为单词可能很多，所以不能求出所有的方案
    //考虑一个单词，那我们直接比较首字符查找即可，但现在候选字符多，性能肯定差
    //所以考虑字典树

    unordered_map<string,int> um;
    Trie* trie = new Trie();
    for(int i=0;i<words.size();++i)
    {
        insertTrie(trie,words[i]);
        um[words[i]]++;
    }

    vector<int> res;
    Trie* tmp = trie;
    vector<bool> flags(words.size(),false);
    for(int i=0;i<s.size();++i)
    {
        if(findInTrie(trie,s,i,um,words.size()))
        {
            res.push_back(i);
        }
    }

    return res;
}

vector<int> findSubstring2(string s, vector<string>& words) {
    //思路：审题还是不仔细，words中的字符串长度相同。。。
    //直接把s按长度分，这个时候就可以使用滑动窗口了

    if(words.empty())
    {
        return {};
    }
    unordered_map<string,int> um;
    for(int i=0;i<words.size();++i)
    {
        um[words[i]]++;
    }

    vector<int> res;
    int len = words[0].size();
    int sz = s.size();
    int wordsSz = words.size();
    for(int i=0;i<=sz - len * wordsSz;++i)
    {
        printf("i:%d\n",i);
        unordered_map<string,int> uu;
        bool valid = true;
        for(int j=0;j<words.size();++j)
        {
            string ss = s.substr(i+len*j,len);
            printf("ss:%s\n",ss.c_str());
            if(uu[ss] >= um[ss])
            {
                valid = false;
                break;
            }
            uu[ss]++;
        }
printf("------\n");
        if(valid)
        {
            res.push_back(i);
        }
    }

    return res;
}


int main()
{
    string s = "barfoothefoobarman";
    vector<string> words = {"foo","bar"}; //[0,9]

    s = "wordgoodgoodgoodbestword";
    words = {"word","good","best","word"}; //[]

    s = "wordgoodgoodgoodbestword";
    words = {"word","good","best","good"}; // [8]

    s="a";
    words={"a","a"}; //
    for(auto a : findSubstring2(s,words))
    {
        printf("%d ",a);
    }
    printf("\n");
    return 0;
}