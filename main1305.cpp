//1305. 两棵二叉搜索树中的所有元素

#include <cstdio>
#include <vector>
#include <stack>
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

void inorderTraversal(TreeNode* root,vector<int>& arr)
{
    if(root)
    {
        inorderTraversal(root->left,arr);
        arr.push_back(root->val);
        inorderTraversal(root->right,arr);
    }
}

vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
    //思路：最简单的思路就是遍历获取所有元素然后排序
    //但二叉搜索树自带顺序性，所以应该利用这个
    //二叉搜索树的中序遍历就是有序的，先遍历获取两个数组然后合并

    vector<int> res1;
    vector<int> res2;

    inorderTraversal(root1,res1);
    inorderTraversal(root2,res2);

    vector<int> res(res1.size()+res2.size());
    int p=0,p1=0,p2=0;
    while(p1<res1.size() && p2<res2.size())
    {
        if(res1[p1]<res2[p2])
        {
            res[p++] = res1[p1++];
        }
        else
        {
            res[p++] = res2[p2++];
        }
    }

    while(p1 < res1.size())
    {
        res[p++] = res1[p1++];
    }
    while(p2 < res2.size())
    {
        res[p++] = res2[p2++];
    }

    return res;
}

int main()
{
    vector<int> v1 = {2,1,4};
    v1 = {};
    vector<int> v2 = {1,0,3};

    vector<int> res = getAllElements(createTree(v1),createTree(v2));
    for(auto a : res)
    {
        printf("%d ",a);
    }
    printf("\n");
    return 0;
}