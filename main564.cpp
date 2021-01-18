//564. 寻找最近的回文数

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

// void backtrace(string& n, int index)
// {
//     int len = n.size();
//     if(index > len / 2)
//     {
//         return;
//     }

//     //+1
//     if(n[index] < '9')
//     {
//         n[index] += 1;
//         int t = n[len-1-index];
//         n[len-1-index] = n[index];
//         backtrace(n,index+1);
//         n[index]-=1;
//         n[len-1-index]=t;
//     }

//     //-1
//     if(n[index] > '0')
//     {

//     }
// }

string nearestPalindromic(string n) {
    //思路：数字，要想差值小，那么肯定优先高位匹配，同时因为是回文，所以对应的低位也就是确定了
    //但这不是绝对的，比如10，优先匹配高位，会得到11，但最佳答案是9
    //对于1283，按上述原则得到1221,但最佳匹配是1331
    //所以不能按照上面的想法来，我们考虑第一位k，我们的选择有:k,k+1,k-1，对于k+1和k-1都有边界情况，也就是9和1的时候,这两种情况对于最接近n的回文是确定的：9……9，10……01
    //对于第二位，如果k-1了，那么中间就都是9，如果k+1了，那么中间就都是0

    if(n.empty())
    {
        return "";
    }


    long long orgValue = stoll(n);
    long long res=LONG_MAX;
    long long dif = LONG_MAX;
    //首位+1
    if(n[0] == '9')
    {
        string tmp(n.size()+1,'0');
        tmp.front()='1';
        tmp.back() = '1';
        res = stoll(tmp);
        dif = abs(stoll(tmp)-orgValue);
    }
    
    //首位-1
    if(n[0] == '1' && n.size() > 1)
    {
        string tmp(n.size()-1,'9');
        long long d = abs(stoll(tmp)-orgValue);
        if(d <= dif)
        {
            res = stoll(tmp);
            dif = d;
        }
    }

    //高位不变的,那么中间还是面临+1，-1的选择，但因为高位不变了，所以不能进位
    int len = n.size();
    string tmp(n.size(),'0');
    tmp[0] = n[0];
    tmp[len-1]=n[0];
    //+1
    for(int i=0;i<(len+1)/2;++i)
    {
        if(n[i] != '9')
        {
            tmp[i] = n[i]+1;
            tmp[len-1-i] = tmp[i];
            long long tmpVal = stoll(tmp);
            long long d = abs(tmpVal - orgValue); 
            if(d < dif || (d==dif && tmpVal < res))
            {
                res = tmpVal;
                dif=d;
            }

        }

        tmp[i] = n[i];
        tmp[len-1-i] = n[i]; //恢复
    }

    //-1
    for(int i=0;i<len;++i)
    {
        tmp[i]='9';
    }
    for(int i=0;i<(len+1)/2;++i)
    {
        if(n[i] != '0')
        {
            tmp[i] = n[i]-1;
            tmp[len-1-i] = tmp[i];
            long long tmpVal = stoll(tmp);
            long long d = abs(tmpVal - orgValue); 
            if(d < dif || (d==dif && tmpVal < res))
            {
                res = tmpVal;
                dif=d;
            }
        }

        tmp[i] = n[i];
        tmp[len-1-i] = n[i];
    }

    if(tmp != n)
    {
        long long tmpVal = stoll(tmp);
        long long d = abs(tmpVal - orgValue); 
        if(d < dif || (d==dif && tmpVal < res))
        {
            res = tmpVal;
            dif=d;
        }
    }

    
    return to_string(res);
}

int main()
{
    // printf("%s\n",nearestPalindromic("1").c_str());//0
    // printf("%s\n",nearestPalindromic("123").c_str());//121
    // printf("%s\n",nearestPalindromic("10").c_str());//9
    // printf("%s\n",nearestPalindromic("99").c_str());//101
    // printf("%s\n",nearestPalindromic("1805170081").c_str());//101

    vector<int> nums = {1,2,3};
    printf("%d\n",arrayNesting(nums));
    return 0;
}