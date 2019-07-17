//leetcode 722. 删除注释

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

vector<string> removeComments(vector<string>& source) {
    
    //思路：//的注释简单，复杂性在/**/的注释，
    //每一个注释都会闭合，所以不用判断合法性，而且第一个注释优先，所以我们只要记录/*开始状态即可，
    //同时要处理a/*dfdfd的情况，

    vector<string> res;
    int startBlockRow = -1;
    int startBlockCol = -1;
    string pre;
    for(int i=0;i<source.size();++i)
    {
        bool haveComment = false;
        for(int j=0;j<source[i].size()-1;++j)
        {
            if(startBlockRow == -1 && source[i][j] == '/')
            {
                if(source[i][j+1] == '*')
                {
                    printf("start block:%d %d\n",i,j);
                    startBlockRow = i;
                    startBlockCol = j+1;
                    pre = source[i].substr(0,j);
                    haveComment = true;
                }
                else if(source[i][j+1] == '/')
                {
                    if(j > 0)
                    {
                        res.push_back(source[i].substr(0,j));
                    }
                    
                    haveComment = true;
                    break;
                }
            }       
            else if(startBlockRow != -1 && source[i][j] == '*' && source[i][j+1] == '/')
            {
                if(startBlockRow == i && startBlockCol == j)
                {
                    continue; // 避免/*/的情况
                }
                startBlockRow = -1;
                haveComment = true;
                printf("i:%d j:%d pre:%s +:%s\n",i,j,pre.c_str(),source[i].substr(j+2).c_str());
                printf("sss:%d\n",pre.size() + source[i].size() - j - 2);
                if(pre.size() + source[i].size() - j - 2 > 0)
                {  
                    res.push_back(pre + source[i].substr(j+2)); 
                }
                
                
                break;
            }
        }

        haveComment |= (startBlockRow != -1);
        if(!haveComment)
        {
            printf("push:%d\n",i);
            res.push_back(source[i]);
        }   
    }

    return res;
}

int main()
{
    vector<string> source = {"/*Test program /*/", "int main()", "{ ", "  // variable declaration ", "int a, b, c;", "/* This is a test", "   multiline  ", "   comment for ", "   testing */", "a = b + c;", "}"};
    source = {"a/*comment", "line", "more_comment*/b"};
    source = {"main() { "
"  int a = 1; /* Its comments here "
""
"  "
"  */ return 0;"
"} "};
    auto res = removeComments(source);
    for(auto s : res)
    {
        printf("%s\n",s.c_str());
    }
    return 0;
}