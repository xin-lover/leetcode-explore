//leetcode 889. 根据前序和后序遍历构造二叉树

#include <cstdio>
#include <vector>
#include <stack>

using namespace std;


// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post,int pre_left, int pre_right,int post_left,int post_right) {

    // printf("%d %d %d %d\n",pre_left,pre_right,post_left,post_right);
    if(pre_left > pre_right)
    {
        return nullptr;
    }

    if(pre_left == pre_right)
    {
        return new TreeNode(pre[pre_left]);
    }

    TreeNode* root = new TreeNode(pre[pre_left]);
    int v = pre[pre_left+1];
    int len = 0;
    for(int i=post_left;i<=post_right;++i)
    {
        if(post[i] == v)
        {
            len = i - post_left+1;
            break;
        }
    }

    root->left = constructFromPrePost(pre,post,pre_left+1,pre_left+len,post_left,post_left+len-1);
    root->right = constructFromPrePost(pre,post,pre_left+len+1,pre_right,post_left+len,post_right-1);

    return root;

}

TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
    //思路：之前做过前序和中序的，解法还是一样
    //不过，不同的是中序我们很好划分，后序如何划分？
    //可能有多个结果，比如有一个孩子为空，则哪个为空都一样
    //以前序遍历为指导，根据子树根在后续遍历中的位置来划分
    return constructFromPrePost(pre,post,0,pre.size()-1,0,post.size()-1);
}

void printTree(TreeNode* node)
{
    if(node != nullptr)
    {
        printf("%d ",node->val);
        printTree(node->left);
        printTree(node->right);
    }
}

//非递归法
TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
  if (pre.empty()) return NULL;
  stack<TreeNode*> S;
  auto root = new TreeNode(pre[0]);
  S.push(root);
  for (int i = 1, j = 0; i < pre.size(); i++) {
    auto node = new TreeNode(pre[i]);
    while (S.top()->val == post[j]) S.pop(), j++;  // 回溯
    if (!S.top()->left)
      S.top()->left = node;
    else
      S.top()->right = node;
    S.push(node);
  }
  return root;
}

int main()
{
// 输入：pre = [1,2,4,5,3,6,7], post = [4,5,2,6,7,3,1]
// 输出：[1,2,3,4,5,6,7]

    vector<int> pre = {1,2,4,5,3,6,7};
    vector<int> post = {4,5,2,6,7,3,1};
    TreeNode* res = constructFromPrePost(pre,post);
    printTree(res);
    printf("\n");
    return 0;

}