//leetcode 918. 环形子数组的最大和

#include<cstdio>
#include <vector>

using namespace std;

int maxSubarraySumCircular(vector<int>& A) {
    //思路：使用滑动窗口法，把子数组分成两部分，一部分是已添加的数，另一个是将要添加的数
    //已添加数的部分必须大于0才有意义，否则就舍弃它
    //但对于环形数组，还有一个选择，就是必须选取第0个和最后一个数，也就是第0个向右扩张，第n个向左扩张
    //其实也可以认为是舍去了中间的一段数，那么这段数肯定是负数且为最小，所以思路就是计算整个数组的和，同时也计算负数开始的连续最小子数组和

    int sum = A[0];
    int res = sum;
    int allSum = A[0];
    int minSum = 0;
    int tmpMinSum = 0;

    for(int i=1;i<A.size();++i)
    {
        if(sum < 0)
        {
            sum = A[i];
        }
        else
        {
            sum += A[i];
        }

        res = max(sum,res);

        allSum += A[i];

        if(tmpMinSum > 0)
        {
            tmpMinSum = A[i];
        }
        else
        {
            tmpMinSum += A[i];
        }
        
        minSum = min(minSum,tmpMinSum);
    }
    return max(res,allSum - minSum);
}

//其它思路：
//1.使用动归分别记录从0往左的最大值和从n-1开始往右的最大值，然后计算i位置两者和的最大值
//2.另一种就是既然循环，那就重复一次，比如[0,1,3],就变成[0,1,3,0,1,3],然后计算Pi,表示0-i的和，那么子数组最大长度为n，也就是求pj-pi的最大值，其中j-i<=n的最大值
//做法是使用优先队列存储索引，然后把pj<pi的索引删除
//3.其它的就跟我写的这种一个思路，只不过在找最小子数组和时我考虑的是小于0，他们则是考虑计算两次，一次去掉第一个数，一次去掉最后一个数

int main()
{
    vector<int> A = {1,-2,3,-2};//3
    A = {5,-2,5};//10
    printf("%d\n",maxSubarraySumCircular(A));
    A = {3,-1,2,-1};    //4
    printf("%d\n",maxSubarraySumCircular(A));
    A = {3,-2,2,-3};    //3
    printf("%d\n",maxSubarraySumCircular(A));
    A = {-2,-3,-1};//-1
    printf("%d\n",maxSubarraySumCircular(A));
    A = {5,5,0,-5,3,-3,2};//12
    printf("%d\n",maxSubarraySumCircular(A));
    A = {2,-2,2,7,8,0};//19
    printf("%d\n",maxSubarraySumCircular(A));
    A = {-1,3,-3,9,-6,8,-5,-5,-6,10}; //20
    printf("%d\n",maxSubarraySumCircular(A));
    A = {-2,4,-5,4,-5,9,4};//15
    printf("%d\n",maxSubarraySumCircular(A));
    return 0;
}