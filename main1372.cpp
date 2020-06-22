//1372. 二叉树中的最长交错路径

#include <cstdio>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

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

int longestZigZag(TreeNode* node,bool dir,int& maxLen,unordered_map<TreeNode*,vector<int>>& dp)
{
    if(!node)
    {
        return -1;
    }

    if(dp.find(node) == dp.end())
    {
        int left = longestZigZag(node->left,false,maxLen,dp);
        int right = longestZigZag(node->right,true,maxLen,dp);
        
        int childLeft = longestZigZag(node->left,true,maxLen,dp);
        int childRight = longestZigZag(node->right,false,maxLen,dp);

        dp.insert({node,{left,right,childLeft,childRight}});
    }

    int len = 1 + (dir ? dp[node][0] : dp[node][1]);
    maxLen= max(max(len,maxLen),max(dp[node][2],dp[node][3]));

    return len;
}

int longestZigZag(TreeNode* root) {
    //思路：采用递归即可
    //对于每个节点，有3个选择
    //1.根据父节点的选择确定下一个节点和方向
    //2.从该节点重新开始，这样可以有两个选择，选择左或右方向

    //超时，原因应该是重复遍历了，使用动归优化
    unordered_map<TreeNode*,vector<int>> um;
    int res = 0;
    longestZigZag(root,true,res,um);
    longestZigZag(root,false,res,um);

    return res;
}


int longestZigZag2(TreeNode* root,bool dir,int& maxLen) {

    if(!root)
    {
        return -1;
    }
    int leftPath = longestZigZag2(root->left,false,maxLen);
    int rightPath = longestZigZag2(root->right,true,maxLen);
    printf("%d %d %d %s\n",root->val,leftPath,rightPath,dir ? "true" : "false");

    maxLen = max(maxLen,1 + max(leftPath,rightPath));
    return 1 + (dir ? leftPath : rightPath);
}

int longestZigZag2(TreeNode* root) {
    //思路：上面的思路其实还可以优化
    //对于某个节点，它其实只有2种选择
    //1.选择左儿子
    //2.选择右儿子
    unordered_map<TreeNode*,vector<int>> um;
    int res = 0;
    int left = 1 + longestZigZag2(root->left,false,res);
    int right = 1 + longestZigZag2(root->right,true,res);

    return max(res,max(left,right));
}

int main()
{
    vector<int> nums = {1,-1000,2,3,4,-1000,-1000,5,6,-1000,7,-1000,-1000,-1000,8,-1000,9}; //3
    // nums = {1}; //0
    nums = {1,1,1,-1000,1,-1000,-1000,1,1,-1000,1}; //4
    printf("%d\n",longestZigZag2(createTree(nums)));

    return 0;
}