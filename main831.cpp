//leetcode 831. 隐藏个人信息

#include <cstdio>
#include <string>

using namespace std;

string maskPII(string S) {
    //思路：首先应判断是邮箱还是电话号
    //邮箱的话，有a-z，A-Z的字符，@和.
    //电话需要先去除括号等不需要的符号，后10位是本地号码
    //策略：构建一个新字符串，然后添加符合要求的字符

    bool isEmail = false;
    for(int i=0;i<S.size();++i)
    {
        if((S[i]>='a' && S[i] <='z') ||(S[i] >= 'A' && S[i] <= 'Z') || S[i] == '@')
        {
            isEmail = true;
            break;
        }
    }

    string res;
    if(isEmail)
    {
        res.append(1,S[0] >= 'A' && S[0] <= 'Z' ? S[0] + 32 : S[0]);
        res.append("*****");
        int spos = 0;
        for(int i=1;i<S.size();++i)
        {
            if(S[i] == '@')
            {
                spos=i;
                break;
            }
        }   

        for(int i=spos-1;i<S.size();++i)
        {
            res.append(1,S[i] >= 'A' && S[i] <= 'Z' ? S[i] + 32 : S[i]);
        }
    }
    else
    {
        string tmp;
        for(int i=0;i<S.size();++i)
        {
            if(S[i] >= '0' && S[i] <= '9')
            {
                tmp.append(1,S[i]);
            }
        }

        if(tmp.size() <= 10)
        {
            res.append("***-***-");
            res.append(tmp,tmp.size()-4,4);  
        }
        else
        {
            res.append("+");
            res.append(tmp.size()-10,'*');
            res.append("-***-***-");
            res.append(tmp,tmp.size()-4,4);  
        }
        
    }

    return res;
    
}

int main()
{
    printf("%d %d\n",'@','.');
    printf("%s\n",maskPII("LeetCode@LeetCode.com").c_str());
    printf("%s\n",maskPII("AB@qq.com").c_str());
    printf("%s\n",maskPII("1(234)567-890").c_str());
    printf("%s\n",maskPII("86-(10)12345678").c_str());
    printf("%s\n",maskPII("L@LeetCode.com").c_str());

    return 0;
}