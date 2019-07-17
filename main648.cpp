//leetcode 648 单词替换

#include <cstdio>
#include <string>
#include <vector>

using namespace std;

struct PrefixTree
{
    PrefixTree(){
        for(int i=0;i<26;++i)
        {
            childs[i] = nullptr;
        }
        end_=false;
    }

    ~PrefixTree()
    {
        for(int i=0;i<26;++i)
        {
            if(childs[i] != nullptr)
            {
                delete childs[i];
                childs[i] = nullptr;
            }
        }
    }

    PrefixTree* childs[26];
    bool end_;

    void insert(const string& s)
    {
        PrefixTree* tmp = this;
        for(int i=0;i<s.size();++i)
        {
            int p = s[i] - 'a';
            if(tmp->childs[p] == nullptr)
            {
                tmp->childs[p] = new PrefixTree();
            }

            tmp = tmp->childs[p];
        }
        tmp->end_ = true;
    }

    int findMinLen(const string& s)
    {
        PrefixTree* tmp = this;
        for(int i=0;i<s.size();++i)
        {
            int p = s[i]-'a';
            if(tmp->childs[p] == nullptr)
            {
                return 0;
            }
            if(tmp->childs[p] != nullptr && tmp->childs[p]->end_)
            {    
                // printf("i:%d %c\n",i,s[i]);
                return i+1;
            }

            tmp = tmp->childs[p];
        } 
        return 0;
    }
};

string replaceWords(vector<string>& dict, string sentence) {
    
    //思路：句子以空格分割单词，
    //暴力破解：每个单词都与词根比对，这样效率低
    //优化：如果一个词根是另一个词根的词根，更长的词根无须理会
    //但这种优化提升有限，考虑使用前缀树

    PrefixTree tree;
    for(auto a : dict)
    {
        tree.insert(a);
    }

    string res;
    int start = 0;
    for(int i=0;i<=sentence.size();++i)
    {
        if(sentence[i] == ' ' || sentence[i] == '\0')
        {
            string s = sentence.substr(start,i-start);
            int p = tree.findMinLen(s);
            if(p > 0)
            {
                res.append(s.substr(0,p));
            }
            else
            {
                res.append(s);
            }
            
            res.append(" ");

            start = i+1;
        }
    }

    res.erase(res.end()-1);
    return res;
}

int main()
{
    vector<string> dict = {"cat", "bat", "rat"};
    string s = "the cattle was rattled by the battery";
    printf("%s\n",replaceWords(dict,s).c_str());
    return 0;
}