//1080. 根到叶路径上的不足节点

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

int sufficientSubset(TreeNode* node,int preSum,int limit)
{
    if(node == nullptr)
    {
        return 0;
    }

    int child = INT_MIN;
    if(node->left != nullptr)
    {
        int left = sufficientSubset(node->left,preSum+node->val,limit);
        if(preSum + node->val + left < limit)
        {
            delete node->left;
            node->left = nullptr;
        }
        child = max(child,left);
    }
    if(node->right != nullptr)
    {
        int right = sufficientSubset(node->right,preSum + node->val,limit);
        if(preSum + node->val + right < limit)
        {
            delete node->right;
            node->right = nullptr;
        }
        child = max(child,right);
    }

    return node->val + (child == INT_MIN ? 0 : child);
}

TreeNode* sufficientSubset(TreeNode* root, int limit) {
    //思路：树的问题优先递归，根到叶的路径，分为两段
    //根到当前节点，当前节点到叶子节点
    //要求所有的路径和都小于限定值的时候才删除
    //那么我们只需要找和最大的那条路径，它小于限定值那么就能删除了   

    if(sufficientSubset(root,0,limit) < limit)
    {
        delete root;
        root = nullptr;
    }

    return root;
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

void PrintTree(TreeNode* node)
{
    if(node != nullptr)
    {
        PrintTree(node->left);
        printf("%d ",node->val);
        PrintTree(node->right);
    }
}

int main()
{
    vector<int> v = {1,2,3,4,-99,-99,7,8,9,-99,-99,12,13,-99,14};
    TreeNode* root = createTree(v);
    // PrintTree(root);
    // printf("\n");
    // TreeNode* res = sufficientSubset(root,1);
    // PrintTree(res);
    // printf("\n");
    v = {5,4,8,11,-1000,17,4,7,1,-1000,-1000,5,3};
    v = {1,2,-3,-5,-1000,4,-1000};
    v = {10,5,10};
    root = createTree(v);
    TreeNode* res =sufficientSubset(root,21);
    PrintTree(res);
    printf("\n");
    return 0;
}