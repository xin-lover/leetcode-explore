//1348. 推文计数

#include <cstdio>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class TweetCounts {
public:
    TweetCounts() {
        //思路：如何存储推文是一个问题，recordTweet的调用是否有序，这个不清楚
        //可以先简单的使用map和vector来存储记录
        //获取推文总数的时候，重点是计算间隔
        //第一次提交超时,看来还是要用二分法优化,插入的时候也要优化
    }
    
    void recordTweet(string tweetName, int time) {
        um_[tweetName].push_back(time);
        //假定无序
        // for(int i=um_[tweetName].size()-1;i>=1;--i) 
        // {
        //     if(um_[tweetName][i] < um_[tweetName][i-1])//比较太多，用二分优化
        //     {
        //         swap(um_[tweetName][i],um_[tweetName][i-1]);
        //     }
        // }

        auto& arr = um_[tweetName];
        int left=0,right=arr.size()-1;
        while(left < right)
        {
            int mid = left + (right-left)/2;
            if(arr[mid] < time)
            {
                left = mid+1;   
            }
            else
            {
                right = mid;
            }
        }

        
        for(int i=arr.size()-1;i>=right+1;++i)
        {
            arr[i] = arr[i-1];
        }

        arr[right] = time;
    }
    
    vector<int> getTweetCountsPerFrequency(string freq, string tweetName, int startTime, int endTime) {
        
        //记录间隔
        static unordered_map<string,int> interval_map = {{"minute",60},{"hour",3600},{"day",60*60*24}};

        int interval = interval_map[freq];
        vector<pair<int,int>> intervals;
        int mark = startTime;
        while(mark + interval <= endTime)
        {
            intervals.push_back({mark,mark+interval});
            mark += interval;
        }

        if(mark <= endTime)
        {
            intervals.push_back({mark,endTime+1});
        }
        // for(auto a : intervals)
        // {
        //     printf("%d %d\n",a.first,a.second);
        // }

        // int count = 0;
        // int flag = 0;
        // vector<int> res(intervals.size(),0);
        // for(int i=0;i<um_[tweetName].size();++i)
        // {
        //     for(int j=flag;j<intervals.size();++j)
        //     {
        //         if(um_[tweetName][i] >= intervals[j].first && um_[tweetName][i] < intervals[j].second)
        //         {
        //             ++res[j];
        //             flag = j;
        //             break;
        //         }
        //     }
        // }

        //用二分法优化
        vector<int> res(intervals.size(),0);

        for(int i=0;i<intervals.size();++i)
        {
            vector<int>& arr = um_[tweetName];
            
            int left=0,right=arr.size()-1;
            while(left < right)
            {
                int mid = left + (right-left)/2;
                if(arr[mid] < intervals[i].first)
                {
                    left = mid+1;
                }
                else
                {
                    right = mid;
                }
            }

            if(arr[left] < intervals[i].first)
            {
                break;
            }

            int start = left;
            left = 0,right=arr.size()-1;
            while(left < right)
            {
                int mid = left + (right - left) / 2;
                if(arr[mid] < intervals[i].second)
                {
                    left = mid+1;
                }
                else
                {
                    right = mid;
                }
            }

            res[i] = right-start;
            if(arr[right] < intervals[i].second)
            {
                ++res[i];
            }
        }

        return res;
    }

    unordered_map<string,vector<int>> um_;
};

//平衡二叉树，使用了upper_bound和lower_bound的方法
// class TweetCounts {
//     map<string, set<int>> user;
// public:
//     TweetCounts() {
//     }
    
//     void recordTweet(string tweetName, int time) {
//         user[tweetName].insert(time);
//     }
    
//     vector<int> getTweetCountsPerFrequency(string freq, string tweetName, int startTime, int endTime) {
//         int length = 0;
//         if (freq == "minute")
//             length = 60;
//         else if (freq == "hour")
//             length = 60 * 60;
//         else
//             length = 60 * 60 * 24;
//         vector<int> ans((endTime - startTime) / length + 1);
//         auto begin = user[tweetName].lower_bound(startTime);
//         auto end = user[tweetName].upper_bound(endTime);
//         for (; begin != end; ++begin) {
//             ++ans[(*begin - startTime) / length];
//         }
//         return ans;
//     }
// };

int main()
{
    TweetCounts tc;
    tc.recordTweet("tweet3",0);
    tc.recordTweet("tweet3",60);
    tc.recordTweet("tweet3",10);

    for(auto a : tc.getTweetCountsPerFrequency("minute","tweet3",0,59)) //2
    {
        printf("%d ",a);
    }
    printf("\n");

    for(auto a : tc.getTweetCountsPerFrequency("minute","tweet3",0,60)) //2 1
    {
        printf("%d ",a);
    }
    printf("\n");

    tc.recordTweet("tweet3",120);
    for(auto a : tc.getTweetCountsPerFrequency("hour","tweet3",0,210)) //4
    {
        printf("%d ",a);
    }
    printf("\n");

    return 0;
}