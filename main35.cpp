#include <cstdio>
#include <string>
#include <queue>
#include <stack>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int v):val(v),left(nullptr),right(nullptr){}
};

string serialize(TreeNode *root)
{
    //思路：二叉搜索树,使用先序遍历，反序列化时再次构建二叉树即可
    string res;
    stack<TreeNode*> sk;
    TreeNode* tmp = root;
    while(!sk.empty() || tmp != nullptr)
    {
        while (tmp != nullptr)
        {
            sk.push(tmp);
            res += to_string(tmp->val)+ ";";
            tmp = tmp->left;
        }

        if(!sk.empty())
        {
            tmp = sk.top();
            sk.pop();
            tmp = tmp->right;
        }
        
    }

    return res;
}

TreeNode* deserialize(string data)
{
    TreeNode* head = nullptr;
    if(data.empty())
    {
        return head;
    }

    int start = 0;
    for(int i=0;i<data.size();++i)
    {
        if(data[i] == ';')
        {
            int val = stoi(data.substr(start,i-start));
            TreeNode* t = new TreeNode(val);
            if(head == nullptr)
            {
                head = t;
            }
            else
            {
                //insert
                TreeNode* tmp = head;
                while(tmp != nullptr)
                {
                    if(val > tmp->val)
                    {
                        if(tmp->right == nullptr)
                        {
                            tmp->right = t;
                            break;
                        }
                        tmp = tmp->right;
                    }
                    else
                    {
                        if(tmp->left == nullptr)
                        {
                            tmp->left = t;
                            break;
                        }
                        tmp = tmp->left;
                    }
                }
            }
            
            start = i+1;
        }   
    }
    return head;
}

int main()
{
    TreeNode *t = new TreeNode(4);
    t->left = new TreeNode(2);
    t->right = new TreeNode(5);
    t->left->left = new TreeNode(1);
    t->left->right = new TreeNode(3);
    string res = serialize(t);

    printf("%s\n",res.c_str());

    TreeNode *d = deserialize(res);
    stack<TreeNode*> sk;
    while(!sk.empty() || d != nullptr)
    {
        while(d != nullptr)
        {
            sk.push(d);
            printf("%d ",d->val);
            d = d->left;
        }

        if(!sk.empty())
        {
            d = sk.top();
            sk.pop();
            d = d->right;
        }
    }
    printf("\n");
    return 0;
}