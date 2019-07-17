//leetcode 731. 我的日程安排表 II

#include <cstdio>
#include <vector>

using namespace std;

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

TreeNode* root1 = nullptr;
TreeNode* root2 = nullptr;

bool canInsert(TreeNode* node,int start,int end)
{
    if(node == nullptr)
    {
        return true;
    }

    if(end <= node->start)
    {
        return canInsert(node->left,start,end);
    }
    else if(start >= node->end)
    {
         return canInsert(node->right,start,end);
    }
    else
    {
        return false;
    }
}

bool insert(TreeNode* node,int start,int end)
{
    printf("insert:%d %d\n",start,end);
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

bool canInsert2(TreeNode* node,int start,int end)
{
    if(node == nullptr)
    {
        return true;
    }

    if(end <= node->start)
    {
        return canInsert2(node->left,start,end);
    }
    else if(start >= node->end)
    {
        return canInsert2(node->right,start,end);
    }
    else
    {
        //把区间分开
        if(start < node->end)
        {
            if(!canInsert(root2,start,min(end,node->end)))
            {
                return false;
            }

            if(node->end < end)
            {
                return canInsert2(node->right,node->end,end);
            }

            return true;
        }
        else if(end > node->start)
        {
            if(!canInsert(root2,max(start,node->start),end))
            {
                return false;
            }

            if(start < node->start)
            {
                return canInsert2(root1,start,node->start);
            }

            return true;
        }
    }

    return true;
}

void insert2(TreeNode* node,int start,int end)
{
    if(end <= node->start)
    {
        if(node->left == nullptr)
        {
            TreeNode* newNode = new TreeNode(start,end);
            node->left = newNode;
        }
        else
        {
            insert2(node->left,start,end);
        }
    }
    else if(start >= node->end)
    {
        if(node->right == nullptr)
        {
            node->right = new TreeNode(start,end);
        }
        else
        {
           insert2(node->right,start,end);
        }
    }
    else
    {
        //把区间分开
        if(start < node->end)
        {
            insert(root2,start,min(end,node->end));
            if(node->end < end)
            {
                if(node->right == nullptr)
                {
                    node->right = new TreeNode(node->end,end);
                }
                else
                {
                    insert2(node->right,node->end,end);
                }
            }
        }
        else if(end > node->start)
        {
            insert(root2,max(start,node->start),end);
            if(start < node->start)
            {
                if(node->left == nullptr)
                {
                    node->left = new TreeNode(start,node->start);
                }
                else
                {
                    return insert2(root1,start,node->start);
                }
            }
        }
    }
}

TreeNode* findNodeToInsert(TreeNode* node,int start, int end)
{
    if(end <= node->start)
    {
        if(node->left == nullptr)
        {
            return node;
        }
        else
        {
            return findNodeToInsert(node->left,start,end);
        }
    }
    else if(start >= node->end)
    {
        if(node->right == nullptr)
        {
            return node;
        }
        else
        {
            return findNodeToInsert(node->right,start,end);
        }
    }
    else
    {
        return nullptr;
    }    
}

bool book(int start, int end) {
    //思路：三重预定，两重预定我们使用树或者二分查找的方式
    //三重预定可以使用同样的方式，不过要维护两个树，一个二重预定的树

    if(root1 == nullptr)
    {
        root1 = new TreeNode(start,end);
        return true;
    }

    if(root2 == nullptr)
    {
        root2 = new TreeNode(-1,-1);
    }

    if(canInsert2(root1,start,end))
    {
        insert2(root1,start,end);
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    // printf(book(10, 20) ? "true\n" : "false\n"); // returns true
    // printf(book(50, 60) ? "true\n" : "false\n"); // returns true
    // printf(book(10, 40) ? "true\n" : "false\n"); // returns true
    // printf(book(5, 15) ? "true\n" : "false\n"); // returns false
    // printf(book(5, 10) ? "true\n" : "false\n"); // returns true
    // printf(book(25, 55) ? "true\n" : "false\n"); // returns true

    // printf(book(47,50) ? "true\n" : "false\n"); // returns true
    // printf(book(1,10) ? "true\n" : "false\n"); // returns true
    // // printf(book(27,36) ? "true\n" : "false\n"); // returns true
    // // printf(book(40,47) ? "true\n" : "false\n"); // returns true
    // // printf(book(20,27) ? "true\n" : "false\n");
    // // printf(book(15,23) ? "true\n" : "false\n");
    // // printf(book(10,18) ? "true\n" : "false\n");
    // // printf(book(27,36) ? "true\n" : "false\n");
    // // printf(book(17,25) ? "true\n" : "false\n");
    // printf(book(8,17) ? "true\n" : "false\n");
    // // printf(book(24,33) ? "true\n" : "false\n");
    // // printf(book(23,28) ? "true\n" : "false\n");
    // // printf(book(21,27) ? "true\n" : "false\n");
    // // printf(book(47,50) ? "true\n" : "false\n");
    // // printf(book(14,21) ? "true\n" : "false\n");
    // // printf(book(26,32) ? "true\n" : "false\n");
    // // printf(book(16,21) ? "true\n" : "false\n");
    // printf(book(2,7) ? "true\n" : "false\n"); // returns true

    printf(book(12,26) ? "true\n" : "false\n");
    // printf(book(37,47) ? "true\n" : "false\n");
    // printf(book(90,100) ? "true\n" : "false\n");
    printf(book(21,34) ? "true\n" : "false\n");
    // printf(book(99,100) ? "true\n" : "false\n");
    // printf(book(95,100) ? "true\n" : "false\n");
    printf(book(4,16) ? "true\n" : "false\n");
    // printf(book(67,86) ? "true\n" : "false\n");
    // printf(book(55,69) ? "true\n" : "false\n");
    // printf(book(63,81) ? "true\n" : "false\n");
    // printf(book(51,66) ? "true\n" : "false\n");
    // printf(book(18,35) ? "true\n" : "false\n");
    // printf(book(51,64) ? "true\n" : "false\n");
    // printf(book(40,56) ? "true\n" : "false\n");
    // printf(book(11,28) ? "true\n" : "false\n");
    // printf(book(13,27) ? "true\n" : "false\n");
    // printf(book(38,51) ? "true\n" : "false\n");

    return 0;
}