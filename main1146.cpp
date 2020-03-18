//1146. 快照数组

#include <cstdio>
#include <vector>

using namespace std;

//思路：
//1.存储每一个快照，空间要求太高；
//2.因为获取的是某个索引的值，也就是说只要知道这个索引位置的操作，就可以知道snap的时候它的值
//那么现在的问题就是如何定义snap和操作，也就是snap id和set的操作前后关系
//记录当前snap id，然后在每次set的时候记录snap id和val的数对

class SnapshotArray {
public:
    SnapshotArray(int length) {
        snap_id_ = 0;
        oprs_.resize(length);
    }
    
    void set(int index, int val) {
        if(!oprs_[index].empty() && oprs_[index].back().first == snap_id_)
        {
            oprs_[index].back().second = val;
        }
        else
        {
            oprs_[index].push_back({snap_id_,val});
        }
        
    }
    
    int snap() {
        return snap_id_++;
    }
    
    int get(int index, int snap_id) {
        // for(int i=oprs_[index].size()-1;i>=0;--i)
        // {
        //     int id = oprs_[index][i].first;
        //     if(snap_id >= id)
        //     {
        //         return oprs_[index][i].second;
        //     }
        // }

        if(oprs_[index].empty())
        {
            return 0;
        }

        //优化，使用二分查找
        int left = 0,right = oprs_[index].size()-1;
        while(left < right)
        {
            int mid = left + (right - left) / 2;
            if(oprs_[index][mid].first <= snap_id)
            {
                left = mid+1;
            }
            else
            {
                right = mid;
            }
            
        }

        if(oprs_[index][left].first == snap_id)
        {
            return oprs_[index][left].second;
        }
        else if(oprs_[index][left].first < snap_id)
        {
            return oprs_[index].back().second;
        }
        else if(left > 0 && oprs_[index][left].first > snap_id)
        {
            return oprs_[index][left-1].second;
        }
        
        return 0;

    }
private:
    int snap_id_;
    vector<vector<pair<int,int>>> oprs_;
};

int main()
{
    // SnapshotArray sa(3);
    // sa.set(0,5);
    // sa.snap();
    // sa.set(0,6);
    // printf("%d\n",sa.get(0,0));

    // SnapshotArray sa(2);
    // sa.snap();
    // printf("%d\n",sa.get(1,0)); //0
    // printf("%d\n",sa.get(0,0)); //0
    // sa.set(1,8);
    // printf("%d\n",sa.get(1,0)); //0
    // sa.set(0,20);
    // printf("%d\n",sa.get(0,0)); //0
    // sa.set(0,7);

    SnapshotArray sa(3);
    sa.set(1,18);
    sa.set(1,4);
    sa.snap();
    // printf("%d\n",sa.get(0,0));
    sa.set(0,20);
    sa.snap();
    sa.set(0,2);
    sa.set(1,1);
    // printf("%d\n",sa.get(1,1));//4
    printf("%d\n",sa.get(1,0));//4
    return 0;
}
