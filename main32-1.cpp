//32. 最长有效括号

#include <cstdio>
#include <vector>
#include <string>
#include <stack>

using namespace std;

int longestValidParentheses(string s) {
    //思路：可以把无效的括号作为分割，问题就变为查找最长的有效区间
    //使用栈，记录左括号的位置，遇到右括号的时候出栈，计算区间长度即可
    //但这种方法不能处理类似"()()"的情况；
    //考虑记录已计算的区间，也就是以i结尾的区间的区间长度

    //优化，不实用额外数组记录，而是改为在最初的时候在栈中push一个-1，这样就意味着栈中需要存储上一个有效括号的“）”的最后位置
    //所以每次需要栈空的时候，都需要把当前位置压入栈，表示起点。。。
    //     int longestValidParentheses(string s) {
    //     int maxans = 0;
    //     stack<int> stk;
    //     stk.push(-1);
    //     for (int i = 0; i < s.length(); i++) {
    //         if (s[i] == '(') {
    //             stk.push(i);
    //         } else {
    //             stk.pop();
    //             if (stk.empty()) {
    //                 stk.push(i);
    //             } else {
    //                 maxans = max(maxans, i - stk.top());
    //             }
    //         }
    //     }
    //     return maxans;
    // }

    vector<int> flags(s.size(),0);
    stack<int> sk;
    int res = 0;
    // int pre = 0;
    for(int i=0;i<s.size();++i)
    {
        if(s[i] == '(')
        {
            sk.push(i);
        }
        else
        {
            if(sk.empty())
            {
                while(!sk.empty())
                {
                    sk.pop();
                }
            }
            else
            {
                int p = sk.top();
                sk.pop();
                int c = i-p+1;
                flags[i] = c;
                //看是否有连续相连的区间
                int t = 0;
                int pos = i;
                // printf("c:%d\n",c);
                while(pos >= 0 && flags[pos] > 0)
                {
                    t += flags[pos];
                    pos -= flags[pos];
                }
                res = max(res,t);
            }
            
        }
    }

    return res;
}

//计数法，很巧妙
int longestValidParentheses2(string s) {
    int left = 0, right = 0, maxlength = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') {
            left++;
        } else {
            right++;
        }
        if (left == right) {
            maxlength = max(maxlength, 2 * right);
        } else if (right > left) {
            left = right = 0;
        }
    }
    left = right = 0;
    for (int i = (int)s.length() - 1; i >= 0; i--) {
        if (s[i] == '(') {
            left++;
        } else {
            right++;
        }
        if (left == right) {
            maxlength = max(maxlength, 2 * left);
        } else if (left > right) {
            left = right = 0;
        }
    }
    return maxlength;
}

//动态规划

// 我们从前往后遍历字符串求解 \textit{dp}dp 值，我们每两个字符检查一次：
// s[i] = \text{‘)’}s[i]=‘)’ 且 s[i - 1] = \text{‘(’}s[i−1]=‘(’，也就是字符串形如 “……()”“……()”，我们可以推出：
// \textit{dp}[i]=\textit{dp}[i-2]+2
// dp[i]=dp[i−2]+2
// 我们可以进行这样的转移，是因为结束部分的 "()" 是一个有效子字符串，并且将之前有效子字符串的长度增加了 22 。
// s[i] = \text{‘)’}s[i]=‘)’ 且 s[i - 1] = \text{‘)’}s[i−1]=‘)’，也就是字符串形如 “……))”“……))”，我们可以推出：
// 如果 s[i - \textit{dp}[i - 1] - 1] = \text{‘(’}s[i−dp[i−1]−1]=‘(’，那么
// \textit{dp}[i]=\textit{dp}[i-1]+\textit{dp}[i-\textit{dp}[i-1]-2]+2
// dp[i]=dp[i−1]+dp[i−dp[i−1]−2]+2
// 我们考虑如果倒数第二个 \text{‘)’}‘)’ 是一个有效子字符串的一部分（记作 sub_ssub 
// s
// ​	
//  ），对于最后一个 \text{‘)’}‘)’ ，如果它是一个更长子字符串的一部分，那么它一定有一个对应的 \text{‘(’}‘(’ ，且它的位置在倒数第二个 \text{‘)’}‘)’ 所在的有效子字符串的前面（也就是 sub_ssub 
// s
// ​	
//   的前面）。因此，如果子字符串 sub_ssub 
// s
// ​	
//   的前面恰好是 \text{‘(’}‘(’ ，那么我们就用 22 加上 sub_ssub 
// s
// ​	
//   的长度（\textit{dp}[i-1]dp[i−1]）去更新 \textit{dp}[i]dp[i]。同时，我们也会把有效子串 “(sub_s)”“(sub 
// s
// ​	
//  )” 之前的有效子串的长度也加上，也就是再加上 \textit{dp}[i-\textit{dp}[i-1]-2]dp[i−dp[i−1]−2]。

// 最后的答案即为 \textit{dp}dp 数组中的最大值。

int main()
{
    string s = "(()"; //2
    // s = ")()())";   //4
    // s = "()(()";    //2
    // s = "(()(((()"; //2
    // s = "(()()";    //4
    //132
    s = ")(()(()(((())(((((()()))((((()()(()()())())())()))()()()())(())()()(((()))))()((()))(((())()((()()())((())))(())))())((()())()()((()((())))))((()(((((()((()))(()()(())))((()))()))())";

    //54
    s = "))(())()((((((())(()))((())(((((((()))())((((())())(()())))))))))((()((()(()(()()((()()()(()()()))(()()(()(())())))()())()(((((";
    printf("%d\n",longestValidParentheses(s));

    return 0;
}