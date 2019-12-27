//1031. 两个非重叠子数组的最大和

#include <cstdio>
#include <vector>

using namespace std;

int maxSumTwoNoOverlap(vector<int>& A, int L, int M) {
    //思路：根据题意，一个元素分在左侧或是右侧的子数组中对结果的没影响 
    //L，M我们可以看作两个窗口，
    //一个思路是使用动归思路算出前n个元素的和，这样方便求sum(i,j)
    //同时可以求出第i个元素（含）之前长度为L或M的最大子数组和
    //我们还需要一个第i个元素之后的数组长度为L或M的子数组的最大和
    //所以再计算一次第i个元素（含）之后的L或M的最大数组和
    //那么方案就是：第i个元素前的长度为L的子数组最大和和之后的长度为M的子数组最大和的总和
    //或者前M后L的组合

    int n = A.size();
    vector<int> sum_ay(n+1);
    vector<int> max_L(n+1);
    vector<int> max_M(n+1);

    int tmp = 0;
    for(int i=0;i<n;++i)
    {
        tmp+=A[i];
        sum_ay[i+1] = tmp;
        if(i+1 >= L)
        {
            max_L[i+1] = max(sum_ay[i+1]-sum_ay[i+1-L],max_L[i]);
        }
        if(i+1 >= M)
        {
            max_M[i+1] = max(sum_ay[i+1]-sum_ay[i+1-M],max_M[i]);
        }
    }

    tmp = 0;
    vector<int> max_L_2(n+1),max_M_2(n+1);
    sum_ay[n]=0;
    for(int i=n-1;i>=0;--i)
    {
        tmp += A[i];
        sum_ay[i] = tmp;
        if(i+L <= n)
        {
            max_L_2[i] = max(sum_ay[i] - sum_ay[i+L],max_L_2[i]);
        }

        if(i+M <= n)
        {
            max_M_2[i] = max(sum_ay[i] - sum_ay[i+M],max_M_2[i]);
        }

    }
    for(auto a : max_L)
    {
        printf("%d ",a);
    }
    printf("\n");

    int res = 0;
    for(int i=L;i<n;++i)
    {
        res = max(res,max_L[i] + max_M_2[i]);
    }   

    for(int i=M;i<n;++i)
    {
        res = max(res,max_M[i] + max_L_2[i]);
    }

    return res;
}

int main()
{
    vector<int> v = {0,6,5,2,2,5,1,9,4};
    int L = 1;
    int M = 2; //20

    // v = {3,8,1,3,2,1,8,9,0};
    // L = 3;
    // M = 2; //29

    // v = {2,1,5,6,0,9,5,0,3,8};
    // L = 4;
    // M = 3; //31

    printf("%d\n",maxSumTwoNoOverlap(v,L,M));
    return 0;
}