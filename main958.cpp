//leetcode 958. 二叉树的完全性检验

#include <cstdio>
#include <queue>

using namespace std;

//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

bool isCompleteTree(TreeNode* root,int& h,bool& full) {
    if(root == nullptr)
    {
        h = 0;
        full = true;
        return true;
    }

    int lh,rh;
    bool lf,rf;
    if(!isCompleteTree(root->left,lh,lf) || !isCompleteTree(root->right,rh,rf))
    {
        return false;
    }

    if(lh > rh + 1 || rh > lh || (lh == rh && !lf))
    {
        printf("node: %d lh:%d rh:%d\n",root->val,lh,rh);
        return false;
    }

    if(root->val == 1)
    {
        printf("lh:%d rh:%d\n",lh,rh);
        printf(lf ? "left full\n" : "left not full\n");
        printf(rf ? "right full\n" : "right not full\n");
    }
    full = ((lf && rf) && (lh == rh));
    h = 1 + lh;

    return true;
}

bool isCompleteTree(TreeNode* root) {
    //思路：树的解决方案都优先使用递归，完全二叉树的子树也是完全二叉树，
    //不过这里要保证右侧的满二叉树儿子第h-1层是满的
    //一种方案就是看左右层高,一种就是看孩子数量和层高

    int h;
    bool full;
    return isCompleteTree(root,h,full);
}

bool isCompleteTree2(TreeNode* root) {
    //思路：满二叉树的特性，儿子节点的编号是2*i和2*i+1;

    queue<pair<TreeNode*,int>> qu;
    qu.push({root,1});

    int count=0;
    // int seq = 1;
    while(!qu.empty())
    {
        int sz = qu.size();
        for(int i=0;i<sz;++i)
        {
            pair<TreeNode*,int> tmp = qu.front();
            qu.pop();

            if(tmp.first != nullptr)
            {
                ++count;
                if(count != tmp.second)
                {
                    return false;
                }
                // seq = tmp.second;
                qu.push({tmp.first->left,2 * tmp.second});
                qu.push({tmp.first->right, 2 * tmp.second + 1});
            }
        }
    }

    return true;// count == seq;
}

int main()
{
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    // root->right->right= new TreeNode(7);
    // root->left->left->left= new TreeNode(7);

    printf(isCompleteTree2(root) ? "true\n" : "false\n");
    return 0;
}