//691. 贴纸拼词

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <climits>
#include <queue>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;

void backtrace(vector<vector<int>>& stickerWords,vector<int>& targetWords,int index,int stickerNum,int& minStcikerNum)
{
    if(index == stickerWords.size())
    {
        for(int i=0;i<targetWords.size();++i)
        {
            if(targetWords[i] > 0)
            {
                return;
            }
        }

        minStcikerNum = min(minStcikerNum,stickerNum);
        return;
    }


    int mxNum = 0;
    for(int i=0;i<targetWords.size();++i)
    {
        if(stickerWords[index][i] == 0)
        {
            continue;
        }

        mxNum = max(mxNum, targetWords[i] / stickerWords[index][i] + (targetWords[i] % stickerWords[index][i] == 0 ? 0 : 1));
    }


    backtrace(stickerWords,targetWords,index+1,stickerNum,minStcikerNum);
    for(int i=0;i<mxNum;++i)
    {
        for(int j=0;j<targetWords.size();++j)
        {
            targetWords[j] -= stickerWords[index][j];
        }
        backtrace(stickerWords,targetWords,index+1,stickerNum+i+1,minStcikerNum);
    }

    for(int i=0;i<targetWords.size();++i)
    {
        targetWords[i] += stickerWords[index][i]*mxNum;
    }
}

int minStickers(vector<string>& stickers, string target) {
    //思路：首先肯定是统计字母数量，
    //没有思路，先回溯
    //官方题解也是穷举，然后优化，优化的点：1.首先判断是否可以拼出target，不然直接返回-1
    //2.剪枝，对于某个贴纸，可以先判断是否对target有用，如果一个字符都没用，那么不必考虑它。。。

    vector<vector<int>> stickerWords(stickers.size(),vector<int>(26,0));
    for(int i=0;i<stickers.size();++i)
    {
        for(int j=0;j<stickers[i].size();++j)
        {
            stickerWords[i][stickers[i][j]-'a']++;
        }
    }

    vector<int> targetWords(26,0);
    for(int i=0;i<target.size();++i)
    {
        targetWords[target[i]-'a']++;
    }

    int res = INT_MAX;
    backtrace(stickerWords,targetWords,0,0,res);

    return res == INT_MAX ? -1 : res;
}

int minStickers2(vector<string>& stickers, string target) {
    //思路：首先肯定是统计字母数量，
    //没有思路，先回溯
    int has[26] = {0}, lmasks[26] = {0}, M = (1 << target.size()) - 1;

    // T 中如果有重复字母也需要分别分配比特位。
    // 重复字母分配的比特位相邻。
    sort(target.begin(), target.end());
    for(int i = 0; i < target.size(); ++i)
        lmasks[target[i] - 'a'] |= (1 << i);
    
    for(string& w : stickers)
        for(char c : w)
            has[c-'a'] = 1;

    // 判断不可能状态
    for(int l = 0; l < 26; ++l)
        if(!has[l] && lmasks[l])
            return -1;
    
    // 按照单词长度排序
    sort(stickers.begin(), stickers.end(), [&](string& a, string& b) {
        return a.size() > b.size();
    });

    vector<int> smasks[stickers.size()];
    for(int i = 0; i < stickers.size(); ++i)
        for(char c : stickers[i])
            if(lmasks[c-'a']) // 必须在 T 中出现过
                smasks[i].push_back(lmasks[c-'a']);
    
    int steps[1 << target.size()];
    memset(steps, 0xff, sizeof(steps));
    steps[0] = 0;
    
    // BFS
    queue<int> q({0});
    for(;;) {
        int cur = q.front();
        q.pop();
        for(int i = 0; i < stickers.size(); ++i) {
            int ne = cur;
            for(int m : smasks[i]) {
                // 遇到有重复字母的情况时，从低位到高位依次寻找是否有可填充的位
                // m & (-m) 用于求出最后一个比特位
                for(int bit = (m & (-m)); bit & m; bit <<= 1) {
                    if(!(ne & bit)) {
                        ne |= bit;
                        break;
                    }
                }
            }
            if(ne == M)
                return steps[cur] + 1;
            if(steps[ne] == -1)
                steps[ne] = steps[cur] + 1, q.push(ne);
        }
    }
    return 0;
}

int main()
{
    vector<string> stickers = {"with", "example", "science"};
    string target = "thehat"; //3

    stickers = {"notice", "possible"};
    target= "basicbasic";

    printf("%d\n",minStickers(stickers,target));
    return 0;
}