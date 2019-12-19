//1008. 先序遍历构造二叉树

#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* bstFromPreorder(vector<int>& preorder,int left,int right) {
    if(left > right)
    {
        return nullptr;
    }
    if(left == right)
    {
        return new TreeNode(preorder[left]);
    }

    TreeNode* root = new TreeNode(preorder[left]);
    int i;
    for(i=left+1;i<=right;++i)
    {
        if(preorder[i] > preorder[left])
        {
            break;
        }
    }

    root->left = bstFromPreorder(preorder,left+1,i-1);
    root->right = bstFromPreorder(preorder,i,right);
    return root;
}

TreeNode* bstFromPreorder(vector<int>& preorder) {
    //思路：有一个简单的思路就是递归，因为是二叉搜索树，又是先序遍历
    //所以第一个数是根节点，后面的数分成两部分，第一部分是小于这个数的，为左子树，右侧是大于这个树的，为右子树
    //这里查找第一个大于根节点的数时可以使用二分查找，因为二叉搜索树的中序遍历是递增的，也就是把先序遍历排序即得到中序遍历

    return bstFromPreorder(preorder,0,preorder.size()-1);
}

TreeNode* bstFromPreorder2(int lower,int upper,vector<int>& preorder,int& index)
{
    if(index == preorder.size()) return nullptr;

    int val = preorder[index];

    if(val < lower || val > upper) return nullptr;

    ++index;
    TreeNode* node = new TreeNode(val);
    node->left = bstFromPreorder2(lower,val,preorder,index);
    node->right = bstFromPreorder2(val,upper,preorder,index);
    return node;
}
TreeNode* bstFromPreorder2(vector<int>& preorder) {
    //思路：递归,因为通过先序遍历构造的二叉搜索树是唯一的
    //所以可以通过递归的方法，在扫描先序遍历的时候构造二叉搜索树
    //我们维护一个空间（lower,upper),因为是先序，我们每遇到一个数val，如果不在这个空间内，说明不属于这个空间所代表的树
    //否则，为val构建一个节点,(lower,val) 属于这个节点的左子树，(val,upper)属于这个节点的右子树
    //也就是说先遍历的val，如果后面的数比val小，那么表示是val节点的左边的节点，否则是右边的节点
    //如果遍历完整个序列，二叉构造树就完成了

    int index= 0;
    return bstFromPreorder2(INT_MIN,INT_MAX,preorder,index);
}

TreeNode* bstFromPreorder3(vector<int>& preorder) {
    //思路：使用栈，先使用第一个数构建根节点并入栈
    //之后的数，如果小于栈顶元素，则表示是左子树，将栈顶元素弹出，作为新的父节点，直到栈空或者栈顶的元素大于节点的元素值
    //如果父节点的元素值小于节点的元素值，则子节点为右孩子，否则为左孩子
    //然后再将子节点放入栈中

    if(preorder.empty())
    {
        return nullptr;
    }

    TreeNode* root = new TreeNode(preorder[0]);

    stack<TreeNode*> sk;
    sk.push(root);

    for(int i=1;i<preorder.size();++i)
    {
        TreeNode* node = sk.top(); //这里先取出了根节点，如果栈为空，说明是节点的右孩子
        TreeNode* child = new TreeNode(preorder[i]);

        //adjust the parent
        while(!sk.empty() && sk.top()->val < child->val)
        {
            node = sk.top();
            sk.pop();
        }

        if(node->val < child->val) node->right = child;
        else node->left = child;

        sk.push(child);
    }

    return root;
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

int main()
{
    vector<int> v = {8,5,1,7,10,12};
    TreeNode* node = bstFromPreorder3(v);
    printTree(node);
    return 0;
}