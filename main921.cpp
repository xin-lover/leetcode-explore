//leetcode 921. 使括号有效的最少添加

#include <cstdio>
#include <string>

using namespace std;

int minAddToMakeValid(string S) {
    //思路：括号是成对的，所以记录左括号的数量，如果碰到有括号就-1
    //如果在碰到新的左括号时，左括号的数量为负数，这个负数表示缺少的右括号数量
    //最后，左扩号数量表示缺失的右括号数量

    int left = 0;
    int res = 0;
    for(int i=0;i<S.size();++i)
    {
        if(S[i] == '(')
        {
            if(left < 0)
            {
                res -=left;
                left = 1;
            }
            else
            {
                ++left;
            }
        }
        else if(S[i] == ')')
        {
            --left;
        }
    }

    return res + abs(left);
}

int main()
{
    printf("%d\n",minAddToMakeValid("())")); //1 
    printf("%d\n",minAddToMakeValid("((("));//3
    printf("%d\n",minAddToMakeValid("()"));//0
    printf("%d\n",minAddToMakeValid("()))(("));//4
    return 0;
}