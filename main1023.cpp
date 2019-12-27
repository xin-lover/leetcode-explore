//1023. 驼峰式匹配

#include <cstdio>
#include <string>
#include <vector>

using namespace std;

vector<bool> camelMatch(vector<string>& queries, string pattern) {
    //思路：因为只能插入小写字母，所以遍历的时候如果遇到大写字母且不在pattern中，则返回false
    //如果遇到小写字母，如果预期的pattern的字符不匹配，可以略过，否则更新预期的字符


    vector<bool> res(queries.size(),false);
    for(int i=0;i<queries.size();++i)
    {
        if(queries[i].size() >= pattern.size())
        {
            int k =0;   //表示当前要匹配的pattern中的字符
            for(int j=0;j<queries[i].size();++j)
            {
                if(k >= pattern.size())
                {
                    if(queries[i][j] < 'a')
                    {
                        k=0;
                        break;
                    }
                }
                else if(queries[i][j] != pattern[k])
                {
                    if(queries[i][j] < 'a')
                    {
                        break;
                    }
                }
                else
                {
                    // printf("%s j:%d\n",queries[i].c_str(),j);
                    ++k;
                }
                
            }     

            // printf("h: %s k:%d\n",queries[i].c_str(),k);
            if(k >= pattern.size())
            {
                res[i]=true;
            }
        }

    }

    return res;
}

vector<bool> camelMatch2(vector<string>& queries, string pattern) 

}

int main()
{
    vector<string> queries = {"FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"};
    string pattern = "FB";  //true,false,true,true,false

    queries = {"FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"};
    pattern = "FoBa"; //true,false,true,false,false

    queries = {"FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"};
    pattern = "FoBaT";//false,true,false,false,false

    vector<bool> res = camelMatch(queries,pattern);
    for(auto a : res)
    {
        printf(a ? "true " : "false ");
    }
    printf("\n");

    return 0;

}