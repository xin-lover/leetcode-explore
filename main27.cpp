#include <cstdio>
#include <string>

using namespace std;

string removeKdigits(string num, int k) {
    //思路：考虑只移走一个数的情况，213移除2，223移除3，234移除4
    //也就是第一个数大则移除第一个，否则移除之后遇到的第一个峰值点

    int start = 0;
    while(k > 0)
    {
        if(k >= num.size())
        {
            return "0";
        }
        if(num[0] > num[1])
        {
            num.erase(0,1);
            while(!num.empty() && num[0] == '0')
            {
                num.erase(0,1);
            }
        }
        else
        {
            int j = 1;
            while(j+1 < num.size() && num[j] <= num[j+1])
            {
                ++j;
            }

            num.erase(j,1);
        }

        --k;
    }

    return num.empty() ? "0" : num;
}
int main()
{
    string res = removeKdigits("112",1);
    printf("%s\n",res.c_str());
    printf("%s\n",removeKdigits("1432219",3).c_str());
    printf("%s\n",removeKdigits("10200",1).c_str());
    printf("%s\n",removeKdigits("10",2).c_str());
    printf("%s\n",removeKdigits("178376050256835161",1).c_str());
    return 0;
}