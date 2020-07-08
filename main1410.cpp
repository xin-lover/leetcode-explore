//1410. HTML 实体解析器

#include <cstdio>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

struct TrieNode
{
    TrieNode* childs[26];
    bool end;

    TrieNode()
    {
        end = false;
        for(int i=0;i<26;++i)
        {
            childs[i] = nullptr;
        }
    }
};

void insert(TrieNode* trie,const string& text)
{
    TrieNode* tmp = trie;
    for(int i=0;i<text.length();++i)
    {
        int c = text[i]-'a';
        if(!tmp->childs[c])
        {
            tmp->childs[c] = new TrieNode();
        }

        tmp = tmp->childs[c];
    }

    tmp->end = true;
}

string entityParser(string text) {
    //思路：这里的问题主要是如何识别关键词的结束位置
    //考虑字典树
    //误会题意了，";"是结束标志

    TrieNode* trie = new TrieNode();
    insert(trie,"&quot");
    insert(trie,"&apos");
    insert(trie,"&amp");
    insert(trie,"&gt");
    insert(trie,"&lt");
    insert(trie,"&frasl");

    unordered_map<string,char> um;
    um["&quot"] = '"';
    um["&apos"] = '\'';
    um["&amp"] = '&';
    um["&gt"] = '>';
    um["&lt"] = '<';
    um["&frasl"] = '/';

    string res;
    for(int i=0;i<text.length();++i)
    {
        if(text[i] != '&')
        {
            res.append(1,text[i]);
        }
        else
        {
            TrieNode* tmp = trie;
            int len = min(i+6,(int)text.length());
            int j = i;
            bool match = false;
            for(;j<len;++j)
            {
                int c = text[j] - 'a';
                if(tmp->childs[c])
                {
                    tmp = tmp->childs[c];
                    if(tmp && tmp->end)
                    {
                        match = true;
                        break;
                    }
                }
                else
                {
                    break;
                }
            }

            if(!match)
            {
                for(int k=i;k<=j;++k)
                {
                    res.append(1,text[k]);
                }
            }
            else
            {
                // printf("%s\n",text.substr(i,j-i+1).c_str());
                res.append(1,um[text.substr(i,j-i+1)]);
            }

            i = j;
        }
        
    }

    return res;
}

string entityParser2(string text) {
    //思路：关键字符，&开头，";"结束

    unordered_map<string,char> um;
    um["&quot;"] = '"';
    um["&apos;"] = '\'';
    um["&amp;"] = '&';
    um["&gt;"] = '>';
    um["&lt;"] = '<';
    um["&frasl;"] = '/';

    string res;
    for(int i=0;i<text.length();++i)
    {
        if(text[i] != '&')
        {
            res.append(1,text[i]);
        }
        else
        {
            int len = min(i+8,(int)text.length());
            int j = i;
            for(;j<len;++j)
            {
                if(text[j] == ';')
                {
                    string word = text.substr(i,j-i+1);
                    printf("%s\n",word.c_str());
                    if(um.find(word) != um.end())
                    {
                        res.append(1,um[word]);
                    }
                    else
                    {
                        res.append(word);
                    }

                    break;
                }
            }

            if(j == len)
            {
                for(int k=i;k<=j;++k)
                {
                    res.append(1,text[k]);
                }
            }

            i = j;
        }
    }

    return res;
}

int main()
{
    // printf("%s\n",entityParser2("&amp; is an HTML entity but &ambassador; is not.").c_str()); //"& is an HTML entity but &ambassador; is not."
    // printf("%s\n",entityParser2( "x &gt; y &amp;&amp; x &lt; y is always false").c_str());   //"x > y && x < y is always false"
    printf("%s\n",entityParser2("leetcode.com&frasl;problemset&frasl;all").c_str()); //"leetcode.com/problemset/all"
    return 0;
}