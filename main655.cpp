//leetcode 655. 输出二叉树

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

struct  TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x):val(x),left(nullptr),right(nullptr){}
};

void extend(vector<string>& small,vector<string>& big,int smallLeft,int smallRight,int bigLeft,int bigRight)
{
    int smallMid = (smallLeft + smallRight) / 2;
    int bigMid = (bigLeft + bigRight) / 2;

    big[bigMid] = small[smallMid];
    if(smallLeft < smallRight)
    {
        extend(small,big,smallLeft,smallMid-1,bigLeft,bigMid-1);
        extend(small,big,smallRight,smallMid+1,bigRight,bigMid+1);
    }
}

vector<vector<string>> printTree(TreeNode* root) {
    
    //思路：使用递归，左子树和右子树都是输出一个结果，然后合并这两个结果

    if(root == nullptr)
    {
        return {};
    }
    printf("root:%d\n",root->val);
    vector<vector<string>> leftRes = printTree(root->left);
    vector<vector<string>> rightRes = printTree(root->right);

    printf("wy:%d %d\n",leftRes.size(),rightRes.size());
    //补齐
    if(leftRes.size() > rightRes.size())
    {
        rightRes.insert(rightRes.end(),leftRes.size() - rightRes.size(),vector<string>(leftRes[0].size(),""));
    }
    else if(rightRes.size() > leftRes.size())
    {
        leftRes.insert(leftRes.end(),rightRes.size() - leftRes.size(),vector<string>(rightRes[0].size(),""));
    }
    printf("after:%d %d\n",leftRes.size(),rightRes.size());

    //合并
    int n = leftRes.size();
    for(int i=0;i<n;++i)
    {
        //补齐
        printf("nn:%d %d\n",leftRes[i].size(),rightRes[i].size());
        if(leftRes[i].size() > rightRes[i].size())
        {
            vector<string> t(leftRes[i].size(),"");
            swap(t,rightRes[i]);
            extend(t,rightRes[i],0,t.size()-1,0,rightRes[i].size()-1);
            // printf("wwww\n");
            // int c = (leftRes[i].size() - rightRes[i].size())/2;
            // c /= rightRes[i].size();
            // printf("rc:%d\n",c);
            // int k = rightRes[i].size();
            // for(int i=0;i<k;++i)
            // {
            //     rightRes[i].insert(rightRes[i].begin()+i*c + i,c,"");
            //     rightRes[i].insert(rightRes[i].begin()+(i+1)*c + i + 1,c,"");
            // }
            
            // // rightRes[i].insert(rightRes[i].end(),c,"");
            // printf("vvv:%lu\n",rightRes[i].size());
        }
        else if(rightRes[i].size() > leftRes[i].size())
        {
            // printf("get\n");
            // int c = (rightRes[i].size() - leftRes[i].size())/2;
            // c /= leftRes[i].size();
            // printf("c:%d\n",c);
            // int k = leftRes[i].size();
            // for(int i=0;i<k;++i)
            // {
            //     leftRes[i].insert(leftRes[i].begin()+i*c + i,c,"");
            //     leftRes[i].insert(leftRes[i].begin()+(i+1)*c + i + 1,c,"");
            // }
            vector<string> t(rightRes[i].size(),"");
            swap(t,leftRes[i]);
            extend(t,leftRes[i],0,t.size()-1,0,leftRes[i].size()-1);

        }
        leftRes[i].push_back("");
        leftRes[i].insert(leftRes[i].end(),rightRes[i].begin(),rightRes[i].end());
        printf("hhh:%lu\n",leftRes[i].size());
    }

    int m = leftRes.empty() ? 1 : leftRes[0].size();
    leftRes.insert(leftRes.begin(),vector<string>(m,""));
    leftRes.front()[m/2] = to_string(root->val);
    printf("root:%d sz:%lu\n",root->val,leftRes.front().size());

    return leftRes;
}

int main()
{
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2); 
    root->right= new TreeNode(3); 
    root->left->right= new TreeNode(4); 

    auto res = printTree(root);
    printf("%d %d\n",res.size(),res[0].size());
    for(auto a : res)
    {
        for(auto b : a)
        {
            printf("%s ",b.c_str());
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}