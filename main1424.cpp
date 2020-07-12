//1424. 对角线遍历 II

#include <cstdio>
#include <vector>

using namespace std;

vector<int> findDiagonalOrder(vector<vector<int>>& nums) {
    //思路：一个简单的思路就是给一行一个标记
    //另一个思路就是记录最开始的开始位置，每一个对角线更新开始位置
    //开始位置是第0列，然后是最后一行

    vector<int> res;
    int m = nums.size();
    int n = 0;
    for(int i=0;i<m;++i)
    {
        int x = i;
        int y = 0;
        n = max(n,(int)nums[i].size());
        while(x >= 0)
        {
            if(y < nums[x].size())
            {
                res.push_back(nums[x][y]);
            }
            --x;
            ++y;
        }
    }

    for(int i=1;i<n;++i)
    {
        int x = m-1;
        int y = i;

        while(y < n)
        {
            if(x>=0 && y < nums[x].size())
            {
                res.push_back(nums[x][y]);
            }
            --x;
            ++y;
        }
    }

    return res;
}

vector<int> findDiagonalOrder2(vector<vector<int>>& nums) {
    //思路：上面的算法超时，估计还是判断太多
    //我们换个思路，直接计算元素最后的位置
    //如何计算？某个元素最终的位置是它所在对角线左上角的元素的数量和在对角线中的位置
    
    int m = nums.size();
    int n = 0;
    for(auto& a : nums)
    {
        n = max(n,(int)a.size());
    }

    vector<vector<int>> tmp(m,vector<int>(n,0));
    for(int i=0;i<m;++i)
    {
        for(int j=0;j<nums[i].size();++j)
        {
            tmp[i][j] = 1;
        }
    }

    int count=0;
    for(int i=0;i<m;++i)
    {
        int x = i;
        int y = 0;
        while(x >= 0)
        {
            count += tmp[x][y];
            tmp[x][y] = count;
            --x;
            ++y;
        }
    }

    for(int i=1;i<n;++i)
    {
        int x = m-1;
        int y = i;

        while(y < n)
        {
            count += tmp[x][y];
            tmp[x][y] = count;
            --x;
            ++y;
        }
    }

    //计算左上角数量
    // int count = 0;
    // for(int i=0;i<nums.size();++i)
    // {
    //     count += nums[i].size();
    //     for(int j=0;j<nums[i].size();++j)
    //     {
    //         tmp[i][j] = 0;
    //         for(int row=i, k=j;k>=0&&row<nums.size();--k,++row)
    //         {
    //             // printf("i:%d j:%d k:%d\n",i,j,k);
    //             tmp[i][j] += min((int)nums[row].size(),k+1);
    //         }
    //         for(int row=i-1,k=j;row>=0;--row,++k)
    //         {
    //             tmp[i][j] += min((int)nums[row].size(),k+1);
    //         }
    //     }
    // }

    vector<int> res(count,-1);
    for(int i=0;i<nums.size();++i)
    {
        for(int j=0;j<nums[i].size();++j)
        {
            printf("%d ",tmp[i][j]);
            res[tmp[i][j]-1] = nums[i][j];
        }
        printf("\n");
    }

    return res;
}

//利用对角线下标相加和相同的特性
class Solution {
public:
    vector<int> ans[200050];
    vector<int> findDiagonalOrder(vector<vector<int>>& nums) {
        for(int i = 0; i < nums.size(); i++)
            for(int j = 0; j < nums[i].size(); j++)
                ans[i+j].push_back(nums[i][j]);
                //cout<<"ans["<<i+j<<"] push"<<nums[i][j]<<endl;
        vector<int> res;
        for(int i = 0; i <= 200000; i++){
            if(ans[i].size() == 0) continue;
            for(int j = ans[i].size()-1; j >= 0; j--)
                res.push_back(ans[i][j]);
        }
            
        return res;
    }
};

int main()
{
    vector<vector<int>> nums = {{1,2,3,4,5},{6,7},{8},{9,10,11},{12,13,14,15,16}};//[1,6,2,8,7,3,9,4,12,10,5,13,11,14,15,16]
    // nums = nums = {{1,2,3},{4,5,6},{7,8,9}};    //[1,4,2,7,5,3,8,6,9]
    // nums = {{1,2,3,4,5,6}};

    for(auto a : findDiagonalOrder2(nums))
    {
        printf("%d ",a);
    }
    printf("\n");

    return 0;
}