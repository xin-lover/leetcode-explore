//446. 等差数列划分 II - 子序列

#include <cstdio>
#include <vector>
#include <unordered_map>

using namespace std;

long long C(int N, int M) {
    long long sum = 1;
    for(int i=1;i<=M; i++) {
        sum=sum*(N-M+i)/i;
    }
    return sum;
}

void backtrace(vector<int>& A, int index,long long expected, int diff,int count,int& res)
{

    if(index >= A.size())
    {
        return;
    }


    if(A[index] == expected)
    {
        if(count + 1 >=3)
        {
            ++res;
        }
        backtrace(A,index+1,expected+diff,diff,count+1,res);
    }

    backtrace(A,index+1,expected,diff,count,res);
}

int numberOfArithmeticSlices(vector<int>& A) {
    //思路：如果一个子序列是等待数列，那么其子序列（元素个数大于2）也是等差数列
    //同理，还可以间隔一个元素拿掉一个数，构成新的等差数列
    //所以，先找出所有所有可能的最长的等差子序列，再求和
    //如何找等差数列？等差数列需要确定开始项和差值，还需要注意避免重复
    //常规方式复杂度太高，而且避免重复计算在有相同元素值的时候不太好搞
    //因为我们只需要个数，可以用一个集合记录等差序列的最后一个数和差值
    //还有相等元素如何处理？
    //负责问题都是由简单问题构成的，不要把自己陷入到一个死胡同中，落点一点要简单
    //用回溯求等差数列

    //回溯超时，

    int res = 0;
    for(int i=0;i<A.size();++i)
    {
        for(int j=i+1;j<A.size();++j)
        {
            long long dif = static_cast<long long>(A[j]) - A[i];
            backtrace(A,j+1,A[j]+dif,dif,2,res);
        }
    }
    
    return res;
}

//官方题解，动态规划
//弱等差数列，即长度为2的等差数列
//dp[i][d]为以索引i结束，公差为d的弱等差数列个数，那么对于所有的:i<j,dp[j][d]+=dp[A[j]-A[i]] + dp[i][d];
//最后得到的是弱等差数列，如何计算真等差数列（长度>2），第一种思路是减去弱等差数列数量，这个很容易得到(n-1)*n/2
//还有一种就是在新增等差数列的时候计数，因为新增的时候弱等差数列是额外添加的

// #define LL long long
// class Solution {
// public:
//     int numberOfArithmeticSlices(vector<int>& A) {
//         int n = A.size();
//         LL ans = 0;
//         vector<map<LL, int>> cnt(n);
//         for (int i = 1; i < n; i++) {
//             for (int j = 0; j < i; j++) {
//                 LL delta = (LL)A[i] - (LL)A[j];
//                 int sum = 0;
//                 if (cnt[j].find(delta) != cnt[j].end()) {
//                     sum = cnt[j][delta];
//                 }
//                 cnt[i][delta] += sum + 1;
//                 ans += sum;
//             }
//         }

//         return (int)ans;
//     }
// };
 


int main()
{
    vector<int> A = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}; //7
    // A = {2, 4, 6, 8, 10};   //7
    // A = {0,1,2,2,2}; //4
    // A= {1,1,1,1}; //5
    // A= {1,1,1,1,1}; //16
    // A = {1,1,1,1,1,1,1,1,1,1,1,1,1}; //8100
    A = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; //8100
    printf("%d\n",numberOfArithmeticSlices(A));

    // printf("%d\n",C(4,2));
    return 0;
}