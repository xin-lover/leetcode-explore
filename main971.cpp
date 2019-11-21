//leetcode 971. 翻转二叉树以匹配先序遍历

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

bool flipMatchVoyage(TreeNode* node,vector<int>& voyage,int& index,vector<int>& flipNodes)
{
    if(node == nullptr)
    {
        return true;
    }
    if(index>=voyage.size() || node->val != voyage[index])
    {
        return false;
    }

    ++index;
    if(node->left == nullptr && node->right == nullptr)
    {
        return true;
    }

    if(node->left != nullptr && node->right != nullptr && index < voyage.size() && node->left->val != voyage[index])
    {
        swap(node->left,node->right);
        flipNodes.push_back(node->val);
    }
    
    return flipMatchVoyage(node->left,voyage,index,flipNodes) && flipMatchVoyage(node->right,voyage,index,flipNodes);
}

vector<int> flipMatchVoyage(TreeNode* root, vector<int>& voyage) {
    //思路：树的问题，首先考虑递归，采用先序遍历，如果某个节点的顺序不是预期的，则交换左右子节点
    vector<int> res;
    int index = 0;
    if(!flipMatchVoyage(root,voyage,index,res))
    {
        return {-1};
    }
    return res;
}

int main()
{
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    
    // vector<int> voyage = {1,3,2}; //1
    vector<int> voyage = {1,2,3}; //[]
    // vector<int> voyage = {2,3}; //-1
    // vector<int> voyage = {1,3}; //[]

    vector<int> res = flipMatchVoyage(root,voyage);
    for(auto a : res)
    {
        printf("%d ",a);
    }
    printf("\n");
    return 0;
}