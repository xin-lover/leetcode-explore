//leetcode 930. 和相同的二元子数组

#include <cstdio>
#include <vector>

using namespace std;

int numSubarraysWithSum(vector<int>& A, int S) {
    
    //思路，使用滑动窗口，要考虑0的存在
    //策略：当找到子数组时，查看子数组首位0的个数
    int start = 0;
    int sum = 0;
    int res = 0;

    for(int i=0;i<A.size();++i)
    {
        if(A[i] > S)
        {
            start = i+1;
            sum = 0;
            continue;
        }

        sum += A[i];

        while(sum > S)
        {
            sum -= A[start];
            ++start;
        }

        if(sum == S)
        {
            ++res;
            int j=start;
            while(j < i && A[j++] == 0) //可优化，记录前一次的结果
            {
                ++res;
            }
        }
    }

    return res;
}

//只有0和1.。。。。。。，这个点没注意
//一个思路：就是利用另一个数组记录总和变化的位置，因为只有0和1，所以和最大就是A的长度，这样子数组前后0的个数也能简单求出，按照和是否为0分别求解
//另一个思路是：求前缀和，然后转换为求双数之和，也就是p[j] = p[i] + S,其中 i < j
//三指针法，跟我上面的思路一样,固定右边端点，求出两个和的位置，一个是最长子数组，一个是最短子数组


int main()
{
    vector<int> v = {1,0,1,0,1};
    printf("%d\n",numSubarraysWithSum(v,2));
    v = {0,0,0,0,0};
    printf("%d\n",numSubarraysWithSum(v,0));
    v = {0,0,0,0,0,0,1,0,0,0};
    printf("%d\n",numSubarraysWithSum(v,0));
    return 0;
}

