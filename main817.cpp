//leetcode 817. 链表组件

#include <cstdio>
#include <vector>
#include <set>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

int numComponents(ListNode* head, vector<int>& G) {
    //思路：G可能是乱序的
    //可以记录节点的下一个节点，然后遍历G，一个一个的查找
    //可以使用set来存储G中的元素提高查找效率

    set<int> gset;
    for(auto a : G)
    {
        gset.insert(a);
    }

    bool start = false;
    int res = 0;
    ListNode* tmp = head;
    while(tmp != nullptr)
    {
        //set查找可以优化，使用哈希表
        if(gset.find(tmp->val) != gset.end())
        {
            if(!start)
            {
                start = true;
            }
        }
        else
        {
            if(start)
            {
                start =false;
                ++res;
            }
        }

        tmp = tmp->next;
    }

    if(start)
    {
        ++res;
    }

    return res;
}

int main()
{
    vector<int> v = {1,2,3,4};
    v = {0,1,2,3,4};
    ListNode* head = new ListNode(v[0]);
    ListNode* tmp = head;
    for(int i=1;i<v.size();++i)
    {
        tmp->next = new ListNode(v[i]);
        tmp = tmp->next;
    }

    vector<int> G = {1,2,4};
    G = {0,3,1,4};
    printf("%d\n",numComponents(head,G));
    return 0;
}
