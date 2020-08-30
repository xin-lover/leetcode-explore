//1529. 灯泡开关 IV

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

int minFlips(string target) {
    //思路：只能翻转某个位置之后的，所以我们优先翻转左侧的

    int flip = 0;
    char cur = '0'; //当前字符

    for(int i=0;i<target.size();++i)
    {
        if(target[i] != cur)
        {
            cur = '0' + '1'-cur;
            ++flip;
        }
    }

    return flip;
}

int main()
{
    printf("%d\n",minFlips("10111"));
    printf("%d\n",minFlips("101"));
    printf("%d\n",minFlips("001011101"));
    return 0;
}