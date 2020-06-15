//1358. 包含所有三种字符的子字符串数目

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

int numberOfSubstrings(string s) {
    //思路：简单遍历，因为是至少一次，所以只要都出现一次，
    //那么后面以这个子字符串为前缀的所有的字符串都符合要求

    //超时
    int sum = 0;
    // static vector<int> flags={0b1,0b10,0b100};
    for(int i=0;i<s.length();++i)
    {
        int flag = 0b111;
        for(int j=i;j<s.length();++j)
        {
            flag &= (~(1 << s[j]-'a'));
            if(flag == 0)
            {
                sum += (s.length()-j);
                break;
            }
        }
    }

    return sum;
}

int numberOfSubstrings2(string s) 
{
    //思路：动态规划
    //还是超时

    //这种算法的一个优化思路就是第二层循环使用二分，从而把复杂度降低至O(nlog(n))
    //二分法是基于如果[i,j]刚好合法，那么[i,j+1】合法,[i,j-1]不合法
    //也就是有单调性

    vector<vector<int>> states(s.length()+1,vector<int>(3,0));
    for(int i=0;i<s.length();++i)
    {
        states[i+1] = states[i];
        int p = s[i]-'a';
        states[i+1][p] = states[i][p] + 1;   
    }

    int sum = 0;
    for(int i=0;i<s.length();++i)
    {
        for(int j=i+2;j<s.length();++j)
        {
            int a = states[j+1][0]-states[i][0];
            int b = states[j+1][1]-states[i][1];
            int c = states[j+1][2]-states[i][2];

            if(a >= 1 && b>=1 && c>=1)
            {
                sum += (s.length()-j);
                break;
            }
        }
    }

    return sum;
}

int numberOfSubstrings3(string s) 
{
    //思路：双层循环不行，也就是O(n^2)的复杂度不行
    //第二循环其实是用来找满足条件的最短子字符串
    //可以考虑浮动窗口,或者说双指针

    vector<int> states(3,0);
    int sum = 0;
    int left = 0;
    for(int i=0;i<s.length();++i)
    {
        states[s[i]-'a']++;
        for(auto a : states)
        {
            printf("%d ",a);
        }
        printf("\n");
        if(states[0]>=1 && states[1]>=1 && states[2] >= 1)
        {
            sum += (s.length()-i);

            for(;left<i;)
            {
                states[s[left++]-'a']--;
                if(states[0]>=1 && states[1]>=1 && states[2] >= 1)
                {
                    sum += (s.length()-i);
                }
                else
                {
                    break;
                }
                
            }
        }
    }

    return sum;
}
int main()
{
    printf("%d\n",numberOfSubstrings3("abcabc"));//10
    printf("%d\n",numberOfSubstrings3("aaacb")); //3
    return 0;

}