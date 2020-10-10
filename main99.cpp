//99. 恢复二叉搜索树

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
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

void recoverTree(TreeNode* root) {
    //思路：根据提示，用O(n)的方式做
    //先中序遍历获得数组，然后找到两个逆序的位置交换

    stack<TreeNode*> sk;
    vector<TreeNode*> arr;

    TreeNode* tmp = root;
    while(tmp || !sk.empty())
    {
        while(tmp)
        {
            sk.push(tmp);
            tmp=tmp->left;
        }

        if(!sk.empty())
        {
            tmp = sk.top();
            sk.pop();

            arr.push_back(tmp);

            tmp = tmp->right;
        }
    }

    //有序数组中交换任意两个数的结果是，两个逆序，第一个逆序的较大值，第二个是较小值
    int first=-1,second=-1;
    for(int i=1;i<arr.size();++i)
    {
        if(arr[i-1]->val > arr[i]->val)
        {
            if(first == -1)
            {
                first = i-1;
            }
            else
            {
                second = i;
                break;
            }
        }
    }

    if(second == -1)
    {
        second = first+1;
    }
    int t = arr[first]->val;
    arr[first]->val = arr[second]->val;
    arr[second]->val = t;
}

void recoverTree2(TreeNode* root) {
    //思路：使用常数空间，那我们只能在遍历过程中记录逆序的节点
    //逆序的节点肯定是右节点小于其父节点，左节点大于其父节点
    //这样我们需要记录其父节点，因为是中序遍历,使用栈的话，在出栈的时候时候有右节点能知道，但左节点不清楚
    //但这里有个问题，栈不算空间吗？先不考虑这个，左节点在压栈的时候记录即可

    stack<TreeNode*> sk;
    TreeNode* tmp = root;

    TreeNode* first=nullptr,*second=nullptr,*firstOther=nullptr;
    TreeNode* cur = nullptr,*curParent=nullptr;
    while((tmp || !sk.empty()) && (!first || !second))
    {
        while(tmp)
        {
            sk.push(tmp);
            tmp=tmp->left;
        }

        if(!sk.empty())
        {
            tmp = sk.top();
            sk.pop();

            curParent = cur;
            cur = tmp;
            if(curParent && cur->val < curParent->val)
            {
                if(first == nullptr)
                {
                    first = curParent;
                    firstOther = cur;
                }
                else
                {
                    second = cur;
                    int t = first->val;
                    first->val = second->val;
                    second->val = t;
                    return;
                }
            }
            tmp = tmp->right;
        }
    }

    if(!second)
    {
        second = firstOther;
        int t = first->val;
        first->val = second->val;
        second->val = t;
    }
}

//栈空间是O(H)的复杂度，H是树的高度，使用morris方式
//记录当前节点的左子树的最右儿子节点，也就是中序遍历x的前驱节点，pre
//这样遍历的时候pre的右节点为空，那么将其指向x，再次访问x的左节点，否则表示左节点遍历完成。。。。
//也就是遍历了两次

// Morris 遍历算法整体步骤如下（假设当前遍历到的节点为 xx）：

// 1.如果 xx 无左孩子，则访问 xx 的右孩子，即 x = x.\textit{right}x=x.right。
// 2.如果 xx 有左孩子，则找到 xx 左子树上最右的节点（即左子树中序遍历的最后一个节点，xx 在中序遍历中的前驱节点），我们记为predecessor。根据 predecessor 的右孩子是否为空，进行如下操作。
//   1)如果 predecessor 的右孩子为空，则将其右孩子指向 xx，然后访问 xx 的左孩子，即 x = x.left。
//   2)如果 predecessor 的右孩子不为空，则此时其右孩子指向 xx，说明我们已经遍历完 xx 的左子树，我们将 predecessor 的右孩子置空，然后访问 xx 的右孩子，即 x = x.right。
// 重复上述操作，直至访问完整棵树。
// class Solution {
// public:
//     void recoverTree(TreeNode* root) {
//         TreeNode *x = nullptr, *y = nullptr, *pred = nullptr, *predecessor = nullptr;

//         while (root != nullptr) {
//             if (root->left != nullptr) {
//                 // predecessor 节点就是当前 root 节点向左走一步，然后一直向右走至无法走为止
//                 predecessor = root->left;
//                 while (predecessor->right != nullptr && predecessor->right != root) {
//                     predecessor = predecessor->right;
//                 }
                
//                 // 让 predecessor 的右指针指向 root，继续遍历左子树
//                 if (predecessor->right == nullptr) {
//                     predecessor->right = root;
//                     root = root->left;
//                 }
//                 // 说明左子树已经访问完了，我们需要断开链接
//                 else {
//                     if (pred != nullptr && root->val < pred->val) {
//                         y = root;
//                         if (x == nullptr) {
//                             x = pred;
//                         }
//                     }
//                     pred = root;

//                     predecessor->right = nullptr;
//                     root = root->right;
//                 }
//             }
//             // 如果没有左孩子，则直接访问右孩子
//             else {
//                 if (pred != nullptr && root->val < pred->val) {
//                     y = root;
//                     if (x == nullptr) {
//                         x = pred;
//                     }
//                 }
//                 pred = root;
//                 root = root->right;
//             }
//         }
//         swap(x->val, y->val);
//     }
// };

void printTree(TreeNode* node)
{
    if(node)
    {
        printTree(node->left);
        printf("%d ",node->val);
        printTree(node->right);
    }
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


int main()
{
    vector<int> nums = {1,3,-1000,-1000,2};
    nums = {3,1,4,-1000,-1000,2};
    TreeNode* node = createTree(nums);
    printTree(node);
    printf("\n");
    recoverTree2(node);
    printTree(node);
    printf("\n");

    return 0;   
}