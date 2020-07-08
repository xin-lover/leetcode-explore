//1415. 长度为 n 的开心字符串中字典序第 k 小的字符串

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

string getHappyString(int n, int k) {
    //思路：这又是一个组合的问题，要求是s[i] != s[i+1]
    //从0开始，s[0]有3中可能， s[1]两种，s[2]两种，所以对于n位，能构造的开心字符串总数知道
    //假设f(n)标识长度位n的字符串数量，对于n!=1,f(n)=2*f(n-1)，
    //同理，长度位n，如果s[0]确定，那么开心字符串的数量也能确定是2^(n-1),
    //这个规律是可以步进的，也就是如果s[0],s[1],确定，那么开心字符串的数量为2^(n-2);
    //这个规律有点像二进制，但因为开始有3种可能，所以我们一步一步来

    int m = 1 << n;
    if(m / 2 * 3 < k)
    {
        return "";
    }

    vector<char> chs = {'a','b','c'};
    string res;
    int count = 0;
    for(int i=0;i<n;++i)    //一位一位的确定
    {
        int t = (1 << (n-i-1));
        printf("t:%d\n",t);
        int j = 0;  //用于标识第几个字符
        while(count + t  < k)  //因为之前已经确定总数大于k，所以这里不会出现意外
        {
            count += t;
            ++j;
        }

        printf("j:%d\n",j);
        if(res.empty())
        {
            res.append(1,chs[j]);
        }
        else
        {
            //查找不等与res.back()的第j个字符
            int t = -1;
            for(int x=0;x<chs.size();++x)
            {
                if(chs[x] != res.back())
                {
                    ++t;
                    if(t == j)
                    {
                        res.append(1,chs[x]);
                        break;
                    }
                }
            }
        }
        
    }

    return res;
}

int main()
{
    int n = 1, k = 3;   //c
    // n = 3, k = 9;   //"cab"
    n = 10, k = 100;    //abacbabacb
    printf("%s\n",getHappyString(n,k).c_str());
    return 0;
}