//leetcode 816. 模糊坐标

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

bool validSplit(const string& S,int left,int right, int point)
{
    //第一位为0
    if(point > left && S[left] == '0')
    {
        return false;
    }

    //小数点后的最后一位为0
    if(point < right && S[right] == '0')
    {
        return false;
    }

    return true;
}

vector<string> ambiguousCoordinates(string S) {
    //思路：首先S需要分为两部分，然后每一部分都可以添加小数点，其实也是分为两部分
    //注意0的情况
    //主要有几种情况：
    //1.分组时每一部分开头最多一个0
    //2.结尾可以有多个0，但小数点不能添加到0之前，也就是不能出现.0的情况

    //策略：先分组，判断分组是否可行，如果可行，则添加小数点

    if(S.size() < 4)
    {
        return {};
    }

    vector<string> res;

    int c = S.size()-3; //c种分法
    for(int i=0;i<c;++i)
    {
        int start = 1;
        int end = start+i;
        vector<string> leftValids;
        for(int j=start;j<=end;++j)
        {
            if(validSplit(S,start,end,j))
            {
                string t;
                t.append(S,start,j-start+1);
                if(j < end)
                {
                    t.append(".");
                    t.append(S,j+1,end-j);
                }

                leftValids.push_back(t);
            }
        }

        start = end + 1;
        end = S.size()-2;
        vector<string> validRights;
        for(int j=start;j<=end;++j)
        {
            if(validSplit(S,start,end,j))
            {
                string t;
                t.append(S,start,j-start+1);
                if(j < end)
                {
                    t.append(".");
                    t.append(S,j+1,end-j);
                }

                validRights.push_back(t);
            }
        }

        for(auto& a : leftValids)
        {
            for(auto& b : validRights)
            {
                string t;
                t.append("(");
                t.append(a);
                t.append(", ");
                t.append(b);
                t.append(")");

                res.push_back(t);
            }
        }
    }

    return res;
}

int main()
{
    vector<string> res = ambiguousCoordinates("(123)");
    res = ambiguousCoordinates("(100)");
    res = ambiguousCoordinates("(00011)");
    res = ambiguousCoordinates("(0123)");
    for(auto a : res)
    {
        printf("%s\n",a.c_str());
    }

    printf("\n");
    return 0;
}