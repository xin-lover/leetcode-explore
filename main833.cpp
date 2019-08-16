//leetcode 833. 字符串中的查找与替换

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

string findReplaceString(string S, vector<int>& indexes, vector<string>& sources, vector<string>& targets) {
    //思路：这个的难点在于判断是用原来字符串判断是否替换
    //策略：因为替换操作不会重叠，所以不同担心先替换后替换的问题
    //先遍历S，看看当前符合那个可替换的字符串，用替换字符串添加到新字符串，不符合则添加到新字符串中

    string res;
    for(int i=0;i<S.size();++i)
    {
        bool replaced = false;
        for(int j=0;j<indexes.size();++j)
        {
            if(i == indexes[j])
            {
                bool same = true;
                if(i+sources[j].size() > S.size())
                {
                    same = false;
                }
                else
                {
                    for(int k=0;k<sources[j].size();++k)
                    {
                        if(S[i+k] != sources[j][k])
                        {
                            same =false;
                            break;
                        }
                    }
                }

                if(same)
                {
                    res.append(targets[j]);
                    i+=sources[j].size()-1;
                    replaced = true;
                }
            }
        }

        if(!replaced)
        {
            res.append(1,S[i]);
        }   
    }

    return res;
}


string findReplaceString2(string S, vector<int>& indexes, vector<string>& sources, vector<string>& targets) {

    //思路：必须位置匹配，那就直接遍历要替换的字符串，记录可替换的字符串，再替换即可

    vector<int> replacable(S.size(),-1);
    for(int i=0;i<indexes.size();++i)
    {
        bool same = true;
        if(indexes[i] + sources[i].size() > S.size())
        {
            same = false;
        }
        else
        {
            for(int j=0;j<sources[i].size();++j)
            {
                if(S[indexes[i] + j] != sources[i][j])
                {
                    same = false;
                    break;
                }
            }
        }
        
        if(same)
        {
            replacable[indexes[i]] = i;
        }
    }

    string res;
    for(int i=0;i<S.size();++i)
    {
        if(replacable[i] > -1)
        {
            res.append(targets[replacable[i]]);
            i+= sources[replacable[i]].size()-1;
        }
        else
        {
            res.append(1,S[i]);
        }
        
    }

    return res;
}

int main()
{
    // string S = "abcd";
    // vector<int> indexes = {0,2};
    // vector<string> sources = {"a","cd"};
    // vector<string> targets = {"eee","ffff"};
    // printf("%s\n",findReplaceString(S,indexes,sources,targets).c_str());

    string S = "abcd";
    vector<int> indexes = {0,2};
    vector<string> sources = {"ab","ec"};
    vector<string> targets = {"eee","ffff"};

    printf("%s\n",findReplaceString2(S,indexes,sources,targets).c_str());
//     "jjievdtjfb"
// [4,6,1]
// ["md","tjgb","jf"]
// ["foe","oov","e"]

// "jjievdteb"
// "jjievdtjfb"
    return 0;
}