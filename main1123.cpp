//1123. 最深叶节点的最近公共祖先

#include<cstdio>
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

int lcaDeepestLeaves(TreeNode* root,int depth,int& maxdepth,TreeNode** res) {
    
    if(root == nullptr)
    {
        return 0;
    }

    int left = lcaDeepestLeaves(root->left,1+depth,maxdepth,res);
    int right = lcaDeepestLeaves(root->right,1+depth,maxdepth,res);
    int h = max(left,right);
    if(depth + h > maxdepth)
    {
        maxdepth = depth + h;
        *res = root;
    }

    if(left == right && depth + h == maxdepth)
    {
        *res = root;
    }

    return max(left,right) + 1;
}

TreeNode* lcaDeepestLeaves(TreeNode* root) {
    //思路：如果最大深度的节点只有一个，返回其本身
    //树问题，使用递归
    //树分高度和深度，因为会出现只有一个最大深度节点的情况，也就是返回的节点可能是叶子节点
    //所以我们在每个节点递归的时候要能统一判断
    //我们同时记录高度和深度，高度是到叶子节点的最大距离，深度是距离根节点最大的距离，一个节点的高度+深度就是这个节点最大深度的子节点的深度
    //我们就用它来判断

    //还能再简单点，就判断深度即可，如果左右深度相同，那么结果当然是当前节点，因为采用的是深度遍历，所以叶子节点的情况已经考虑到了
    // class Solution:
    // def lcaDeepestLeaves(self, root: TreeNode) -> TreeNode:
    //     return self.getDeep(root)[1]

    // def getDeep(self,root):
    //     if not root:
    //         return 0,None
    //     l,r = self.getDeep(root.left),self.getDeep(root.right)
    //     if l[0]==r[0]:
    //         fa = root
    //     elif l[0]<r[0]:
    //         fa = r[1]
    //     else:
    //         fa = l[1]
    //     return max(l[0],r[0])+1,fa

    TreeNode* res;
    int maxdepth = 0;
    lcaDeepestLeaves(root,0,maxdepth,&res);
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
    vector<int> v = {1,2,3,4};//4
    TreeNode* root = createTree(v);
    PrintTree(root);
    printf("\n");
    TreeNode* res = lcaDeepestLeaves(root);
    PrintTree(res);
    printf("\n");
    return 0;
}