//1419. 数青蛙

#include <cstdio>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

int minNumberOfFrogs(string croakOfFrogs) {
    //思路：这个使用贪心策略，如果当前的字符可以用一只青蛙发出，则用一只
    //不行就加一只
    //方案：使用一个数组存储当前青蛙发出的下一个字符，如果最后数组中都是完整的字符串，返回数组长度
    //这个方案就是每次都需要遍历这个数组去找合适的青蛙

    if(croakOfFrogs.empty())
    {
        return 0;
    }
    vector<char> chs = {'c','r','o','a','k'};
    vector<int> frogs;
    frogs.push_back(0);
    for(int i=0;i<croakOfFrogs.size();++i)
    {
        bool find = false;
                printf("%d %c\n",i,croakOfFrogs[i]);
        for(auto& a  : frogs)
        {
            if(chs[a] == croakOfFrogs[i])
            {
                printf("find\n");
                ++a;
                if(a >= chs.size())
                {
                    a = 0;
                }
                find = true;
                break;
            }
        }

        if(!find)
        {
            if(croakOfFrogs[i] == chs[0])
            {
                frogs.push_back(1);
            }
            else
            {
                return -1;
            }
        }
    }

    for(auto a : frogs)
    {
        if(a != 0)
        {
            printf("get 2\n");
            return -1;
        }
    }

    return frogs.size();
}

int minNumberOfFrogs2(string croakOfFrogs) {
    //思路：优化，上面的数组可能太大了
    //其实当前字符只有5种可能，所以我们改为使用一个存储发出每一个字符的青蛙的数量即可

    if(croakOfFrogs.empty())
    {
        return 0;
    }
    // vector<char> chs = {'c','r','o','a','k'};
    unordered_map<char,int> char_pos;
    char_pos['c'] = 0;
    char_pos['r'] = 1;
    char_pos['o'] = 2;
    char_pos['a'] = 3;
    char_pos['k'] = 4;
    vector<int> frogs(char_pos.size(),0);
    frogs[0] = 1;
    for(auto a : croakOfFrogs)
    {
        int pos = char_pos[a];
        if(frogs[pos] > 0)
        {
            --frogs[pos];
            ++pos;
            pos = pos >= char_pos.size() ? 0 : pos;
            ++frogs[pos];
        }
        else
        {
            if(a == 'c')
            {
                ++frogs[char_pos[a]+1];
            }
            else
            {
                return -1;
            }
        }
    }

    for(int i=1;i<frogs.size();++i)
    {
        if(frogs[i] != 0)
        {
            return -1;
        }
    }

    return frogs[0];
}


int main()
{
    printf("%d\n",minNumberOfFrogs2("croakcroak"));  //1
    printf("%d\n",minNumberOfFrogs2("crcoakroak"));  //2
    printf("%d\n",minNumberOfFrogs2("croakcroa"));  //-1
    printf("%d\n",minNumberOfFrogs2("croakcrook"));  //-1

    return 0;
}