//460. LFU 缓存

#include <cstdio>
#include <vector>
#include <unordered_map>

using namespace std;

class LFUCache {
public:
    LFUCache(int capacity) {
        //思路：要想O（1），那么就在hash和数组下标取值之间选
        //现在数据是键值，那么使用hash
        //接下来的问题就是如何记录次数和最后一次操作时间并排序
        //要想这一步也是O（1），那么也就是在put和get的时候就要更新时间和次数并排序；
        //删除只能发生在put的时候，这个时候要找次数最少且时间最早那个，假设我们知道这个，那么我们先删除这个
        //同时put了一个进来，我们这个时候还需要标记一个次数最少且时间最早的数据
        //put时，该数据的次数+1，时间肯定是同次数数据中最晚的，所以如果我们按次数分组，那么只需要把这个数据添加到这个组的末尾即可，删除即删除第一个
        //但更新如何搞？因为要从之前的分组中删除，如何快速获取？考虑地址或下表获取，这个时候借鉴双向链表
        //所以最终的方案就是，使用散列表储存键值（包括其频率），同时频率分组，便于快速变更元素位置（频率增加或找新的最少使用元素）；同时借鉴双向链表思路，使能在O(1)删除元素，实时维护一个最少使用的索引
        //这样在频率增加或删除元素时，先从链表中取出这个元素，然后根据需要放到对应频率组的后面即可
    

        capacity_ = capacity;
        minCountKey_ = -1;
    }
    
    int get(int key) {
        if(um_.find(key) != um_.end())
        {
            um_[key][1]++;
            update(key);
            return um_[key][0];
        }

        return -1;
    }
    
    void put(int key, int value) {
        if(capacity_ == 0)
        {
            return;
        }
        if(um_.find(key) == um_.end())
        {
            um_.insert({key,{value,1,-1,-1}});
        }
        else
        {
            um_[key][1]++;
            um_[key][0] = value;
        }

        if(um_.size() > capacity_)
        {
            int next = um_[minCountKey_][2];
            leaveGroup(um_[minCountKey_][1],minCountKey_);
            // assert(um_[minCountKey_][3] == -1);
            if(next != -1)
            {
                um_[next][3] = -1;
            }

            um_.erase(minCountKey_);
            minCountKey_ = next;
        }
        
        update(key);
    }

    void insertAfter(int pre, int key)
    {
        // printf("pre:%d key:%d\n",pre,key);
        if(pre == key || pre == -1)
        {
            return;
        }
        int next = um_[pre][2];
        um_[pre][2]= key;
        um_[key][2]= next;
        if(next != -1)
        {
            um_[next][3]= key;
        }
        um_[key][3]= pre;
    }

    void leaveGroup(int group,int key)
    {
        if(groups_.find(group) == groups_.end())
        {
            return;
        }

        if(groups_[group].first == key)
        {
            int next = um_[key][2];
            if(next != -1 && um_[next][1] == group)
            {
                groups_[group].first = next;
            }
            else
            {
                groups_[group].first = -1;
            }
        }

        if(groups_[group].second == key)
        {
            int pre = um_[key][3];
            if(pre != -1 && um_[pre][1] == group)
            {
                groups_[group].second = pre;

            }
            else
            {
                groups_[group].second = -1;
            }
            
        }

        if(groups_[group].first == groups_[group].second && groups_[group].first == -1)
        {
            groups_.erase(group);
        }

    }

