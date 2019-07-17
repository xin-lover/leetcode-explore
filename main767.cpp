//leetcode 767. 重构字符串

#include <cstdio>
#include <string>
#include <vector>

using namespace std;

string reorganizeString(string S) {
    
    //思路：一种思路是记录各字符的数量，然后间隔重新排列
    //一种就是回溯

    if(S.size() <= 1)
    {
        return S;
    }
    vector<int> cCounts(26,0);
    for(int i=0;i<S.size();++i)
    {
        ++cCounts[S[i]-'a'];
    }

    string res(S.size(),'a');
    printf("res:%s\n",res.c_str());
    int cur = 0;
    while(true)
    {
        int mxi = cCounts[0] > cCounts[1] ? 0 : 1;
        int smxi = cCounts[0] > cCounts[1] ? 1 : 0;
        for(int i=2;i<cCounts.size();++i)
        {
            if(cCounts[i] > cCounts[mxi])
            {
                smxi = mxi;
                mxi = i;
            }
            else if(cCounts[i] > cCounts[smxi])
            {
                smxi=i;
            }
        }

        printf("%c %c\n",mxi+'a',smxi+'a');
        if(cCounts[mxi] > 0 && cCounts[smxi] == 0)
        {
            if(cCounts[mxi] == 1 && cur>0 && mxi+'a' != res[cur-1])
            {
                res[cur] = mxi+'a';
                return res;
            }
            return "";
        }

        if(cCounts[mxi] == 0)
        {
            break;
        }

        for(int i=0;i<cCounts[smxi];++i)
        {
            res[cur]=(mxi+'a');
            res[cur+1] =smxi+'a';
            cur+=2;
        }

        cCounts[mxi]-=cCounts[smxi];
        cCounts[smxi] = 0;
    }

    return res;
}

int main()
{
    printf("w:%s\n",reorganizeString("aab").c_str());
    printf("w:%s\n",reorganizeString("daaaabc").c_str());
    printf("w:%s\n",reorganizeString("a").c_str());
    printf("w:%s\n",reorganizeString("ab").c_str());
    return 0;
}