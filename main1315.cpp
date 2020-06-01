//1315. 祖父节点值为偶数的节点和

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void trace(TreeNode* root,int& res)
{
    if(root == nullptr)
    {
        return;
    }

    if((root->val & 1) == 0)
    {
        if(root->left)
        {
            res += root->left->left ? root->left->left->val : 0;
            res += root->left->right ? root->left->right->val : 0;
        }   

        if(root->right)
        {
            res += root->right->left ? root->right->left->val : 0;
            res += root->right->right ? root->right->right->val : 0;
        }
    }

    trace(root->left,res);
    trace(root->right,res);
}

int sumEvenGrandparent(TreeNode* root) {
    //思路：树的问题，优先考虑递归
    //另一种思路就是满二叉树的思路，把二叉树层序遍历得到数组，然后可以快速得到祖父节点，但需要额外的空间，这种方案对差距更大的节点有优势
    int res = 0;
    trace(root,res);
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
    vector<int> nums = {6,7,8,2,7,1,3,9,-1000,1,4,-1000,-1000,-1000,5}; //18
    nums = {61,13,46,-1000,-1000,-1000,56,72}; //72
    TreeNode* root = createTree(nums);

    printf("%d\n",sumEvenGrandparent(root));
    return 0;
}