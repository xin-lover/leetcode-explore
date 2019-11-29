//981. 基于时间的键值存储

#include <cstdio>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>

using namespace std;

class Pcmp
{
public:
    bool operator() (const pair<int,string>& a,const pair<int,string>& b)
    {
        return a.first > b.first;
    }
};

class TimeMap {
public:
    /** Initialize your data structure here. */
    TimeMap() {
        //思路：正常的就是用map存储就行，接下来就是针对时间戳再存储就可以了
        //因为时间递增，所以有另一个选择就是set
        //map嵌套set  

    }
    
    void set(string key, string value, int timestamp) {
        um_[key].insert({timestamp,value});
    }
    
    string get(string key, int timestamp) {
        if(um_.find(key) == um_.end())
        {
            return "";
        }

        auto it = um_[key].upper_bound({timestamp+1,""});
        if(it == um_[key].end())
        {
        printf("get\n");
            return "";
        }

        return it->second;
    }

    std::unordered_map<string,std::set<pair<int,string>,Pcmp>> um_;
};

int main()
{
    TimeMap tm;
    tm.set("foo","bar",1);
    printf("%s\n",tm.get("foo",1).c_str());
    printf("%s\n",tm.get("foo",2).c_str());
    tm.set("foo","bar2",4);
    printf("%s\n",tm.get("foo",4).c_str());
    printf("%s\n",tm.get("foo",5).c_str());
    return 0;
}