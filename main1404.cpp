//1404. 将二进制表示减到 1 的步骤数

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

int numSteps(string s) {
    //思路：偶数除2相当于右移一位，奇数末位是1，加1后进位，末位变0，也就是偶数
    //推算一下过程：
    //1.当前位是0，且无进位，那么右移；
    //2.当前位是0，有进位，那么相当于1，给当前位+1；
    //3.当前位是1，无进位，同2；
    //4.当前位是1，有进位，右移，保持进位


    int res = 0;
    bool carry = false;
    for(int i=s.length()-1;i>0;--i)
    {
        if(s[i] == '0')
        {
            if(carry)
            {
                res += 2;
                carry = true;
            }
            else
            {
                ++res;
            }
        }
        else
        {
            if(carry)
            {
                ++res;
            }
            else
            {
                res += 2;
                carry = true;
            }
        }
    }

    if(!s.empty() && ((s[0] == '0' && !carry) || (s[0] == '1' && carry)))
    {
        ++res;
    }

    return res;
}

int main()
{
    string s = "1101"; //6
    s = "10"; //1
    s = "1";//0
    printf("%d\n",numSteps(s));
    return 0;
}