//leetcode 623. 在二叉树中增加一行

#include <cstdio>
#include <queue>

using namespace std;

 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

TreeNode* addOneRow(TreeNode* root, int v, int d) {

    //首先要确定层上的节点，然后就是接入了
    //使用层序遍历

    if(d <= 0)
    {
        return root;
    }

    if(d == 1)
    {
        TreeNode* t = new TreeNode(v);
        t->left = root;
        return t;
    }

    queue<TreeNode*> qu;
    qu.push(root);

    int h = 1;
    while(!qu.empty())
    {
        if(h == d - 1)
        {
            printf("get\n");
            int n = qu.size();
            for(int i=0;i<n;++i)
            {
                TreeNode *t = qu.front();
                printf("t:%d\n",t->val);
                qu.pop();

                TreeNode* node = new TreeNode(v);
                if(t->left)
                {
                    node->left = t->left;
 
                }
                t->left = node;

                node = new TreeNode(v);
                if(t->right)
                {
                    node->right = t->right;
                }
                t->right = node;
            }
        }
        else
        {
            printf("nnn\n");
            int n = qu.size();
            for(int i=0;i<n;++i)
            {
                TreeNode* t = qu.front();
                qu.pop();

                if(t->left)
                {
                    qu.push(t->left);
                }

                if(t->right)
                {
                    qu.push(t->right);
                }
            }
            ++h;
        }
    }

    return root;
}

void printNode(TreeNode* node)
{
    if(node == nullptr)
    {
        return;
    }
    printf("%d ",node->val);
    printNode(node->left);
    printNode(node->right);
}
 
int main()
{
    TreeNode* node4 = new TreeNode(4);
    TreeNode* node2 = new TreeNode(2);
    TreeNode* node3 = new TreeNode(3);
    TreeNode* node1 = new TreeNode(1);

    node1->left = node2;
    node1->right= node3;
    node3->left = node4;

    TreeNode *node = addOneRow(node1,5,4);
    printNode(node);
    printf("\n");

    return 0;

}