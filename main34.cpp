#include <cstdio>
#include <string>
#include <vector>

using namespace std;

int characterReplacement(string s, int k) {
    
    //思路：滑动窗口,选取这个窗口中最多的字符为目标，替换其它的字符，如果不足则缩小窗口
    int left = 0;
    int maxc = 0;
    int res = 0;

    vector<int> mem(26,0);

    for(int right=0;right<s.size();++right)
    {
        mem[s[right]-'A']++;
        maxc = max(maxc,mem[s[right]-'A']);
        if(right-left+1-maxc > k)
        {
            mem[s[left++]-'A']--;
        }

        res = max(res,right-left+1);
    }
    
    return res;
}

int main()
{
    string s = "ABAB";
    printf("%d\n",characterReplacement(s,2));
    return 0;
}
