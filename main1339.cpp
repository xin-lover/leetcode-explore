//1339. 分裂二叉树的最大乘积

#include <cstdio>
#include <vector>
#include <queue>
#include <stack>

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
    int i=0;
    while(!qu.empty() && i<v.size())
    {
        TreeNode* parent = qu.front();
        qu.pop();

        if(i+1 < v.size() && v[i+1] > -1000)
        {
            TreeNode* left = new TreeNode(v[i+1]);
            parent->left = left;
            qu.push(left);
        }

        if(i+2<v.size() && v[i+2] > -1000)
        {
            TreeNode* right = new TreeNode(v[i+2]);
            parent->right = right;
            qu.push(right);
        }
        
        i+=2;
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

int maxProduct(TreeNode* root) {
    //思路：在每个节点，可以3中选择分裂为两颗子树
    //1.与父节点断开；
    //2.与左儿子断开；
    //3.与右儿子断开；
    //那现在的问题就是如何求子树和了
    //为了避免重复计算,可以先遍历一次，求出以该节点为根的子树的和

    //使用后序遍历，使用栈的后序遍历，可以把每个节点压入两次，出栈两次访问即后序遍历了
    stack<TreeNode*> sk;
    TreeNode* tmp = root;
    static int kMax = 1000000007;
    while(!sk.empty() || tmp != nullptr)
    {
        while(tmp != nullptr)
        {
            sk.push(tmp);
            sk.push(tmp);
            tmp = tmp->left;
        }

        if(!sk.empty())
        {
            tmp = sk.top();
            sk.pop();

            while(sk.empty() || tmp != sk.top())
            {
                //左右儿子都访问过了，执行处理逻辑
                int left = tmp->left ? tmp->left->val : 0;
                int right = tmp->right ? tmp->right->val : 0;
                tmp->val = (static_cast<long long>(left) + right + tmp->val)%kMax;
                if(!sk.empty())
                {
                    tmp = sk.top();
                    sk.pop();
                }
                else
                {
                    tmp = nullptr;
                    break;
                }
                
            }

            if(tmp)
            {
                tmp = tmp->right;
            }
            
        }
    }

    long long res = 0;
    int sum = root->val;
    
    tmp = root;
    while(!sk.empty() || tmp != nullptr)
    {
        while(tmp != nullptr)
        {
            sk.push(tmp);
            tmp = tmp->left;
        }

        if(!sk.empty())
        {
            tmp = sk.top();
            sk.pop();

            //拆分
            if(tmp->left)
            {
                long long t = static_cast<long long>(tmp->left->val) * (sum - tmp->left->val);
                res = max(res, t);
            }

            if(tmp->right)
            {
                long long t = static_cast<long long>(tmp->right->val) * (sum - tmp->right->val);
                res = max(res, t);
            }

            tmp = tmp->right;
        }
    }

    return res % kMax;
}

//另一种思路，不先求最后的结果，而是根据均值不等式，选择最接近sum/2的节点，最后求乘积
int main()
{
    vector<int> num = {1,2,3,4,5,6};   //110
    // num = {2,3,9,10,7,8,6,5,4,11,1};//1025
    // num = {1,1};//1
    // num = {1,2,3};
    TreeNode* root = createTree(num);
    PrintTree(root);

    printf("res:%d\n",maxProduct(root));
    return 0;

}