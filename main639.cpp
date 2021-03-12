//639. 解码方法 II

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

int numDecodings(string s) {
    //思路：参考1*，可以分为{1,*}和{1,*}两种方式，主要是这个地方引入的复杂性
    //假设我们已经知道了钱n个数的可能性了f(n)，s[n+1]='1',那么这个时候的可能性是f(n+1)=f(n)+f(n-1)+...+f(0),f(0)=1，也就是新的这个字符单独分组，与前一个分组，与前两个分组。。。。
    //而如果s[n+1]='*',那么s[n+1]的可能有9种，所以f(n+1)=9*(f(n)+f(n-1)+f(n-2)+....+f(0))
    //同时，如果s[n+2]='1',那么f(n+2)=f(n+1)+f(n)*9*(f(1)+f(0)) + f(n-1)*(f(2)+9*(f(1)+f(0))+9*(f0))+ ..... +f(0) * 9
    //也就是说令f(n)表示s的前n个字符的可能性，m(n)表示s的后n个字符作为一个整体时的可能性，那么
    //f(n)=f(0)*m(n)+f(1)*m(n-1)+f(2)*m(n-2)+...+f(n-1)*m(1)
    //对于没有'*'的时候，我们看看能不能化简：
    //f(n) = f(n-1) + f(n-2) + ... + f(0)
    //f(n+1) = f(n) + f(n-1) + .... + f(0)
    //f(n+1) = f(n) +f(n)=2*f(n)
    //有*号的时候，好像不行
    //题意理解错了。。。。
    
    const int kLimit=1000000007;
    vector<long long> f(s.size()+1,0);
    vector<int> countStarArr(s.size()+1,0);

    for(int i=0;i<s.size();++i)
    {
        countStarArr[i+1] = countStarArr[i] + (s[i]=='*' ? 1 : 0);
    }

    vector<int> nineMulti(countStarArr.back()+1,1);
    int sz = nineMulti.size();  
    for(int i=1;i<sz;++i)
    {
        nineMulti[i] = (static_cast<long long>(nineMulti[i-1])*9) % kLimit;
    }

    f[0]=1;
    for(int i=0;i<s.size();++i)
    {
        for(int j=1;j<=i+1;++j)
        {
            f[i+1] += f[i+1-j] * nineMulti[countStarArr[i+1]-countStarArr[i+1-j]];
            f[i+1] %= kLimit;
        }
    }

    return f[s.size()];
}

int numDecodings2(string s) {
    //思路：我靠，题意都理解错了，是先组成数字，然后数字翻译成字母。。。。。。
    //数字最大26，所以3*，只能拆为{3,*}....
    //参照上面的思路，对于f(n),最后的字符最多与它前面的字符连接。。。。
    //这样我们就需要考察s[n]和s[n-1]
    //s[n]='*',s[n]独立解码，那么结果是9*f(n-1),s[n-1]>2，不能结合，s[n-1]='2',6*f(n-1),s[n-1]=1,9*f(n-1)
    
    //优化，发现只用了f[i],f[i-1]两项，所以可以空间复杂度可以优化到O(1)
    if(s.empty())
    {
        return 0;
    }
    if(s[0] == '0')
    {
        return 0;
    }
    const int kLimit=1000000007;
    vector<long long> f(s.size()+1,0);
    f[0] = 1;
    f[1] = s[0] == '*' ? 9 : 1;
    for(int i=1;i<s.size();++i)
    {
        if(s[i] == '*')
        {
            f[i+1] += f[i] * 9;
            if(s[i-1] == '1')
            {
                f[i+1] += f[i-1] * 9;
            }
            else if(s[i-1] == '2')
            {
                f[i+1] += f[i-1] * 6;
            }
            else if(s[i-1] == '*')
            {
                f[i+1] += f[i-1] * 15; //两位数只有15个。。。。
            }
        }
        else if(s[i] == '0')
        {
            if(s[i-1] == '1' || s[i-1] == '2')
            {
                f[i+1] += f[i-1];
            }
            else if(s[i-1] == '*')
            {
                f[i+1] += f[i-1]*2;
            }
            else
            {
                return 0;
            }
            
        }
        else
        {
            if(s[i-1] == '*')
            {
                if(s[i] <= '6')
                {
                    f[i+1] += f[i] + f[i-1]*2;
                }
                else
                {
                    f[i+1] += f[i] + f[i-1];
                }
            }
            else if(s[i-1] == '0')
            {
                f[i+1] += f[i];
            }
            else
            {
                f[i+1] += f[i];
                if((s[i-1]-'0')*10+s[i]-'0' <= 26)
                {
                    f[i+1] += f[i-1];
                }
            }
        }

        f[i+1] %= kLimit;
    }

    return f[s.size()];

}


int main()
{
    string s = "*"; //9
    s = "1*"; //18
    s = "2*"; //15
    s = "**"; //96
    s = "*1*1*0"; //404
    s = "0"; //0
    s = "104";  //1
    s = "*********";    //291868912
    s = "1111111111111111111111111111****0***0**0*0*********0888888888888888888888888*********";//313076501
    s = "10***0**0*0*********0"; //76315447
    s = "10***0**0*0*********08"; //76315447
    printf("%d\n",numDecodings2(s));
    return 0;
}