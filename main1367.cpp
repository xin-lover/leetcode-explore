//1367. 二叉树中的列表

#include <cstdio>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


bool isSubPath2(ListNode* head, TreeNode* root) {
    //以root开始的子路径
    if(head == nullptr)
    {
        return true;
    }

    if(root == nullptr)
    {
        return false;
    }

    if(head->val == root->val)
    {
        return isSubPath2(head->next,root->left) || isSubPath2(head->next,root->right);
    }

    return false;
}

bool isSubPath(ListNode* head, TreeNode* root) {
    //思路：二叉树每个节点有两个选择，不能把所有结果都求出来比对
    //同时遍历求解，也就是前面的节点不符合就放弃
    //对于树，可以使用递归

    //使用深度或广度遍历确定head->val==root->val的节点
    stack<TreeNode*> sk;
    TreeNode* tmp = root;
    while(!sk.empty() || tmp != nullptr)
    {
        while(tmp != nullptr)
        {
            sk.push(tmp);
            tmp=tmp->left;
        }

        if(!sk.empty())
        {
            tmp = sk.top();
            sk.pop();

            if(tmp->val == head->val) //不用判断也行
            {
                if(isSubPath2(head,tmp))
                {
                    return true;
                }
            }

            tmp = tmp->right;
        }
    }

    return false;

    //不用栈的递归
    // if (root == NULL) return false;
    //     return isSubPath2(head, root) || isSubPath(head, root->left) || isSubPath(head, root->right);
}

TreeNode* createTree(const vector<int>& v)
{
    queue<TreeNode*> qu;
    if(v.empty())
    {
        return nullptr;
    }

    TreeNode* t = new TreeNode(v.front());
    qu.push(t);
    int i=1;
    while(!qu.empty() && i<v.size())
    {
        TreeNode* parent = qu.front();
        qu.pop();

        if(v[i] > -1000)
        {
            TreeNode* left = new TreeNode(v[i]);
            parent->left = left;
            qu.push(left);
        }
        ++i;
        if(v[i] > -1000)
        {
            TreeNode* right = new TreeNode(v[i]);
            parent->right = right;
            qu.push(right);
        }
        ++i;

    }

    return t;
}

ListNode* createList(const vector<int>& nums)
{
    if(nums.empty())
    {
        return nullptr;
    }

    ListNode* head = new ListNode(nums[0]);
     ListNode* pre = head;
    for(int i=1;i<nums.size();++i)
    {
        ListNode* tmp = new ListNode(nums[i]);
        pre->next = tmp;
        pre = tmp;
    }

    return head;
}

int main()
{
    vector<int> headNums = {4,2,8}, rootNums = {1,4,4,-1000,2,2,-1000,1,-1000,6,8,-1000,-1000,-1000,-1000,1,3}; //true

    headNums = {1,4,2,6,8}, rootNums = {1,4,4,-1000,2,2,-1000,1,-1000,6,8,-1000,-1000,-1000,-1000,1,3};
    ListNode* head=  createList(headNums);
    TreeNode* root = createTree(rootNums);

    printf(isSubPath(head,root) ? "true\n" : "false\n");

    return 0;
}