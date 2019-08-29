//leetcode 856. 括号的分数

#include <cstdio>
#include <string>
#include <stack>

using namespace std;

int scoreOfParentheses(string S) {
    //思路：关键在于嵌套括号，根据题目要求，不需要考虑不成对括号的情况
    //可以考虑栈，遇到左括号入栈，右括号出栈
    //问题是对于（）（）的情况，也就是第二个右括号不只要计算自己的值，还要加上以前的值
    //解决方案，压入一个0作为当前左括号的标识，也就是遇到右括号后不停的出栈，直到遇到0，然后把这些数相加

    // bool end = false;//标识连续右括号
    stack<int> sk;
    int left = 0;
    int right = 0;
    for(int i=0;i<S.size();++i)
    {
        if(S[i] == '(')
        {
            sk.push(0);
        }
        else
        {
            int p = 0;
            while(sk.top() != 0)
            {
                p+=sk.top();
                sk.pop();
            }
            sk.pop();
            p*=2;
            sk.push(p==0?1:p);
        }
    }

    int res = 0;
    while(!sk.empty())
    {
        res += sk.top();
        sk.pop();
    }
    return res;
}

int scoreOfParentheses2(string S) {
    int length=S.length();
    int sum=0;
    int n=0;
    for(int i=0;i<length;i++)
    {
        if(S[i]=='(')
        {
            if(n==0)
            {
                n=1;
            }
            else
            {
                n=n<<1;
            }
        }
        else if(S[i]==')')
        {
                if(S[i-1]=='(')
            {
                    sum+=n;
            }
            n=n>>1;
            
        }
    }
    return sum;
}


int main()
{
    printf("%d\n",scoreOfParentheses("()"));
    printf("%d\n",scoreOfParentheses("(())"));
    printf("%d\n",scoreOfParentheses("()()"));
    printf("%d\n",scoreOfParentheses2("(()(()))"));
    return 0;
}