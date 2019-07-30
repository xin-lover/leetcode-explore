//leetcode  795. 区间子数组个数

#include <cstdio>
#include <vector>

using namespace std;

int numSubarrayBoundedMax(vector<int>& A, int L, int R) {
    //思路：其实可以理解为符合要求的数可以带小于L的数，大于R的数就去除，
    //所以我们可以根据A[i]大于R分为多个子数组，分别求子数组中符合要求的子数组数
    //对于每一个符合要求的A[i]和A[j],j>i,则i到j之间的数都小于L，所以符合要求的子数组可分为包含A[i]和包含A[j]的情况
    //对于包含A[i]，假设左侧有left个数（i-start+1)，右侧有right个数，即（j-i+1），共有(left+1)*(right+1)种情况，A[j]同理
    //策略：根据A[i]大于R分段，则每一段的数都小于R，对于每一段都记录大于等于L小于等于R的数，然后计算总数

    int res =0;
    int start = -1;
    vector<int> flags;
    A.push_back(R+1);
    for(int i=0;i<A.size();++i)
    {
        if(A[i]<=R)
        {
            if(start == -1)
            {
                start = i;
            }

            if(A[i] >= L)
            {
                printf("i:%d\n",i);
                flags.push_back(i);
            }
        }
        else
        {
            //计算
            if(start != -1)
            {
                printf("sz:%d\n",flags.size());
                for(int j=0;j<flags.size();++j)
                {
                    int mid = flags[j];
                    int end = j+1>=flags.size() ? i-1 : flags[j+1]-1;

                    int left = mid-start+1;
                    int right = end - mid + 1;

                    res += left * right;
                }

                flags.clear();
            }

            start = -1;
        }
    }
    A.pop_back();

    return res;
}

int numSubarrayBoundedMax2(vector<int>&A, int m)
{
    int cnt =0;
    int res = 0;
    for(auto a : A)
    {
        if(a <= m)
        {
            cnt++;
            res += cnt;
        }
        else
        {
            cnt = 0;
        }
    }

    return res;
}

int numSubarrayBoundedMax2(vector<int>& A, int L, int R) 
{
    //思路：最大元素满足大于等于L小于等于R的子数组个数 = 最大元素小于等于R的子数组个数 - 最大元素小于L的子数组个数
    return numSubarrayBoundedMax2(A,R) - numSubarrayBoundedMax2(A,L-1);
}

int main()
{
    vector<int> v = {2, 1, 4, 3};
    printf("%d\n",numSubarrayBoundedMax2(v,2,3));
    return 0;
}