//1573. 分割字符串的方案数

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

int numWays(string s) {
    //思路：字符‘1’的数目相同，所以每个子字符串中‘1’的数目可以提前确定
    //这样我们确定3个包含‘1’数量相同的最小子字符串，剩下的就是之间的‘0’
    //假设分别为m和n，那么最后的结果就是m*n
    //当然，注意全‘0’的情况

    const int kLimit=1000000007;

    int cnt = 0;
    for(auto a : s)
    {
        if(a == '1')
        {
            ++cnt;
        }
    }

    if(cnt % 3 != 0)
    {
        return 0;
    }

    int n = s.size();
    if(cnt == 0)
    {
        //通过阶乘计算，总共n-1个位置，选择两个
        return (static_cast<long long>(n-1)*(n-2)/2) % kLimit;
    }

    int part = cnt/3;
    int part_low_pos=s.size(),part_high_pos = 0;
    int part2_low_pos=s.size(),part2_high_pos = 0;
    int t = 0;
    for(int i=0;i<s.size();++i)
    {
        if(s[i] == '1')
        {
            ++t;
        }

        if(t == part)
        {
            part_low_pos = min(part_low_pos,i);
            part_high_pos = max(part_high_pos,i);
        }
        else if(t == part * 2)
        {
            part2_low_pos = min(part2_low_pos,i);
            part2_high_pos = max(part2_high_pos,i);
        }
    }

    printf("%d %d %d %d\n",part_low_pos,part_high_pos,part2_low_pos,part2_high_pos);
    return (static_cast<long long>(part_high_pos-part_low_pos+1) * (part2_high_pos-part2_low_pos+1))%kLimit;
    
}

int main()
{
    string s = "10101"; //4
    s = s = "1001";//0
    // s = "0000"; //3
    // s = "100100010100110";//12

    printf("%d\n",numWays(s));

    return 0;
}