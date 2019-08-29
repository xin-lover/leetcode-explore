//leetcode 848. 字母移位

#include <cstdio>
#include <string>
#include <vector>

using namespace std;

string shiftingLetters(string S, vector<int>& shifts) {
    //思路:一个一个应用估计要超时
    //观察，可以总结一个表达式
    //第一个字母是SS[0] = shifts[0]*1 + shifts[1]*0+......+shifts[n-1]*0
    //第二个字母是SS[1] = shifts[0]*1+shifts[1]*1+shifts[1]*1+.....shifts[n-1]*0
    //第i个字母是SS[i] = shifts[0]*1+shifts]1]*1+...+shifs[i] + ......shifts[i]*1+shitfs[i+1]*0+..shifts[n]*0
    //令f[i]字母在第i次位移的次数则f[i] = f[i-1]+shifts[i]
    //所以策略就是动归

    int n=shifts.size();
    shifts[n-1] %= 26;
    S[n-1] = (S[n-1]-'a' + shifts[n-1]) % 26 + 'a';
    for(int i=n-2;i>=0;--i)
    {
        shifts[i] = shifts[i+1] % 26 +shifts[i];
        S[i] = (S[i]-'a' + shifts[i]) % 26 + 'a';
    }

    return S;
}

int main()
{
    vector<int> shifts = {3,5,9};
    printf("%s\n",shiftingLetters("abc",shifts).c_str());
    return 0;
}