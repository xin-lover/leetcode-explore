
// leetcode 863. 二叉树中所有距离为 K 的结点

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

void findNodes(TreeNode* node,int K,vector<int>& nums)
{
    if(node == nullptr)
    {
        return;
    }
    if(K == 0)
    {
        nums.push_back(node->val);
    }
    else if(K>0)
    {
        findNodes(node->left,K-1,nums);
        findNodes(node->right,K-1,nums);
    }
    else
    {
        //do nothing
    }
}

vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
    //思路：主要考查遍历，这个可以使用dfs，因为要查找目标节点
    //也是就是我们用栈存储已遍历的节点，等找到后就可以回溯
    
    //还有一种思路就是先构建图，然后bfs。。。。。

    vector<int> res;
    stack<TreeNode*> sk;
    TreeNode* tmp = root;
    while(tmp != nullptr || !sk.empty())
    {
        while(tmp != nullptr)
        {
            if(tmp == target)
            {
                //找到后
                findNodes(tmp,K,res);
                int n = K;
                TreeNode* pre = target;
                while(n>= 0 && !sk.empty())
                {
                    --n;
                    if(n == 0)
                    {
                        res.push_back(sk.top()->val);
                    }
                    TreeNode* t = sk.top();
                    sk.pop();
                    if(!sk.empty() && t == sk.top())
                    {
                        sk.pop();
                    }
                    if(t->left == pre)
                    {
                        findNodes(t->right,n-1,res);
                    }
                    else
                    {
                        findNodes(t->left,n-1,res);
                    }
                    pre = t;
                }

                return res;
            }

            //因为要保留路径信息，所以push两次
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
                tmp = sk.top();
                sk.pop();
            }
            tmp = tmp->right;
        }
    }

    return res;
}

void printTree(TreeNode* node)
{
    if(node != nullptr)
    {
        printf("%d \n",node->val);
        printTree(node->left);
        printTree(node->right);      
    }

}

int main()
{
    //
    vector<int>  v= {3,5,1,6,2,0,8,1000,1000,7,4};
    // v = {0,1,1000,3,2};
    // v = {0,1000,1,1000,2,1000,3};
    v = {0,1,15,4,2,1000,1000,10,7,3,8,11,1000,9,1000,1000,5,12,1000,1000,17,1000,1000,6,1000,18,16,1000,19,1000,13,1000,1000,1000,1000,1000,1000,1000,14};
    int val = 2;
    int dis = 5;
    
    queue<TreeNode*> qu;
    TreeNode* root = new TreeNode(v[0]);
    qu.push(root);

    TreeNode* target = nullptr;
    int i = 1;
    while(i < v.size())
    {
        TreeNode* cur = qu.front();
        qu.pop();
        if(i < v.size())
        {
            if(v[i] < 1000)
            {
                TreeNode* t = new TreeNode(v[i]);
                cur->left = t;
                qu.push(t);
                if(v[i] == val)
                {
                    target = t;
                }
            }
        }

        ++i;
        if(i < v.size())
        {
            if(v[i] < 1000)
            {
                TreeNode* t = new TreeNode(v[i]);
                cur->right = t;
                qu.push(t);
                if(v[i] == val)
                {
                    target = t;
                }
            }
        }
        ++i;
    }

    printTree(root);
    printf("\n");
        

    vector<int> res = distanceK(root,target,dis);
    for(auto a : res)
    {
        printf("%d ",a);
    }
    printf("\n");
    return 0;
}