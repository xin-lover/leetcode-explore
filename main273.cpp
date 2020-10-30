//273. 整数转换英文表示

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

string numberToWords(int num) {
    //思路：正常取位，英文数字的另一个基数是千，所以每3位之后要额外处理
    //注意0的处理

    static vector<string> smallDigits = {"Zero","One","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen","Fifteen","Sixteen","Seventeen","Eighteen","Nineteen"};
    static vector<string> twoDigitsHigh = {"Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety"};
    static vector<string> orders = {"","Thousand","Million","Billion"};

    string res;
    int radix = 0;
    int pos = 0;
    int lowDigit = 0;
    bool allZero = true;
    string curRes;
    while(num > 0)
    {
        int d = num % 10;
        num /= 10;
        
        allZero = (allZero && (d == 0));

        ++pos;
        if(pos == 1)
        {
            lowDigit = d;
        }
        else if(pos == 2)
        {
            string tmp;
            if(d >= 2)
            {
                tmp = twoDigitsHigh[d-2];
                if(lowDigit > 0)
                {
                    tmp += " " + smallDigits[lowDigit];
                }
            }
            else
            {
                if(lowDigit + d*10 > 0)
                {
                    tmp = smallDigits[lowDigit + d*10]; 
                }
                
            }

            curRes = tmp + (curRes.empty() ? "" : " ") + curRes;
        }
        else
        {
            if(d > 0)
            {
                curRes = smallDigits[d] + " Hundred" + (curRes.empty() ? "" : " ") + curRes;
            }

            if(!allZero)
            {
                curRes += (orders[radix].empty()? "" : " ") + orders[radix];
                res = curRes + (res.empty() ? "" : " ") + res;
            }

            ++radix;
            pos= 0;
            allZero = true;

            curRes = "";
        }
    }
printf("%s\n",res.c_str());
    if(!allZero)
    {
        if(curRes.empty())
        {
            curRes = smallDigits[lowDigit];
        }
        curRes += (orders[radix].empty()? "" : " ") + orders[radix];
        res = curRes + (res.empty()? "" : " ") + res;
    }
    else
    {
        if(res.empty())
        {
            return smallDigits[lowDigit];
        }
    }
    

    return res;
}

int main()
{
    printf("%s\n",numberToWords(1000010).c_str());
    return 0;
}
