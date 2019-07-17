#include <cstdio>
#include <string>

using namespace std;

string originalDigits(string s) {
    //思路：单词有zero one two three four five six seven eight nine
    //保证输入合法的话，只需要统计各字符数量和独有的字符找出一种合理组合即可
    //可以使用矩阵求解方程的办法
    //现在我们找取数字独有的字符,比如g只有eight，u只有four有， w只有two有，x只有six
    //剔除这些后再次重复这个过程，eight确定后，通过h可以确定three，之后t可以确定ten，f确定five，v确定seven，o确定one,i确定nine

    int ay[26]={0};
    for(int i=0;i<s.size();++i)
    {
        ++ay[s[i]-'a'];
    }

    int nums[10] = {0};

    nums[0] = ay['z'-'a'];
    ay['o'-'a'] -= nums[0];

    nums[2] = ay['w'-'a'];
    ay['t'-'a'] -= nums[2];
    ay['o'-'a'] -= nums[2];

    nums[4] = ay['u'-'a'];
    ay['f'-'a']-= nums[4];
    ay['o'-'a']-= nums[4];

    nums[1] = ay['o'-'a'];

    nums[5] = ay['f'-'a'];
    ay['v'-'a'] -= nums[5];
    ay['i'-'a'] -= nums[5];

    nums[7] = ay['v'-'a'];

    nums[6] = ay['x'-'a'];
    ay['i'-'a'] -= nums[6];

    nums[8] = ay['g'-'a'];
    ay['h'-'a']-=nums[8];
    ay['i'-'a'] -= nums[8];

    nums[3] = ay['h' - 'a'];

    nums[9] = ay['i'-'a'];

    string res;
    for(int i=0;i<10;++i)
    {
        res.append(nums[i],'0'+i);
    }

    return res;
}

int main()
{
    string s = "fviefuro";
    string res = originalDigits(s);
    printf("%s\n",res.c_str());
    return 0;
}