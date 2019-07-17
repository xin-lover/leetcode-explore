//leetcode 692. 前K个高频单词

#include <cstdio>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;

vector<string> topKFrequent(vector<string>& words, int k) {
    
    //思路：首先统计次数，然后维持一个最小堆

    unordered_map<string,int> um;
    for(auto& s : words)
    {
        ++um[s];
    }

    auto f = [](const pair<string,int>& a, const pair<string,int>& b){
        if(a.second == b.second)
        {
            return a.first > b.first;
        }

        return a.second < b.second;
    };

    priority_queue<pair<string,int>,vector<pair<string,int>>,function<bool(const pair<string,int>&,const pair<string,int>&)>> pq(f);

    for(auto& a : um)
    {
        pq.push(a);
    }

    vector<string> res;
    for(int i=0;i<k;++i)
    {
        auto y = pq.top();
        pq.pop();
        res.push_back(y.first);
    }

    return res;

}

int main()
{
    vector<string> words = {"i", "love", "leetcode", "i", "love", "coding"};
    words = {"the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"};
    for(auto a : topKFrequent(words,4))
    {
        printf("%s ",a.c_str());
    }
    printf("\n");
    return 0;
}