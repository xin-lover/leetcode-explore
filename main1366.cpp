//1366. 通过投票对团队排名

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

string rankTeams(vector<string>& votes) {
    //思路：使用排序，重点是把数据结构给出
    //可以统计每个对各名次的票数，组合为一个字符串排序；
    //因为最后还要考虑字典序，所以把队伍名字也放到这个字符串后面

    if(votes.empty())
    {
        return string();
    }
    int n = votes[0].size();
    //最多26个字母
    vector<vector<int>> states(26,vector<int>(n+1,0));
    for(int i=0;i<states.size();++i)
    {
        states[i].back() = 25-i;
    }

    for(int i=0;i<votes.size();++i)
    {
        for(int j=0;j<votes[i].size();++j)
        {
            char team = votes[i][j];
            ++states[team-'A'][j];
        }
    }

    sort(states.begin(),states.end(),[](vector<int>& a,vector<int>& b)
    {
        for(int i=0;i<a.size();++i)
        {
            if(a[i] == b[i])
            {
                continue;   
            }

            return a[i] > b[i];
        }

        return false;
    });

    for(auto a : states)
    {
        for(auto b : a)
        {
            printf("%d ",b);
        }
        printf("\n");
    }

    // for(auto a : states)
    // {
    //     printf("%s\n",a.c_str());
    // }

    string res(n,'A');
    for(int i=0;i<n;++i)
    {
        res[i] = 'A' + 25 - states[i].back();
    }

    return res;
}

int main()
{
    vector<string> votes = {"ABC","ACB","ABC","ACB","ACB"}; //"ACB"
    votes = {"WXYZ","XYZW"};    //"XWYZ"
    // votes = {"ZMNAGUEDSJYLBOPHRQICWFXTVK"};
    votes = {"BCA","CAB","CBA","ABC","ACB","BAC"};  //"ABC"
    // votes = {"YEQG","QYGE","QYGE","GEQY","QYEG","EYGQ","GYQE","EQGY","QYGE","GQYE","YGEQ","GQYE","EGQY","YEGQ","GEQY","YGEQ","EYQG","EGYQ","GYQE","GEYQ","EGYQ","YEGQ","YEQG","QGEY","QYEG","YQGE","GQYE","EQYG","EYGQ","EQGY","QGYE","QYGE","GQEY","YGEQ","QEGY","YQEG","GYQE","QYGE","QYGE","EYGQ","EGYQ","QEGY","YEGQ","GQEY","GYEQ","EQYG","QGYE","QEGY","YQGE","QEYG","GQEY","YGEQ","GQYE","YEQG","QGEY"};
    printf("%s\n",rankTeams(votes).c_str());
    return 0;
}