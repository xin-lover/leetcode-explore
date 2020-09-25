//85. 最大矩形

#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

int maximalRectangle(vector<vector<char>>& matrix) {
    //思路：第一想法就是动归，记录dp[i][j]为{(0,0),(i,j)}矩形的元素和
    //第一个O(MN^2)的思路就出来了，但性能肯定低
    //假设我们记录的是行中1的连续个数，那么连续矩形就是连续行中连续1个数的最小值
    //那么对于行i，我们找小于i的行中连续1个数的最小值，就可以求出以(i,j)为右下角的最大矩形
    //但这个的复杂度还是O(M^2*N)，可以再次考虑动归。。。

    int m = matrix.size();
    int n = m == 0 ? 0 : matrix[0].size();
    vector<vector<int>> dp(m,vector<int>(n,0));

    int res = 0;
    for(int i=0;i<m;++i)
    {
        int tmp = 0;
        for(int j=0;j<n;++j)
        {
            if(matrix[i][j] == '1')
            {
                ++tmp;
                dp[i][j] = tmp;

                //第一种思路
                int len = n;
                for(int k=i;k>=0;--k)
                {
                    len = min(len,dp[k][j]);
                    res = max(res,len * (i-k+1));
                }
            }
            else
            {
                tmp = 0;
                dp[i][j] = tmp;
            }
            
        }
    }

    return res;
}

int maximalRectangle2(vector<vector<char>>& matrix) {
    //思路：第一想法就是动归，记录dp[i][j]为{(0,0),(i,j)}矩形的元素和
    //第一个O(MN^2)的思路就出来了，但性能肯定低
    //假设我们记录的是行中1的连续个数，那么连续矩形就是连续行中连续1个数的最小值
    //那么对于行i，我们找小于i的行中连续1个数的最小值，就可以求出以(i,j)为右下角的最大矩形
    //但这个的复杂度还是O(M^2*N)，可以再次考虑动归。。。

    int m = matrix.size();
    int n = m == 0 ? 0 : matrix[0].size();
    vector<vector<int>> dp(m,vector<int>(n,0));

    int res = 0;
    for(int j=0;j<n;++j)
    {
        for(int i=0;i<m;++i)
        {
            if(matrix[i][j] == '1')
            {
                dp[i][j] = j > 0 ? dp[i][j-1] + 1 : 1;
                printf("%d %d %d\n",i,j,dp[i][j]);
            }
        }

        //相当于柱状图中的最大矩形，使用栈，用栈来快速找出某个位置左右两侧最近的小于hight[i]的位置
        stack<int> leftSk,rightSk;
        vector<int> left(m,0),right(m,0);
        for(int k=0;k<m;++k)
        {
            while(!leftSk.empty() && dp[k][j] <= dp[leftSk.top()][j])
            {
                leftSk.pop();
            }

            left[k] = leftSk.empty() ? -1 : leftSk.top();
            leftSk.push(k);
        }

        for(int k=m-1;k>=0;--k)
        {
            while(!rightSk.empty() && dp[k][j] <= dp[rightSk.top()][j])
            {
                rightSk.pop();
            }

            right[k] = rightSk.empty() ? m : rightSk.top();
            rightSk.push(k);
        }
        printf("left:");
        for(auto a : left)
        {
            printf("%d ",a);
        }
        printf("\n");

        printf("right:");
        for(auto a : right)
        {
            printf("%d ",a);
        }
        printf("\n");

        for(int k=0;k<m;++k)
        {
            printf("k:%d %d\n",k,dp[k][j]);
            res = max(res,dp[k][j] * (right[k] - left[k]-1));
        }
    }

    return res;
}

//动态规划算法
//想象一个算法，对于每个点我们会通过以下步骤计算一个矩形：
//1.不断向上方遍历，直到遇到“0”，以此找到矩形的最大高度。
//1.向左右两边扩展，直到无法容纳矩形最大高度。
int maximalRectangle3(vector<vector<char>>& matrix) {
    //一行一行的遍历，用h,l,r3个数组，分别存储矩形高度，左边界和右边界
    //这样，不断更新3个数组即可，area = heights[i] * (right[i] - left[i])

    int m = matrix.size();
    int n = m == 0 ? 0 : matrix[0].size();

    int res = 0;
    vector<int> heights(n,0),lefts(n,0),rights(n,n);
    for(int i=0;i<m;++i)
    {
        int cur_right = n;
        for(int j=n-1;j>=0;--j)
        {
            if(matrix[i][j] == '1')
            {
                rights[j] = min(rights[j],cur_right);
            }
            else
            {
                cur_right = j;
                rights[j] = n;
            }
        }

        int cur_left = 0;
        for(int j=0;j<n;++j)
        {
            if(matrix[i][j] == '1')
            {
                lefts[j] = max(lefts[j],cur_left);
            }
            else
            {
                cur_left = j+1;
                lefts[j] = 0;
            }
        }

        printf("%d %d\n",lefts[n-1],rights[n-1]);
        for(int j=0;j<n;++j)
        {
            if(matrix[i][j] == '1')
            {
                heights[j] += 1;
            }
            else
            {
                heights[j] = 0;
            }

            res = max(res,heights[j] * (rights[j] - lefts[j]));
        }
    }

    return res;
}

int main()
{
    vector<vector<char>> matrix = {{'1','0','1','0','0'},
        {'1','0','1','1','1'},
        {'1','1','1','1','1'},
        {'1','0','0','1','0'}
    }; //6

    // matrix = {{'0','1'}};

    printf("%d\n",maximalRectangle3(matrix));
    return 0;
}