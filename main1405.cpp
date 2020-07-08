//1405. 最长快乐字符串

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

string longestDiverseString(int a, int b, int c) {
    //思路：每轮放置字符时优先先放剩余次数最多的, 如果上次放的2个字符和剩余个数最多的字符相同，则放置次多的字符

    vector<pair<char,int>> charInfo = {{'a',a},{'b',b},{'c',c}};

    string res;
    while(true)
    {
        sort(charInfo.begin(),charInfo.end(),[](pair<char,int>& a,pair<char,int>& b)
        {
            return a.second > b.second;
        });

        int index = 0;
        if(res.length() >= 2 && res[res.length()-1] == res[res.length()-2] && res.back() == charInfo[0].first)
        {
            index = 1;
        }

        if(charInfo[index].second == 0)
        {
            break;
        }
        res.append(1,charInfo[index].first);
        --charInfo[index].second;
    }

    return res;
}

//另一种思路：
// 首先拿出 c 个 'a', 'b', 'c' 进行拼接。
// 再拿出 b-c 个 'a'，'b' 进行拼接。此时所有 'b'，'c' 都已拼接到答案中，仅剩 a-b 个 'a' 未拼接。
// 然后可以通过暴力枚举将尽可能多的 'a' 插入到答案中。

int main()
{
    printf("%s\n",longestDiverseString(1,1,7).c_str()); //ccaccbcc
    printf("%s\n",longestDiverseString(2,2,1).c_str()); //aabbc

    return 0;
}