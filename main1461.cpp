//1461. 检查一个字符串是否包含所有长度为 K 的二进制子串

#include <cstdio>
#include <vector>
#include <string>
#include <set>
#include <cmath>

using namespace std;

bool hasAllCodes(string s, int k) {
    //思路：一种思路是构建所有长度为k的字符串，然后比对
    //一种是找出s中所有长度为k的子字符串，看看总数量是否大于等于2的k次方
    //方案，用第二种思路

    set<string> st;
    int p = s.size() - k;
    for(int i=0;i<=p;++i)
    {
        st.insert(s.substr(i,k));
    }

    return st.size() >= pow(2,k);
}

bool hasAllCodes2(string s, int k) {
    //思路：一种思路是构建所有长度为k的字符串，然后比对
    //一种是找出s中所有长度为k的子字符串，看看总数量是否大于等于2的k次方
    //方案，用第二种思路
    //直接存字符串超时，优化变为存数字

    if(s.size()<=k)
    {
        return false;
    }
    
    int t = 0;
    for(int i=0;i<k;++i)
    {
        t += (1 << (k-i-1)) * (s[i] - '0');
    }
    set<int> st;
    st.insert(t);
    for(int i=1;i+k-1<s.size();++i)
    {
        t -= (1 << (k-1)) * (s[i-1] - '0');
        t <<=1;
        t += (s[i+k-1] - '0');

        st.insert(t);
    }

    return st.size() >= pow(2,k);
}

int main()
{
    string s = "00110110";
    int k = 2;  //true

    s = "0110", k = 2;  //false;
    s = "0000000001011100", k = 4;  //false;
    s="00110",k=2;    //true;
    // s="0101",k=13;

    printf(hasAllCodes2(s,k) ? "true\n" : "false\n");

    return 0;
}