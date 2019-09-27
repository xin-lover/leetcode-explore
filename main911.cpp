//leetcode 911. 在线选举

#include <cstdio>
#include <vector>

using namespace std;

class TopVotedCandidate {
public:
    TopVotedCandidate(vector<int>& persons, vector<int>& times) {
        //思路：times严格递增，然后q是多次调用，q的参数t也是递增的，那么就使用动归的思想只存储上次投票结果
        //如果不是，那么就是空间和时间的选择
        //对于t，我们遍历times，小于等于t的投票我们要进行一个计数，这个时候使用数组记录即可
        //因为多次调用，所以我们构建对象时就把times中时间点的结果都计算出来

        int n = 0;
        for(int i=0;i<persons.size();++i)
        {
            if(persons[i]>n)
            {
                n = persons[i];
            }
        }

        vector<int> counts(n+1,0);
        int win = 0;
        for(int i=0;i<times.size();++i)
        {
            ++counts[persons[i]];
            if(counts[persons[i]] >= counts[win])
            {
                win = persons[i];
            }
            flags_.push_back({times[i],win});
        }

        //一个改进是只存储win改变的时刻，不用存所有时刻
    }
    
    int q(int t) {
    //     for(int i=0;i<flags_.size();++i)
    //     {
    //         if(flags_[i].first > t)
    //         {
    //             return flags_[i-1].second;
    //         }
    //     }

    //     return flags_.back().second;

        //因为递增，所以二分查找
        int left =0,right=flags_.size();
        while(left < right)
        {
            int mid = left + (right-left)/2;
            if(flags_[mid].first <= t)
            {
                left = mid+1;
            }
            else
            {
                right = mid; 
            }
        }

        return flags_[right-1].second;
    }

    vector<pair<int,int>> flags_;
};


int main()
{
    vector<int> persons = {0,1,1,0,0,1,0};
    vector<int> times = {0,5,10,15,20,25,30};

    //[[[0,0,0,0,1],[0,6,39,52,75]],[45],[49],[59],[68],[42],[37],[99],[26],[78],[43]]
    // persons = {0,0,0,0,1};
    // times ={0,6,39,52,75};

    TopVotedCandidate tv(persons,times);
    // printf("%d\n",tv.q(3));
    // printf("%d\n",tv.q(12));
    // printf("%d\n",tv.q(25));
    printf("%d\n",tv.q(15));
    printf("%d\n",tv.q(24));
    printf("%d\n",tv.q(8));

    // printf("%d\n",tv.q(99));

    return 0;
}