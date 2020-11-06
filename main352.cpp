//352. 将数据流变为多个不相交区间

#include <cstdio>
#include <vector>

using namespace std;

class SummaryRanges {
public:
    /** Initialize your data structure here. */
    SummaryRanges() {
        //思路：这里主要是如何获取区间。一种是每次都计算区间，一种是在添加数字的时候更新区间
        //每次都计算区间在数字多了之后就不太合适了
        //所以策略是在添加数字时合并区间
        //一个一个数字来考虑，
        //1.第一个数字单独成立区间；
        //2.第二个数字，如果与第一个数字相邻，则合并区间，否则开辟新的区间
        //所以问题变成了，对于一个数字，如何快速的找到可合并的区间
        //使用二分法，但删除区间可能会影响性能
    }
    
    void addNum(int val) {

        int left = 0,right=intervals_.size()-1;
        while(left < right)
        {
            int mid = left + (right-left) / 2;

            if(val < intervals_[mid][0]-1)
            {
                right = mid-1;
            }
            else if(val > intervals_[mid][1]+1)
            {
                left = mid+1;
            }
            else
            {
                left = mid;
                break;
            }
            
        }

        printf("val:%d left:%d\n",val,left);
        if(intervals_.empty())
        {
            intervals_.push_back({val,val});
        }
        else if(val > intervals_[left][1]+1)
        {
            intervals_.insert(intervals_.begin()+left+1, {val,val});
        }
        else if(val < intervals_[left][0]-1)
        {
            intervals_.insert(intervals_.begin()+left, {val,val});
        }
        else if(val == intervals_[left][1]+1)
        {
            intervals_[left][1] = val;
            if(left+1 < intervals_.size() && intervals_[left+1][0]-1 == intervals_[left][1])
            {
                intervals_[left][1] = intervals_[left+1][1];
                intervals_.erase(intervals_.begin()+left+1);
            }
        }
        else if(val == intervals_[left][0]-1)
        {
            intervals_[left][0] = val;
            if(left > 0 && intervals_[left-1][1]+1 == intervals_[left][0])
            {
                intervals_[left-1][1] = intervals_[left][1];
                intervals_.erase(intervals_.begin()+left);
            }
        }
    }
    
    vector<vector<int>> getIntervals() {
        return intervals_;
    }

    vector<vector<int>> intervals_;
};

int main()
{
    SummaryRanges sr; //1，3，7，2，6
    sr.addNum(0);
    for(auto a : sr.getIntervals())
    {
        for(auto b : a)
        {
            printf("%d ",b);
        }
    }
    printf("\n--------\n");

    sr.addNum(4);
    for(auto a : sr.getIntervals())
    {
        for(auto b : a)
        {
            printf("%d ",b);
        }
    }
    printf("\n--------\n");

        sr.addNum(6);
    for(auto a : sr.getIntervals())
    {
        for(auto b : a)
        {
            printf("%d ",b);
        }
    }
    printf("\n--------\n");

        sr.addNum(8);
    for(auto a : sr.getIntervals())
    {
        for(auto b : a)
        {
            printf("%d ",b);
        }
    }
        printf("\n--------\n");

                sr.addNum(7);
    for(auto a : sr.getIntervals())
    {
        for(auto b : a)
        {
            printf("%d ",b);
        }
    }
        printf("\n--------\n");

                        sr.addNum(4);
    for(auto a : sr.getIntervals())
    {
        for(auto b : a)
        {
            printf("%d ",b);
        }
    }
        printf("\n--------\n");

    return 0;
}