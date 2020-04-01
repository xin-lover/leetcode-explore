//1208. 尽可能使字符串相等

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

int equalSubstring(string s, string t, int maxCost) {
    //思路：这个问题可以转换为一个数组，求子子数组和小于maxcost的最大长度
    //直观暴力的解决O(n^2)的复杂度，可以使用浮动窗口来解决

    vector<int> arr(s.size(),0);
    for(int i=0;i<s.size();++i)
    {
        arr[i] = abs(s[i]-t[i]);
    }

    int sum = 0;
    int left=0,right=0;
    int res = 0;
    while(right < arr.size())
    {
        if(sum <= maxCost)
        {
            sum += arr[right];
            ++right;

            if(sum <= maxCost)
            {
                res = max(right-left,res);
            }
        }
        else
        {
            sum -= arr[left];
            ++left;
        }
        

    }

    return res;
}

int main()
{
    string s = "abcd", t = "bcdf";
    int cost = 3; //3

    // s = "abcd", t = "cdef";
    // cost = 3;   //1

    // s = "abcd", t = "acde";
    // cost = 0;   //1

    printf("%d\n",equalSubstring(s,t,cost));
    return 0;
}