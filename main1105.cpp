//1105. 填充书架

#include <cstdio>
#include <vector>

using namespace std;

int minHeightShelves(vector<vector<int>>& books, int shelf_width) {
    //思路：摆放的顺序和整理的顺序相同，那么遍历顺序也就确定
    //这里有个选择就是后面的书能否放在低层，先假定不能
    //我们摆放的一个原则就是让高度相近或是相同的书尽量放在同一层
    //这个有点像之前的  1043. 分隔数组以得到最大和。
    //一个分割连续子数组，然后子数组中的元素都替换为子数组中的最大值
    //解法相同，使用动归，dp[i]表示包含第i本书时的书架最小高度
    //dp[i] = min{dp[i],dp[i-j] + max(h(i),h(i-1),h(i-2)……)}
    int n = books.size();
    vector<int> dp(n+1,INT_MAX);
    dp[0] = 0;
    for(int i=1;i<=n;++i)
    {
        int h = 0;//books[i][1];
        int w = 0;
        for(int j=i-1;j>=0 && w+books[j][0] <= shelf_width;--j)
        {
            w+=books[j][0];
            h = max(books[j][1],h);
            dp[i] = min(dp[i],dp[j] + h);
        }
    }

    return dp[n];
}

int main()
{
    vector<vector<int>> books = {{1,1},{2,3},{2,3},{1,1},{1,1},{1,1},{1,2}};
    int shelf_width = 4;
    printf("%d\n",minHeightShelves(books,shelf_width));
    return 0;
}