//leetcode 919. 完全二叉树插入器

#include<cstdio>
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
 
class CBTInserter {
public:
    CBTInserter(TreeNode* root) {
        //思路：就是构建完全二叉树，主要是快速查找的插入点，如果使用遍历，那就很慢
        //完全二叉树是可以使用数组来存的，所以一开始就构建一个node的数组，通过下标可以快速知道父节点

        nodes_.push_back(nullptr);  //父节点放在1位置
        if(root)
        {
            queue<TreeNode*> qu;
            qu.push(root);

            while(!qu.empty())
            {
                TreeNode *t = qu.front();
                qu.pop();

                nodes_.push_back(t);
                if(t->left)
                {
                    qu.push(t->left);
                }

                if(t->right)
                {
                    qu.push(t->right);
                }
            }
        }
    }
    
    int insert(int v) {

        TreeNode* tmp = new TreeNode(v);
        nodes_.push_back(tmp);
        int sz = nodes_.size();
        if(sz == 2)
        {
            return v;
        }

        int parentIndex = (sz-1) / 2;
        if((sz-1) & 1)
        {
            nodes_[parentIndex]->right = tmp;
        } 
        else
        {
            nodes_[parentIndex]->left = tmp;
        }

        return nodes_[parentIndex]->val;
    }
    
    TreeNode* get_root() {
        return nodes_.size() == 1 ? nullptr : nodes_[1];
    }

    vector<TreeNode*> nodes_;
};

void PrintTree(TreeNode* node)
{
    if(node)
    {
        printf("%d ",node->val);
        PrintTree(node->left);
        PrintTree(node->right);
    }
}


//另一种思路：维护一个双端队列，只存储不满的二叉树，然后插入的新节点入队，同时作为队列最前端节点的儿子，如果最前端的节点已满，则出对
//这里空间复杂度都是O(N)，双端队列需要两个指针，所以双端队列存储的节点少，但需要双倍的空间，所以和存储所有节点相比差不多，甚至更高

int main()
{
    TreeNode* root = new TreeNode(1);
    CBTInserter cb(root);
    cb.insert(2);

    TreeNode* res = cb.get_root();
    PrintTree(res);
    printf("\n");
    return 0;
}