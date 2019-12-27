//1026. 节点与其祖先之间的最大差值

#include <cstdio>
#include <limits.h>
#include <vector>
#include <algorithm>

using namespace std;


 //Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

pair<int,int> maxAncestorDiff(TreeNode* root,int& maxAncestor)
{
    if(root == nullptr)
    {
        return {INT_MAX,INT_MIN};
    }

    pair<int,int> left = maxAncestorDiff(root->left,maxAncestor);
    pair<int,int> right = maxAncestorDiff(root->right,maxAncestor);
    int mn = min(left.first,right.first);
    int mx = max(left.second,right.second);
    if(mn != INT_MAX)
    {
        maxAncestor = max(maxAncestor,abs(root->val - mn));
    }

    if(mx != INT_MIN)
    {
        maxAncestor = max(maxAncestor,abs(root->val - mx));
    }

    return {min(mn,root->val),max(mx,root->val)};
}

int maxAncestorDiff(TreeNode* root) {
    //思路：递归，每个节点与其最小的子节点的差肯定是最大的
    //这个不一定，题目中是绝对值，所以还要看子节点的最大值

    int res = 0;
    maxAncestorDiff(root,res);
    return res;
}

int main()
{
    TreeNode* root = new TreeNode(8);
    root->left = new TreeNode(3);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(6);
    root->left->right->left = new TreeNode(4);
    root->left->right->right = new TreeNode(7);
    root->right = new TreeNode(10);
    root->right->right = new TreeNode(14);
    root->right->right->left = new TreeNode(13);

    printf("%d\n",maxAncestorDiff(root));
    return 0;
}