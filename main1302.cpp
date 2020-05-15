//1302. 层数最深叶子节点的和

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
 

int deepestLeavesSum(TreeNode* root) {
    //思路：层序遍历

    queue<TreeNode*> qu;
    qu.push(root);
    
    int sum =0;
    while(!qu.empty())
    {
        sum = 0;
        int sz = qu.size();
        for(int i=0;i<sz;++i)
        {
            TreeNode* tmp = qu.front();
            qu.pop();

            sum += tmp->val;
            if(tmp->left)
            {
                qu.push(tmp->left);
            }
            if(tmp->right)
            {
                qu.push(tmp->right);
            }
        }
    }

    return sum;
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
    vector<int> v = {1,2,3,4,5,-1000,6,7,-1000,-1000,-1000,-1000,8};
    TreeNode* root = createTree(v);
    printf("%d\n",deepestLeavesSum(root));
    return 0;
}