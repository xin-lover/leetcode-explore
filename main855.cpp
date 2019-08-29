//leetcode 855. 考场就座

#include <cstdio>
#include <set>

using namespace std;

class ExamRoom {
public:
    ExamRoom(int N) {
        //思路：把它看成区间，我们的操作就是划分和合并区间，每次划分最大的区间
        //有人离开，则向左右查找有人坐的位置，查找到后，中间的位置就是下一次要坐的位置
        //策略：使用set记录当前已做人位置

        n_ = N;
    }
    
    int seat() {
        
        if(poses_.empty())
        {
            poses_.insert(0);
            return 0;
        }
        // if(poses_.size() == 1)
        // {
        //     int p = *(poses_.begin());
        //     if(n_-1-p > p)
        //     {
        //         poses_.insert(n_-1);
        //         return n_-1;
        //     }
        //     else
        //     {
        //         poses_.insert(0);
        //         return 0;
        //     }
        // }

        int pre = 0;
        int dist = *(poses_.begin());
        int pos = 0;
        // auto endit = poses_.end();
        // --endit;
        for(auto it = poses_.begin();it != poses_.end();++it)
        {
            int p = *it;

            int d = (p - pre)/2;
            if(d > dist)
            {
                dist = d;
                pos = pre + d;
            }
            pre = p;
        }
        
        //考虑最后一个位置
        int end = *(poses_.rbegin());
        if(n_-1-end > dist)
        {
            pos = n_-1;
        }
        
        poses_.insert(pos);
        return pos;
    }
    
    void leave(int p) {
         poses_.erase(p);
    }
    
private:
    set<int> poses_;
    int n_;
};

int main()
{
    return 0;
}