    void update(int key)
    {
        int group = um_[key][1];
        int oldgroup = group - 1;

        //更新链表关系,加入到新组的末端,更新group的关系
        leaveGroup(oldgroup,key);
        //断开现有链接
        int oldpre = um_[key][3];
        int oldnext = um_[key][2];
        // printf("update:%d group:%d old:%d %d\n",key,group,oldpre,oldnext);
        if(oldpre != -1)
        {
            um_[oldpre][2] = oldnext;
        }
        if(oldnext != -1)
        {
            um_[oldnext][3] = oldpre;
        }
        um_[key][2] = -1;
        um_[key][3] = -1;

        //建立新的链接
        if(groups_.find(group) == groups_.end())
        {
            groups_.insert({group,{key,key}});
            if(group == 1)
            {
                um_[key][2] = minCountKey_;
                if(minCountKey_ != -1)
                {
                    um_[minCountKey_][3] = key;
                }
            }
            else if(groups_.find(oldgroup) != groups_.end())
            {
                insertAfter(groups_[oldgroup].second,key);
            }
            else
            {
                um_[key][2] = oldnext;
                um_[key][3] = oldpre;
                if(oldnext != -1)
                {
                    um_[oldnext][3] = key;
                }
                if(oldpre != -1)
                {
                    um_[oldpre][2] = key;
                }
                
            }
        }
        else
        {
            insertAfter(groups_[group].second,key);
            groups_[group].second = key;
        }



        if(groups_.find(1) != groups_.end())
        {
            minCountKey_ = groups_[1].first;
        }
        else if(minCountKey_ == key && oldnext != -1 && um_[oldnext][1] <= group)
        {
            minCountKey_ = oldnext;
        }
    }

    int capacity_;
    unordered_map<int,vector<int>> um_;
    unordered_map<int,pair<int,int>> groups_;
    int minCountKey_;
};

int main()
{
    LFUCache lFUCache(1101);
    // lFUCache.put(1, 1);
    // lFUCache.put(2, 2);
    // printf("%d\n",lFUCache.get(1));      // 返回 1
    // lFUCache.put(3, 3);   // 去除键 2
    // printf("%d\n",lFUCache.get(2));      // 返回 -1（未找到）
    // printf("%d\n",lFUCache.get(3));      // 返回 3
    // lFUCache.put(4, 4);   // 去除键 1
    // printf("----------\n");
    // printf("%d\n",lFUCache.get(1));      // 返回 -1（未找到）
    // printf("%d\n",lFUCache.get(3));      // 返回 3
    // printf("%d\n",lFUCache.get(4));      // 返回 4

    // lFUCache.put(1,1);
    // lFUCache.put(2,2);
    // lFUCache.put(3,3);
    // lFUCache.put(4,4);
    // printf("%d\n",lFUCache.get(4)); //4
    // printf("%d\n",lFUCache.get(3)); //3
    // printf("%d\n",lFUCache.get(2)); //2
    // printf("%d\n",lFUCache.get(1)); //-1
    // lFUCache.put(5,5);
    // printf("%d\n",lFUCache.get(1)); //-1
    // printf("%d\n",lFUCache.get(2)); //2
    // printf("%d\n",lFUCache.get(3));//3
    // printf("%d\n",lFUCache.get(4));//-1
    // printf("%d\n",lFUCache.get(5));//5

    vector<vector<int>> nums = {{10,13},{3,17},{6,11},{10,5},{9,10},{13},{2,19},{2},{3},{5,25},{8},{9,22},{5,5},{1,30},{11},{9,12},{7},{5},{8},{9},{4,30},{9,3},{9},{10},{10},{6,14},{3,1},{3},{10,11},{8},{2,14},{1},{5},{4},{11,4},{12,24},{5,18},{13},{7,23},{8},{12},{3,27},{2,12},{5},{2,9},{13,4},{8,18},{1,7},{6},{9,29},{8,21},{5},{6,30},{1,12},{10},{4,15},{7,22},{11,26},{8,17},{9,29},{5},{3,4},{11,30},{12},{4,29},{3},{9},{6},{3,4},{1},{10},{3,29},{10,28},{1,20},{11,13},{3},{3,12},{3,8},{10,9},{3,26},{8},{7},{5},{13,17},{2,27},{11,15},{12},{9,19},{2,15},{3,16},{1},{12,17},{9,1},{6,19},{4},{5},{5},{8,1},{11,7},{5,2},{9,28},{1},{2,2},{7,4},{4,22},{7,24},{9,26},{13,28},{11,26}};
    nums = {{2,1},{2},{3,2},{2},{3}};

    for(auto a : nums)
    {
        if(a.size() == 1)
        {
            printf("%d\n",lFUCache.get(a[0]));
        }
        else
        {
            lFUCache.put(a[0],a[1]);
        }
        
    }

    return 0;
}