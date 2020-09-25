//25. K 个一组翻转链表

#include <cstdio>
#include <vector>

using namespace std;


//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


ListNode* reverseKGroup(ListNode* head, int k) {
    //思路：想想我们是如何反转整个链表的，记录两个节点，第一个是反转链表的头节点，一个是剩余的原链表的头节点
    //不断后者移动到前者的前面，然后更新
    //而现在题目加了一个k的长度，思路还是相同

    if(!head)
    {
        return nullptr;
    }
    if(k == 1)
    {
        return head;
    }
    int count = 1;
    ListNode* aHead = nullptr;
    ListNode* rHead = head->next;
    ListNode* nHead = head;
    nHead->next = nullptr;
    ListNode* curTail = nHead;
    ListNode* lastTail = nullptr;
    while(rHead)
    {
        ListNode* rNext = rHead->next;
        rHead->next = nHead;
        nHead = rHead;
        rHead = rNext;
        
        ++count;
        if(count == k)
        {
            if(!aHead)
            {
                aHead = nHead;
            }
            if(lastTail)
            {
                lastTail->next = nHead;
            }
            lastTail = curTail;

            count = 1;
            nHead = rHead;
            if(rHead)
            {
                rHead = rHead->next;
                nHead->next = nullptr;
            }
            curTail = nHead;
        }
    }

    //对于最后一部分处理，可以先统计处链表长度，也可以选择最后再翻转回来
    if(nHead)
    {
        rHead = nHead->next;
        curTail = nHead;
        while(rHead)
        {
            ListNode* rNext = rHead->next;
            rHead->next = nHead;
            nHead = rHead;
            rHead = rNext;
        }
        curTail->next = nullptr;

        if(!aHead)
        {
            aHead = nHead;
        }
        else
        {
            lastTail->next = nHead;
        }
    }

    return aHead;
}

int main()
{
    ListNode* node = new ListNode(1);
    auto tmp = node;
    for(int i=2;i<=2;++i)
    {
        ListNode* t = new ListNode(i);
        tmp->next = t;
        tmp = t;;
    }

    auto res = reverseKGroup(node,2); //2 1 4 3 5
    while(res)
    {
        printf("%d ",res->val);
        res = res->next;
    }
    printf("\n");

    return 0;
}