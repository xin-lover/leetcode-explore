//1325. 删除给定值的叶子节点

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

void printTree(TreeNode* t)
{
    if(t != nullptr)
    {
        printf("%d ",t->val);
        printTree(t->left);
        printTree(t->right);
    }

}

bool postOrderRemove(TreeNode* node,TreeNode* parent, int target)
{
    if(node)
    {
        postOrderRemove(node->left,node,target);
        postOrderRemove(node->right,node,target);

        if(!node->left && !node->right && node->val == target)
        {
            if(parent)
            {
                if(parent->left == node)
                {
                    parent->left = nullptr;
                }
                else
                {
                    parent->right = nullptr;
                }
            }

            delete node;
            return true;
        }

    }

    return false;
}

TreeNode* removeLeafNodes(TreeNode* root, int target) {
    //思路：这个用后序遍历即可,但因为涉及删除
    //也就是说要记录父节点，而根节点又没有父节点，所以还要处理这种情况
    if(postOrderRemove(root,nullptr,target))
    {
        return nullptr;
    }

    return root;
}

//写法简单明了。。。。。
TreeNode* removeLeafNodes2(TreeNode* root,int target)
{
    if (!root) {
        return nullptr;
    }
    root->left = removeLeafNodes(root->left, target);
    root->right = removeLeafNodes(root->right, target);
    if (!root->left && !root->right && root->val == target) {
        return nullptr;
    }
    return root;
}

int main()
{
    vector<int> nums= {1,2,3,2,-1000,2,4};
    int target = 2; //1,3,4

    nums = {1,3,3,3,2};
    target = 3; //1,3,2

    nums = {1,1,1};
    target = 1;

    auto res = removeLeafNodes(createTree(nums),target);
    printTree(res);
    printf("\n");
    return 0;
}
