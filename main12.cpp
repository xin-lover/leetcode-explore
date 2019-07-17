#include <vector>
#include <cstdio>
#include <stack>

using namespace  std;

class TreeNode
{
    public:
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x):val(x),left(nullptr),right(nullptr)
    {

    }
};

void printTree(TreeNode *node)
{
    if(node == nullptr)
    {
        return;
    }

    stack<TreeNode*> sk;
    sk.push(node);

    printf("[");
    while(!sk.empty())
    {
        int n = sk.size();
        for(int i=0;i<n;++i)
        {
            TreeNode *n = sk.top();
            sk.pop();
            if(n == nullptr)
            {
                printf("null,");
            }
            else
            {
                printf("%d,",n->val);
                sk.push(n->left);
                sk.push(n->right);
            }
        }
    }
    printf("],");
}
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        if(n < 1)
        {
            return {};
        }
        //思路：分治，对于每一个序列，其结果由root和左右子树共同构成
        //解决问题的步骤就变为：确定root，然后确定左右子树即可
        //左子树由root左侧的数列确定，右子树由右侧的数确定，
        //递归求解即可
        return generateTrees(1,n);
    }
    
    vector<TreeNode*> generateTrees(int left,int right)
    {
        printf("left:%d right:%d\n",left,right);
        vector<TreeNode*> v;
        if(left == right)
        {
            v.push_back(new TreeNode(left));
            return v;
        }
        for(int i=left;i<=right;++i)
        {
            auto leftNodes = generateTrees(left,i-1);
            auto rightNodes = generateTrees(i+1,right);

            if(leftNodes.empty())
            {
                leftNodes.push_back(nullptr);
            }
            if(rightNodes.empty())
            {
                rightNodes.push_back(nullptr);
            }
            for(auto ln : leftNodes)
            {
                for(auto rn : rightNodes)
                {
                    TreeNode *node = new TreeNode(i);
                    node->left = ln;
                    node->right = rn;
                    v.push_back(node);
                }
            }
        }
        
        for(auto jj:v)
        {
            printTree(jj);
            printf("\n");
        }
        return v;
    }
    
    void insert(TreeNode* root,TreeNode *node)
    {
        if(node->val < root->val)
        {
            if(root->left == nullptr)
            {
                root->left = node;
            }
            else
            {
                insert(root->left,root);
            }
        }
        else
        {
            if(root->right == nullptr)
            {
                root->right = node;
            }
            else
            {
                insert(root->right,node);
            }
        }
    }
};


int main()
{
    Solution s;
    auto a = s.generateTrees(3);
    for(auto b : a)
    {
        printTree(b);
    }
    printf("\n");
    return 0;
}