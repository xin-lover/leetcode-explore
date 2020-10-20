//126. 单词接龙 II

#include <cstdio>
#include <vector>
#include <string>
#include <queue>

using namespace std;

void dfs(vector<vector<int>>& graphic,vector<string>& wordList,int index,const string& endWord,vector<bool>& visited,vector<int>& curPath,vector<vector<int>>& resPath)
{
    if(wordList[index] == endWord)
    {
        if(resPath.empty())
        {
            resPath.push_back(curPath);
        }
        else if(curPath.size() == resPath[0].size())
        {
            resPath.push_back(curPath);
        }
        else if(curPath.size() < resPath[0].size())
        {
            resPath.clear();
            resPath.push_back(curPath);
        }

        return;
    }

    visited[index] = true;
    curPath.push_back(index);
    for(int i=0;i<graphic[index].size();++i)
    {
        if(!visited[graphic[index][i]])
        {
            dfs(graphic,wordList,graphic[index][i],endWord,visited,curPath,resPath);
        }
    }
    curPath.pop_back();
    visited[index] = false;
}

vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
    //思路：可以构建一个图，问题就变成了求最短路径

    int n = wordList.size();
    vector<vector<int>> graphic(n);

    for(int i=0;i<wordList.size();++i)
    {
        for(int j=i+1;j<wordList.size();++j)
        {
            int d = 0;
            for(int k=0;k<wordList[i].size();++k)
            {
                if(wordList[i][k] != wordList[j][k])
                {
                    d++;
                }
            }

            if(d < 2)
            {
                graphic[i].push_back(j);
                graphic[j].push_back(i);
            }
        }
    }

    vector<int> curPath;
    vector<vector<int>> resPath;
    vector<bool> visited(n,false);
    for(int i=0;i<n;++i)
    {
        int d = 0;
        for(int j=0;j<wordList[i].size();++j)
        {
            if(wordList[i][j] != beginWord[j])
            {
                ++d;
            }
        }

        if(d < 2)
        {
            dfs(graphic,wordList,i,endWord,visited,curPath,resPath);
        }
    }

    vector<vector<string>> res(resPath.size());
    for(int i=0;i<resPath.size();++i)
    {
        res[i].push_back(beginWord);
        for(int j=0;j<resPath[i].size();++j)
        {
            res[i].push_back(wordList[resPath[i][j]]);
        }
        res[i].push_back(endWord);
    }

    return res;
}

vector<vector<string>> findLadders2(string beginWord, string endWord, vector<string>& wordList) {
    //思路：用dfs，复杂度高,改成bfs

    int n = wordList.size();
    vector<vector<int>> graphic(n);

    for(int i=0;i<wordList.size();++i)
    {
        for(int j=i+1;j<wordList.size();++j)
        {
            int d = 0;
            for(int k=0;k<wordList[i].size();++k)
            {
                if(wordList[i][k] != wordList[j][k])
                {
                    d++;
                }
            }

            if(d == 1)
            {
                graphic[i].push_back(j);
                graphic[j].push_back(i);
            }
        }
    }

    //bfs
    queue<vector<int>> qu;
    for(int i=0;i<n;++i)
    {
        int d = 0;
        for(int j=0;j<beginWord.size();++j)
        {
            if(beginWord[j] != wordList[i][j])
            {
                ++d;
            }
        }

        if(d == 1)
        {
            qu.push({i});
        }
    }

    vector<vector<int>> resPath;
    vector<bool> visited(n,false);
    while(resPath.empty() && !qu.empty())
    {
        int sz = qu.size();
        for(int i=0;i<sz;++i)
        {
            auto p = qu.front();
            qu.pop();

            if(wordList[p.back()] == endWord)
            {
                resPath.push_back(p);
            }

            visited[p.back()] = true;
            for(int j=0;j<graphic[p.back()].size();++j)
            {
                int q = graphic[p.back()][j];
                if(!visited[q]) //这里本轮中非最优的路径并为剔除，使用cost可以剔除
                {
                    //不能在这个位置设置visited[q]=true，否则结果会少
                    vector<int> path(p.begin(),p.end());
                    path.push_back(q);

                    qu.push(path);
                }
            }
        }
    }

    vector<vector<string>> res(resPath.size());
    for(int i=0;i<resPath.size();++i)
    {
        res[i].push_back(beginWord);
        for(int j=0;j<resPath[i].size();++j)
        {
            res[i].push_back(wordList[resPath[i][j]]);
        }
    }

    return res;
}

const int INF = 1 << 20;

//思路一模一样，为什么我的通不过？
//观察发现，主要是在visited的使用上，visited剪枝太慢，也就是在本轮的遍历中不能剪枝
//把visited换成cost后，可以在本轮中把一些已经非最优的路径剔除
// class Solution {
// private:
//     unordered_map<string, int> wordId;
//     vector<string> idWord;
//     vector<vector<int>> edges;
// public:
//     vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
//         int id = 0;
//         for (const string& word : wordList) {
//             if (!wordId.count(word)) {
//                 wordId[word] = id++;
//                 idWord.push_back(word);
//             }
//         }
//         if (!wordId.count(endWord)) {
//             return {};
//         }
//         if (!wordId.count(beginWord)) {
//             wordId[beginWord] = id++;
//             idWord.push_back(beginWord);
//         }
//         edges.resize(idWord.size());
//         for (int i = 0; i < idWord.size(); i++) {
//             for (int j = i + 1; j < idWord.size(); j++) {
//                 if (transformCheck(idWord[i], idWord[j])) {
//                     edges[i].push_back(j);
//                     edges[j].push_back(i);
//                 }
//             }
//         }
//         const int dest = wordId[endWord];
//         vector<vector<string>> res;
//         queue<vector<int>> q;
//         vector<int> cost(id, INF);
//         q.push(vector<int>{wordId[beginWord]});
//         cost[wordId[beginWord]] = 0;
//         while (!q.empty()) {
//             vector<int> now = q.front();
//             q.pop();
//             int last = now.back();
//             if (last == dest) {
//                 vector<string> tmp;
//                 for (int index : now) {
//                     tmp.push_back(idWord[index]);
//                 }
//                 res.push_back(tmp);
//             } else {
//                 for (int i = 0; i < edges[last].size(); i++) {
//                     int to = edges[last][i];
//                     if (cost[last] + 1 <= cost[to]) {
//                         cost[to] = cost[last] + 1;
//                         vector<int> tmp(now);
//                         tmp.push_back(to);
//                         q.push(tmp);
//                     }
//                 }
//             }
//         }
//         return res;
//     }

//     bool transformCheck(const string& str1, const string& str2) {
//         int differences = 0;
//         for (int i = 0; i < str1.size() && differences < 2; i++) {
//             if (str1[i] != str2[i]) {
//                 ++differences;
//             }
//         }
//         return differences == 1;
//     }
// };


int main()
{
    string beginWord = "hit", endWord = "cog";
    vector<string> wordList = {"hot","dot","dog","lot","log","cog"};//[{hit hot dot dog cog},{hit hot lot log cog}]

    // beginWord = "hit";
    // endWord = "cog";
    // wordList = {"hot","dot","dog","lot","log"};//[]

    // beginWord ="a";
    // endWord = "c";
    // wordList = {"a","b","c"}; //[{a,c}]

    beginWord = "hot";
    endWord = "dog";
    wordList ={"hot","dog"};

    for(auto a : findLadders2(beginWord,endWord,wordList))
    {
        for(auto b : a)
        {
            printf("%s ",b.c_str());
        }
        printf("\n");
    }

    return 0;
}