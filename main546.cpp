//546. 移除盒子

#include <cstdio>
#include <vector>

using namespace std;

int backtrace(vector<int>& boxes)
{
    int res = 0;
    for(int i=0;i<boxes.size();++i)
    {
        if(i==0 || boxes[i] != boxes[i-1])
        {
            int j=i;
            for(;j<boxes.size();++j)
            {
                if(boxes[j] != boxes[i])
                {
                    break;
                }
            }

            vector<int> tmp(boxes.size()-(j-i));
            // copy(boxes.begin(),boxes.begin()+i,tmp.begin());
            // copy(boxes.begin()+j,boxes.end(),tmp.begin()+i);

            res = max(res,(j-i)*(j-i) + backtrace(tmp));
        }
    }

    return res;
}

int DevidePart(vector<int>& boxes,int start,int end)
{
    int res = 0;
    for(int i=start;i<=end;++i)
    {
        if(i==start || boxes[i] != boxes[i-1])
        {
            int j=i;
            for(;j<=end;++j)
            {
                if(boxes[j] != boxes[i])
                {
                    break;
                }
            }

            //i到j是要消除的那段
            int r = (j-i)*(j-i);

            //分成两半，
        }
    }
}

int dp[100][100][100];

int calculatePoints(vector<int>& boxes, int l, int r, int k) {
    if (l > r) return 0;
    if (dp[l][r][k] != 0) return dp[l][r][k];
    while (r > l && boxes[r] == boxes[r - 1]) {
        r--;
        k++;
    }
    dp[l][r][k] = calculatePoints(boxes, l, r - 1, 0) + (k + 1) * (k + 1);
    for (int i = l; i < r; i++) {
        if (boxes[i] == boxes[r]) {
            dp[l][r][k] = max(dp[l][r][k], calculatePoints(boxes, l, i, k + 1) + calculatePoints(boxes, i + 1, r - 1, 0));
        }
    }
    return dp[l][r][k];
}

int removeBoxes(vector<int>& boxes) {
    //思路：有点像祖龙游戏。。。。假设只有两种颜色，发现好像颜色多少并不影响算法。。
    //假设我们选了一个位置，消除这个段它会把左右两边连起来，因为左右两侧的颜色可能会由于消除而改变
    //回溯先试试,轻松超时。。。。
    //从数学角度，这个感觉没什么策略，回溯时间主要是创建新数组比较耗时，是否可以分治？应该不行，
    //如果copy数组费时，那么可以考虑链表的结构


    // return backtrace(boxes);

    //动态规划，dp[i][j][k]表示消除i到j位置数字和j位置右侧k个与boxes[j]相等的的数字的最大积分
    //那么dp[i][j][k] = max{dp[i][j-1][0]+(k+1)*(k+1),dp[i][r][k+1]+dp[r+1][j-1][0]*(boxes[r]==boxes[j])}
    //时间复杂度O(n^4),空间复杂度O(n^3)
    memset(dp, 0, sizeof dp);
    return calculatePoints(boxes, 0, boxes.size() - 1, 0);
}

int main()
{
    vector<int> boxes = {1,3,2,2,2,3,4,3,1};//23
    boxes = {1,2,3,4,5,6,7,8,9,10,11,12};
    printf("%d\n",removeBoxes(boxes));
    // vector<int> tmp(10);
    // copy(boxes.begin(),boxes.begin()+0,tmp.begin());
    // for(auto a : tmp)
    // {
    //     printf("%d ",a);
    // }
    // printf("\n");
    // printf("%d\n",tmp.size());
    return 0;
}