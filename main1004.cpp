//1004. 最大连续1的个数 III

#include <cstdio>
#include <vector>

using namespace std;

int longestOnes(vector<int>& A, int K) {
    //思路：滑动窗口，如果K大于0的话，窗口扩大，否则把窗口右移

    int left=0;
    int res = 0;
    for(int i=0;i<A.size();++i)
    {
        if(A[i] == 0)
        {
            if(K > 0)
            {
                --K;
            }
            else
            {
                while(A[left] != 0)
                {
                    ++left;
                }
                ++left;
            }
        }
        res = max(res,i-left+1);
    }

    return res;
}

// int longestOnes2(vector<int>& A, int K) {

//     //还可以考虑把A分成两组，一组存储1的个数，一组存储0的个数,还是滑动窗口
//     //本质没有变
// }

int main()
{
    vector<int> A = {1,1,1,0,0,0,1,1,1,1,0};
    printf("%d\n",longestOnes(A,2));//6
    A = {0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1};
    printf("%d\n",longestOnes(A,3));//10

    return 0;
}