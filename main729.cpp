//leetcode 729. 我的日程安排表 I

#include <cstdio>
#include <vector>

using namespace std;

vector<int> points_;
bool book(int start,int end)
{
    //思路：其实就是添加区间，区间不能重合
    //暴力解法就是每次都遍历所有区间；
    //优化解法是维持一个递增数组（因为不会重合,每两个数代表一个区间），每次添加区间时，只需要找最右侧的小于start的数即可，使用二分法效率提高,缺点就是insert会引起内存移动
    //移动内存代价还是高
    int left = 0,right=points_.size()-1;
    while(left <= right)
    {
        int mid = left + (right-left) / 2;
        if(points_[mid] <= start)
        {
            left = mid+1;
        }
        else
        {
            right = mid-1;
        }
    }

    printf("right:%d\n",right);
    
    int res = false;
    if(right >= 0)
    {
        if((right & 1) == 0 && points_[right+1] <= start)
        {
            points_.insert(points_.begin() + right+2,start);
            points_.insert(points_.begin() + right+3,end);
            res = true;
        }
        else if((right & 1) == 1 && (right + 1 >= points_.size() || points_[right+1] >= end))
        {
            points_.insert(points_.begin() + right + 1, start);
            points_.insert(points_.begin() + right + 2, end);
            res = true;
        }
    }
    else
    {
        if(!points_.empty())
        {
            if(points_[0] >=end)
            {
                points_.insert(points_.begin(), start);
                points_.insert(points_.begin() + 1, end);
                res = true;
            }
        }
        else
        {
            res = true;
            points_.push_back(start);
            points_.push_back(end);
        }
    }

    return res;
}

struct TreeNode
{
    int start;
    int end;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int a,int b):start(a),end(b),left(nullptr),right(nullptr)
    {

    }
};

bool insert(TreeNode* node,int start,int end)
{
    if(end <= node->start)
    {
        if(node->left == nullptr)
        {
            TreeNode* newNode = new TreeNode(start,end);
            node->left = newNode;
            return true;
        }
        else
        {
            return insert(node->left,start,end);
        }
    }
    else if(start >= node->end)
    {
        if(node->right == nullptr)
        {
            node->right = new TreeNode(start,end);
            return true;
        }
        else
        {
            return insert(node->right,start,end);
        }
    }
    else
    {
        return false;
    }
}

TreeNode* root = nullptr;
bool book2(int start,int end)
{
    //构建一颗区间二叉查找树
    if(root == nullptr)
    {
        root = new TreeNode(start,end);
        return true;
    }
    else
    {
        return insert(root,start,end);
    }
    
}

int main()
{
    printf(book2(47,50) ? "true\n" : "false\n");
    printf(book2(33,41) ? "true\n" : "false\n");
    printf(book2(39,45) ? "true\n" : "false\n");
    printf(book2(33,42) ? "true\n" : "false\n");
    printf(book2(25,32) ? "true\n" : "false\n");
    return 0;
}