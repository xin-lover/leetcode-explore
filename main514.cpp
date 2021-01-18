//514. 自由之路

#include <cstdio>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;

void backtrace(unordered_map<char,vector<int>>& um,int ringSize, const string& key,int index,int lastPos,int curStep,int& res)
{
    if(index >= key.size())
    {
        res = min(curStep,res);
        return;
    }

    char c = key[index];
    for(int i=0;i<um[c].size();++i)
    {
        int step = abs(um[c][i]-lastPos);
        backtrace(um,ringSize,key,index+1,um[c][i], curStep + step +1,res);
        backtrace(um,ringSize,key,index+1,um[c][i], curStep + ringSize - step +1,res);
    }
}
int findRotateSteps(string ring, string key) {
    //思路：左旋和右旋中选，所以需要知道当前字符到目标字符两种选择下的步数
    //这个使用map存储字符及其位置即可，但这个题目加了一个复杂性，就是可以有相同字符
    //那么也就意味着每个字符可能有多个位置，除了在这些位置中找最优解外
    //我们还需要考虑这样的:acd，其中c的位置有两个，那么使用a到c的最短距离会在最优解中？
    //也就是说选择a->c1 < a->c2是否会导出a->c1 + c1->d < a->c2+c2->d
    //这个显然不行，这里分几种情况，（b-a）表示a到b的顺时针距离
    //那么acd的可能有:(c-a)+(d-c),12-(c-a)+(d-c),12-(c-a)+12-(d-c),(c-a)+12-(d-c)
    //那么可能的结果有:d-a,12+a+d-2c,24-(d-a),12+2c-a-d
    //取a=0，得d,24-d,12+d-2c,12+2c-d
    //这里d<12，所以min(d,24-d)=d；
    //如果对于12+d-2c,12+2c-d,取决于d和2c假设d>2c，则min(12+d-2c,12+2c-d)=12+2c-d
    // 12+2c-d-d,因为12>d>2c，
    //先回溯试试,回溯超时,继续上面的思路,这个有点最短路径的意思，区别在于这个题的每个点有多个选择
    
    unordered_map<char,vector<int>> um;
    for(int i=0;i<ring.size();++i)
    {
        um[ring[i]].push_back(i);
    }

    int res = INT_MAX;
    backtrace(um,ring.size(),key,0,0,0,res);
    return res;
}

int findRotateSteps2(string ring, string key) {
    //思路：记录从开始位置到达每个位置需要的步数，用bfs

    unordered_map<char,vector<int>> um;
    for(int i=0;i<ring.size();++i)
    {
        um[ring[i]].push_back(i);
    }

    int ringSize = ring.size();
    unordered_map<int,int> stepsFromStart; //到当前字符的所有路径的长度
    stepsFromStart[0] = 0;
    for(int i=0;i<key.size();++i)
    {
        char c = key[i];
        unordered_map<int,int> tmp;
        for(int j=0;j<um[c].size();++j)
        {
            int pos = um[c][j];
            if(tmp.find(pos) == tmp.end())
            {
                tmp.insert({pos,INT_MAX});
            }
            for(auto it=stepsFromStart.begin();it!=stepsFromStart.end();++it)
            {
                tmp[pos] = min(tmp[pos],abs(pos - it->first) + it->second + 1);
                tmp[pos] = min(tmp[pos],ringSize - abs(pos - it->first) + it->second +1);
            }
        }

        swap(stepsFromStart,tmp);
    }

    int res = INT_MAX;
    for(auto it=stepsFromStart.begin();it!=stepsFromStart.end();++it)
    {
        res = min(it->second,res);
    }

    return res;
}

int main()
{
    string  ring = "godding", key = "gd"; //4
    // ring = "godding", key="godding"; //13
    printf("%d\n",findRotateSteps2(ring,key));

    return 0;
}