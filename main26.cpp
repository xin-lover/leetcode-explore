#include <cstdio>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <set>

using namespace std;

bool calcVal(unordered_map<string,vector<pair<string,double>>>& graph,set<string>& visited, string dividend,string divisor,double& val)
{
    printf("%s\n",dividend.c_str());
    auto vt = graph[dividend];
    for(auto a : vt)
    {
        if(a.first == divisor)
        {
            val = a.second;
            printf("val:%f\n",val);
            return true;
        }
        if(visited.find(a.first) == visited.end())
        {
            visited.insert(a.first);
            if(calcVal(graph,visited,a.first,divisor,val))
            {
                val *= a.second;
                printf("%f %f\n",val,a.second);
                return true;
            }
        }
    }

    return false;
}

vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
    
    //思路：就是组合，组合，还有就是倒数和结果为1的特殊情况
    //对于组合，就有点像是找一条路径，除数为起点，被除数是终点
    //所以使用图的思维，先构建一个图，然后查找路径

    unordered_map<string,vector<pair<string,double>>> graph;
    for(int i=0;i<equations.size();++i)
    {
        auto p = equations[i];
        if(graph.find(p.first) == graph.end())
        {
            graph[p.first] = vector<pair<string,double>>();
        }

        graph[p.first].push_back(make_pair(p.second,values[i]));

        if(graph.find(p.second) == graph.end())
        {
            graph[p.second] = vector<pair<string,double>>();
        }
        graph[p.second].push_back(make_pair(p.first,1.0/values[i]));
    }

    vector<double> res;
    for(int i=0;i<queries.size();++i)
    {
        string dividend = queries[i].first;
        string divisor = queries[i].second;

        if(graph.find(dividend) == graph.end() || graph.find(divisor) == graph.end())
        {
            res.push_back(-1.0);
            continue;
        }

        if(dividend == divisor)
        {
            res.push_back(1.0);
            continue;
        }

        double val=-1.0;
        set<string> visited;
        calcVal(graph,visited,dividend,divisor,val);
        res.push_back(val);
    }

    return res;
}

int main()
{
   vector<pair<string, string>> equations=
//    {
//        {"a","b"},
//        {"b","c"},
//    };
//    {{"a","b"},{"b","c"},{"bc","cd"}};
{{"x1","x2"},{"x2","x3"},{"x3","x4"},{"x4","x5"}};
    vector<double> values=
    // {
    //     1.0,2.0,
    // };
    // {1.5,2.5,5.0};
    {3.0,4.0,5.0,6.0};
    vector<pair<string, string>> queries=
    // {
    //     {"a","c"},
    //     {"a","a"},
    //     {"b","a"},
    //     {"b","e"},
    //     {"x","x"},
    // };
    // {{"a","c"},{"c","b"},{"bc","cd"},{"cd","bc"}};
    // {{"x1","x5"},{"x5","x2"}};//,{"x2","x4"},{"x2","x2"},{"x2","x9"},{"x9","x9"}};
    {{"x1","x5"},{"x5","x2"}};

    auto res = calcEquation(equations,values,queries);
    for(double a: res)
    {
        printf("%f ",a);
    }
    printf("\n");
    return 0;
}