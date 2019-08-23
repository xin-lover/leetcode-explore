//leetcode 838. 推多米诺

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

string pushDominoes(string dominoes) {
    //思路：下落是有时间的，所以状态传递有先后顺序   
    //可以遍历每一个状态，记录它对其它牌的影响及时间，每个牌只接受最早的影响

    string res(dominoes.size(),'.');
    vector<int> steps(dominoes.size(),dominoes.size());
    for(int i=0;i<dominoes.size();++i)
    {
        if(dominoes[i] == 'L')
        {
            for(int j=i;j>=0;--j)
            {
                if(steps[j]>i-j)
                {
                    steps[j] = i-j;
                    res[j] = 'L';
                }
                else if(steps[j] == i-j)
                {
                    res[j] = '.';
                }
                else
                {
                    break;
                }
            }
        }
        else if(dominoes[i] == 'R')
        {
            for(int j=i;j<dominoes.size()&&dominoes[j] != 'L';++j)
            {
                if(steps[j]>j-i)
                {
                    steps[j] = j-i;
                    res[j] = 'R';
                }
                else if(steps[j] == j-i)
                {
                    res[j] = '.';
                }
                else
                {
                    break;
                }
                
            }
        }
        
    }

    return res;

}


int main()
{
    printf("%s\n",pushDominoes("RR.L").c_str());//"RR.L"
    printf("%s\n",pushDominoes(".L.R...LR..L..").c_str()); //"LL.RR.LLRRLL.."
    return 0;
}