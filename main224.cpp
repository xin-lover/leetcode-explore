//224. 基本计算器

#include <cstdio>
#include <vector>
#include <string>
#include <stack>

using namespace std;

int calculate(string s) {
    //思路：只有括号和加减，那么先把字符变数字，使用栈解决
    //关键在括号的处理，使用一个负数

    int start = -1;
    stack<pair<int,int>> sk;
    for(int i=0;i<=s.size();++i)
    {
        if(s[i]>='0' && s[i]<='9')
        {
            if(start == -1)
            {
                start = i;
            }
        }
        else
        {
            if(start > -1)
            {
                int num = 0;
                for(int j=start;j<i;++j)
                {
                    num *= 10;
                    num += s[j] - '0';
                }
                sk.push({0,num});
                printf("push:%d\n",num);
                start = -1;
            }
            if(s[i] == ' ')
            {
                continue;
            }
            else if(s[i] == '(')
            {
                sk.push({1,0});
            }
            else if(s[i] == ')' || s[i] == '\0')
            {
                int sum = 0;
                int val = 0;
                while(!sk.empty() && sk.top().first != 1)
                {
                    pair<int,int> em = sk.top();
                    sk.pop();

                    if(em.first == 0)
                    {
                        val = em.second;
                    }
                    else
                    {
                        if(em.first == 3)
                        {
                            sum -= val;
                        }
                        else
                        {
                            sum += val;
                        }
                    }
                }

                sum += val;
                if(!sk.empty())
                {
                    sk.pop();
                }
                sk.push({0,sum});
            }
            else if(s[i] == '+')
            {
                sk.push({2,0});
            }
            else if(s[i] == '-')
            {
                sk.push({3,0});
            }
            else
            {
                return -1;
            }
        }
    }

    return sk.top().second;
}

//leetcode题解1:
// 1.按逆序迭代字符串。
// 2.操作数可以由多个字符组成，字符串 "123" 表示数字 123，它可以被构造为：123 >> 120 + 3 >> 100 + 20 + 3。如果我们读取的字符是一个数字，则我们要将读取的数字乘以 10 的幂并将当前数字相加，形成操作数。因为我们是按逆序处理字符串。
// 3.操作数由多个字符组成，一旦我们遇到的字符不是数字，则我们将操作数添加到栈上。
// 4.当我们遇到最括号 (，这意味这遇到了一个子表达式结束。由于我们是逆序，所以开括号成了表达式的结尾。则需要从栈中弹出操作数和运算发来计算表达式，直到弹出相应的右括号。子表达式的最终结果最终添加到栈上。
// 5.将非数字字符添加到栈上。
// 6.这样做直到我们得到最终的结果。可能我们没有更多的字符要处理，但是栈仍然是非空的。当主表达式没有用括号括起来时，就会发生这种情况。因此，在完成对整个表达式求值之后，我们将检查栈是否非空。如果是的话，我们将栈中的元素作为最终表达式处理，并像遇到左括号时那样对其求值。我们还可以用一组括号覆盖原表达式，以此避免额外调用。

//题解2:
// 1.正序迭代字符串。
// 2.操作数可以由多个字符组成，字符串 "123" 表示数字 123，它可以被构造为：123 >> 120 + 3 >> 100 + 20 + 3。如果我们读取的字符是一个数字，则我们要将先前形成的操作数乘以 10 并于读取的数字相加，形成操作数。
// 3.每当我们遇到 + 或 - 运算符时，我们首先将表达式求值到左边，然后将正负符号保存到下一次求值。
// 4.如果字符是左括号 (，我们将迄今为止计算的结果和符号添加到栈上，然后重新开始进行计算，就像计算一个新的表达式一样。
// 5.如果字符是右括号 )，则首先计算左侧的表达式。则产生的结果就是刚刚结束的子表达式的结果。如果栈顶部有符号，则将此结果与符号相乘。

int main()
{
    printf("%d\n",calculate("1 + 1")); //2
    // printf("%d\n",calculate(" 2-1 + 2 ")); //3
    // printf("%d\n",calculate("(1+(4+5+2)-3)+(6+8)")); //23
    return 0;
}