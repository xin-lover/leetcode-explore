//321. 拼接最大数

#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

void trace(vector<int>& nums1,int left1,vector<int>& nums2,int left2,int k,vector<int>& res)
{
    if(k<1)
    {
        return;
    }

    int m = nums1.size();
    int n = nums2.size();

    //暴力实现
    int mx1 = left1;
    for(int i=left1;m-i+n-left2>=k && i < m;++i)
    {
        if(nums1[mx1] < nums1[i])
        {
            mx1 = i;
        }
    }
    
    int mx2 = left2;
    for(int i=left2;m-left1+n-i>=k && i < n;++i)
    {
        if(nums2[mx2] < nums2[i])
        {
            mx2 = i;
        }
    }

    if(left1 >= m)
    {
        res[res.size()-k] = nums2[mx2];
        trace(nums1,left1,nums2,mx2+1,k-1,res);
        return;
    }

    if(left2 >= n)
    {
        res[res.size()-k] = nums1[mx1];
        trace(nums1,mx1+1,nums2,left2,k-1,res);
        return;
    }

    if(nums1[mx1] < nums2[mx2])
    {
        res[res.size()-k] = nums2[mx2];
        trace(nums1,left1,nums2,mx2+1,k-1,res);
    }
    else if(nums1[mx1] > nums2[mx2])
    {
        res[res.size()-k] = nums1[mx1];
        trace(nums1,mx1+1,nums2,left2,k-1,res);
    }
    else
    {
        //这里还是有问题，不能确保最优解
        if(nums1.size() - mx1 + nums2.size() - left2 < nums1.size() - left1 + nums2.size() - mx2)
        {
            res[res.size()-k] = nums2[mx2];
            trace(nums1,left1,nums2,mx2+1,k-1,res);
        }
        else
        {
            res[res.size()-k] = nums1[mx1];
            trace(nums1,mx1+1,nums2,left2,k-1,res);
        }
        
    }
}

vector<int> dfs(vector<int>& nums1,int left1,vector<int>& nums2,int left2,int k)
{
    if(k<1)
    {
        return {};
    }

    int m = nums1.size();
    int n = nums2.size();

    //暴力实现
    int mx1 = left1;
    for(int i=left1;m-i+n-left2>=k && i < m;++i)
    {
        if(nums1[mx1] < nums1[i])
        {
            mx1 = i;
        }
    }
    
    int mx2 = left2;
    for(int i=left2;m-left1+n-i>=k && i < n;++i)
    {
        if(nums2[mx2] < nums2[i])
        {
            mx2 = i;
        }
    }

    vector<int> res(k);
    if(left1 >= m)
    {
        res[0] = nums2[mx2];
        vector<int> tt = dfs(nums1,left1,nums2,mx2+1,k-1);
        copy(tt.begin(),tt.end(),res.begin()+1);
    }
    else if(left2 >= n)
    {
        res[0] = nums1[mx1];
        vector<int> tt = dfs(nums1,mx1+1,nums2,left2,k-1);
        copy(tt.begin(),tt.end(),res.begin()+1);
    }
    else
    {
        if(nums1[mx1] < nums2[mx2])
        {
            res[0] = nums2[mx2];
            vector<int> tt = dfs(nums1,left1,nums2,mx2+1,k-1);
            copy(tt.begin(),tt.end(),res.begin()+1);
        }
        else if(nums1[mx1] > nums2[mx2])
        {
            res[0] = nums1[mx1];
            vector<int> tt = dfs(nums1,mx1+1,nums2,left2,k-1);
            copy(tt.begin(),tt.end(),res.begin()+1);
        }
        else
        {
            res[0] = nums2[mx2];
            vector<int> tt1 = dfs(nums1,left1,nums2,mx2+1,k-1);
            vector<int> tt2 = dfs(nums1,mx1+1,nums2,left2,k-1);

            int cmp = 0;
            for(int i=0;i<tt1.size();++i)
            {
                if(tt1[i] > tt2[i])
                {
                    cmp = 1;
                    break;
                }
                else if(tt1[i] < tt2[i])
                {
                    cmp =-1;
                    break;
                }
                
            }

            if(cmp == 1 )
            {
                copy(tt1.begin(),tt1.end(),res.begin()+1);
            }
            else
            {
                copy(tt2.begin(),tt2.end(),res.begin()+1);
            }
            
        }
        
    }
    

    return res;
}

vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
    //思路：一个思路就是找到两个数组最大的数，假设其跟其后的数与另一个数组的长度大于等于k，那么选择它作为第一位
    //问题在于不够的时候，那么就要我们的选择应该是能满足这个条件的最大数字
    //但这个也会遇到问题，就是如果两个数组符合条件的数字一样大，那么选择哪个？
    //采用贪心策略，采用使接下来可选数字多的选择
    //贪心策略不行，
    //还是回溯dfs吧


    if(nums1.size() + nums2.size() < k)
    {
        return {};
    }

    vector<int> res(k);
    res = dfs(nums1,0,nums2,0,k);
    return res;
}

