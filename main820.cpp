//leetcode 820. 单词的压缩编码

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

struct TrieNode
{
    TrieNode* childs[26];

    TrieNode()
    {
        for(int i=0;i<26;++i)
        {
            childs[i] = nullptr;
        }
    }

    ~TrieNode()
    {
        for(int i=0;i<26;++i)
        {
            if(childs[i] != nullptr)
            {
                delete childs[i];
            }
        }
    }
};

void insert(TrieNode* node,const string& word)
{
    TrieNode* tmp = node;
    for(int i=word.size()-1;i>=0;--i)
    {
        int p = word[i]-'a';
        if(tmp->childs[p] == nullptr)
        {
            tmp->childs[p] = new TrieNode();
        }

        tmp = tmp->childs[p];
    }
}

bool find(TrieNode* node,const string& word)
{
    TrieNode* tmp = node;
    for(int i=word.size()-1;i>=0;--i)
    {
        int p = word[i]-'a';
        if(tmp->childs[p] == nullptr)
        {
            return false;
        }

        tmp = tmp->childs[p];
    }
    return true;
}

int minimumLengthEncoding(vector<string>& words) {
    
    //思路：求压缩的最小列表长度，这里就有这集中情况：
    //1.两个字符串没有重合，则直接连接
    //2.一个字符是另一个字符的一部分，只有后半部分相同的可共用，长的进入列表，短的共用；
    //3.两个字符串有一部分相同，因为以#号分离，所以不能共用
    //所以只有一种情况能共用
    //问题就变为如何找共用的情况
    //策略：没加入一个字符串的时候，找是否共用，不能则添加到最后，可以继续，为加快速度，可存储每个字符开头的索引，加快查找
    //也可考虑字典树，空间占用大
    //需要先插入长的字符串

    sort(words.begin(),words.end(),[](string& a,string& b){
        return a.size() > b.size();
    });

    vector<vector<pair<int,int>>> flags(26);
    int res = 0;
    for(int i=0;i<words.size();++i)
    {
        if(words[i].empty())
        {
            continue;
        }

        int p = words[i][0] - 'a';
        bool contain = false;
        for(int j=0;j<flags[p].size();++j)
        {
            int word_i = flags[p][j].first;
            int start_i = flags[p][j].second;

            if(words[word_i].size() - start_i == words[i].size())
            {
                bool have = true;
                for(int k=0;k<words[i].size();++k)
                {
                    if(words[word_i][start_i + k] != words[i][k])
                    {
                        have = false;
                        break;
                    }
                }

                if(have)
                {
                    contain = true;
                    break;
                }
            }
        }

        if(!contain)
        {
            res+= words[i].size() +1;
            for(int k=0;k<words[i].size();++k)
            {
                flags[words[i][k]-'a'].push_back({i,k});
            }
        }
    }

    return res;
}

int minimumLengthEncoding2(vector<string>& words) {
    //字典树
    //优化，反过来存

    sort(words.begin(),words.end(),[](string& a,string& b){
        return a.size() > b.size();
    });
    int res = 0;
    TrieNode* trie = new TrieNode();
    for(int i=0;i<words.size();++i)
    {
        if(find(trie,words[i]))
        {
            continue;
        }

        res+= words[i].size()+1;
        insert(trie,words[i]);
    }

    return res;
}

int main()
{
    vector<string> words = {"time","me","bell"};
    words={"me","time"};
    printf("%d\n",minimumLengthEncoding2(words));
    return 0;
}
