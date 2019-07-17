//leetcode 592 分数加减运算

#include <cstdio>
#include <string>

using namespace std;

int gcd3(int x,int y)
{
    if(x == 0 || y == 0)
    {
        return 0;
    }
    if(x == y)
    {
        return x;
    }

    if(x < y)
    {
        return gcd3(y,x);
    }
    else
    {
        if(!(x&1) && !(y&1))
        {
            return gcd3(x>>1,y>>1) << 1;
        }
        else if(!(x&1) && (y&1))
        {
            return gcd3(x>>1,y);
        }
        else if((x&1) && !(y&1))
        {
            return gcd3(x,y>>1);
        }
        else
        {
            return gcd3(y,x-y);
        }
        
    }
}

string fractionAddition(string expression) {
    //思路：以加减号分割，注意正负号的存在
    //然后分数按‘/’分为分子和分母，转化为数字后计算，最后求最大公约数
    //因为只有加减，所以不需要考虑运算的优先级

    int start = -1;
    int numerator = 0;
    int denominator = 1;

    int curN = 0;
    int curD = 0;
    for(int i=0;i<=expression.size();++i)
    {
        char c = expression[i];
        if(c == '-' || c == '+' || c=='\0')
        {
            if(start == -1)
            {
                start = i;
            }
            else
            {
                curD = stoi(expression.substr(start,i-start));
                printf("curD:%d\n",curD);
                start = i;

                numerator = numerator * curD + curN * denominator;
                denominator *= curD;
            }
        }
        else if(c == '/')
        {
            curN =  stoi(expression.substr(start,i-start));
            printf("curN:%d\n",curN);
            start = -1;   

        }
        else
        {
            if(start == -1)
            {
                start = i;
            }
        }
    }

    int d = gcd3(abs(numerator),abs(denominator));
    d = (d==0 ? 1 : d);
    return to_string(numerator/d) + "/" + to_string(denominator/d);
}

int main()
{
    printf("%s\n",fractionAddition("1/2+1/2").c_str());
    printf("%s\n",fractionAddition("1/3-1/2").c_str());
    printf("%s\n",fractionAddition("-1/2+1/2").c_str());
    return 0;
}