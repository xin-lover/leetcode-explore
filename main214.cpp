//214. 最短回文串

#include <cstdio>
#include <vector>
#include <string>
#include <set>

using namespace std;

string shortestPalindrome(string s) {
    //思路：在字符串前面添加新的字符，那么要想最短
    //那么肯定是要充分使用s中的原字符，最好s就是回文字符串
    //所以问题就变成了求s中从索引0开始的最长回文字符串，剩余的字符反转后拼接到s的前方即可
    //采用贪心策略，从中间开始求

    //超时，主要是两端探测复杂度是O(n),整体复杂度是O(n^2)

    if(s.empty())
    {
        return s;
    }

    int n = s.size();
    int mid = (n+1)/2;
    int len = 1;
    for(int i=mid;i>0;--i)
    {
        int left=i,right=i;
        if(i*2+1 <= n)
        {
            while(left>=0&&s[left]==s[right])
            {
                --left;
                ++right;
            }
            
            if(left < 0)
            {
                len = i*2+1;
                break;
            }
        }

        left=i-1,right=i;
        if(s[left] == s[right])
        {
            while(left>=0&&s[left]==s[right])
            {
                --left;
                ++right;
            }

            if(left < 0)
            {
                len = i*2;
                break;
            }
        }
    }

    int addlen = n-len;
    string res(n+addlen,'a');
    for(int i=0;i<addlen;++i)
    {
        res[i] = s[n-1-i];
    }

    for(int i=0;i<n;++i)
    {
        res[addlen+i] = s[i];
    }

    return res;
}

string shortestPalindrome2(string s) {

    //思路：字符串哈希，简化字符串比较
    if(s.empty())
    {
        return s;
    }

    int n = s.size();
    int base = 131, mod = 1000000007;
    int left = 0, right = 0, mul = 1;
    int best = -1;
    for (int i = 0; i < n; ++i) {
        left = ((long long)left * base + s[i]) % mod;
        right = (right + (long long)mul * s[i]) % mod;
        if (left == right) {
            best = i;
        }
        mul = (long long)mul * base % mod;
    }
    string add = (best == n - 1 ? "" : s.substr(best + 1, n));
    reverse(add.begin(), add.end());
    return add + s;
}


//KMP算法
string shortestPalindrome3(string s) {
    int n = s.size();
    vector<int> fail(n, -1);
    for (int i = 1; i < n; ++i) {
        int j = fail[i - 1];
        while (j != -1 && s[j + 1] != s[i]) {
            j = fail[j];
        }
        if (s[j + 1] == s[i]) {
            fail[i] = j + 1;
        }
    }
    int best = -1;
    for (int i = n - 1; i >= 0; --i) {
        while (best != -1 && s[best + 1] != s[i]) {
            best = fail[best];
        }
        if (s[best + 1] == s[i]) {
            ++best;
        }
    }
    string add = (best == n - 1 ? "" : s.substr(best + 1, n));
    reverse(add.begin(), add.end());
    return add + s;
}


int main()
{
    // string s = "aacecaaa"; //"aaacecaaa"
    // s = "abcd"; //"dcbabcd"
    // // s = "abb"; //"bbabb"
    // printf("%s\n",shortestPalindrome(s).c_str());
    // return 0;

//     "mississippi"
// "issipi"
    KMP kmp("issipi");
    printf("%d\n",kmp.search("mississippi"));
    return 0;
}


// bool kmp(const string& query, const string& pattern) {
//     int n = query.size();
//     int m = pattern.size();
//     vector<int> fail(m, -1);
//     for (int i = 1; i < m; ++i) {
//         int j = fail[i - 1];
//         while (j != -1 && pattern[j + 1] != pattern[i]) {
//             j = fail[j];
//         }
//         if (pattern[j + 1] == pattern[i]) {
//             fail[i] = j + 1;
//         }
//     }
//     int match = -1;
//     for (int i = 1; i < n - 1; ++i) {
//         while (match != -1 && pattern[match + 1] != query[i]) {
//             match = fail[match];
//         }
//         if (pattern[match + 1] == query[i]) {
//             ++match;
//             if (match == m - 1) {
//                 return true;
//             }
//         }
//     }
//     return false;
// }
