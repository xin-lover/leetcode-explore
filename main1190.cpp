//1190. 反转每对括号间的子串

#include <cstdio>
#include <string>
#include <stack>

using namespace std;

string reverseParentheses(string s) {
    //思路：我们可以使用首尾两个指针
    //用一个标志位来表示是否反转，

    //这种方案只能针对嵌套的情况，对于顺序排列的括号没有处理

    bool flag = false;
    int head = 0,tail = s.size()-1;

    string tmp(s.size(),'0');
    int head_i = 0,tail_i = s.size()-1;

    while(head <= tail)
    {
        printf("head:%d tail:%d\n",head,tail);
        while(s[head] != '(' && head <= tail)
        {
            if(!flag)
            {
                tmp[head_i++] = s[head];
            }
            else
            {
                tmp[tail_i--] = s[head];
            }

            ++head;
        }
        
        while(s[tail] != ')' && head <= tail)
        {
            if(flag)
            {
                tmp[head_i++] = s[tail];
            }
            else
            {
                tmp[tail_i--] = s[tail];
            }

            --tail; 
        }
        ++head;
        --tail;
        flag = !flag;
    }
    printf("end head:%d tail:%d\n",head,tail);
    printf("head_i:%d tail_i:%d\n",head_i,tail_i);

    printf("tmp:%s\n",tmp.c_str());
    string res(head_i+tmp.size()-1-tail_i,'0');
    for(int i=0;i<head_i;++i)
    {
        res[i] = tmp[i];
    }

    for(int i=tail_i+1;i<tmp.size();++i)
    {
        res[i-tail_i-1+head_i] = tmp[i];
    }

    return res;
}

string reverseParentheses2(string s) {
    //思路：拼接字符串的，这种做法简单，但反转很多次，其实不高效

    string res;
    stack<string> stk;
    for (char &c : s) {
        if (c == '(') {
            stk.push(res);
            res = "";
        } else if (c == ')') {
            reverse(res.begin(), res.end());
            res = stk.top() + res;
            stk.pop();
        } else {
            res.push_back(c);
        }
    }
    return res;


}


int main()
{
    string s = "(abcd)";//dcba
    s = "(u(love)i)";//iloveu
    s = "(ed(et(oc))el)";//leetcode
    s = "((eqk((h))))";//eqkh
    s="ta()usw((((a))))";//"tauswa"
    printf("%s\n",reverseParentheses(s).c_str());

    return 0;
}