//1541. 平衡括号字符串的最少插入次数

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

int minInsertions(string s) {
    //思路：首先第一个条件就是右括号等于左括号的两倍
    //因为有顺序要求，所以不能简单搞数量
    //一个简单的方案就是：记录当前左右括号数量，
    //如果先遇到右括号，那么肯定是要补左括号的，否则左右括号需要抵消

    int left=0,right=0;

    int res = 0;
    for(int i=0;i<=s.size();++i)
    {
        if(s[i] != ')')
        {
            int p= right / 2;
            int q = right % 2;
            int needLeft = p + q;
            if(left >= needLeft)
            {
                left -= needLeft;
                res += q;
            }
            else
            {
                needLeft -= left;
                res += needLeft + q;
                left = 0;
            }
            
            right = 0;
            ++left;
            printf("left:%d right:%d res:%d\n",left,right,res);
        }
        else
        {
            ++right;
        }
    }

    res += 2 * (left-1);

    return res;
}

int main()
{
    string s = "(()))"; //1
    s = "())";   //0
    // s = "))())(";    //3
    // s = "(((((("; //12
    // s = ")))))))";   //5
    printf("%d\n",minInsertions(s));

    return 0;
}