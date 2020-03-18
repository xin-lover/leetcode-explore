//1145. 二叉树着色游戏

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

int nodeCount(TreeNode* node,int n,int x,bool& res)
{
    if(node == nullptr)
    {
        return 0;
    }
    int leftCount = nodeCount(node->left,n,x,res);
    int rightCount = nodeCount(node->right,n,x,res);

    int cc = leftCount + rightCount + 1;
    if(node->val == x)
    {
        if(n - cc > cc)
        {
            res = true;
        }
        if(n - leftCount < leftCount)
        {
            res = true;
        }
        if(n - rightCount < rightCount)
        {
            res = true;
        }
    }

    return cc;
}
bool btreeGameWinningMove(TreeNode* root, int n, int x) {
    //思路：可以简单的理解哪个子树节点多我就选哪个，因为只要把父节点一选
    //另一个人是无法蔓延过来的，所以现在的问题就变为看第一个人选的节点树的元素数量
    //这里面需要处理两种情况
    //1.2号玩家选取x的子节点；那么只要x有一个子树超过半数，返回true；
    //2.2号玩家选取x的父节点，那么只要x的节点不超过半数，返回true

    bool res =false;
    nodeCount(root,n,x,res);
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

void PrintTree(TreeNode* node)
{
    if(node != nullptr)
    {
        PrintTree(node->left);
        printf("%d ",node->val);
        PrintTree(node->right);
    }
}


int main()
{
    vector<int> a = {1,2,3,4,5,6,7,8,9,10,11};
    TreeNode* root = createTree(a);

    printf(btreeGameWinningMove(root,11,1) ? "true\n" : "false\n");
    return 0;
}
 

    //        6
    //     3
    // 7      4
    //           2
    //              1
    //                 5