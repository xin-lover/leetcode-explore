//1019. 链表中的下一个更大节点

#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
 

vector<int> nextLargerNodes(ListNode* head) {
    //思路：其实就是找递减最大值序列，也就是说后面如果有一个值大于当前的最大值
    //那么直接更新最大值，前面的n个节点的后续最大值都是这个值
    //所以使用栈来解决，存储一个递减序列
    //是更大值，不是最大值
    //那就还是递减栈,但在本题中因为是最靠近的更大值，所以我们如果遇到一个更大值的时候，如何分辨之前是否已经遇到一个更大值了？
    //一个做法就是把遍历的序号入栈，遇到更大值就出栈

    ListNode* tmp = head;
    vector<int> res;
    while(tmp != nullptr)
    {
        res.push_back(tmp->val);
        tmp = tmp->next;
    }

    stack<int> sk;
    for(int i=0;i<res.size();++i)
    {
        while(!sk.empty() && res[i] > res[sk.top()])
        {
            auto p = sk.top();
            sk.pop();
            res[p]=res[i];
        }

        sk.push(i);
    }

    while(!sk.empty())
    {
        auto p = sk.top();
        sk.pop();
        res[p]=0;
    }
    
    return res;
}

ListNode* createList(vector<int> v)
{
    ListNode* head = new ListNode(v[0]);
    ListNode* tmp = head;
    for(int i=1;i<v.size();++i)
    {
        tmp->next = new ListNode(v[i]);
        tmp=tmp->next;
    }

    return head;
}

int main()
{
    ListNode* head = new ListNode(2);
    head->next = new ListNode(1);
    head->next->next = new ListNode(5); //5,5,0

    // head = new ListNode(2);
    // head->next = new ListNode(7);
    // head->next->next = new ListNode(4);
    // head->next->next->next = new ListNode(3);
    // head->next->next->next->next = new ListNode(5);//7,0,5,5,0

    head = createList({1,7,5,1,9,2,5,1});   //[7,9,9,9,0,5,0,0]

    auto res = nextLargerNodes(head);
    for(auto a : res)
    {
        printf("%d ",a);
    }
    printf("\n");

    return 0;
}