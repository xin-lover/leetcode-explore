#include <vector>
#include <cstdio>

using namespace std;

class Solution {
public:
    class TreeNode
    {
    public:
        int val;
        TreeNode* left;
        TreeNode* right;

        TreeNode(int x):val(x),left(nullptr),right(nullptr){}
    };

    void insert(TreeNode* root,int val)
    {
        TreeNode* tmp = root;
        while(tmp != nullptr)
        {
            if(val <= tmp->val)
            {
                if(tmp->left == nullptr)
                {
                    tmp->left = new TreeNode(val);
		    return;
                }
                else
                {
                    tmp = tmp->left;
                }
            }
            else
            {
                if(tmp->right == nullptr)
                {
                    tmp->right = new TreeNode(val);
		    return;
                }
                else
                {
                    tmp = tmp->right;
                }
            }
        }
    }

    TreeNode* remove(TreeNode* root, int val)
    {
        TreeNode* tmp = root;
        while(tmp != nullptr)
        {
            if(val == tmp->val)
            {
                if(tmp->right == nullptr)
                {
                    if(tmp->left == nullptr)
                    {
                        delete tmp;
                        return nullptr;
                    }

                    TreeNode* bedel = tmp->left;
                    tmp->val = bedel->val;
                    tmp->left = bedel->left;
                    tmp->right = bedel->right;

                    delete bedel;
                }
                else
                {
                    //find right min
                    TreeNode* t = root->right;
                    TreeNode* pre = nullptr;
                    while(t->left != nullptr)
                    {
                        t = t->left;
                        pre = t;
                    }

                    if(pre != nullptr)
                    {
                        pre->left = t->right;
                    }
                    else
                    {
                        tmp->right = t->right;
                    }

                    tmp->val = t->val;
                    delete t;
                }

                return root;
            }
            else if(val > tmp->val)
            {
                tmp = tmp->right;
            }
            else
            {
                tmp = tmp->left;
            }
        }

        return nullptr;
    }

    int getMin(TreeNode* root)
    {
        TreeNode* tmp = root;
        while(tmp->left != nullptr)
        {
            tmp = tmp->left;
        }

        return tmp->val;
    }

    int getMax(TreeNode* root)
    {
        TreeNode* tmp = root;
        while(tmp->right != nullptr)
        {
            tmp = tmp->right;
        }

        return tmp->val;
    }

    bool checkNode(TreeNode* root, int val,int t)
    {
	TreeNode* tmp = root;
	while(tmp != nullptr)
	{
		if(val <= tmp->val)
		{
			if(abs(val-tmp->val) <= t)
			{
				return true;
			}

			tmp = tmp->left;
		}
		else
		{
			if(abs(val-tmp->val) <= t)
			{
				return true;
			}
			tmp = tmp->right;
		}
	}
					

        return false;
    }

    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        if(nums.size() < 2)
        {
            return false;
        }

        TreeNode* root = new TreeNode(nums[0]);
	//insert(root,nums[1]);
        for(int i=1;i<nums.size();++i)
        {
            if(checkNode(root,nums[i],t))
            {
                return true;
            }

	    printf("root:%d\n",root->val);
            insert(root,nums[i]);
            if(i >= k)
            {
                remove(root,nums[i-k]);
            }
        }

        return false;
    }
};

int main()
{
	Solution s;
	vector<int> nums = {4,1,6,3};
	bool res = s.containsNearbyAlmostDuplicate(nums,100,1);
	printf(res ? "true" : "false");
	printf("\n");
	return 0;
}
