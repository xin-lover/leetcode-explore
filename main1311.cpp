//1311. 获取你好友已观看的视频

#include <cstdio>
#include <vector>
#include <queue>
#include <map>
#include <string>

using namespace std;

vector<string> watchedVideosByFriends(vector<vector<string>>& watchedVideos, vector<vector<int>>& friends, int id, int level) {
    //思路：还是bfs，最后需要按频率和字典排序输出
    vector<bool> visited(watchedVideos.size(),0);
    
    queue<int> qu;
    qu.push(id);
    visited[id] = true;

    while(!qu.empty() && level > 0)
    {
        int sz = qu.size();
        for(int i=0;i<sz;++i)
        {
            int k = qu.front();
            qu.pop();

            for(int j=0;j<friends[k].size();++j)
            {
                if(!visited[friends[k][j]])
                {
                    qu.push(friends[k][j]);
                    visited[friends[k][j]] = true;
                }
            }
        }

        --level;
    }

    //排序
    map<string,int> v_map;
    while(!qu.empty())
    {
        int k = qu.front();
        qu.pop();

        for(int i=0;i<watchedVideos[k].size();++i)
        {
            ++v_map[watchedVideos[k][i]];
        }
    }

    vector<pair<string,int>> vv;
    for(auto it = v_map.begin();it!=v_map.end();++it)
    {
        vv.push_back({it->first,it->second});
    }

    sort(vv.begin(),vv.end(),[](pair<string,int>& a, pair<string,int>& b)
    {
        if(a.second == b.second)
        {
            return a.first < b.first;
        }

        return a.second < b.second;
    });

    vector<string> res;
    for(int i=0;i<vv.size();++i)
    {
        res.push_back(vv[i].first);
    }

    return res;
}

int main()
{
    vector<vector<string>> watchedVideos = {{"A","B"},{"C"},{"B","C"},{"D"}};
    vector<vector<int>> friends = {{1,2},{0,3},{0,3},{1,2}};
    int id = 0;
    int level = 1; //B,C


    //D
    // watchedVideos = {{"A","B"},{"C"},{"B","C"},{"D"}}, friends = {{1,2},{0,3},{0,3},{1,2}}, id = 0, level = 2;

    auto res = watchedVideosByFriends(watchedVideos,friends,id,level);
    for(auto a : res)
    {
        printf("%s ",a.c_str());
    }
    printf("\n");

    return 0;
}