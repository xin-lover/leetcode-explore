//381. O(1) 时间插入、删除和获取随机元素 - 允许重复

#include <cstdio>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class RandomizedCollection {
public:
    /** Initialize your data structure here. */
    RandomizedCollection() {
        //思路：要想O(1)，考虑能O(1)操作的集合，数组、散列表
        //删除也要O(1)，那么基本就考虑散列表了
        //获取随机值，这个用散列表怎么搞？先考虑O（N）的
        count_ = 0;
    }
    
    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        count_++;
        bool res = um_.find(val) == um_.end();
        um_[val]++;

        return res;
    }
    
    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        if(um_.find(val)!=um_.end() && um_[val] > 0)
        {
            um_[val]--;
            count_--;

            return true;
        }

        return false;
    }
    
    /** Get a random element from the collection. */
    int getRandom() {
        if(count_ > 0)
        {
            int seq = rand() % count_ + 1;
            for(auto it=um_.begin();it!=um_.end();++it)
            {
                seq -= it->second;
                if(seq <= 0)
                {
                    return it->first;
                }
            }
        }

        return 0;
    }

    unordered_map<int,int> um_;
    int count_;
};


class RandomizedCollection2 {
public:
    /** Initialize your data structure here. */
    RandomizedCollection2() {
        //思路：要想O(1)，考虑能O(1)操作的集合，数组、散列表
        //删除也要O(1)，那么基本就考虑散列表了
        //删除使用了一个技巧，就是把要删除的元素放到最后的位置，因为位置不影响随机性。。。
    }
    
    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        nums_.push_back(val);
        ids_[val].insert(nums_.size()-1);

        return ids_[val].size() == 1;
    }
    
    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        if(ids_.find(val)!=ids_.end() && ids_[val].size() > 0)
        {
            int valp = *(ids_[val].begin());
            ids_[val].erase(valp);

            int lastVal = nums_.back();
            ids_[lastVal].insert(valp);
            ids_[lastVal].erase(nums_.size()-1);

            nums_[valp] = lastVal;
            nums_.pop_back();

            return true;
        }

        return false;
    }
    
    /** Get a random element from the collection. */
    int getRandom() {
        return nums_[rand() % nums_.size()];
    }

    vector<int> nums_;
    unordered_map<int,unordered_set<int>> ids_;
};

int main()
{
    RandomizedCollection2 rc;
    rc.insert(0);
    rc.remove(0);
    rc.insert(-1);
    printf(rc.remove(0) ? "true\n" : "false\n");
    // printf(rc.remove(4) ? "true\n" : "false\n");
    // printf(rc.remove(4) ? "true\n" : "false\n");

    // printf("%d\n",rc.getRandom());
    // printf("%d\n",rc.getRandom());
    // printf("%d\n",rc.getRandom());
    // printf("%d\n",rc.getRandom());
    // printf("%d\n",rc.getRandom());

    return 0;
}