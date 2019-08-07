//leetcode 809. 情感丰富的文字

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

int expressiveWords(string S, vector<string>& words) {
    //思路：可以看出如果以字符串中的不同字母作为字符串的特征
    //则它们除了字符数量不同，拥有的字符种类及其顺序是一致的

    vector<pair<char,int>> s_feature;
    int start = 0;
    for(int i=0;i<=S.size();++i)
    {
        if(S[i] != S[start])
        {
            s_feature.push_back({S[start],i-start});
            printf("%c %d\n",S[start],i-start);
            start = i;
        }
    }

    int res = 0;
    for(auto word : words)
    {
        int start = 0;
        int c = 0;
        bool isStretch = true;
        for(int i=0;i<=word.size();++i)
        {
            if(word[i] != word[start])
            {
                if(word[start] != s_feature[c].first 
                || !(s_feature[c].second == i-start || (s_feature[c].second > i- start && s_feature[c].second >= 3)))
                {
                    isStretch = false;
                    break;
                }

                start = i;
                ++c;
            }
        }

        if(isStretch && c == s_feature.size()){
            ++res;
        }
    }

    return res;
}

int main()
{
    vector<string> words = {"hello", "hi", "helo"};
    printf("%d\n",expressiveWords("heeellooo",words));
    words = {"aaaa"};
    printf("%d\n",expressiveWords("aaa",words));
    return 0;
}