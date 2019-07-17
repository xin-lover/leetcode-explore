//leetcode 649. Dota2 参议院

#include <cstdio>
#include <string>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

string predictPartyVictory(string senate) {
    
    //思路：根据思路，这个disable的权利是顺序性的，即前面的人disable了后面的人，后面的人就没有发言的全力了
    //而选择很简单，就是disble后面跟自己不同阵营的人
    //使用一个状态序列来标志各议员的状态，同时记录两个阵营剩余人数，知道一方先变为0
    //还有一种情况考虑，就是DRD但第一个 D已使用权利把之前的Rdisable了，也就是R现在有disable的权利，R这个时候的选择是diable后面的D而不是前面的

    vector<bool> flags(senate.size(),true);

    while(true)
    {
        queue<int> validVotingR;
        queue<int> validVotingD;

        queue<int> remainR;
        queue<int> remainD;
        for(int i=0;i<senate.size();++i)
        {
            if(!flags[i])
            {
                continue;
            }

            if(senate[i] == 'R')
            {
                if(!validVotingD.empty())
                {
                    validVotingD.pop();
                    flags[i] = false;
                }
                else
                {
                    remainR.push(i);
                    validVotingR.push(i);
                }
            }
            else
            {
                if(!validVotingR.empty())
                {
                    validVotingR.pop();
                    flags[i] = false;
                }
                else
                {
                    remainD.push(i);
                    validVotingD.push(i);
                }
            }
            
        }

        while(!validVotingR.empty() && !remainD.empty())
        {
            int p = remainD.front();
            remainD.pop();
            flags[p] = false;
            printf("1 p:%d\n",p);

            validVotingR.pop();
        }

        while(!validVotingD.empty() && !remainR.empty())
        {
            int p = remainR.front();
            remainR.pop();
            flags[p] = false;
            printf("2 p:%d\n",p);

            validVotingD.pop();
        }

        printf("%d %d\n",remainR.size(),remainD.size());
        if(remainR.size() == 0)
        {
            return "Dire";
        }
        else if(remainD.size() == 0)
        {
            return "Radiant";
        }
        
    }

    return "Dire";

}

int main()
{
    printf("%s\n",predictPartyVictory("RRDRDDRDRRDDDDDRDRDR").c_str());
    return 0;
}