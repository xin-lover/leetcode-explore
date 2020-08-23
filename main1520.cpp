//1520. 最多的不重叠子字符串

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

void backtrace(vector<pair<int,int>>& positions,int index,vector<pair<int,int>>& curSelect,vector<pair<int,int>>& res)
{
    if(index >= positions.size())
    {
        return;
    }

    if(curSelect.size() > res.size())
    {
        res = curSelect;
    }
    else if(curSelect.size() == res.size())
    {
        auto getLen = [](vector<pair<int,int>> container){
            int len = 0;
            for(auto a : container)
            {
                len += a.second-a.first+1;
            }

            return len;
        };
        
        if(getLen(curSelect) < getLen(res))
        {
            res = curSelect;
        }
    }

    //选择要,需要判断是否重叠
    bool overlay = false;
    for(int i=0;i<curSelect.size();++i)
    {
        if((positions[index].first>=curSelect[i].first && positions[index].first <=curSelect[i].second)
        || (positions[index].second >= curSelect[i].first && positions[index].second <= curSelect[i].second))
        {
            overlay = true;
            break;       
        }
    }
    if(!overlay)
    {
        curSelect.push_back(positions[index]);
        backtrace(positions,index+1,curSelect,res);
        curSelect.pop_back();
    }
    backtrace(positions,index+1,curSelect,res);
}

void backtrace2(vector<vector<int>>& positions,int index,vector<vector<int>>& curSelect,int curLen,vector<vector<int>>& res,int& resLen)
{
    if(index >= positions.size() || positions[index][0] > positions[index][1])
    {
        return;
    }

    //用二分法找到下一个可用的区间
    int left=index+1,right=positions.size()-1;
    while(left < right)
    {
        int mid = left + (right-left)/2;
        if(positions[mid][0] > positions[index][1])
        {
            right = mid;
        }
        else
        {
            left= mid+1;
        }
    }

    //选择要
    curSelect.push_back(positions[index]);
    curLen += positions[index][1]-positions[index][0]+1;
    if(curSelect.size() > res.size() || (curSelect.size() == res.size() && curLen < resLen))
    {
        res = curSelect;
        resLen = curLen;
    }

    if(positions[left][0] > positions[index][1])
    {
        backtrace2(positions,left,curSelect,curLen,res,resLen);
    }
    
    curLen -= positions[index][1]-positions[index][0]+1;
    curSelect.pop_back();
    //选择不要
    backtrace2(positions,index+1,curSelect,curLen,res,resLen);
}

vector<string> maxNumOfSubstrings(string s) {
    //所有相同字符都需要在同一个字符串中，而且子字符串不能重叠
    //所以我们记录字符最开始和最后出现的位置，
    //那接下来遍历，对于每一个字符，只有两个选择，要或者不要
    //还有26个字符，26*26种可能。。。

    //直接回溯，需要解决的问题
    //1.如何快速判断重叠；
    //2.如何快速求出子字符串的长度总和
    //重叠可以使用二分解决

    //这个算法不对，没考虑中间的元素，

    
    int n = s.size();
    vector<vector<int>> positions(26,{n,0});

    for(int i=0,j=s.size()-1;i<s.size();++i,--j)
    {
        positions[s[i]-'a'][0] = min(positions[s[i]-'a'][0],i);
        positions[s[j]-'a'][1] = max(positions[s[j]-'a'][1],j);
    }

    //排序
    sort(positions.begin(),positions.end(),[](vector<int>& a,vector<int>& b)
    {
        return a[0] < b[0];
    });

    for(auto a : positions)
    {
        printf("%d %d\n",a[0],a[1]);
    }

    vector<vector<int>> res;
    for(int i=1;i<positions.size()-1;++i)
    {
        if(positions[i+1][0] > positions[i+1][1])
        {
            break;
        }
        if(positions[i+1][0] > positions[i][1] && positions[i-1][1] < positions[i][0])
        {
            res.push_back(positions[i]);
        }
    }

    printf("%d\n",res.size());

    if(res.empty())
    {
        return {s};
    }

    vector<string> resStr;
    for(auto a : res)
    {
        resStr.push_back(s.substr(a[0],a[1]-a[0]+1));
    }

    return resStr;

}

void backtrace3(vector<vector<int>>& positions, int index,vector<vector<int>> cur,int curLen,vector<vector<int>>& res,int& resLen)
{
    //两种选择，要还是不要
    if(index >= positions.size())
    {
        return;
    }

    if(positions[index][0] <= positions[index][1] && (cur.empty() || positions[index][0] > cur.back()[1]))
    {
        //加入
        cur.push_back(positions[index]);
        curLen += positions[index][1]-positions[index][0]+1;
        if(cur.size() > res.size() || (cur.size() == res.size() && curLen < resLen))
        {
            res = cur;
            resLen = curLen;
        }
        backtrace3(positions,index,cur,curLen,res,resLen);
        cur.pop_back();
        curLen -= positions[index][1]-positions[index][0]+1;
    }


    //不加入
    backtrace3(positions,index+1,cur,curLen,res,resLen);

}

vector<string> maxNumOfSubstrings2(string s) {
    //思路：26个字符，我们记录其最后出现的位置
    //遍历时，如果要包含当前字符，那么我们直接跳到它最后出现的位置，然后继续
    
    vector<vector<int>> positions(26,vector<int>({INT_MAX,0}));

    for(int i=0,j=s.size()-1;i<s.size();++i,--j)
    {
        positions[s[i]-'a'][1] = i;
        positions[s[j]-'a'][0] = j;
    }

    //计算包含该字符时且符合题意要求的最后一个位置
    for(int i=0;i<26;++i)
    {
        int start = positions[i][0],end= positions[i][1];
        for(int j=start;j<=end;++j)
        {
            int p = s[j]-'a';
            if(positions[p][0] < start)
            {
                start = positions[p][0];
                j = start;
            }
            
            if(positions[p][1] > end)
            {
                end = positions[p][1];
            }
        }

        positions[i] = {start,end};
    }

    sort(positions.begin(),positions.end(),[](vector<int>& a,vector<int>& b)
    {
        if(a[1]==b[1])
        {
            return a[0] < b[0];
        }
        return a[1] < b[1];
    });

    for(auto a : positions)
    {
        printf("%d %d\n",a[0],a[1]);
    }

    //回溯性能太低了，不是26*26，而是最大可能是2^26
    // vector<vector<int>> cur,res;
    // int resLen = INT_MAX;
    // backtrace3(positions,0,cur,0,res,resLen);

    // vector<string> resStr;
    // for(auto a : res)
    // {
    //     resStr.push_back(s.substr(a[0],a[1]-a[0]+1));
    // }

    // return resStr;

    //贪心
    vector<string> res;
    int end = -1;
    for(auto a : positions)
    {
        if(a[0] > a[1])
        {
            continue;
        }
        if(res.empty() || a[0] > end)
        {
            end = a[1];
            res.emplace_back(s.substr(a[0],a[1]-a[0]+1));
        }   
    }

    return res;
}

int main()
{
    string s = "adefaddaccc";   //["e","f","ccc"]
//   // s = "abbaccd";  //["d","bb","cc"]
//     s = "abab"; //abab
    s = "ababcc";   //abab cc
//     s = "ababa";    //ababa
    // s = "abcdefghijklmnopqrstuvwxyz"; //a b c……  
    for(auto a : maxNumOfSubstrings2(s))
    {
        printf("%s ",a.c_str());
    }
    printf("\n");

    return 0;
}