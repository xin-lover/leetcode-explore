//1379. 找出克隆二叉树中的相同节点

#include <cstdio>
#include <vector>
#include <queue>
#include <stack>

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

TreeNode* getTargetCopy(TreeNode* original, TreeNode* cloned, TreeNode* target) {
    //思路：同步遍历两颗树，在原树中查找到target节点，返回clone位置的节点
    //遍历使用dfs或bfs都可以

    stack<TreeNode*> sk1,sk2;
    TreeNode* tmp1 = original,*tmp2 = cloned;

    while(!sk1.empty() || tmp1 != nullptr)
    {
        while(tmp1 != nullptr)
        {
            sk1.push(tmp1);
            sk2.push(tmp2);

            tmp1 = tmp1->left;
            tmp2 = tmp2->left;
        }

        if(!sk1.empty())
        {
            tmp1 = sk1.top();
            sk1.pop();
            tmp2 = sk2.top();
            sk2.pop();

            if(tmp1 == target)
            {
                return tmp2;
            }

            tmp1 = tmp1->right;
            tmp2 = tmp2->right;
        }
    }

    return nullptr;
}

int main()
{
    vector<int> tree = {7,4,3,-1000,-1000,6,19};
    int target = 3;
    TreeNode* root1 = createTree(tree);
    TreeNode* root2 = createTree(tree);

    TreeNode* res = getTargetCopy(root1,root2,root1);
    printf("%d\n",res->val);
    return 0;
}