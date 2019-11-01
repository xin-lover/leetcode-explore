//leetcode 951. 翻转等价二叉树

#include <cstdio>
#include <vector>

using namespace std;


//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

bool flipEquiv(TreeNode* root1, TreeNode* root2) {
    //思路：一种是把树序列化，但在每个节点处都可能翻转，所以序列化结果会很多，可以先按一种规则翻转，比如左儿子小于等于右儿子，然后在序列化比较就可以
    //一种就是直接判断左右节点是否相等，使用递归，两种情况，满足一种即可

    if(root1 == nullptr && root2 == nullptr)
    {
        return true;
    }

    if(!(root1!=nullptr && root2!=nullptr && root1->val == root2->val))
    {
        return false;
    }

    return (flipEquiv(root1->left,root2->left) && flipEquiv(root1->right,root2->right))
     || (flipEquiv(root1->left,root2->right) && flipEquiv(root1->right,root2->left));
}

int main()
{
    TreeNode *root1=new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(3);
    root1->left->left = new TreeNode(4);
    root1->left->right = new TreeNode(5);
    root1->left->right->left = new TreeNode(7);
    root1->left->right->right = new TreeNode(8);
    root1->right->left = new TreeNode(6);

    TreeNode *root2 = new TreeNode(1);
    root2->left = new TreeNode(3);
    root2->left->right = new TreeNode(6);
    root2->right = new TreeNode(2);
    root2->right->left = new TreeNode(4);
    root2->right->right = new TreeNode(5);
    root2->right->right->left = new TreeNode(8);
    root2->right->right->right = new TreeNode(7);

    printf(flipEquiv(root1,root2) ? "true\n" : "false\n");
    return 0;

}