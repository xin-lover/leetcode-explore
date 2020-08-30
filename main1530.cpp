//1530. 好叶子节点对的数量

#include <cstdio>
#include <vector>
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

vector<pair<TreeNode*,int>> dfs(TreeNode* node,int distance,int& res)
{
    if(!node)
    {
        return {};
    }

    vector<pair<TreeNode*,int>> left = dfs(node->left,distance,res);
    vector<pair<TreeNode*,int>> right = dfs(node->right,distance,res);
    if(left.empty() && right.empty())
    {
        return {{node,0}};
    }

    vector<pair<TreeNode*,int>> tmp(left.size()+right.size());
    for(int i=0;i<left.size();++i)
    {
        left[i].second++;
        tmp[i] = left[i];
    }
    for(int i=0;i<right.size();++i)
    {
        int j = i + left.size();
        right[i].second++;
        tmp[j] = right[i];
    }

    for(int i=0;i<left.size();++i)
    {
        for(int j=0;j<right.size();++j)
        {
            if(left[i].second + right[j].second <= distance)
            {
                ++res;
            }
        }
    }

    return tmp;
}

//官方题解
// 对于 dfs(root,distance)，同时返回：
// 1）每个叶子节点与 root 之间的距离
// 2) 以 root 为根节点的子树中好叶子节点对的数量
// pair<vector<int>, int> dfs(TreeNode* root, int distance) {
//     vector<int> depths(distance + 1, 0);
//     bool isLeaf = (!root->left && !root->right);
//     if (isLeaf) { 
//         depths[0] = 1;
//         return make_pair(depths, 0);
//     }

//     vector<int> leftDepths(distance + 1, 0), rightDepths(distance + 1, 0);
//     int leftCount = 0, rightCount = 0;
//     if (root->left) {
//         tie(leftDepths, leftCount) = dfs(root->left, distance);
//     }
//     if (root->right) {
//         tie(rightDepths, rightCount) = dfs(root->right, distance);
//     }

//     for (int i = 0; i < distance; i++) {
//         depths[i + 1] += leftDepths[i];
//         depths[i + 1] += rightDepths[i];
//     }

//     int cnt = 0;
//     for (int i = 0; i <= distance; i++) {
//         for (int j = 0; j + i + 2 <= distance; j++) {
//             cnt += (leftDepths[i] * rightDepths[j]);
//         }
//     }
//     return make_pair(depths, cnt + leftCount + rightCount);
// }
    // int countPairs(TreeNode* root, int distance) {
    //     auto [depths, ret] = dfs(root, distance);
    //     return ret;
    // }

int countPairs(TreeNode* root, int distance) {
    //思路：最短距离就是到共同祖先节点的高度和
    //递归，每次返回当前节点的叶子节点，若数量大于1，开始寻找
    int res = 0;
    dfs(root,distance,res);

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


int main()
{
    vector<int> nums = {1,2,3,-1000,4};
    int distance = 3; //1

    nums = {1,2,3,4,5,6,7}, distance = 3; //2
    nums = {1,1,1}, distance = 2;   //1

    nums = {7,1,4,6,-1000,5,3,-1000,-1000,-1000,-1000,-1000,2}, distance = 3;//1
    nums = {1,2,3,4,5,6,7},distance =3;

    TreeNode* root = createTree(nums);

    printf("%d\n",countPairs(root,distance));

    return 0;
}