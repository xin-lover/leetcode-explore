//1038. 从二叉搜索树到更大和树

#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* bstToGst(TreeNode* root) {
    //思路：二叉搜索树，树的问题优先递归
    //根据题意，有两种情况：
    //1.节点N为左儿子，最终值val(N)=节点右子树的值 +父节点值 + val(父节点)
    //2.节点N为右儿子,val(N) = 节点右子树的值 + （存在祖先M，是左子树)val(M)
    //所以这里递归的问题在于节点的值既依赖父节点又依赖子节点,没有办法往一个方向递归
    //另一种想法就是把二叉树变成一个数组，求出结果再给节点赋值
    //衍生的另一种方式就是，使用传统中序遍历是从数组的左边遍历到数组的右边，而现在需要的是右到左的遍历
    //所以修改一下遍历方式，先遍历右儿子

    stack<TreeNode*> sk;
    TreeNode* tmp = root;
    int sum =0;
    while(!sk.empty() || tmp != nullptr)
    {
        while(tmp != nullptr)
        {
            sk.push(tmp);
            tmp = tmp->right;
        }

        if(!sk.empty())
        {
            tmp = sk.top();
            sk.pop();
            sum += tmp->val;
            tmp->val = sum;
            tmp=tmp->left;
        }
    }

    return root;
}

void printTree(TreeNode* node)
{
    if(node != nullptr)
    {
        printTree(node->left);
        printf("%d ",node->val);
        printTree(node->right);
    }
}

int main()
{
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(1);
    root->right= new TreeNode(2);

    bstToGst(root);
    printTree(root);
    printf("\n");
    return 0;
}