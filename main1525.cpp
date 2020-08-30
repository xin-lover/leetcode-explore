//1525. 字符串的好分割数目

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

int numSplits(string s) {
    //思路：就是分割字符，左右两边的字符种类相同，记录每个字符出现的次数

    //同样是动态规划，还有另一种写法，就是左右，右左遍历分别统计字符种类

    vector<int> counts(26,0);

    int charCount= 0;
    for(auto c : s)
    {
        counts[c-'a']++;
    }

    for(auto a : counts)
    {
        if(a > 0)
        {
            ++charCount;
        }
    }

    int res = 0;
    vector<int> left(26,0);
    int leftCount = 0,rightCount = charCount;
    for(auto c : s)
    {
        left[c-'a']++;
        if(left[c-'a'] == 1)
        {
            ++leftCount;
        }

        counts[c-'a']--;
        if(counts[c-'a'] == 0)
        {
            --rightCount;
        }

        if(leftCount == rightCount)
        {
            ++res;
        }
    }

    return res;
}

int main()
{
    string s = "aacaba"; //2
    s = "aaaaa";    //4
    printf("%d\n",numSplits(s));

    return 0;
}