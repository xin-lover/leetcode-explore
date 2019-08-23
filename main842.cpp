//leetcode 842. 将数组拆分成斐波那契序列

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

bool splitIntoFibonacci(const string& S,int previous, int expected,int start,vector<int>& nums) 
{
    printf("start:%d\n",start);
    if(start >= S.size())
    {
        printf("get\n");
        return true;
    }

    int end = S.size();
    if(S[start] == '0')
    {
        end = start+1;
    }

    long long n = 0;
    int i;
    for(i=start;i<end;++i)
    {
        n*=10;
        n+=S[i]-'0';
        if(n >= expected)
        {
            break;
        }
    }



    if(n == expected)
    {
        if(n == 1550452755)
        {
            printf("whhhhhhhhh   %d %d\n",i,S.size());
        }
        nums.push_back(expected);
        long long ee = previous + static_cast<long long>(expected);
        if(ee <= INT_MAX)
        {
            if(!splitIntoFibonacci(S,expected,ee,i+1,nums))
            {
                nums.pop_back();
                return false;
            }
            else
            {
                return true;
            }  
        }
        else
        {
            return i+1 >= S.size();
        }
    }
    else
    {
        return false;
    }
    
}

vector<int> splitIntoFibonacci(string S) {
    //思路：只需要求出一种即可，数列要求最少为3个数
    //其实只要确定前两个数就能知道是否是斐波那契数列
    //策略：回溯法

    vector<int> res;
    int n = S.size();
    int g1 = S[0]=='0' ? 1 : n-1;
    for(int i=1;i<=g1;++i)
    {
        long long f1 = stoll(S.substr(0,i));
        if(f1 > INT_MAX)
        {
            break;
        }
        int g2 = S[i]=='0' ? 1 : n-1;
        for(int j=1;j<=g2;++j)
        {
            long long f2 = stoll(S.substr(i,j));
            if(f2 > INT_MAX)
            {
                break;
            }
            res.push_back(f1);
            res.push_back(f2);
            printf("f1:%lld f2:%lld\n",f1,f2);
            if(splitIntoFibonacci(S,f2,f1+f2,i+j,res))
            {
                return res;
            }
            res.pop_back();
            res.pop_back();
        }
    }


    return {};
}

int main()
{
    // vector<int> res = splitIntoFibonacci("123456579");
    // vector<int> res = splitIntoFibonacci("11235813");
    // vector<int> res = splitIntoFibonacci("112358130");
    // vector<int> res = splitIntoFibonacci("012324");
    // vector<int> res = splitIntoFibonacci("00246");
    // vector<int> res = splitIntoFibonacci("214748364721474836422147483641");
    // vector<int> res = splitIntoFibonacci("1101111");
    // vector<int> res = splitIntoFibonacci("0000");
    // vector<int> res = splitIntoFibonacci("17522");
    vector<int> res = splitIntoFibonacci("417420815174208193484163452262453871040871393665402264706273658371675923077949581449611550452755");

    for(int a : res)
    {
        printf("%d ",a);
    }
    printf("\n");

    return 0;
}