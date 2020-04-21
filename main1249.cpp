//1249. 移除无效的括号

#include <cstdio>
#include <vector>
#include <string>
#include <stack>

using namespace std;

string minRemoveToMakeValid(string s) {
    //思路：使用栈，栈存储左括号，遇到右括号时，有一下几种状况：
    //1.栈中没有右括号，那么这个左括号非法；
    //3.栈中有右括号,合法;

    stack<int> sk;
    vector<bool> flags(s.size(),true);
    for(int i=0;i<s.size();++i)
    {
        if(s[i] == '(')
        {
            sk.push(i);
        }
        else if(s[i] == ')')
        {
            if(sk.empty())
            {
                flags[i]=false;
            }
            else
            {
                sk.pop();
            }
        }
    }

    while(!sk.empty())
    {
        int p = sk.top();
        sk.pop();
        flags[p] = false;
    }

    string res;
    for(int i=0;i<s.size();++i)
    {
        if(flags[i])
        {
            res.push_back(s[i]);
        }
        
    }



    return res;
}

int main()
{
    string s = "lee(t(c)o)de)"; //lee(t(c)o)de
    s  ="a)b(c)d";//"ab(c)d"
    s = "))((";//""
    s = "())()(((";//"()()"
    printf("%s\n",minRemoveToMakeValid(s).c_str());
    return 0;
}