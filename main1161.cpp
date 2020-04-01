//1161. 最大层内元素和

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

int maxLevelSum(TreeNode* root) {
    //思路:就是层序遍历

    if(root == nullptr)
    {
        return 0;
    }

    queue<TreeNode*> qu;
    qu.push(root);
    int res = 1;
    int layer=0;   
    int sum = INT_MIN;
    while(!qu.empty())
    {
        int t = 0;
        int sz = qu.size();
        for(int i=0;i<sz;++i)
        {
            TreeNode * node = qu.front();
            qu.pop();
            t += node->val; 

            if(node->left != nullptr)
            {
                qu.push(node->left);
            }
            if(node->right != nullptr)
            {
                qu.push(node->right);
            }
        }

        ++layer;
        if(t > sum)
        {
            sum = t;
            res = layer;
        }
    }

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
    vector<int> v = {1,7,0,7,-8,-1000,-1000};
    TreeNode* root = createTree(v);
    printf("%d\n",maxLevelSum(root));//2
    return 0;
}