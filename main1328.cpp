//1328. 破坏回文串

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

string breakPalindrome(string palindrome) {
    //思路：因为字典序最小，所以优先考虑前面的字符
    //要破坏回文，随便改一个字符就行，如果前面的字典序最小，那么就要改后面的
    //只有一个字符，直接返回空

    if(palindrome.length() < 2)
    {
        return "";
    }

    int len = palindrome.length();
    int first_half_end = len / 2 - (len & 1);
    //长度为奇数，中间元素改变不能破坏回文
    //变小可能
    int pos=0;
    while(pos <= first_half_end)
    {

        if(palindrome[pos] !='a')
        {
            palindrome[pos]='a';
            return palindrome;
        }
        ++pos;
    }

    int second_half_start = len / 2 + (len & 1);
    pos = second_half_start;
    while(pos < len)
    {
        if(palindrome[pos] != 'a')
        {
            ++palindrome[pos];
            return palindrome;
        }
        ++pos;
    }
    //变大可能
    pos = len - 1;
    while(pos >= second_half_start)
    {
        if(palindrome[pos]+1 <= 'z')
        {
            ++palindrome[pos];
            return palindrome;
        }
        --pos;
    }

    pos = first_half_end;
    while(pos >= 0)
    {
        if(palindrome[pos]+1 <= 'z')
        {
            ++palindrome[pos];
            return palindrome;
        }
        --pos;      
    }

    return "";
}

//更深入理解，写法更简洁
string breakPalindrome2(string palindrome)
{
    if (palindrome.size() <= 1) return "";

    //只需要判断前半段，除非前半段都是'a',否则不需要判断后半段
    //而如果都是'a',那么后半段也是'a',那么只能变大。。。。。
    for (int i = 0; i < palindrome.size() / 2; i++) {
        if (palindrome[i] != 'a') {
            palindrome[i] = 'a';
            return palindrome;
        }
    }

    palindrome.back() = palindrome.back() + 1;//注意是改最后一个 字典序要小
    return palindrome;
}

int main()
{
    printf("%s\n",breakPalindrome("abccba").c_str());   //aaccba
    printf("%s\n",breakPalindrome("aba").c_str());   //aaccba
    return 0;
}