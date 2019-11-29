//987. 二叉树的垂序遍历

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


vector<vector<int>> verticalTraversal(TreeNode* root) {
    //思路：根据题意，其实每个节点现在变成了一个坐标，
    //简单的一个方案就是坐标排序，根据题意就是先比x在比y，最后比值

    if(root == nullptr)
    {
        return {{}};
    }

    //使用中序遍历
    vector<vector<int>> ay;
    stack<pair<vector<int>,TreeNode*>> sk;
    TreeNode* tmp=root;
    int x=0,y=0;
    while(!sk.empty() || tmp != nullptr)
    {
        while(tmp != nullptr)
        {
            sk.push({{x,y},tmp});
            tmp = tmp->left;
            --x;
            --y;
        }      

        if(!sk.empty())
        {
            int tx = sk.top().first[0];
            int ty = sk.top().first[1];
            ay.push_back({tx,ty,sk.top().second->val});
            tmp = sk.top().second->right;
            sk.pop();

            x = tx + 1;
            y = ty - 1;
        }
    }

    for(auto a : ay)
    {
        printf("[%d,%d,%d],",a[0],a[1],a[2]);
    }
    printf("\n");
    std::sort(ay.begin(),ay.end(),[](const vector<int>& a,const vector<int>& b)
    {
        if(a[0] == b[0])
        {
            if(a[1] == b[1])
            {
                return a[2] < b[2];
            }

            return a[1] > b[1];
        }

        return a[0] < b[0];
    });


    vector<vector<int>> res;
    res.push_back({ay[0][2]});
    for(int i=1;i<ay.size();++i)
    {
        if(ay[i][0] == ay[i-1][0])
        {
            res.back().push_back(ay[i][2]);
        }
        else
        {
           res.push_back({ay[i][2]});
        }
    }
    return res;
}

vector<vector<int>> verticalTraversal2(TreeNode* root) {
    //优化：上述思路中排序算法是一个性能点，根据题意，其实坐标是有界限的
    //结果是按x坐标来组织的，所以直接使用一个1000长度的vector来存储
    //x的排序就可以避免，只剩下x坐标相同的组内排序
}

int main()
{
    // TreeNode* root = new TreeNode(3);
    // root->left = new TreeNode(9);
    // root->right = new TreeNode(20);
    // root->right->left = new TreeNode(15);
    // root->right->right = new TreeNode(7);

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);

    auto res = verticalTraversal(root);
    for(auto a : res)
    {
        printf("[");
        for(auto b : a)
        {
            printf("%d,",b);
        }
        printf("],");
    }
    printf("\n");

    return 0;

}