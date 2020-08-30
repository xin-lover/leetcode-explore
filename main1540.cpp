//1540. K 次操作转变字符串

#include <cstdio>
#include <vector>
#include <map>
#include <string>

using namespace std;

bool canConvertString(string s, string t, int k) {
    //思路：k次操作，除开0，我们可以k种操作
    //所以我们记录s和t的不同，看看k种排序是否满足
    //因为字符表成环，对于k需要求余

    if(s.size() != t.size())
    {
        return false;
    }

    int p = k / 26;
    int q = k % 26;
    vector<int> steps(26,p);
    steps[0] = s.size();
    for(int i=1;i<=q;++i)
    {
        steps[i]++;
    }
    for(auto a : steps)
    {
        printf("%d ",a);
    }

    printf("\n");

    for(int i=0;i<s.size();++i)
    {
        int dif = (t[i] - s[i] + 26) % 26;
        printf("i:%d dif:%d\n",i,dif);
        if(steps[dif] <= 0)
        {
            return false;
        }

        steps[dif]--;
    }

    return true;
}

int main()
{
    string s = "input", t = "ouput";
    int k = 9;  //true

    s = "abc", t = "bcd", k = 10;   //false
    // s = "aab", t = "bbb", k = 27;   //true

    printf(canConvertString(s,t,k) ? "true\n" : "false\n");

    return 0;
}