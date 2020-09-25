//LCP 19. 秋叶收藏集

#include <cstdio>
#include <string>
#include <vector>

using namespace std;

int minimumOperations(string leaves) {
    //思路：红、黄、红已确定，现在的问题就变为选择哪个点开始变黄
    //现考虑红、黄，问题变为找一个点，让其左侧变红，右侧变黄代价最少
    //这个问题可以用动归完成
    //但还有黄、红阶段，这个可以先实现一个O(n^2)的解法

    int n = leaves.size();
    vector<int> ytor(n,0);
    ytor[0] = leaves[0] == 'r' ? 0 : 1;
    for(int i=1;i<n;++i)
    {
        ytor[i] = ytor[i-1] + (leaves[i] == 'r' ? 0 : 1);
    }

    int res = n;
    for(int i=1;i<n;++i)
    {
        int left = ytor[i-1];
        for(int j=i+1;j<n;++j)
        {
            int mid = (j - i) - (ytor[j-1] - ytor[i-1]);
            int right = ytor[n-1] - ytor[j-1];

            res = min(res,left+mid+right);
        }
    }

    return res;
}

int minimumOperations2(string leaves) 
{
    //思路：优化内层循环,在上面的算法中，我们计算了left+mid+right
    //都带入值可得ytor[i-1] + (j-i)-(ytor[j-1] - ytor[i-1]) + ytor[n-1] - ytor[j-1]
    //即2*ytor[i-1]+(j-i)+ytor[n-1] - 2*ytor[j-1]
    //整理j-i+2*(ytor[i-1]-ytor[j-1])+ytor[n-1]
    //这个公式无法优化，所以要改变一下思路
    //只有两种叶子,数量分别是：r,y，且分成两个部分，取中间的部分，mid_r,mid_y,
    //那么我们的目标是要mid_r + (y-mid_y)最小，也就是mid_r-mid_y最小
    //假设区间是[i,j],那么就是(j-i+1-2*mid_y)最小,....结果和上面一样。。。
    //
    
    //同样的思路先用于左边，即红黄,j_y表示到索引j时yellow的数量,取i为分割点，则
    //i_y + j_r-i_r => i_y + j_r - (i+1-i_y) => 2*i_y + (j+1-j_y) - i -1
    //在j点时，j和j_y是已知且确定的，所以就变成了2*i_y-i最小的时候代价最小
    //同理用于右边，则是2*i_y + i - n最小
    //所以内层循环就可以优化了。。。
    //而实际中的编程，假设dp[i]表示0到i区间红黄分割的最小代价，
    //leaves[i+1]=='y',则dp[i+1]=dp[i],否则，dp[i+1]=min(dp[i]+1,i+2-i+2_y)
    

    int n = leaves.size();
    vector<int> leftPre(n,n);
    int t = leaves[0] == 'y' ? 1 : 0;
    leftPre[0] = leaves[0] == 'y' ? 1 : 0;
    for(int i=1;i<n;++i)
    {
        if(leaves[i] == 'y')
        {
            ++t;
            leftPre[i] = leftPre[i-1];
        }
        else
        {
            leftPre[i] = min(leftPre[i-1]+1,t);
        }
    }

    vector<int> rightPre(n,n);
    t = leaves[n-1] == 'y' ? 1 : 0;
    rightPre[n-1] = leaves[n-1] == 'y' ? 1 : 0;
    for(int i=n-2;i>=0;--i)
    {
        if(leaves[i] == 'y')
        {
            ++t;
            rightPre[i] = rightPre[i+1];
        }
        else
        {
            rightPre[i] = min(rightPre[i+1]+1,t);
        }
    }

    int res = n;
    for(int i=1;i<n-1;++i)
    {
        if(leaves[i] == 'y')
        {
            res = min(res,leftPre[i-1]+rightPre[i+1]);
        }
        else
        {
            res = min(res,leftPre[i-1]+rightPre[i+1]+1);
        }
        
    }

    return res;

}

int main()
{
    string leaves = "rrryyyrryyyrr"; //2
    // leaves = "ryr"; //0
    // leaves = "rryy"; //1
    // leaves = "yry"; //3

    printf("%d\n",minimumOperations2(leaves));

    return 0;
}