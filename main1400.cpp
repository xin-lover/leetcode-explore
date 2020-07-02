//1400. 构造 K 个回文字符串

#include <cstdio>
#include <string>
#include <unordered_map>

using namespace std;

bool canConstruct(string s, int k) {
    //思路：回文字符串，因为是s的字符随意排列，也就是只考虑字符数量就行
    //我们考虑单个字符，它只能放到回文字符串中间，而且一个回文只能有一个
    //而两个相同的字符串就没有这个限制了
    //所以我们使用hash map统计各字符的数量
    //记录数量为奇数的字符数量，如果多余k，返回false
    //最多能分为s.size()个组，如果小于k，返回false

    if(s.size() < k)
    {
        return false;
    }

    unordered_map<char,int> um;
    for(auto a : s)
    {
        um[a]++;
    }

    // int even = 0;
    int odd = 0;
    for(auto& a : um)
    {
        // even += a.second / 2;
        odd += a.second % 2;
    }

    return odd <= k;
}

int main()
{
    printf(canConstruct("annabelle",2) ? "true\n" : "false\n"); //true
    printf(canConstruct("leetcode",3) ? "true\n" : "false\n"); //false
    printf(canConstruct("true",4) ? "true\n" : "false\n"); //true
    printf(canConstruct("qlkzenwmmnpkopu",15) ? "true\n" : "false\n"); //true

    return 0;
}