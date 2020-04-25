//1261. 在受污染的二叉树中查找元素

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
 
class FindElements {
public:
    TreeNode* root_;
    FindElements(TreeNode* root) {
        //思路：根据题意，先还原，重点是如何遍历，可以考虑先序遍历+栈深度遍历
        //对于查找，使用一个数组来存储结果，是O(1)复杂度，但空间复杂度是O(n)
        //而这个本身就是二叉树，可以考虑遍历,不需要额外空间
        //每一层，开始元素是2^n-1,结束元素是2^(n+1)-2
        //我们确定n的话，除2递归即可，过程是n%2==1表示左儿子，然后n=n/2，然后递归
        //这样能够确定路径，然后遍历判断是否存在即可

        root_ = root;

        stack<TreeNode*> sk;
        
        TreeNode* tmp = root;
        int cur_val = 0;
        while(tmp != nullptr || !sk.empty())
        {
            while(tmp != nullptr)
            {
                sk.push(tmp);
                tmp->val = cur_val;
                tmp=tmp->left;
                cur_val = cur_val * 2 + 1;
            }

            if(!sk.empty())
            {
                tmp = sk.top();
                sk.pop();
                cur_val = tmp->val * 2 + 2;
                tmp = tmp->right;
            }
        }
    }
    
    bool find(int target) {
        vector<bool> flags;
        while(target != 0)
        {
            flags.push_back(target & 1);    //左儿子为true
            int t = flags.back() ? 1 : 2;
            target = (target-t) / 2;
        }

        TreeNode* tmp = root_;
        for(int i=flags.size() - 1;i>=0;--i)
        {
            if(flags[i])
            {
                tmp = tmp->left;
            }
            else
            {
                tmp = tmp->right;
            }
            if(tmp == nullptr)
            {
                return false;
            }
        }

        return true;
    }
};

void printTree(TreeNode* t)
{
    if(t != nullptr)
    {
        printf("%d ",t->val);
        printTree(t->left);
        printTree(t->right);
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
    vector<int> v = {-1,-1000,-1};
    v = {-1,-1,-1,-1,-1};
    TreeNode* root = createTree(v);
    printTree(root);
    printf("\n");
    FindElements fe(root);
    printf(fe.find(1) ? "true\n" : "false\n");
    printf(fe.find(3) ? "true\n" : "false\n");
    printf(fe.find(5) ? "true\n" : "false\n");
    printTree(root);
    printf("\n");
    return 0;
}