vector<int> maxNumber2(vector<int>& nums1, vector<int>& nums2, int k) {
    //思路：分治，从nums1中选择i个数，nums2中j个数，那么共有k中组合
    //注意从nums1和nums2中选择若干数是相互独立的，接下来就只需要在合并即可
    //从一个数组中选择若干数使其最大，可以使用单调栈

    auto getKArray = [](vector<int>& nums,int k){
        stack<int> sk;
        int m = nums.size()-k;
        for(int j=0;j<nums.size();++j)
        {
            while(m>0 && !sk.empty() && nums[j] > sk.top())
            {
                sk.pop();
                m--;
            }
            sk.push(nums[j]);
        }

        while(sk.size()>k)
        {
            sk.pop();
        }
        vector<int> tmp(sk.size());
        for(int j=tmp.size()-1;j>=0;--j)
        {
            tmp[j] = sk.top();
            sk.pop();
        }
        return tmp;
    };

    vector<int> res(k,0);
    int validk = min(k,(int)nums1.size());
    for(int i=0;i<=validk;++i)
    {
        if(k-i>nums2.size())
        {
            continue;
        }
        vector<int> v1 = getKArray(nums1,i);
        vector<int> v2 = getKArray(nums2,k-i);

        vector<int> tmp(k);
        int tmpPos = 0;
        int pos1=0,pos2=0;
        while(tmpPos<tmp.size())
        {
            int p1=pos1,p2=pos2;
            while(p1 < v1.size() && p2 < v2.size() && v1[p1] == v2[p2])
            {
                p1++;
                p2++;
            }
            if(p1 >= v1.size())
            {
                tmp[tmpPos++] = v2[pos2++];
            }
            else if(p2 >= v2.size())
            {
                tmp[tmpPos++] = v1[pos1++];
            }
            else
            {
                if(v1[p1] < v2[p2])
                {
                    tmp[tmpPos++] = v2[pos2++];
                }
                else
                {
                    tmp[tmpPos++] = v1[pos1++];
                }
                
            }
            
        }

        printf("i:%d\n",i);
        for(auto b :tmp)
        {
            printf("%d ",b);
        }
        printf("\n");
        for(int j=0;j<k;++j)
        {
            if(res[j] < tmp[j])
            {
                printf("j:%d get:%d %d\n",j,res[j],tmp[j]);
                swap(res,tmp);
                break;
            }
            else if(res[j] > tmp[j])
            {
                break;
            }
        }
    }

    return res;
}

int main()
{
    vector<int> nums1 = {3, 4, 6, 5}, nums2 = {9, 1, 2, 5, 8, 3};
    int k = 5; //[9, 8, 6, 5, 3]

    // nums1 = {6, 7};
    // nums2 = {6, 0, 4};
    // k = 5;  //[6, 7, 6, 0, 4]

    // nums1 = {3, 9};
    // nums2 = {8, 9};
    // k = 3;  //[9, 8, 9]

    // nums1 = {8,6,9};
    // nums2 = {1,7,5};
    // k = 3;  //[9.7,5]

    nums1 = {8,9};
    nums2 = {3,9};
    k = 3;  //[9,8,9]

    // nums1 = {2,5,6,4,4,0};
    // nums2 = {7,3,8,0,6,5,7,6,2};
    // k = 15; //[7,3,8,2,5,6,4,4,0,6,5,7,6,2,0]

    // nums1= {7,6,4,0,5,8,2,2,6,8,2,0,5,3,0,8,7,7,7,3,3,2,0,8,4,0,1,2};
    // nums2 ={1,9,2,3,9,6,1,5,8,7,9,9,1,5,4,1,7,2,2,2,1,1,7,2,8,1,2,6,6,6,5,1,9,9,8,1,4,6,3,3,1,5,0,0,0,5,6,6,2,3,6,6,0,3,5,4,2,4,0,8,2,4,6,1,0,1,1,4,0,3,0,9,2,5,6,3,4,7,0,7,2,4,1,0,6,6,9,6,5,7,2,4,7,5,7,1,9,3,5,8,8,7,2,4,7,9,7,4,5,1,6,3,5,5,8,8,6,2,8,0,9,9,0,3,8,1,3,0,3,5,7,7,6,4,2,5,8,3,3,5};
    // k = 140;



    for(auto a : maxNumber2(nums1,nums2,k))
    {
        printf("%d ",a);
    }
    printf("\n");

    return 0;
}