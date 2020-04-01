//1171. 从链表中删去总和值为零的连续节点

#include <cstdio>
#include <vector>
#include <unordered_map>

using namespace std;


//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* removeZeroSumSublists(ListNode* head) {
    //思路：还是使用前缀和的方式，如果存在两个点的总和一样，那么两点之间的和就是0
    //节点是0的要特殊处理一下，

    unordered_map<int,ListNode*> um;
    ListNode* tmp = head;
    ListNode* pre = nullptr;
    int sum = 0;
    while(tmp != nullptr)
    {
        sum += tmp->val;
        printf("sum:%d\n",sum);
        if(sum == 0)
        {
            head = tmp->next;
            um.clear();
        }
        else if(um.find(sum) != um.end() && um[sum] != nullptr)
        {
            //需要处理被删除后的情况，在该位置存储nullptr
            ListNode* del = um[sum]->next;
            int t = sum;
            while(del != tmp->next)
            {
                t += del->val;
                if(um.find(t) != um.end() && um[t] == del)
                {
                    um[t] = nullptr;
                }
                del = del->next;
            }

            um[sum]->next = tmp->next;

        }
        else
        {
            um[sum] = tmp;
        }

        tmp = tmp->next;
    }

    return head;
}

int main()
{
    vector<int> v = {1,2,3,-3,4};
    v = {0,1,2,2};
    // v = {1,3,2,-3,-2,5,5,-5,1};
    v = {1,-1,1};
    ListNode* root = new ListNode(v[0]);
    ListNode* tmp = root;
    for(int i=1;i<v.size();++i)
    {
        tmp->next = new ListNode(v[i]);
        tmp = tmp->next;
    }

    ListNode* res = removeZeroSumSublists(root);
    while(res != nullptr)
    {
        printf("%d ",res->val);
        res = res->next;
    }
    printf("\n");
    return 0;
    
}