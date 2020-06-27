//1382. 将二叉搜索树变平衡

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

TreeNode* leftRotate(TreeNode* node)
{
    //左旋转,以右孩子为轴
    TreeNode* tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;

    return tmp;
}

TreeNode* rightRotate(TreeNode* node)
{
    //右旋转,以左孩子为轴
    TreeNode* tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;

    return tmp;
}

// pair<int,int> dfs(TreeNode* node,int leftRight,TreeNode** newRoot)
// {
//     if(!node)
//     {
//         return {-1,-1};
//     }

//     auto leftPath= dfs(node->left,1,&(node->left));
//     auto rightPath = dfs(node->right,-1,&(node->right));

//     *newRoot = node;
//     int left = max(leftPath.first,leftPath.second);
//     int right = max(rightPath.first,rightPath.second);
//     if(left - right > 1)
//     {
//         if(leftPath.first >= leftPath.second)
//         {
//             node->left = rightRotate(node->left);
//         }
//         else if(leftPath.second )
        
//     }
//     else if(right-left > 1)
//     {
//         *newRoot = leftRotate(node);
//         ++left;
//         --right;
//     }
    
//     //因为递归，所以左右两个字树在本次旋转之前各自是平衡的，
//     return {left+1,right+1};
// }

void printTree(TreeNode* root)
{
    if(!root){
        return ;
    }
    printTree(root->left);
    printf("%d ",root->val);
    printTree(root->right);
}

void getPreOrder(TreeNode* node,vector<int>& nums)
{
    if(!node)
    {
        return;
    }

    getPreOrder(node->left,nums);
    nums.push_back(node->val);
    getPreOrder(node->right,nums);
}

TreeNode* build(vector<int>& nums,int left,int right)
{
    if(left > right)
    {
        return nullptr;
    }
    int mid = left + (right-left)/2;
    TreeNode* node = new TreeNode(nums[mid]);
    node->left = build(nums,left,mid-1);
    node->right = build(nums,mid+1,right);

    return node;
}

TreeNode* balanceBST(TreeNode* root) {
    //最简单的思路：纯粹重新构建，也就是遍历所有的值然后构建一个新的二叉树
    //递归思路：具体到某个节点后，也就是左孩子和右孩子的高度差大于1
    //对于这种情况，简单的旋转不能解决问题，因为插入构建时只会在插入的子树中出现一个不平衡点
    //而且这个不平衡点高度差只可能到2，所以旋转可以解决
    //但现在左右子树的高度差可能超过2，旋转之后，新的子树可能还不平衡
    //所以重点是如何处理左右孩子高度差超过2的情况
    //如果我们用旋转，平衡了一侧的子树后，还是会引入新的不平衡，也就是说把原来构建的平衡又打破，
    //所以这种思路进入了死胡同，还不如重新构建
    //如果不想重新创建节点，还是使用原树的节点，那么可以遍历之后把这些节点存储下来，然后使用这些节点构建
    //和重新构建差不多

    //还是重新构建
    vector<int> nums;
    getPreOrder(root,nums);

    return build(nums,0,nums.size()-1);
}

int main()
{
    vector<int> nums = {1,-1000,2,-1000,3,-1000,4,-1000,-1000};
    nums = {19,10,-1000,4,17,-1000,5};
    nums = {1,-1000,15,14,17,7,-1000,-1000,-1000,2,12,-1000,3,9,-1000,-1000,-1000,-1000,11};
    TreeNode* root = createTree(nums);
    root = balanceBST(root);
    printf("root:%d\n",root->val);
    printf("left:%d\n",root->left->val);
    // printf("left left:%d\n",root->left->left->val);
    printTree(root);
    printf("\n");
    return 0;
}
