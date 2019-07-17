//leetcode 678. 有效的括号字符串

#include <cstdio>
#include <string>
#include <stack>

using namespace std;

bool checkValidString(string s) {
    //思路：如果没有*号，则只需要记录左括号留存数量即可，
    //现在有*号，我们同时记录*的留存，优先使用括号，不够使用*号代替
    //这里有个原则就是*只能抵消在它之前的左括号和在它之后的右括号

    int left=0,star=0;

    stack<int> leftsk;
    stack<int> starsk;
    for(int i=0;i<s.size();++i)
    {
        if(s[i] == '(')
        {
            leftsk.push(i);
        }
        else if(s[i] == '*')
        {
            starsk.push(i);
        }
        else
        {
            if(!leftsk.empty())
            {
                leftsk.pop();
            }
            else if(!starsk.empty())
            {
                starsk.pop();
            }
            else
            {
                return false;
            }
        }
    }

    printf("%d %d\n",starsk.size(),leftsk.size());
    if(starsk.size() < leftsk.size())
    {
        return false;
    }
   
    while(!leftsk.empty() && !starsk.empty())
    {
        int lp = leftsk.top();
        printf("lp:%d\n",lp);
        while(!starsk.empty())
        {
            int sp = starsk.top();
            printf("sp:%d\n",sp);
            starsk.pop();
            if(sp > lp)
            {
                leftsk.pop();
                break;
            }
        }

    }

    return leftsk.empty();
}

void cc(string s, int& left,int& right, int& star)
{
    for(int i=0;i<s.size();++i)
    {
        if(s[i] == '(')
        {
            ++left;
        }
        else if(s[i] == '*')
        {
            ++star;
        }
        else
        {
            ++right;
        }
    }
}

bool checkValidString(string s)
{
        //思路：两次循环，正循环右括号不能多余做括号加*，反循环左括号不能多余右括号加*
        
        int left=0,right=0,star=0;
        for(int i=0;i<s.size();++i)
        {
            if(s[i] == '(')
            {
                ++left;
            }
            else if(s[i] == ')')
            {
                ++right;
            }
            else
            {
                ++star;
            }
            
            if(right - left > star)
            {
                return false;
            }
        }
        
        left=0;right=0;star=0;
        for(int i=s.size()-1;i>=0;--i)
        {
            if(s[i] == '(')
            {
                ++left;
            }
            else if(s[i] == ')')
            {
                ++right;
            }
            else
            {
                ++star;
            }
            
            if(left - right > star)
            {
                return false;
            }
        }
        
        return true;
}

int main()
{
    // int left=0,right=0,star=0;
    // cc("((()))()(())(*()()())**(())()()()()((*()*))((*()*)",left,right,star);
    // printf("left:%d right:%d star:%d\n",left,right,star);
    printf("%s\n",checkValidString("(())((())()()(*)(*()(())())())()()((()())((()))(*") ? "true" : "false");
    // printf("%s\n",checkValidString("(**))") ? "true" : "false");
    // printf("%s\n",checkValidString("((*)(*))((*") ? "true" : "false");
    // printf("%s\n",checkValidString("(((*)(*(((((*") ? "true" : "false");
    // printf("%s\n",checkValidString("()") ? "true" : "false");
    // printf("%s\n",checkValidString("(*)") ? "true" : "false");
    // printf("%s\n",checkValidString("((*)") ? "true" : "false");
    // printf("%s\n",checkValidString("(*))") ? "true" : "false");
    // printf("%s\n",checkValidString("(((*)") ? "true" : "false");
    // printf("%s\n",checkValidString("(*)))") ? "true" : "false");
    return 0;
}