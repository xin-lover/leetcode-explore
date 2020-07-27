//1457. 二叉树中的伪回文路径

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
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


int pseudoPalindromicPaths (TreeNode* root) {
    //思路：因为拍断的是排列，所以统计字符数量即可
    //现在的问题就是遍历了，采用深度后序遍历即可

    int res = 0;
    vector<int> chs(9,0);

    TreeNode* tmp = root;
    stack<TreeNode*> sk;
    sk.push(nullptr);
    while(tmp || !sk.empty())
    {
        while(tmp)
        {
            sk.push(tmp);
            sk.push(tmp);   //push两次
            chs[tmp->val-1] ^= 1;
            tmp = tmp->left;
        }

        if(!sk.empty())
        {
            tmp = sk.top();
            sk.pop();

            while(tmp && tmp != sk.top())
            {
                if(!tmp->right && !tmp->left) //叶子节点
                {
                    int t = 0;
                    for(int i=0;i<chs.size();++i)
                    {
                        t+=chs[i];
                    }

                    if(t <= 1)
                    {
                        ++res;
                    }
                }

                chs[tmp->val-1] ^= 1;
                tmp = sk.top();
                sk.pop();
            }

            if(tmp)
            {
                tmp = tmp->right;
            }
            
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
    vector<int> nums = {2,3,1,3,1,-1000,1}; //2
    nums = {2,1,1,1,3,-1000,-1000,-1000,-1000,-1000,1};  //1
    // nums = {1}; //1
    TreeNode* root = createTree(nums);

    printf("%d\n",pseudoPalindromicPaths(root)); 

    return 0;

}