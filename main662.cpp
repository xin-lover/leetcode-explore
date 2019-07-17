//leetcode 662. 二叉树最大宽度

#include <cstdio>
#include <queue>
#include <cmath>

using namespace std;

 struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
  
int widthOfBinaryTree(TreeNode* root) {
    //思路：这个树可以理解为满二叉树，我们要求的是每一层第一个和最后一个非空节点间的节点数，空节点也算
    //按层序遍历的方法，使用队列记录节点，空节点也记录，计数时分空节点计数和非空节点计数，但空节点只有在两端都有非空节点时才算入总数内

    if(root == nullptr)
    {
        return 0;
    }

    queue<TreeNode*> qu;
    qu.push(root);

    int width = 0;
    while(!qu.empty())
    {
        int n = qu.size();
        int emptyCount = 0;
        int validCount = 0;

        bool haveValid = false;
        for(int i=0;i<n;++i)
        {
            TreeNode *t = qu.front();
            qu.pop();
            
            if(t == nullptr)
            {
                if(validCount > 0)
                {
                    ++emptyCount;
                }

                qu.push(nullptr);
                qu.push(nullptr);
            }
            else
            {
                ++validCount;
                if(validCount > 1)
                {
                    validCount+=emptyCount;
                }

                emptyCount= 0 ;

                qu.push(t->left);
                qu.push(t->right);

                haveValid |= (t->left || t->right);
            }
            
        }

        width = max(width,validCount);
        if(!haveValid)
        {
            break;
        }
    }

    return width;
}

void Traversing(TreeNode* node,long long seq,int height,vector<pair<long long,long long>>& flags)
{
    if(node != nullptr)
    {
        if(height > flags.size())
        {
            //注意要传入最大最小值
            flags.push_back({pow(2,height)-1,0});
        }

        flags[height-1].first = min(seq,flags[height-1].first);
        flags[height-1].second = max(seq,flags[height-1].second);

        Traversing(node->left,2*seq+1,height+1,flags);
        Traversing(node->right,seq*2+2,height+1,flags);
    }
}

int widthOfBinaryTree2(TreeNode* root) {
    //思路：满二叉树，假设父节点序号为i，则左儿子序号为2*i+1，右儿子为2*i+2；
    //记录每一层的最大序号和最小序号

    vector<pair<long long,long long>> flags;
    Traversing(root,0,1,flags);

    int width = 0;
    for(auto v : flags)
    {
        printf("%d %d\n",v.first,v.second);
        width = max(width,static_cast<int>(v.second-v.first+1));
    }

    return width;





}

int main()
{
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(6);

    printf("%d\n",widthOfBinaryTree2(root));
    return 0;
}