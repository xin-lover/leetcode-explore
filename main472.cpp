//472. 连接词

#include <cstdio>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;

bool concatable(string& word, int start,int count,const string& last,bool same,unordered_map<int,unordered_set<string>>& um)
{
    if(start >= word.size())
    {
        return !same && count > 1;
    }

    for(int len=1;len+start<=word.size();++len)
    {
        string tmp = word.substr(start,len);
        if(um[len].find(tmp) != um[len].end())
        {
            if(concatable(word,start+len,count+1,tmp,same && (tmp==last),um))
            {
                // printf("%s\n",tmp.c_str());
                return true;
            }
        }
    }

    return false;
}

vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
    //思路：采用长度提前剪枝，按单词长度分组，长度匹配才能进行字符串匹配
    //这里复杂的是至少两个，那么我们先从两个开始，那么对于每个字符串，分成两组，根据长度在对应分组中找
    //前半部分找不到，直接终止
    //解决方案：递归

    unordered_map<int,unordered_set<string>> um;

    for(int i=0;i<words.size();++i)
    {
        um[words[i].size()].insert(words[i]);
    }

    //
    vector<string> res;
    for(auto& word : words)
    {
        if(concatable(word,0,0,"",true,um))
        {
            res.push_back(word);
        }
    }

    return res;
}

//其它思路：字典树。。。。。。

int main()
{
    vector<string> words = {"cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"};

    for(auto a : findAllConcatenatedWordsInADict(words))
    {
        printf("%s ",a.c_str());
    }
    printf("\n");

    return 0;
}