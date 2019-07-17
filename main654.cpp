//leetcode 654. 最大二叉树

#include <cstdio>
#include <vector>

using namespace std;

struct  TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x):val(x),left(nullptr),right(nullptr){}
};

TreeNode* constructMaximumBinaryTree(vector<int>& nums,int start,int end)
{
    if(start > end)
    {
        return nullptr;   
    }
    if(start == end)
    {
        return new TreeNode(nums[start]);
    }

    //找取最大值
    int pos = start;
    for(int i=start;i<=end;++i)
    {
        if(nums[i] > nums[pos])
        {
            pos = i;
        }
    }

    TreeNode* root = new TreeNode(nums[pos]);
    root->left = constructMaximumBinaryTree(nums,start,pos-1);
    root->right = constructMaximumBinaryTree(nums,pos+1,end);

    return root;
}

TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
    
    //思路：递归构造
    return constructMaximumBinaryTree(nums,0,nums.size()-1);
}

void printTree(TreeNode* t)
{
    if(t != nullptr)
    {
        printf("%d ",t->val);
        printTree(t->left);
        printTree(t->right);
    }

}

int main()
{
    vector<int> v = {3,2,1,6,0,5};
    TreeNode* r = constructMaximumBinaryTree(v);
    printTree(r);
    printf("\n");
    return 0;
}