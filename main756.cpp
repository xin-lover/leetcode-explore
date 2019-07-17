//leetcode 756. 金字塔转换矩阵

#include <cstdio>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

bool fun(string str1,string str2,vector<string>& allowed){
    if(str1.size()==1) return true;
    if(str1.size()-str2.size()>1){
        bool judge=false;
        for(string s:allowed){
            if(str1[str2.size()]==s[0]&&str1[str2.size()+1]==s[1]){
                judge=judge||fun(str1,str2+s[2],allowed);
            }
        }
        return judge;
    }
    else return fun(str2,"",allowed);
}

bool backtrace(unordered_map<string,vector<int>>& um,vector<char>& bottom,vector<char>& nextBottom)
{
    if(nextBottom.size() == bottom.size() - 1)
    {
        if(nextBottom.size() == 1)
        {
            printf("hg\n");
            return true;
        }
        else
        {
            vector<char> newBottom;
            return backtrace(um,nextBottom,newBottom);
        }
    }
    int index = nextBottom.size();
    string p(bottom.begin()+index,bottom.begin()+index+2);
    printf("p:%s\n",p.c_str());
    if(um.find(p) == um.end())
    {
        printf("get\n");
        return false;
    }

    for(int i=0;i<um[p].size();++i)
    {
        if(um[p][i] > 0)
        {
            printf("up:%c\n",'A'+i);
            nextBottom.push_back('A' + i);
            --um[p][i];
            if(backtrace(um,bottom,nextBottom))
            {
                return true;
            }
            ++um[p][i];
            nextBottom.pop_back();
        }
    }

    printf("b\n");
    return false;
}

bool pyramidTransition(string bottom, vector<string>& allowed) {
    if(bottom=="") return true;
        return fun(bottom,"",allowed);
    //思路：根据规则，我们知道金字塔每层的元素总数按1递减，直到塔顶1个
    //所以allowed的数量除bottom元素的总数，否则不够
    //类似前缀树，我们可以使用前两个元素作为标志，但问题是重复元组怎么处理
    //使用map和vector存储数据，然后使用回溯法

    int mnCount=0;
    for(int i=1;i<bottom.size();++i)
    {
        mnCount+=i;
    }

    printf("mncount:%d\n",mnCount);
    if(allowed.size() < mnCount)
    {
        return false;
    }

    unordered_map<string,vector<int>> um;
    for(auto& a : allowed)
    {
        string pre = a.substr(0,2);
        if(um.find(pre) == um.end())
        {
            um[pre] = vector<int>(7,0);
        }
        ++um[pre][a[2]-'A'];
    }

    vector<char> nBottom(bottom.begin(),bottom.end());
    vector<char> nextBottom;
    return backtrace(um,nBottom,nextBottom);
}

int main()
{
    vector<string> v = {"DEF","FFF","ABD","BCE"};
    v = {"ACC","ACB","ABD","DAA","BDC","BDB","DBC","BBD","BBC","DBD","BCC","CDD","ABA","BAB","DDC","CCD","DDA","CCA","DDD"};
    // v = {"AAA", "AAB", "ABA", "ABB", "BAC"};
    printf(pyramidTransition("BCD",v) ? "true\n" : "false\n");
    return 0;
}