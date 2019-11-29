//988. 从叶结点开始的最小字符串

#include <cstdio>
#include <vector>
#include <string>
#include <stack>

using namespace std;

//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

string smallestFromLeaf(TreeNode* root) {
    //思路：因为越深的节点决定排序，所以使用dfs先序遍历，同时用一个vector存储路径点
    //随栈一起弹入弹出,这时需要对这个栈有要求，必须能同步vector的弹入弹出
    //一个节点什么时候可以弹出？当左右节点都遍历后
    //所以每个节点都压入两次，当第二次弹出的时候vector才pop_back

    stack<TreeNode*> sk;
    vector<int> path;

    vector<int> minPath(1,26);
    TreeNode* tmp = root;
    TreeNode* lastTmp = nullptr;
    while(!sk.empty() || tmp != nullptr)
    {
        while(tmp != nullptr)
        {
            sk.push(tmp);
            sk.push(tmp);
            path.push_back(tmp->val);
            lastTmp = tmp;
            tmp = tmp->left;
        }

        //表示到达叶子节点
        if(lastTmp != nullptr && lastTmp->left == nullptr && lastTmp->right == nullptr)
        {
            int cmp = 0;
            int m = minPath.size();
            int n = path.size();
            int len = min(m,n);
            for(int i=0;i<len;++i)  //从后往前比较
            {
                if(path[n-i-1] == minPath[m-i-1])
                {
                    continue;
                }

                cmp = path[n-i-1] < minPath[m-i-1] ? 1 : -1;
                break;
            }
            if(cmp == 0)
            {
                cmp = n < m ? 1 : -1;
            }
            if(cmp == 1)
            {
                minPath = path;
            }
        }

        if(!sk.empty())
        {
            TreeNode* bePop = sk.top();
            sk.pop();
            while(!sk.empty() && bePop != sk.top()) //说明到达两次
            {
                bePop = sk.top();
                sk.pop();

                //弹出
                path.pop_back();
            }

            if(!sk.empty())
            {
                tmp = sk.top()->right;
                lastTmp = nullptr;
            }

        }
    }

    string res(minPath.size(),'a');
    for(int i=minPath.size()-1,j=0;i>=0;--i,++j)
    {
        res[j] = 'a'+minPath[i];
    }

    return res;
}

void smallestFromLeaf2(TreeNode* root,vector<int>& path,vector<int>& minPath) 
{
    if(root==nullptr)
    {
        return;
    }

    path.push_back(root->val);
    if(root->left == nullptr && root->right == nullptr)
    {
        for(auto a : path)
        {
            printf("%d ",a);
        }
        printf("\n");
        int len = min(path.size(),minPath.size());
        bool equ = true;
        for(int i=0;i<len;++i)
        {
            if(minPath[minPath.size()-1-i] == path[path.size()-1-i])
            {
                continue;
            }

            equ = false;
            if(minPath[minPath.size()-1-i] > path[path.size()-1-i])
            {
                minPath = path;
                printf("i:%d minval:%d\n",i,minPath[minPath.size()-1-i]);
            }
            break;
        }

        if(equ && minPath.size() > path.size())
        {
            minPath = path;
        }
    }

    smallestFromLeaf2(root->left,path,minPath);
    smallestFromLeaf2(root->right,path,minPath);
    path.pop_back();
}
string smallestFromLeaf2(TreeNode* root) 
{
    //思路：递归，当前节点最小的字符串等于左儿子加当前字符与右儿子当前字符的最小值
    if(root == nullptr)
    {
        return "";
    }

    vector<int> path,minPath(1,26);
    smallestFromLeaf2(root,path,minPath);
    
    string res(minPath.size(),'a');
    for(int i=minPath.size()-1,j=0;i>=0;--i,++j)
    {
        res[j] = 'a'+minPath[i];
    }

    return res;
}

int main()
{
    // TreeNode* root = new TreeNode(0);
    // root->left= new TreeNode(1);
    // root->left->left= new TreeNode(3);
    // root->left->right= new TreeNode(4);
    // root->right= new TreeNode(2);
    // root->right->left= new TreeNode(3);
    // root->right->right = new TreeNode(4);

    // printf("%s\n",smallestFromLeaf(root).c_str()); //dba

    // TreeNode* root = new TreeNode(2);
    // root->left= new TreeNode(2);
    // // root->left->left= new TreeNode(3);
    // root->left->right= new TreeNode(1);
    // root->left->right->left= new TreeNode(0);
    // root->right= new TreeNode(1);
    // root->right->left= new TreeNode(0);
    // printf("%s\n",smallestFromLeaf2(root).c_str()); //abc 


    TreeNode* root = new TreeNode(18);
    root->left= new TreeNode(23);
    root->left->left= new TreeNode(12);
    root->left->right= new TreeNode(2);
    root->right= new TreeNode(17);
    root->right->left= new TreeNode(11);
    root->right->right= new TreeNode(15);
    printf("%s\n",smallestFromLeaf2(root).c_str()); //cxs
    return 0;
}
 
