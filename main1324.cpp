//1324. 竖直打印单词

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

vector<string> printVertically(string s) {
    //思路：横变竖，重点是空格的处理
    //首先前置的空格需要存在，而这个怎么来的呢？是因为s中字符串长度不同导致的
    //也就是说字符串竖直表示之后，长度是最长的长度，不够的就补空格
    //而对于尾随的空格，一个简单的思路就是先补全，再删除
    //另一个思路就是记录当前位置到s尾部的字符串中最长的长度,这样可以知道后面是否会有字符，也就能知道是否是尾随空格了

    //先分割，我们可以用记录开始位置和长度的方式，不用额外的生成string了
    vector<vector<int>> words;
    int start = 0;
    for(int i=0;i<s.length();++i)
    {
        if(s[i] == ' ')
        {
            words.push_back({start,i-start});
            start = i+1;
        }
    }

    words.push_back({start,int(s.length()-start)});

    vector<int> flags(words.size(),0);
    flags.back() = words.back()[1];
    for(int i=words.size()-2;i>=0;--i)
    {
        flags[i] = max(flags[i+1],words[i][1]);
    }
    
    vector<string> res(flags[0]);
    for(int i=0;i<res.size();++i)//一行一行的填充
    {
        for(int j=0;j<words.size();++j)
        {
            if(i < words[j][1])
            {
                res[i].append(1,s[words[j][0] + i]);
            }            
            else if(flags[j] >= i+1)
            {
                res[i].append(1,' ');
            }
        }
    }

    return res;
}

int main()
{
    //"TBONTB"
    //"OEROOE"
    //"   T"
    string s = "TO BE OR NOT TO BE";

    // //  "HAY"
    // //  "ORO"
    // //  "WEU"
    // s = "HOW ARE YOU";

    // //"CIC"
    // //"OSO"
    // //"N M"
    // //"T I"
    // //"E N"
    // //"S G"
    // //"T"
    // s = "CONTEST IS COMING";

    auto res = printVertically(s);
    for(auto a : res)
    {
        printf("%s\n",a.c_str());
    }
    printf("%d\n",res.back().size());
    return 0;
}