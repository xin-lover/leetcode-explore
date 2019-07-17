//leetcode 636. 函数的独占时间

#include <vector>
#include <string>
#include <stack>

using namespace std;

vector<int> exclusiveTime(int n, vector<string>& logs) {
    
    //思路，日志是按时间排序的，解析函数序号和时间，直接计算
    //需要维护一个栈

    vector<int> times(n,0);
    
    stack<int> funcs;
    int curID = -1;
    int curStart = 0;
    for(int i=0;i<logs.size();++i)
    {
        string c = logs[i];
        
        int start = 0;
        vector<string> parts;
        for(int j=0;j<=c.size();++j)
        {
            if(c[j] == ':' || c[j] == '\0')
            {
                parts.push_back(c.substr(start,j-start));
                start = j+1;
            }
        }

        int id = stoi(parts[0]);
        int time = stoi(parts[2]);

        if(curID == -1)
        {
            curID = id;
            curStart = time;
        }
        else
        {
            if(parts[1] == "start")
            {
                times[curID] += time-curStart;
                funcs.push(curID);
                curID = id;
                curStart = time;
            }
            else
            {
                times[curID] += time-curStart + 1;
                if(!funcs.empty())
                {
                    curID = funcs.top();
                    funcs.pop();
                    curStart = time+1;
                }
                else
                {
                    curID = -1;
                }
            }
            
        }
        
    }

    return times;
}

int main()
{
    vector<string> v = {"0:start:0",
 "1:start:2",
 "1:end:5",
 "0:end:6"};

    auto res = exclusiveTime(2,v);
    for(auto a : res)
    {
        printf("%d ",a);
    }
    printf("\n");
    return 0;
}