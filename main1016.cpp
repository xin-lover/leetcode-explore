//1016. 子串能表示从 1 到 N 数字的二进制串

#include <cstdio>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

bool queryString(string S, int N) {
    //思路：肯定不能比较字符串，所以是字符串转数字
    //不考虑负整数，那么每个整数最多31位，对于S的每一字符，最多可能是31位，如果到末尾的距离位k，那么数量就是k+1
    //先判断S能表示的数量，如果小于N，那么直接返回false
    //接下来就是求所有数字了，这个可以确定长度，然后每个长度记录所有的数字，看是否满足要求
    //也可以遍历每个字符，因为每个字符最多32种可能，计算所有数字，但问题就是如何判断所有1到N的数字都有
    //这里S的长度最大位1000，每个字符32种可能，所以表示31位的所有数字是不可能的
    //所以很明显，只能表示长度10位的数字，也就是首位为1，2的9次方
    //所以我们考察二进制首位为1，如果它表示的数字要覆盖所有连续数字的情况，那么后面的连续数列要覆盖所有的情况
    //比如总共4位，首位为1，那么后面三位所有的情况都要有，也就是{000,001,010,011,100,101,110,111};
    //而在这里，3位的情况已经覆盖了，同理更小的数字也都覆盖了
    //但在这里我们发现，每个数字都是不同的，意味这连续数列都不同，我们只需要考察最长的
    //比如最长4位，那么总共8中情况，美中4位，那么需要32位
    //也就是长度n，数字最大位2的n次方-1，需要的数组长度位n*2的n-1次方
    //所以根据数组长度最大位1000，可以推算出N最大为127，即最长7位
    //那我们就可以选择记录所有数字了

    if(N > 127)
    {
        return false;
    }

    vector<bool> flags(N+1,false);
    for(int i=0;i<S.size();++i)
    {
        if(S[i] == '0')
        {
            continue;
        }
        flags[1]=true;
        int tmp = 1;
        for(int j=1;j<8 && i+j<S.size();++j)
        {
            tmp <<= 1;
            tmp += S[i+j] == '0' ? 0 : 1;
            printf("tmp:%d\n",tmp);
            if(tmp < flags.size())
            {
                flags[tmp] = true;
            }
        }
    }

    for(int i=1;i<flags.size();++i)
    {
        if(!flags[i])
        {
            return false;
        }
    }

    return true;
}

bool queryString(string S, int N) {
    //优化：使用N计算位长

    if(N > 127)
    {
        return false;
    }

    int len = 0;
    int tmp = N;
    while(tmp > 0)
    {
        tmp>>=1;
        ++len;
    }
    vector<bool> flags(pow(2,len),false);
    for(int i=0;i<S.size();++i)
    {
        if(S[i] == '0')
        {
            continue;
        }
        flags[1]=true;
        tmp = 1;
        for(int j=1;j<len && i+j<S.size();++j)
        {
            tmp <<= 1;
            tmp += S[i+j] - '0';
            flags[tmp] = true;
        }
    }

    for(int i=1;i<=N;++i)
    {
        if(!flags[i])
        {
            return false;
        }
    }

    return true;
}

int main()
{
    printf(queryString("0110",3) ? "true\n" : " false\n");//true
    printf(queryString("0110",4) ? "true\n" : " false\n");//false
    return 0;
}