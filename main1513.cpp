//1513. 仅含 1 的子串数

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

int numSub(string s) {
    //思路：统计全1的所有区间即可，区间内全1的子串又（n+1)*n/2个

    static const int kLimit = 1e9 + 7;
    int res = 0;
    int start = -1;
    for(int i=0;i<=s.size();++i)
    {
        if(s[i] == '1')
        {
            if(start == -1)
            {
                start = i;
            }
        }
        else
        {
            if(start != -1)
            {
                //统计
                int len = i - start;
                long long c = (len+1)*len / 2;

                res = (res + c) % kLimit;

                start = -1;
            }
        }
        
    }

    return res;
}

int main()
{
    string s = "0110111"; //9
    s = s = "111111"; //21
    printf("%d\n",numSub(s));

    return 0;
}