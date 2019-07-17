//leetcode 725. 分隔链表

#include <cstdio>
#include <vector>

using namespace std;

//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

vector<ListNode*> splitListToParts(ListNode* root, int k) {
    //思路：尽可能相等且前面比后面的长，
    //直观的做法就是求出长度，然后分割

    int len = 0;
    ListNode* t = root;
    while(t!=nullptr)
    {
        ++len;
        t = t->next;
    }

    int q = len / k;
    int r = len % k;

    vector<ListNode*> res;
    t = root;
    while(k-->0)
    {
        res.push_back(t);
        if(t != nullptr)
        {
            int c = q + (r-- > 0 ? 1 : 0);
            for(int i=0;i<c-1;++i)
            {
                t = t->next;
            }

            ListNode* pre = t;
            t = t->next;
            pre->next = nullptr;
        }
    } 

    return res;
}

int main()
{
    ListNode* root = new ListNode(1);
    ListNode* t = root;
    for(int i=2;i<=10;++i)
    {
        t->next = new ListNode(i);
        t = t->next;
    }
    

    vector<ListNode*> res = splitListToParts(root,3);
    for(auto a : res)
    {
        ListNode* t = a;
        while(t != nullptr)
        {
            printf("%d ",t->val);
            t = t->next;
        }
    
        printf("\n");
    }

    return 0;
}
