//1448. 统计二叉树中好节点的数目

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;


//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

void traverse(TreeNode* node,int maxValue,int& count)
{
    if(!node)
    {
        return ;
    }

    if(node->val >= maxValue)
    {
        ++count;
    }

    int mx = max(node->val,maxValue);
    traverse(node->left,mx,count);
    traverse(node->right,mx,count);
}

int goodNodes(TreeNode* root) {
    //思路：根节点肯定是，对于其它节点，我们需要记录根节点到它的路径中的最大值
    //问题在于如何遍历和存储这些最大值,使用递归比较简单

    int res = 0;
    traverse(root,INT_MIN,res);

    return res;
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

int main()
{

    vector<int> nums = {3,1,4,3,-1000,1,5}; //4
    nums = {3,3,-1000,4,2};//3;
    TreeNode* root =createTree(nums);
    printf("%d\n",goodNodes(root));

    return 0;
}