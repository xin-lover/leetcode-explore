//1110. 删点成林

#include <cstdio>
#include <vector>
#include <set>
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

vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
    //思路：原本存在的树如果没被删除，那肯定在
    //而一个节点被删除，则会新增两颗子树
    //使用后续遍历

    set<int> del_set(to_delete.begin(),to_delete.end());    
    stack<TreeNode*> sk;
    TreeNode* tmp = root;

    vector<TreeNode*> res;
    //判断根节点是否被删除
    if(root != nullptr && del_set.find(root->val) == del_set.end())
    {
        res.push_back(root);
    }
    //后续遍历1
    // TreeNode* pre = nullptr;
    // while(tmp != nullptr)//先推到最左侧
    // {
    //     sk.push(tmp);
    //     tmp = tmp->left;
    // }
    // while(!sk.empty())
    // {
    //     tmp = sk.top();
    //     sk.pop();

    //     if(tmp->right == nullptr || tmp->right == pre)
    //     {
    //         pre = tmp;
            
    //         //逻辑   
    //     }
    //     else
    //     {
    //         sk.push(tmp);
    //         tmp = tmp->right;
    //         while(tmp != nullptr)
    //         {
    //             sk.push(tmp);
    //             tmp = tmp->left;
    //         }
    //     }
    // }

    //后续遍历2:
    // sk.push(root);
    // TreeNode* pre = nullptr;
    // while(!sk.empty())
    // {
    //     tmp = sk.top();
    //     if((tmp->left == nullptr && tmp->right == nullptr) || (pre != nullptr && (tmp->left == pre || tmp->right == pre)))
    //     {
    //         //逻辑

    //         sk.pop();
    //         pre = tmp;
    //     }
    //     else
    //     {
    //         if(tmp->right != nullptr)
    //         {
    //             sk.push(tmp);
    //         }
    //         if(tmp->left != nullptr)
    //         {
    //             sk.push(tmp);
    //         }
    //     }
        
    // }

    //后续遍历3，每个节点栈两次：
    // tmp = root;
    // while(tmp != nullptr || !sk.empty())
    // {
    //     while(tmp != nullptr)
    //     {
    //         sk.push(tmp);
    //         sk.push(tmp);
    //         tmp = tmp->left;
    //     }

    //     if(!sk.empty())
    //     {
    //         tmp = sk.top();
    //         sk.pop();

    //         if(tmp != sk.top())
    //         {
    //             //逻辑
    //         }

    //         tmp = tmp->right;
    //     }
    // }

    return res;
}

vector<TreeNode*> delNodes2(TreeNode* root, vector<int>& to_delete) {
    //思路：原本存在的树如果没被删除，那肯定在
    //而一个节点被删除，则会新增两颗子树
    //因为涉及到节点删除，所以我们需要知道父节点，所以遍历方式改为遍历节点的子节点
    //还是后续遍历

    if(root == nullptr)
    {
        return {};
    }

    set<int> del_set(to_delete.begin(),to_delete.end());    
    stack<TreeNode*> sk;
    sk.push(nullptr);
    TreeNode* tmp = root;

    vector<TreeNode*> res;
    while(tmp != nullptr || !sk.empty())
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

            while(!sk.empty() && tmp != sk.top())
            {
                //
                printf("tmp:%d\n",tmp->val);
                if(tmp->left != nullptr && del_set.find(tmp->left->val) != del_set.end())
                {
                    if(tmp->left->left)
                    {
                        res.push_back(tmp->left->left);
                    }
                    if(tmp->left->right)
                    {
                        res.push_back(tmp->left->right);
                    }

                    delete tmp->left;
                    tmp->left = nullptr;
                }
                if(tmp->right != nullptr && del_set.find(tmp->right->val) != del_set.end())
                {
                    printf("in\n");
                    if(tmp->right->left)
                    {
                        res.push_back(tmp->right->left);
                    }
                    if(tmp->right->right)
                    {
                        printf("in 22\n");
                        res.push_back(tmp->right->right);
                    }

                    delete tmp->right;
                    tmp->right = nullptr;
                }
                tmp = sk.top();
                sk.pop();
            }

            if(tmp != nullptr)
            {
                tmp = tmp->right;
            }
        }
    }
    //判断根节点是否被删除
    if(del_set.find(root->val) == del_set.end())
    {
        res.push_back(root);
    }
    else
    {
        if(root->left)
        {
            res.push_back(root->left);
        }
        if(root->right)
        {
            res.push_back(root->right);
        }

        delete root;
    }
    

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

//这里使用的是非递归，使用递归应该会更简洁

int main()
{
    vector<int> vals = {1,2,3,4,5,6,7};
    vector<int> to_delete = {3,5};

    vals = {1,2,3,-1000,-1000,-1000,4};
    to_delete = {2,1};

    TreeNode* root = createTree(vals);
    PrintTree(root);
    printf("\n---------------\n");

    vector<TreeNode*> res = delNodes2(root,to_delete);
    for(auto a : res)
    {
        PrintTree(a);
        printf("\n");
    }
    return 0;
}