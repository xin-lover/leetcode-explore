//1433. 检查一个字符串是否可以打破另一个字符串

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

bool checkIfCanBreak(string s1, string s2) {
    //思路：s1和s2的排列，根据田忌赛马的情况，让s1和s2先排序再比较试试

    if(s1.empty())
    {
        return false;
    }

    sort(s1.begin(),s1.end());
    sort(s2.begin(),s2.end());
    printf("%s\n%s\n",s1.c_str(),s2.c_str());
    int i = 0;
    while(i < s1.size() && s1[i] == s2[i])
    {
        ++i;
    }
    bool flag = (s1[i] > s2[i]);
    for(;i<s1.size();++i)
    {
        if(s1[i] == s2[i])
        {
            continue;
        }
        if((flag ^ (s1[i] > s2[i])))
        {
            return false;   
        }
    }

    return true;
}

bool checkIfCanBreak2(string s1, string s2) {
    //思路：排序性能低，因为只有26个字母，我们可以考虑统计字符数
    //一方低位字符占多，一方高位字符占多

    vector<int> count1(26,0),count2(26,0);

    for(int i=0;i<s1.size();++i)
    {
        count1[s1[i]-'a']++;
    }

    for(int i=0;i<s2.size();++i)
    {
        count2[s2[i]-'a']++;
    }

    //模拟排列，不够的向前借位，如果一直是向一个方向借位，则返回true
    bool flag1=(count1[0] >= count2[0]),flag2=(count1[0] <= count2[0]);
    for(int i=0;i<count1.size();++i)
    {
        count1[i] = count1[i-1] + count1[i];   
        count2[i] = count2[i-1] + count2[i];

        flag1 = flag1 && (count1[i] >= count2[i]);
        flag2 = flag2 && (count1[i] <= count2[i]);
    }

    return flag1 || flag2;

}

int main()
{
    string s1 = "leetcodee", s2 = "interview"; //true;
    s1 = "abc", s2 = "xya"; //true
    s1 = "abe", s2 = "acd"; //false;
    // s1 = "abc",s2="xya";
    // s1="pazunsabwlseseeiimsmftchpafqkquovuxhhkpvphw", s2="nkrtxuiuhbcyqulfqyzgjjwjrlfwwxotcdtqsmfeing"; //true
    // s1="yopumzgd", s2="pamntyya";//true
    s1="xyzbpvmwulmqfrxbqcziudixceytvvwcohmznmfkoetpgdntrndvjihmxragqosaauthigfjergijsyivo",s2= "zzfrlpndygsmgjzdzadsxarjvyxuecqlszjnqvlyqkadowoljrmkzxvspdummgraiutxxxqgotqnxwjwfo";

    sort(s1.begin(),s1.end());
    sort(s2.begin(),s2.end());
    printf("%s\n%s\n",s1.c_str(),s2.c_str());
    printf(checkIfCanBreak2(s1,s2) ? "true\n" : "false\n");

    return 0;
}