//leetcode 792. 匹配子序列的单词数

#include <cstdio>
#include <string>
#include <vector>

using namespace std;

class TreeNode
{
public:
    TreeNode()
    {
        memset(childs,0,sizeof(childs));
    }
    ~TreeNode()
    {
        for(int i=0;i<26;++i)
        {
            if(childs[i] != nullptr)
            {
                delete childs[i];
            }
        }
    }
    TreeNode* childs[26];
};

void CreateTrie(TreeNode* trie,const string& S,int index,int level)
{
    char c = S[index];
    if(!trie->childs[c-'a'])
    {
        trie->childs[c-'a'] = new TreeNode();
    }

    if(level < 49)
    {
        for(int i=index+1;i<S.size();++i)
        {
            CreateTrie(trie->childs[c-'a'],S,i,level+1);
        }
    }
}


int numMatchingSubseq(string S, vector<string>& words) {
    //思路：子序列问题，一种思路是求出S的所有子序列，再遍历words判断，空间复杂度高
    //另一种就不存储，这个时间复杂度高
    //前一种思路可以使用前缀树，但题目中标注了S的长度最长为5000，words[i]的长度为50，也就是最大50*26*4个字节，这个可以接受
    //但构建树的时间长
    //同理，查找遍历也长，也会超时
    //考虑对words排序，然后遍历

    // TreeNode* trie = new TreeNode();
    // for(int i=0;i<S.size();++i)
    // {
    //     //构建树的时间随长度增加太快，超时
    //     CreateTrie(trie,S,i,0);
    // }
    
    // int res = 0;
    // for(auto word : words)
    // {
    //     TreeNode* node = trie;
    //     int i;
    //     for(i=0;i<word.size();++i)
    //     {
    //         int c = word[i];
    //         if(node->childs[c-'a'])
    //         {
    //             node = node->childs[c-'a'];
    //         }
    //         else
    //         {
    //             break;
    //         }
    //     }

    //     if(i == word.size())
    //     {
    //         ++res;
    //         printf("%s\n",word.c_str());
    //     }
    // }
    
    // return res;

    //记录每个字符出现的位置，根据位置判断
    vector<vector<int>> poses(26);
    for(int i=0;i<S.size();++i)
    {
        poses[S[i]-'a'].push_back(i);
    }

    int res = 0;
    for(auto word : words)
    {
        int p = -1;
        int i;
        for(i=0;i<word.size();++i)
        {
            int j = 0;
            int k = word[i]-'a';
            for(j=0;j<poses[k].size();++j)
            {
                if(poses[k][j] > p)
                {
                    p = poses[k][j];
                    break;
                }
            }

            if(j == poses[k].size())
            {
                break;
            }
        }

        if(i >= word.size())
        {
            ++res;
        }
    }

    return res;
}

int numMatchingSubseq2(string S, vector<string>& words) {

    //对words做预处理，记录当前words中每个word需要匹配的字符下标，然后遍历S，遇到word的匹配的字符，则下标+1，表示匹配下一个字符
    vector<vector<pair<int,int>>> states(26);
    for(int i=0;i<words.size();++i)
    {
        states[words[i][0]-'a'].push_back({i,0});
    }

    int res = 0;
    for(int i=0;i<S.size();++i)
    {
        if(states[S[i]-'a'].empty())
        {
            continue;
        }

        auto state = states[S[i]-'a'];
        states[S[i]-'a'].clear();

        for(int j=0;j<state.size();++j)
        {
            int wordInd = state[j].first;
            int nextpos = state[j].second+1;
            if(nextpos >= words[wordInd].size())
            {
                ++res;
            }
            else
            {
                states[words[wordInd][nextpos]-'a'].push_back({wordInd,nextpos});
            }
        }
    }

    return res;
}
int main()
{
    vector<string> words = {"a", "bb", "acd", "ace"};
    // printf("%d\n",numMatchingSubseq2("abcde",words));
    words = {"ahjpjau","ja","ahbwzgqnuk","tnmlanowax"};
    printf("%d\n",numMatchingSubseq("dsahjpjauf",words));
    // words = {"wpddkvbnn","lnagtva","kvbnnuglnagtvamxkqtwhqgwbqgfbvgkwyuqkdwhzudsxvju","rwpddkvbnnugln","gloeofnpjqlkdsqvruvabjrikfwronbrdyyj","vbgeinupkvgmgxeaaiuiyojmoqkahwvbpwugdainxciedbdkos","mspuhbykmmumtveoighlcgpcapzczomshiblnvhjzqjlfkpina","rgmliajkiknongrofpugfgajedxicdhxinzjakwnifvxwlokip","fhepktaipapyrbylskxddypwmuuxyoivcewzrdwwlrlhqwzikq","qatithxifaaiwyszlkgoljzkkweqkjjzvymedvclfxwcezqebx"};
    // printf("%d\n",numMatchingSubseq("rwpddkvbnnuglnagtvamxkqtwhqgwbqgfbvgkwyuqkdwhzudsxvjubjgloeofnpjqlkdsqvruvabjrikfwronbrdyyjnakstqjac",words));
    return 0;
}
