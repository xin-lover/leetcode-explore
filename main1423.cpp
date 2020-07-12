//1423. 可获得的最大点数

#include <cstdio>
#include <vector>

using namespace std;

int maxScore(vector<int>& cardPoints, int k) {
    //思路：每次都从两侧选取，所以最终的结果就是左侧m个数和右侧n个数的结合
    //问题就变为如何选这m和n个数，也可变为如何选取中间的子序列，使其和最小
    //我们使用后一种思路，那么我们就使用固定窗口即可

    //用前缀和，写法简单些

    int n = cardPoints.size();
    int len = n- k;
    int sum = 0;
    for(int i=0;i<len;++i)
    {
        sum += cardPoints[i];
    }

    int mnSum = sum;
    for(int i=1;i+len-1<n;++i)
    {
        sum -= cardPoints[i-1];
        sum += cardPoints[i+len-1];
        mnSum = min(mnSum,sum);
    }

    sum = 0;
    for(int i=0;i<n;++i)
    {
        sum += cardPoints[i];
    }

    return sum - mnSum;
}

int main()
{
    vector<int> cardPoints = {1,2,3,4,5,6,1};
    int k = 3;  //12

    // cardPoints = {1,79,80,1,1,1,200,1};
    // k = 3; //202

    cardPoints = {1,1000,1}, k = 1;
    printf("%d\n",maxScore(cardPoints,k));
    return 0;
}