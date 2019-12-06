//998. 最大二叉树 II

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


TreeNode* insertIntoMaxTree(TreeNode* root, int val) {
    //思路：树的问题优先使用递归
    //根据题意，就是把val添加到root中，且保证root中树的根节点都大于树的所有儿子
    //直接递归就行
    //注意，这里隐含的条件是根据数组构建的，val附加到数组后面
    //如果以某个值为根，则左左子树由该值左边的数构建，右侧同理
    //所以，如果val<root->val,那么它应该加入到右子树,否则它为根

    if(root == nullptr)
    {
        TreeNode* node = new TreeNode(val);
        return node;
    }

    if(val > root->val)
    {
        TreeNode* node = new TreeNode(val);
        node->left = root;
        return node;
    }

    root->right = insertIntoMaxTree(root->right,val); 
    return root;
}

void printTree(TreeNode* node)
{
    if(node == nullptr)
    {
        return;
    }
    printf("%d ",node->val);
    printTree(node->left);
    printTree(node->right);
}
int main()
{
    // TreeNode* root = new TreeNode(4);
    // root->left = new TreeNode(1);
    // root->right= new TreeNode(3);
    // root->right->left = new TreeNode(2);

    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(2);
    root->right= new TreeNode(4);
    root->left->right= new TreeNode(1);

    root =insertIntoMaxTree(root,3);   
    printTree(root);
    printf("\n");
    return 0;

}