//leetcode 814. 二叉树剪枝

#include <cstdio>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// void pruneTree(TreeNode* node)
// {
//     if(node->val == 1)
//     {
//         return true;
//     }

//     return contain1(node->left) || contain1(node->right);
// }

TreeNode* pruneTree(TreeNode* root) {
    //思路：删除子树，则需要存储其父节点
    //策略：使用深度遍历（广度也行），判断左右节点是否都不包含1

    if(!root)
    {
        return nullptr;
    }

    TreeNode* left = pruneTree(root->left);
    TreeNode* right = pruneTree(root->right);

    if(!left && !right && root->val == 0)
    {
        delete root;
        return nullptr;
    }

    root->left = left;
    root->right = right;
    return root;

}

void printTree(TreeNode* root)
{
    if(!root){
        return ;
    }
    printTree(root->left);
    printf("%d ",root->val);
    printTree(root->right);
}

int main()
{
    TreeNode *root = new TreeNode(1);
    root->right = new TreeNode(0);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(0);

    TreeNode* t = pruneTree(root);
    printTree(t);
    return 0;
}