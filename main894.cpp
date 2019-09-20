//leetcode 894. 所有可能的满二叉树

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

vector<TreeNode*> allPossibleFBT(int N) {
    //思路: 根据定义，一个二叉树，其节点数量是奇数
    //策略：采用递归的方式，根节点占一个，剩余的节点构建左右二叉树
    //优化的点：有重复计算，可以使用动归
    //其实大的N对应的二叉树是小的N的二叉树组成的

    if((N & 1) == 0)
    {
        return {};
    }

    if(N == 1)
    {
        return {new TreeNode(0)};
    }
    
    vector<TreeNode*> res;
    for(int k=1;k<N;k+=2)
    {
        vector<TreeNode*> leftTrees = allPossibleFBT(k);
        vector<TreeNode*> rightTrees = allPossibleFBT(N-1-k);
        for(int i=0;i<leftTrees.size();++i)
        {
            for(int j=0;j<rightTrees.size();++j)
            {
                TreeNode* root = new TreeNode(0);
                root->left = leftTrees[i];
                root->right = rightTrees[j];

                res.push_back(root);
            }
        }
    }

    return res;
}

void printTree(TreeNode* node)
{
    if(node)
    {
        printf("%d ",node->val);
        printTree(node->left);
        printTree(node->right);
    }
}

vector<TreeNode*> allPossibleFBT2(int N, vector<vector<TreeNode*>>& dp)
{
    
    if(!dp[N].empty())
    {
        return dp[N];
    }

    if(N == 1)
    {
        dp[1] = {new TreeNode(0)};
    }
    else
    {
        // printf("N:%d\n",N);
        for(int i=1;i<N;i+=2)
        {
            vector<TreeNode*> leftTrees = allPossibleFBT2(i,dp);
            vector<TreeNode*> rightTrees = allPossibleFBT2(N-1-i,dp);

            for(int j=0;j<leftTrees.size();++j)
            {
                for(int k=0;k<rightTrees.size();++k)
                {
                    TreeNode* root = new TreeNode(0);
                    root->left = leftTrees[j];
                    root->right = rightTrees[k];

                    dp[N].push_back(root);
                }
            }
        }
    }

    return dp[N];

}
vector<TreeNode*> allPossibleFBT2(int N) {
    //动归

    if((N & 1)== 0)
    {
        return {};
    }
    vector<vector<TreeNode*>> dp(N+1);
    return allPossibleFBT2(N,dp);
}

int main()
{
    vector<TreeNode*> res = allPossibleFBT2(7);
    for(auto t : res)
    {
        printTree(t);
        printf("\n");
    }

    return 0;
}