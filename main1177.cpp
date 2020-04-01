//1177. 构建回文串检测

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

vector<bool> canMakePaliQueries(string s, vector<vector<int>>& queries) {
    //思路：可以重新排列，可以替换，那么我们就只需要判读每个字符出现的次数了
    //因为子串可能很长，所以我们使用动归，记录前n个位置

    //空间优化：我们最后其实只关心出现次数的奇偶，所以用位来存储即可,使用异或运算
    //整数32位，而字符数只有26位

    vector<vector<int>> counts(s.size()+1);
    vector<int> tmp(26,0);
    counts[0] = tmp;
    for(int i=1;i<=s.size();++i)
    {
        ++tmp[s[i-1]-'a'];
        counts[i] = tmp;
    }

    vector<bool> res(queries.size(),false);
    for(int i=0;i<queries.size();++i)
    {
        int left = queries[i][0];
        int right = queries[i][1];
        int k = queries[i][2];

        int sum = 0;
        for(int j=0;j<26;++j)
        {
            sum += (counts[right+1][j] - counts[left][j]) % 2;
        }

        res[i] = k >= (sum - (right-left+1) % 2) / 2;
    }

    return res;
}

int main()
{
    string s = "abcda";
    vector<vector<int>>  queries = {{3,3,0},{1,2,0},{0,3,1},{0,3,2},{0,4,1}};
    // queries = {{0,3,2}};
    vector<bool> res = canMakePaliQueries(s,queries);

    for(auto a :res)
    {
        printf(a ? "true," : "false,");
    }
    printf("\n");
    return 0;
}
