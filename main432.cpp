//432. 全 O(1) 的数据结构

#include <cstdio>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;

class AllOne {
public:
    struct LinkList
    {
        LinkList* pre;
        LinkList* next;
        int val;
        unordered_set<string> keys;

        LinkList(int value):val(value),pre(nullptr),next(nullptr){}
    };
    /** Initialize your data structure here. */
    AllOne() {
        //思路：能常数时间运行的就是数组和散列表，这里数量不定，所以用散列表
        //问题的关键在于减少的时候，如何更新最大值和最小值
        //我们使用另一个散列表，该表的key为第一个散列表的value，而value为该值的string的集合，那么我们需要一个查找，添加，删除都是O(1)的结构，还是散列表
        //唯一比较麻烦的是最小值的存储，我们用双向链表

        head_ = nullptr;
        tail_ = nullptr;
    }
    
    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(string key) {
        if(um_.find(key) != um_.end())
        {
            LinkList* t = um_[key];
            if(t == head_)
            {
                if(t->keys.size() == 1)
                {
                    t->val++;
                }
                else
                {
                    LinkList* p = new LinkList(t->val+1);
                    p->keys.insert(key);
                    t->keys.erase(key);
                    t->next = p;
                    p->pre = t;
                    head_ = p;

                    um_[key] = p;
                    
                }
            }
            else
            {
                if(t->val + 1 == t->next->val)
                {
                    if(t->keys.size() == 1)
                    {
                        t->next->keys.insert(key);
                        if(t == tail_)
                        {
                            tail_ = t->next;
                            t->next->pre = nullptr;
                        }
                        else
                        {
                            t->pre->next = t->next;
                            t->next->pre = t->pre;
                        }

                        um_[key] = t->next;
                        delete t;
                    }
                    else
                    {
                        
                        t->next->keys.insert(key);
                        t->keys.erase(key);

                        um_[key] = t->next;
                    }
                }
                else
                {
                    if(t->keys.size() == 1)
                    {
                        t->val++;
                    }
                    else
                    {
                        LinkList* p = new LinkList(t->val+1);
                        p->keys.insert(key);
                        t->keys.erase(key);
                        t->next->pre = p;
                        p->next = t->next;
                        t->next = p;
                        p->pre = t;

                        um_[key] = p;
                    }
 
                }
            }
        }
        else
        {
            if(tail_ == nullptr)
            {
                LinkList* t = new LinkList(1);
                t->keys.insert(key);

                head_ = t;
                tail_ = t;

                um_[key] = t;
            }
            else
            {
                if(tail_->val == 1)
                {
                    tail_->keys.insert(key);
                    um_[key] = tail_;
                }
                else
                {
                    LinkList* t = new LinkList(1);
                    t->keys.insert(key);
                    t->next = tail_;
                    tail_->pre = t;
                    tail_ = t;

                    um_[key] = t;
                }
            }
        }


    }
    
    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key) {
        if(um_.find(key) != um_.end())
        {
            LinkList* t = um_[key];
            if(t->pre != nullptr)
            {
                if(t->val-1 == t->pre->val)
                {
                    t->pre->keys.insert(key);
                    um_[key] = t->pre;
                    if(t->keys.size() == 1)
                    {
                        if(t == head_)
                        {
                            head_ = t->pre;
                        }
                        else
                        {
                            t->keys.erase(key);
                            t->pre->next = t->next;
                            t->next->pre = t->pre;
                        }
                        delete t;
                    }
                    else
                    {
                        t->keys.erase(key);
                    }
                }
                else
                {
                    if(t->keys.size() == 1)
                    {
                        t->val--;
                    }
                    else
                    {
                        LinkList* p = new LinkList(t->val-1);
                        p->keys.insert(key);
                        um_[key] = p;

                        p->pre = t->pre;
                        t->pre->next = p;
                        p->next = t;
                        t->pre = p;
                    }
                    
                }
            }
            else
            {
                if(t->val == 1)
                {
                    if(t->keys.size() == 1)
                    {
                        if(head_ == tail_)
                        {
                            head_ = nullptr;
                            tail_ = nullptr;
                        }
                        else
                        {
                            tail_ = t->next;
                            t->next->pre = nullptr;
                        }
                        
                        delete t;
                    }
                    else
                    {
                        t->keys.erase(key);
                    }

                    um_.erase(key);
                }
                else
                {
                    if(t->keys.size() == 1)
                    {
                        t->val--;
                    }
                    else
                    {
                        LinkList* p = new LinkList(t->val - 1);
                        p->keys.insert(key);
                        um_[key]=p;

                        p->next = t;
                        t->pre = p;
                        tail_ = p;
                    }
                }
            }
        }
    }
    
    /** Returns one of the keys with maximal value. */
    string getMaxKey() {
        if(head_ != nullptr)
        {
            return *(head_->keys.begin());
        }

        return "";
    }
    
    /** Returns one of the keys with Minimal value. */
    string getMinKey() {
        if(tail_ != nullptr)
        {
            return *(tail_->keys.begin());
        }

        return "";
    }

    unordered_map<string,LinkList*> um_;
    LinkList* head_,*tail_;
};

int main()
{
    AllOne obj;
    obj.inc("hello");
    obj.inc("world");
    obj.inc("leet");
    obj.inc("code");
    obj.inc("DS");
    obj.inc("leet");
    printf("%s\n",obj.getMaxKey().c_str());
    obj.inc("DS");
    obj.dec("leet");
    printf("%s\n",obj.getMaxKey().c_str());
    obj.dec("DS");
    obj.inc("hello");
    printf("%s\n",obj.getMaxKey().c_str());

    obj.inc("hello");
    obj.inc("hello");
    obj.dec("world");
    obj.dec("leet");
    obj.dec("code");
    obj.dec("DS");
    printf("%s\n",obj.getMaxKey().c_str());
printf("mn:%s\n",obj.getMinKey().c_str());
    obj.inc("new");
printf("%s\n",obj.getMinKey().c_str());
    obj.inc("new");
    obj.inc("new");
    obj.inc("new");
    obj.inc("new");
    obj.inc("new");
   printf("%s\n",obj.getMaxKey().c_str()); 
printf("%s\n",obj.getMinKey().c_str());
    return 0;
}