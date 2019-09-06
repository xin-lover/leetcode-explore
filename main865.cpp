//leetcode 865. 具有所有最深结点的最小子树

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

int findDeepest(TreeNode* node,int depth,int& maxDepth,TreeNode** target)
{
    if(node==nullptr)
    {
        return -1;
    }

    if(depth > maxDepth)
    {
        *target = node;
        maxDepth = depth;
    }

    int left = findDeepest(node->left,depth+1,maxDepth,target);
    int right = findDeepest(node->right,depth+1,maxDepth,target);

    if(left == right)
    {
        if(1 + left + depth == maxDepth)
        {
            *target = node;
        }
    }
    
    return 1 + max(left,right);
}

 
TreeNode* subtreeWithAllDeepest(TreeNode* root) {
    //思路：首先要找到所有最大深度的节点，然后找到这些节点的共同祖先节点
    //因为是二叉树，我们可以求左子树和右子树的最大深度，如果相同，则此节点是我们要求的节点
    //但遇到没有相同深度的时候，就判断不出来了

    TreeNode* res;
    int maxDepth = 0;
    findDeepest(root,0,maxDepth,&res);
    printf("height:%d\n",maxDepth);
    return res;
}


//其它思路：还是找最深的节点，遍历的时候记录当前节点的深度，如果左右节点相同，则返回当前node，否则返回深度大的那个
//但注意返回的不是当前node的左右孩子，而是深度最小的那个node（注意叶子节点的深度是1）；

int main()
{
    vector<int>  v= {3,5,1,6,2,0,8,1000,1000,7,4};
    // v = {0,2,1,1000,1000,3};
    
    queue<TreeNode*> qu;
    TreeNode* root = new TreeNode(v[0]);
    qu.push(root);

    TreeNode* target = nullptr;
    int i = 1;
    while(i < v.size())
    {
        TreeNode* cur = qu.front();
        qu.pop();
        if(i < v.size())
        {
            if(v[i] < 1000)
            {
                TreeNode* t = new TreeNode(v[i]);
                cur->left = t;
                qu.push(t);
            }
        }

        ++i;
        if(i < v.size())
        {
            if(v[i] < 1000)
            {
                TreeNode* t = new TreeNode(v[i]);
                cur->right = t;
                qu.push(t);
            }
        }
        ++i;
    }

    TreeNode* res = subtreeWithAllDeepest(root);
    printf("%d\n",res->val);
    return 0;
}