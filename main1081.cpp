//1081. 不同字符的最小子序列

#include <cstdio>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

string smallestSubsequence(string text) {
    //思路：主要处理的问题是有重复字符的时候如何选
    //很明显，单个字符必须被包含，而碰到的字符如果后面有重复的可选，那么我们如何决断了？
    //这个时候不依赖前面的字符，而依赖后面可确定的字符
    //比如后面有一个字符是唯一的，那么这个会被包含，如果当前字符小于它，那么当前字符被包含
    //否则，应该使用后面的字符
    //方案：遇到非重复字符先包含，如果当前字符之前已经包含了，那么判断前面位置后方的字符
    //是否比当前的大，然后决定是否保留，这里的问题在于找后方字符，先使用线性遍历实现
    
    //上述思路还有个问题，就是当前面确定了的字符后面再次出现时，顺序可能不一样，这样选择就不唯一了
    //比如"ddeeeccdce"，前面确定了的de，后面都出现了，这个时候de只能相对确定位置，de作为整体的位置确是不能确定了

    vector<bool> flags(text.size(),false);
    unordered_map<int,int> um;
    for(int i=0;i<text.size();++i)
    {
        if(um.find(text[i]) == um.end())
        {
            flags[i] = true;
            um[text[i]] = i;
        }
        else
        {
            for(int j=um[text[i]]+1;j<i;++j)
            {
                if(flags[j])
                {
                    if(text[j] < text[i])
                    {
                        flags[um[text[i]]] = false;
                        flags[i] = true;
                        um[text[i]] = i;
                    }
                    break;
                }
            }
        }
    }

    string res;
    for(int i=0;i<flags.size();++i)
    {
        if(flags[i])
        {
            res.append(1,text[i]);
        }
    }

    return res;
}

string smallestSubsequence2(string text) {
    //思路：我们把顺序反一下，从后向前确定
    //这里解决上面的问题，但新的问题就是一旦一个序列确定了后，比如"acb",那么前面再出现什么字符都改变不了这个顺序
    //因为a已经是最小的了，不可能再调整顺序了
    vector<bool> flags(text.size(),false);
    unordered_map<int,int> um;
    for(int i=text.size()-1;i>=0;--i)
    {
        if(um.find(text[i]) == um.end())
        {
            flags[i] = true;
            um[text[i]] = i;
        }
        else
        {
            for(int j=i+1;j<um[text[i]];++j)
            {
                if(flags[j])
                {
                    if(text[j] > text[i])
                    {
                        flags[um[text[i]]] = false;
                        flags[i] = true;
                        um[text[i]] = i;
                    }
                    break;
                }
            }
        }
    }

    string res;
    for(int i=0;i<flags.size();++i)
    {
        if(flags[i])
        {
            res.append(1,text[i]);
        }
    }

    return res;
}

// string smallestSubsequence3(string text) {
//     //思路：之前的思路不对是因为在碰到一个小字符时不只要考虑前面的字符，也要考虑后面的字符
//     //也就是说一个字符一个字符的方法不行,我们直接从a开始考虑，第一个出现a的位置，我们直接选用
//     //因为a是最小的，我们要尽量往前排它，那么接下来考虑b
//     //如果b能出现在可能的所有位置，那么我们有两种情况：
//     //1.a如果可以排在首位，我们选择a后的最近的b；
//     //2.如果a不能排在首位而b可以排在首位，那么选择能排在首位的b；
//     //3.如果都不能，那么这个时候要看有没有大于b的字符必须排在a前面，这个情况又有两种
    
// }

bool isContain(const string& text,int mask,char ch,int& pos)
{
    printf("ch:%c\n",ch);
    int i=pos;
    for(;i<text.size();++i)
    {
        if(text[i] == ch)
        {
            break;
        }
    }

    int p = i+1;
    int t = 0;
    for(;i<text.size();++i)
    {
        if(mask & (1 << (text[i]-'a')))
        {
            t|= (1<<(text[i]-'a'));
        }
    }

    if(t == mask)
    {
        pos = p;
        return true;
    }

    return false;
}

string smallestSubsequence4(string text) {
    //思路：使用掩码来存储个字符是否存在text，采用贪心策略，从最小字符开始装填
    //比如a，如果能确定填上a，就是出现a的位置之后text中的甚于字符包含要出现剩余的所有字符
    //例如，abccce，第一个添上a必须保证a后面有bce三个字符

    int mask = 0;
    for(int i=0;i<text.size();++i)
    {
        mask |= (1 << (text[i]-'a'));
    }

    int pos = 0;
    string res;
    while(mask)
    {
        for(int i=0;i<26;++i)
        {
            if((mask & (1 << i)) && isContain(text,mask,'a'+i,pos))
            {
                res.push_back('a'+i);
                mask ^= (1 << i);
                break;
            }
        }
    }

    return res;
}

//还有一种是使用递增栈的思想，如果遇到的字符先看是否入栈了，如果没有就与栈顶比大小，如果小，则看栈顶字符是否在后面出现，如果出现就出栈

int main()
{
    printf("%s\n",smallestSubsequence4("cdadabcc").c_str());//adbc
    // printf("%s\n",smallestSubsequence4("abcd").c_str());//abcd
    // printf("%s\n",smallestSubsequence4("ecbacba").c_str());//eacb
    // printf("%s\n",smallestSubsequence3("leetcode").c_str());//letcod
    // printf("%s\n",smallestSubsequence3("ddeeeccdce").c_str());//cde
    // printf("%s\n",smallestSubsequence3("cbaacabcaaccaacababa").c_str());//abc

    return 0;
}