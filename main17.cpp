#include <cstdio>
#include <vector>
#include <unordered_map>
#include <stack>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> findItinerary(vector<pair<string, string>> tickets) {
        
        //思路：有向图，根据题意，需要把所有的票都使用
        //在一个机场，可能有多种选择，使用回溯法，遍历所有可能
        
        unordered_map<string,vector<string>> graph;
        for(auto a : tickets)
        {
            graph[a.first].push_back(a.second);
            if(graph.find(a.second) == graph.end())
            {
                graph[a.second] = {};
            }
        }
        
        for(auto& a : graph)
        {
            sort(a.second.begin(),a.second.end());
        }
        
        string cur = "JFK";
        int curIndex = 0;
        stack<pair<string,string>> sk;
        stack<int> ski;
        vector<string> path;
        while(!cur.empty())
        {
            path.push_back(cur);
            if(curIndex < graph[cur].size())
            {
                string t = graph[cur][curIndex];
                sk.push(make_pair(cur,t));
                ski.push(curIndex);
                graph[cur].erase(graph[cur].begin() + curIndex);
                cur = t;   
                printf("cur:%s\n",cur.c_str());
                curIndex = 0;
            }
            else
            {
                //判断是否完成遍历                
                printf("hh cur:%s\n",cur.c_str());
                for(auto a : path)
                {
                    printf("%s ",a.c_str());
                }
                printf("\n");
                if(path.size() - 1 == tickets.size())
                {
                    return path;
                }
                else
                {
                    path.pop_back();
                    printf("ff:%d\n",path.size());
                    curIndex = ski.top();
                    ski.pop();
                    
                    auto p = sk.top();
                    sk.pop();
                    graph[p.first].insert(graph[p.first].begin() + curIndex,p.second);
                    path.pop_back();
                    cur = p.first;
                    ++curIndex;
                }
            }
        }
        
        return {};
    }
};

int main()
{
    Solution s;
    vector<pair<string,string>> vp = {
        {"MUC", "LHR"}, 
        {"JFK", "MUC"}, 
        {"SFO", "SJC"}, 
        {"LHR", "SFO"},

        // {"JFK","SFO"},
        // {"JFK","ATL"},
        // {"SFO","ATL"},
        // {"ATL","JFK"},
        // {"ATL","SFO"}

        // {"JFK","KUL"},
        // {"JFK","NRT"},
        // {"NRT","JFK"}
    };
    auto res = s.findItinerary(vp);
    printf("res:");
    for(auto a : res)
    {
        printf("%s ", a.c_str());
    }
    printf("\n");
    return 0;
}