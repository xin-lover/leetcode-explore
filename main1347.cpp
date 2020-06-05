//1347. 制造字母异位词的最小步骤数

#include <cstdio>
#include <string>
#include <vector>

using namespace std;

int minSteps(string s, string t) {
    //思路：简单统计各字符的次数，计算差值即可
    //注意，t的字符变换后，如果是最优的结果，那么将让s和t的差异-2；

    vector<int> count1(26,0),count2(26,0);

    for(auto a : s)
    {
        ++count1[a-'a'];
    }

    for(auto a : t)
    {
        ++count2[a-'a'];
    }

    int res = 0;
    for(int i=0;i<count1.size();++i)
    {
        res += abs(count1[i]-count2[i]);
    }

    return res / 2 + res % 2;
}

int minSteps2(string s, string t) {
    //思路：上面的思路计算差值，其实可以再直接一点，就是让t中字符数量多余s的字符去补全少的那些字符即可

    vector<int> count(26,0);
    for(auto a : s)
    {
        ++count[a-'a'];
    }

    int res = 0;
    for(auto a : t)
    {
        if(count[a-'a'] > 0)
        {
            --count[a-'a'];
        }
        else
        {
            ++res;
        }
    }

    return res;
}

int main()
{
    string s = "bab", t = "aba"; //1
    s = "leetcode", t = "practice"; //5
    s = "anagram", t = "mangaar";   //0
    s = "friend", t = "family"; //4

    printf("%d\n",minSteps2(s,t));

    return 0;
}