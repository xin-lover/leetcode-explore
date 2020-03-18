//1156. 单字符重复子串的最大长度

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

int maxRepOpt1(string text) {
    //思路：交换两个字符的方式n^2种，然后再依次检测字符串O(n)，所以复杂度是O(n^3)
    //另一种方案是：记录字符的出现次数，那么从开始遍历，选定一个字符，如果后面的相同就递进，
    //如果不同，看这个字符后面是否有可用字符，有则替换依次，继续前进
    //然后从替换的字符位置再次往前递进

    if(text.empty())
    {
        return 0;
    }
    vector<int> flags(26,0);
    for(int i=0;i<text.size();++i)
    {
        ++flags[text[i]-'a'];
    }

    int res = 0;
    int nextStepPos=1;
    char cur = text[0];
    bool swaped = false;
    int t = 1;
    for(int i=1;i<text.size();++i)
    {
        if(text[i] == cur)
        {
            ++t;
        }
        else
        {
            if(!swaped && flags[cur-'a'] > t)
            {
                swaped = true;
                nextStepPos = i;
                ++t;
            }
            else
            {
                t = min(flags[cur-'a'],t);
                res = max(res,t);
                if(swaped)
                {
                    i = nextStepPos;
                    cur = text[nextStepPos];
                }
                else
                {
                    ++i;
                    if(i >= text.size())
                    {
                        break;
                    }
                    cur = text[i];
                }
                
                t = 1;
                swaped = false;
                
            }
        }
    }

    return max(res,min(t,flags[cur-'a']));
}

int main()
{
    // printf("%d\n",maxRepOpt1("ababa")); //3
    printf("%d\n",maxRepOpt1("aaabaaa")); //6
    printf("%d\n",maxRepOpt1("aaabbaaa")); //4
    printf("%d\n",maxRepOpt1("aaaaa")); //5
    printf("%d\n",maxRepOpt1("abcdef")); //1
    return 0;
}
