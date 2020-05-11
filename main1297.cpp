//1297. 子串的最大出现次数

#include <cstdio>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct Trie
{
public:
    Trie* childs[26];
    bool isEnd;
    int count;

    Trie()
        :isEnd(false),count(0)
    {
        for(int i=0;i<26;++i)
        {
            childs[i] = nullptr;
        }
    }
};

void insertTrie(Trie* node,string val,int& maxCount)
{
    Trie* tmp = node;
    for(int i=0;i<val.length();++i)
    {
        int pos = val[i]- 'a';
        if(tmp->childs[pos] == nullptr)
        {
            tmp->childs[pos] = new Trie();
        }
        tmp = tmp->childs[pos];
    }

    printf("%s\n",val.c_str());
    tmp->isEnd = true;
    tmp->count++;
    maxCount = max(maxCount,tmp->count);
}

int maxFreq(string s, int maxLetters, int minSize, int maxSize) {
    //思路：枚举所有可能的字串不太可行
    //因为最多26个字符不同，所以字串长度最大26
    //使用浮动窗口？让窗口内不同字符符合条件，然后记录出现的字符串
    //考虑结合字典树

    //理解题意错误， 是<=maxLetters

    Trie* root = new Trie();
    int res = 0;
    int left = 0;
    vector<int> flags(26,false);
    int dif = 0;
    for(int i=0;i<s.length();++i)
    {
        for(int j=i;j<s.length();++j)
        {
            if(flags[s[j]-'a'] == 0)
            {
                ++dif;
            }
            ++flags[s[j]-'a'];

            if(dif <= maxLetters && j-i+1>=minSize && j-i+1 <= maxSize)
            {
                insertTrie(root,s.substr(i,j-i+1),res);
            }
            else if(dif > maxLetters || j-i+1>maxSize)
            {
                dif = 0;
                for(int i=0;i<flags.size();++i)
                {
                    flags[i] = 0;
                }
                break;
            }
        }
    }

    return res;
}

int maxFreq2(string s, int maxLetters, int minSize, int maxSize) {
    //假设字符串 T 在给定的字符串 S 中出现的次数为 k，那么 T 的任意一个子串出现的次数至少也为 k，
    //即 T 的任意一个子串在 S 中出现的次数不会少于 T 本身。
    //这样我们就可以断定，在所有满足条件且出现次数最多的的字符串中，一定有一个的长度恰好为 minSize。
    //我们可以使用反证法证明上述的结论：假设所有满足条件且出现次数最多的字符串中没有长度为 minSize 的，
    //不妨任取其中的一个长度为 l 的字符串，根据假设，有 l > minSize。
    //此时我们再任取该字符串的一个长度为 minSize 的子串，子串出现的次数不会少于原字符串出现的次数，与假设相矛盾。

    int n = s.size();
    unordered_map<string, int> occ;
    int ans = 0;
    for (int i = 0; i < n - minSize + 1; ++i) {
        string cur = s.substr(i, minSize);
        unordered_set<char> exist(cur.begin(), cur.end());
        if (exist.size() <= maxLetters) {
            string cur = s.substr(i, minSize);
            ++occ[cur];
            ans = max(ans, occ[cur]);
            if(ans == 2)
            {
                printf("%s\n",cur.c_str());
            }
        }
    }
    return ans;
}

//滚动个窗口法
// using LL = long long;

// class Solution {
// private:
//     static constexpr int mod = 1000000007;

// public:
//     int maxFreq(string s, int maxLetters, int minSize, int maxSize) {
//         int n = s.size();
//         unordered_map<int, int> occ;
//         unordered_map<char, int> exist;
//         int ans = 0, exist_cnt = 0;
//         int rabin = 0, base = 26, base_mul = base;
        
//         for (int i = 0; i < minSize - 1; ++i) {
//             ++exist[s[i]];
//             if (exist[s[i]] == 1) {
//                 ++exist_cnt;
//             }
//             rabin = ((LL)rabin * base + (s[i] - 97)) % mod;
//             base_mul = (LL)base_mul * base % mod;
//         }

//         for (int i = minSize - 1; i < n; ++i) {
//             ++exist[s[i]];
//             if (exist[s[i]] == 1) {
//                 ++exist_cnt;
//             }
//             rabin = ((LL)rabin * base + (s[i] - 97)) % mod;
//             if (i >= minSize) {
//                 --exist[s[i - minSize]];
//                 if (exist[s[i - minSize]] == 0) {
//                     --exist_cnt;
//                 }
//                 rabin = (rabin - (LL)base_mul * (s[i - minSize] - 97) % mod + mod) % mod;
//             }
//             if (exist_cnt <= maxLetters) {
//                 ++occ[rabin];
//                 ans = max(ans, occ[rabin]);
//             }
//         }
//         return ans;
//     }
// };

int main()
{
    // printf("%d\n",maxFreq("aaaa",1,3,3));   //2
    // printf("%d\n",maxFreq("aababcaab",2,3,4));   //2
    // printf("%d\n",maxFreq("aabcabcab",2,2,3));   //3
    // printf("%d\n",maxFreq("abcde",2,3,3));   //0
    // printf("%d\n",maxFreq("abcabababacabcabc",3,3,10));   //3
    printf("%d\n",maxFreq("aaaaacbc",2,4,6));   //2
    return 0;
}